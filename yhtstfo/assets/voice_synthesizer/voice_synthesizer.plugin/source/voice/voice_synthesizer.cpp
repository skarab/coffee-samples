#include "voice_synthesizer.h"

//-META---------------------------------------------------------------------------------------//

COFFEE_BeginType(voice_synthesizer::Synthesizer);
    COFFEE_Ancestor(shell::Module);
COFFEE_EndType();

namespace voice_synthesizer
{
    COFFEE_ImplementModuleSingleton(Synthesizer);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Synthesizer::Synthesizer() :
        shell::Module(shell::MODULE_ATTRIBUTE_Automatic | shell::MODULE_ATTRIBUTE_Threaded)
    {
        COFFEE_CreateModuleSingleton(Synthesizer);
    }

    //--------------------------------------------------------------------------------------------//

    Synthesizer::~Synthesizer()
    {
        COFFEE_DestroyModuleSingleton(Synthesizer);
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Synthesizer::IsGenerating(uint32 id)
    {
        {
            shell::Locker lock(_InputVoicesMutex);
            for (uint32 i=0 ; i<_InputVoices.GetSize() ; ++i)
            {
                if (_InputVoices[i]->Settings.ID==id)
                    return true;
            }
        }
        {
            shell::Locker lock(_OutputVoicesMutex);
            for (uint32 i=0 ; i<_OutputVoices.GetSize() ; ++i)
            {
                if (_OutputVoices[i]->Settings.ID==id)
                    return true;
            }
        }
        return false;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Synthesizer::OnInitialize()
    {        
        storage::PhysicalPath path = Application::Get().GetProject().GetFullPath()+"/others/voice_synthesizer/";
    
        _SampleRate = espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 10000, path.GetBuffer(), 15);
        if (_SampleRate!=EE_INTERNAL_ERROR)
            espeak_SetSynthCallback(&_OnGenerateWav);
    }

    //--------------------------------------------------------------------------------------------//

    void Synthesizer::OnFinalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Synthesizer::OnUpdate(const basic::Time& time_step)
    {
        Voice* process(NULL);
        uint32 index;

        if (_InputVoices.GetSize()>0)
        {
            shell::Locker lock(_InputVoicesMutex);
            if (_InputVoices.GetSize()>0)
            {
                for (uint32 i=0 ; i<_InputVoices.GetSize() ; ++i)
                {
                    if (_HasToBeginGeneration(*_InputVoices[i]))
                    {
                        process = _InputVoices[i];
                        index = i;
                        break;
                    }
                }
            }
        }

        if (process!=NULL)
        {
            if (_SampleRate==EE_INTERNAL_ERROR)
            {
                shell::Locker lock(_InputVoicesMutex);
                _InputVoices[index] = NULL;
                _InputVoices.Remove(index);
                COFFEE_Delete(process);
            }
            else
            {
                _GenerationData = &process->Buffer;

                basic::String voice_name = VOICE_LANGUAGE_GetString(process->Settings.Language);
                if (process->Settings.Effect!=VOICE_EFFECT_None)
                {
                    voice_name += "+";
                    voice_name += VOICE_EFFECT_GetString(process->Settings.Effect,
                        process->Settings.Gender==VOICE_GENDER_Female);
                }

                espeak_VOICE voice;
                memset(&voice, NULL, sizeof(espeak_VOICE));
                voice.name = voice_name.GetBuffer();
                voice.gender = (uint32)process->Settings.Gender+1;
                voice.age = process->Settings.Age;
                voice.variant = process->Settings.Variant;
                espeak_SetVoiceByProperties(&voice);

                espeak_Synth(process->Speach.GetBuffer(), process->Speach.GetLength(), 0,
                    POS_CHARACTER, 0, espeakCHARS_8BIT, 0, NULL);

                if (_GenerationData->GetSize()>0)
                {
                    shell::Locker lock(_OutputVoicesMutex);
                    _OutputVoices.AddItem(process);
                }
                else
                {
                    COFFEE_Delete(process);
                }
                
                shell::Locker lock(_InputVoicesMutex);
                _InputVoices[index] = NULL;
                _InputVoices.Remove(index);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Synthesizer::OnMainThreadUpdate(const basic::Time& time_step)
    {
        Voice* process(NULL);
        uint32 index;

        if (_OutputVoices.GetSize()>0)
        {
            shell::Locker lock(_OutputVoicesMutex);
            if (_OutputVoices.GetSize()>0)
            {
                process = _OutputVoices[0];
                index = 0;
            }
        }
        
        if (process!=NULL)
        {
            audio::Sound* sound = audio::Device::Get().PlayCustomSound(process->Settings.ItIs3D,
                process->Settings.Pitch, process->Settings.Gain, process->Position,
                process->Settings.ID);
            sound->_Create((real)process->Buffer.GetSize()/Synthesizer::Get()._SampleRate,
                1, 0, Synthesizer::Get()._SampleRate, 16,
                (uint8*)process->Buffer.GetLinearBuffer(), process->Buffer.GetSize(), false);
            sound->SetState(resource::STATE_Available);
            sound->InitializeInstance();
            COFFEE_Delete(process);

            shell::Locker lock(_OutputVoicesMutex);
            _OutputVoices[index] = NULL;
            _OutputVoices.Remove(index);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Synthesizer::Speak(const basic::String& text, bool it_is_3d, real pitch, real gain,
            VOICE_GENDER gender, VOICE_LANGUAGE language,
            uint32 age, uint32 variant, VOICE_EFFECT effect,
            const basic::Vector3& position)
    {
        if (text.GetLength()>0)
        {
            Voice* speach = COFFEE_New(Voice);
            speach->Speach = text;
            speach->Settings.ItIs3D = it_is_3d;
            speach->Settings.Pitch = pitch;
            speach->Settings.Gain = gain;
            speach->Settings.Gender = gender;
            speach->Settings.Language = language;
            speach->Settings.Age = age;
            speach->Settings.Variant = variant;
            speach->Settings.Effect = effect;
            speach->Position = position;
            shell::Locker lock(_InputVoicesMutex);
            _InputVoices.AddItem(speach);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Synthesizer::Speak(const basic::String& text, const VoiceSettings& settings,
        const basic::Vector3& position)
    {
        if (text.GetLength()>0)
        {
            Voice* speach = COFFEE_New(Voice);
            speach->Speach = text;
            speach->Settings = settings;
            speach->Position = position;
            shell::Locker lock(_InputVoicesMutex);
            _InputVoices.AddItem(speach);
        }
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool Synthesizer::_HasToBeginGeneration(const Voice& voice)
    {
        {
            shell::Locker lock(_OutputVoicesMutex);
            for (uint32 i=0 ; i<_OutputVoices.GetSize() ; ++i)
            {
                if (_OutputVoices[i]->Settings.ID==voice.Settings.ID)
                    return false;
            }
        }

        return !audio::Device::Get().IsPlayingSound(voice.Settings.ID);
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    int Synthesizer::_OnGenerateWav(short *wav, int numsamples, espeak_EVENT *events)
    {
        uint32 size = _GenerationData->GetSize();
        _GenerationData->Resize(size+numsamples*2);
        memcpy((uint8*)_GenerationData->GetLinearBuffer()+size, wav, numsamples*2);
        return 0;
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    basic::Vector<uint8>* Synthesizer::_GenerationData;
    
}

