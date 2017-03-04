#ifndef _ALIEN_CONTROLLER_H_
#define _ALIEN_CONTROLLER_H_

#include "coffee.h"
using namespace coffee;

namespace alien_controller
{
    //--------------------------------------------------------------------------------------------//
    /// alien_controller::Component
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

        bool HandleInputs() const { return false; }
        bool OnInputEvent(const input::EVENT& event, const void* parameters);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        basic::Vector3 _ComputeMove(real distance);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _MoveSpeed;
        real _RollSpeed;
        bool _KeyArray[4];
        basic::Vector3 _Force;
        basic::Vector3 _Torque;
        basic::Time _UpdateTime;
        real _ReloadTime;
        basic::Time _ShootTime;
        basic::Time _LifeTime;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(alien_controller);

#endif
