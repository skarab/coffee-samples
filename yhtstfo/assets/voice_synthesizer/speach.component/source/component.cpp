#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(speach::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(basic::Text, _Speach, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(bool, _ItIsLooping, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(real, _LineTime, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_Attribute(voice_synthesizer::VoiceSettings, _Settings, meta::MODE_Serializeable | meta::MODE_Editable);
COFFEE_EndType();

namespace speach
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _ItIsLooping(false),
        _LineTime(2.0f),
        _LineIndex(0),
        _TimeCounter(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS-----------------------------------------------------------------------------//

    void Component::Play()
    {
        _LineIndex = 0;
        _TimeCounter = _LineTime;
    }
    
    //-HANDLERS-----------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _PreProcessSpeach();
        Play();
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        if (_TimeCounter>=_LineTime && _LineIndex<_CutDownSpeach.GetLineCount())
        {
            _TimeCounter = 0.0f;

            basic::Vector3 position;
            if (GetNode().HasTransform())
                position = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation();
            
            Synthesizer::Get().Speak(_CutDownSpeach.GetLine(_LineIndex), _Settings, position);
            
            ++_LineIndex;
        }

        if (_LineIndex>=_CutDownSpeach.GetLineCount() && _ItIsLooping
            && !Synthesizer::Get().IsGenerating(_Settings.ID))
        {
            _LineIndex = 0;
        }

        if (_Settings.ItIs3D && GetNode().HasTransform())
        {
            audio::Device::Get().SetCustomSoundPosition(_Settings.ID,
                GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
        }

        _TimeCounter += time_step.GetSecondCount();
    }
        
    //--------------------------------------------------------------------------------------------//

    void Component::OnPropertyModified(const void* prop)
    {
        _LineIndex = 0;
        _TimeCounter = 0.0f;

        if (prop==&_Speach)
            _PreProcessSpeach();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::_PreProcessSpeach()
    {
        uint32 max_words_per_line = 12;
        _CutDownSpeach.SetEmpty();
        basic::String line;
        for (uint32 i=0 ; i<_Speach.GetLineCount() ; ++i)
        {
            uint32 j = 0;
            int32 word_index = NONE;
            uint32 count = 0;
            basic::String word;
            while (_Speach.GetLine(i).GetNextWord(word, word_index))
            {
                line += " ";
                line += word;
                ++count;
                if (count>=max_words_per_line)
                {
                    _CutDownSpeach.AddLine(line);
                    line = "";
                    count = 0;
                }
            }

            if (line.GetLength()>0 || _Speach.GetLine(i).GetLength()==0)
            {
                _CutDownSpeach.AddLine(line);
                line = "";
            }
        }

        if (line.GetLength()>0)
            _CutDownSpeach.AddLine(line);
    }

}
