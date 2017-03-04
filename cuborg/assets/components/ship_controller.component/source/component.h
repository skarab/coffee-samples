#ifndef _SHIP_CONTROLLER_H_
#define _SHIP_CONTROLLER_H_

#include "coffee.h"
using namespace coffee;

namespace ship_controller
{
    //--------------------------------------------------------------------------------------------//
    /// ship_controller::Component
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
        
        bool HandlePhysics() const { return false; }
        void OnCollisionBegin(const physics::Collision& collision);
        void OnCollision(const physics::Collision& collision);
        void OnCollisionEnd(const physics::Collision& collision);
        
        // Inputs

        bool HandleInputs() const { return true; }
        bool OnInputEvent(const input::EVENT& event, const void* parameters);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        basic::Vector3 _ComputeMove(real distance);
        void _Quit();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _MoveSpeed;
        real _RollSpeed;
        bool _KeyArray[4];
        basic::Vector3 _Force;
        basic::Vector3 _Torque;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(ship_controller);

#endif
