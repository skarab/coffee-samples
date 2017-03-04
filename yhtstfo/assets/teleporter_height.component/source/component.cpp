#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(teleporter_height::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace teleporter_height
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
        if (collision.OtherBody->GetNode().HasTransform())
        {
            collision.OtherBody->GetNode().GetTransform().SetTranslation(
                collision.OtherBody->GetNode().GetTransform().GetTranslation()
                + basic::Vector3(0.0f, 40.0f, 0.0f));
        }
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
