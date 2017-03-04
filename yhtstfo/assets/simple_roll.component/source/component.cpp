#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(simple_roll::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace simple_roll
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        if (GetNode().HasTransform())
        {
            basic::Euler rotation(time_step.GetSecondCount()*0.4f,
                time_step.GetSecondCount()*0.8f, time_step.GetSecondCount()*1.2f);
            GetNode().GetTransform().SetRotation(GetNode().GetTransform().GetRotation()
                *rotation);
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnRender(const graphics::Viewport& viewport)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollisionBegin(const physics::Collision& collision)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollision(const physics::Collision& collision)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollisionEnd(const physics::Collision& collision)
    {
    }    

    //--------------------------------------------------------------------------------------------//

    bool Component::OnInputEvent(const input::EVENT& event, void* parameters)
    {
        return false;
    }

}
