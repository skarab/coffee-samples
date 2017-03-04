#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(elevator::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace elevator
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _ItIsUp(false),
        _Height(8.0f),
        _Speed(22.0f),
        _SwitchDelay(0.4f),
        _SwitchTime(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _ItIsUp = false;
        _SwitchTime = 0.0f;
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
            real whished_scale = _ItIsUp?_Height:0.2f;
            basic::Vector3 scale = GetNode().GetTransform().GetScale();
            scale.Y = scale.Y + (whished_scale-scale.Y)*time_step.GetSecondCount()*(_Speed/_Height);

            GetNode().GetTransform().SetScale(scale);
            GetNode().GetTransform().SetTranslation(basic::Vector3(0.0f, 0.5f*scale.Y, 0.0f));
        }

        if (_SwitchTime>0.0f)
        {
            _SwitchTime -= time_step.GetSecondCount();
            if (_SwitchTime<0.0f)
            {
                _ItIsUp = !_ItIsUp;

                audio::ComponentSound* bip_sound = GetNode().FindComponent<audio::ComponentSound>();
                if (bip_sound!=NULL)
                {
                    if (!bip_sound->IsRunning())
                    {
                        bip_sound->Start();
                    }
                    else if (bip_sound->GetSound().IsAvailable())
                    {
                        bip_sound->GetSound().Play();
                    }
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnRender(const graphics::Viewport& viewport)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollisionBegin(const physics::Collision& collision)
    {
        _SwitchTime = _SwitchDelay;
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
