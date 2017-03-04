#ifndef _VOICE_SYNTHESIZER_MODULE_H_
#define _VOICE_SYNTHESIZER_MODULE_H_

#include "plugin_includes.h"
#include "voice.h"

namespace voice_synthesizer
{
    //--------------------------------------------------------------------------------------------//
    /// Voice synthetizer
    //--------------------------------------------------------------------------------------------//
    class VOICE_SYNTHESIZER_API Synthesizer : public shell::Module
    {
        COFFEE_Type(Synthesizer);
        COFFEE_DeclareModuleSingleton(Synthesizer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Synthesizer();
        ~Synthesizer();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsGenerating(uint32 id);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);
        void OnMainThreadUpdate(const basic::Time& time_step);

        void Speak(const basic::String& text, bool it_is_3d=false, real pitch=1.0f, real gain=1.0f,
            VOICE_GENDER gender=VOICE_GENDER_Male, VOICE_LANGUAGE language=VOICE_LANGUAGE_English,
            uint32 age=0, uint32 variant=0, VOICE_EFFECT effect=VOICE_EFFECT_None,
            const basic::Vector3& position=basic::Vector3::Zero);
        void Speak(const basic::String& text, const VoiceSettings& settings,
            const basic::Vector3& position=basic::Vector3::Zero);
        
    private:
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool _HasToBeginGeneration(const Voice& voice);

        //-FUNCTIONS------------------------------------------------------------------------------//

        static int _OnGenerateWav(short *wav, int numsamples, espeak_EVENT *events);
    
        //-VARIABLES------------------------------------------------------------------------------//

        static basic::Vector<uint8>* _GenerationData;
    
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _SampleRate;        
        shell::Mutex _InputVoicesMutex;
        basic::Prow<Voice*, true> _InputVoices;
        shell::Mutex _OutputVoicesMutex;
        basic::Prow<Voice*, true> _OutputVoices;
    };

    COFFEE_RegisterType(VOICE_SYNTHESIZER_EXPORT_STATICS, Synthesizer);
}
#endif
