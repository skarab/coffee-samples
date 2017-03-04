#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

#include "coffee.h"
using namespace coffee;

#include "voice_synthesizer.h"

namespace countdown
{
    //--------------------------------------------------------------------------------------------//
    /// countdown::Component
    //--------------------------------------------------------------------------------------------//
    class COMPONENT_API Component : public plugins::Component
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        ~Component();

        //-HANDLERS-------------------------------------------------------------------------------//

        // Basics
        
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
        void OnFixedUpdate(const basic::Time& time_step);
        
        // Graphics

        bool HandleGraphics() const { return false; }
        void OnRender(const graphics::Viewport& viewport);
        
        // Physics
        
        bool HandlePhysics() const { return true; }
        void OnCollisionBegin(const physics::Collision& collision);
        void OnCollision(const physics::Collision& collision);
        void OnCollisionEnd(const physics::Collision& collision);
        
        // Inputs

        bool HandleInputs() const { return false; }
        bool OnInputEvent(const input::EVENT& event, void* parameters);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeLevel();
        void _InitializeVoice();
        void _Speak(const basic::String& speach);
        void _RestartGame();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Time;
        uint32 _LevelIndex;
        voice_synthesizer::VoiceSettings _Voice;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(countdown);

#endif
