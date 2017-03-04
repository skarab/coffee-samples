#ifndef _MENU_H_
#define _MENU_H_

#include "coffee.h"
using namespace coffee;

namespace menu
{
    //--------------------------------------------------------------------------------------------//
    /// menu::Component
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
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareExternEventHandler(Component, OnStart);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//
        
        bool IsPlaying() const;

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Time _Time;
        ui::Window* _Frame;
        resource::Handler<scene::Resource> _Scene;
    };

    COFFEE_RegisterComponent(Component);
}

COFFEE_ExportComponent(menu);

#endif
