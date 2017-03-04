#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(rotoscale::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace rotoscale
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Time(0.0f),
        _Speed(4.4f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _Time = basic::GetRandom(100)/10.0f;
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
        if (GetNode().HasTransform())
        {
            basic::Euler rotation(_Time*0.2f, _Time*0.6f, _Time*1.2f);
            basic::Vector3 scale(_ComputeScale(_Time*0.2f), _ComputeScale(_Time*0.6f), _ComputeScale(_Time*1.2f)); 
            GetNode().GetTransform().SetRotation(rotation);
            GetNode().GetTransform().SetScale(scale);
            _Time += time_step.GetSecondCount();
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

    bool Component::OnInputEvent(const input::EVENT& event, void* parameters)
    {
        return false;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    real Component::_ComputeScale(real time)
    {
        real scale = cos(time*_Speed);
        return Maximum(scale, 0.01f);
    }

}
