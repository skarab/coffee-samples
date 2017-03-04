#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_

#include "coffee.h"
using namespace coffee;

namespace elevator
{
    //--------------------------------------------------------------------------------------------//
    /// elevator::Component
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

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsUp;
        real _Height;
        real _Speed;
        real _SwitchDelay;
        real _SwitchTime;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(elevator);

#endif