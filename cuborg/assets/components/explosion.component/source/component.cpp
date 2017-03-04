#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(explosion::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace explosion
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
        if (GetNode().GetParent().HasParent())
        {
            GetNode().GetRigidBody().AddForce(basic::Vector3(
                basic::GetRandom(100)-50.0f,
                basic::GetRandom(100)-50.0f,
                basic::GetRandom(100)-50.0f));
        }
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
        if (GetNode().GetParent().HasParent())
        {
            _Time += time_step;
            if (_Time.GetSecondCount()>1.0f)
                GetNode().GetParent().GetParent().Destroy();
        }
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

    bool Component::OnInputEvent(const input::EVENT& event, const void* parameters)
    {
        return false;
    }

}
