#ifndef _SPEACH_H_
#define _SPEACH_H_

#include "coffee.h"
using namespace coffee;

#include "voice_synthesizer.h"
using namespace voice_synthesizer;

namespace speach
{
    //--------------------------------------------------------------------------------------------//
    /// speach::Component
    //--------------------------------------------------------------------------------------------//
    class COMPONENT_API Component : public plugins::Component
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        ~Component();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Play();

        //-HANDLERS-------------------------------------------------------------------------------//

        // Basics
        
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        void OnPropertyModified(const void* prop);        
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PreProcessSpeach();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Text _Speach;
        basic::Text _CutDownSpeach;
        bool _ItIsLooping;
        real _LineTime;
        VoiceSettings _Settings;
        uint32 _LineIndex;
        real _TimeCounter;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(speach);

#endif
