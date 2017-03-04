#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(weapon_gun::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(real, _ReloadTime, meta::MODE_Editable | meta::MODE_Serializeable);
COFFEE_EndType();

namespace weapon_gun
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _ItIsShooting(false),
        _ReloadTime(0.5f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _ItIsShooting = false;
        _Time = 0.0f;
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
        _ItIsShooting = false;
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {
        _Time += time_step;
        if (_ItIsShooting && _Time.GetSecondCount()>=_ReloadTime)
        {
            _Time = 0.0f;
            scene::Instance* projectile = COFFEE_New(scene::Instance, "/projectiles/bullet.scene");
            projectile->AddComponent(COFFEE_New(scene::Transform));
            projectile->AddComponent(COFFEE_New(scene::Bounding));
            
            // Attach to the root of the ship instance
            GetNode().GetParent().GetParent().GetParent().Attach(*projectile);

            audio::Device::Get().PlaySound("/import/sounds/gun.sound", true, 2.0f, 100.0f,
                GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
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
        if (event==input::EVENT_KeyPressed)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;
            if (!parameter->ItIsRepeating && parameter->Key==input::KEY_Space)
            {
                _ItIsShooting = true;
                return true;
            }
        }
        else if (event==input::EVENT_KeyReleased)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;
            if (parameter->Key==input::KEY_Space)
            {
                _ItIsShooting = false;
                return true;
            }
        }
        return false;
    }

}
