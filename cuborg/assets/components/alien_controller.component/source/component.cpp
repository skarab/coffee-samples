#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(alien_controller::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(real, _MoveSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_Attribute(real, _RollSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
COFFEE_EndType();

namespace alien_controller
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _MoveSpeed(1.0f),
        _RollSpeed(1.0f),
        _ReloadTime(0.25f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _Force = 0.0f;
        _Torque = 0.0f;

        for (uint32 index=0 ; index<4 ; ++index)
            _KeyArray[index] = false;

        _ShootTime = 0.0f;
        _LifeTime = 0.0f;
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
        _Force = 0.0f;
        _Torque = 0.0f;

        if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
            GetNode().GetRigidBody().SetVelocity(basic::Vector3::Zero);
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        if (GetNode().GetParent().HasParent())
        {
            _LifeTime += time_step;
            if (_LifeTime.GetSecondCount()>5.0f)
                GetNode().GetParent().GetParent().Destroy();
        }

        // Is Player near ?
        bool it_is_near = false;
        bool it_is_targeting = false;
        if (GetNode().GetParent().HasParent())
        {
            scene::Node* player = GetNode().GetRoot().FindChild("CubeShip");
            if (player!=NULL)
            {
                scene::Node* root = player->FindChild("Root");
                if (root!=NULL)
                {
                    scene::Node* ship = root->FindChild("Ship");
                    if (ship!=NULL)
                    {
                        real distance = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation().GetDistance(
                            ship->GetTransform().GetTranslation());
                        it_is_near = distance < 120.0f;

                        if (it_is_near)
                        {
                            _LifeTime = 0.0f;

                            real dot = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetZAxis().GetDotProduct(
                                ship->GetTransform().GetTranslation()-GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
                            it_is_near = dot > 0.5f;
                            it_is_targeting = dot > 0.8f;
                        }
                    }
                }
            }
        }

        _ShootTime += time_step;
        if (it_is_near && _ShootTime.GetSecondCount()>=_ReloadTime)
        {
            _ShootTime = 0.0f;
            scene::Instance* projectile = COFFEE_New(scene::Instance, "/projectiles/bullet.scene");
            projectile->AddComponent(COFFEE_New(scene::Transform));
            projectile->AddComponent(COFFEE_New(scene::Bounding));
            
            // Attach to the root of the ship instance
            GetNode().GetParent().Attach(*projectile);

            audio::Device::Get().PlaySound("/import/sounds/gun.sound", true, 2.0f, 100.0f,
                GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
        }

        _UpdateTime += time_step;
        if (GetNode().GetParent().HasParent() && _UpdateTime.GetSecondCount()>1.0f)
        {
            for (uint32 index=0 ; index<4 ; ++index)
                _KeyArray[index] = basic::GetRandom(24)>10;

            if (it_is_targeting)
            {
                _KeyArray[input::KEY_Left-input::KEY_Left] = false;
                _KeyArray[input::KEY_Right-input::KEY_Left] = false;
            }
            _UpdateTime = 0.0f;
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {
        if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
        {
            _Force = 0.0f;
            real distance = _MoveSpeed*time_step.GetSecondCount()*8.0f;
            if (_KeyArray[input::KEY_Up-input::KEY_Left]) _Force += _ComputeMove(distance);
            if (_KeyArray[input::KEY_Down-input::KEY_Left]) _Force += _ComputeMove(-distance);
            basic::Vector3 force = ((_Force*1000.0f-GetNode().GetRigidBody().GetVelocity()*0.6f/time_step.GetSecondCount()));
            GetNode().GetRigidBody().AddForce(force);
            _Force = 0.0f;
            
            _Torque = 0.0f;
            real angle = _RollSpeed*time_step.GetSecondCount();
            if (_KeyArray[input::KEY_Right-input::KEY_Left]) _Torque += basic::Vector3(0.0f, angle, 0.0f);
            if (_KeyArray[input::KEY_Left-input::KEY_Left]) _Torque += basic::Vector3(0.0f, -angle, 0.0f);
            basic::Vector3 torque = ((_Torque*1000.0f-GetNode().GetRigidBody().GetOmega()*0.6f/time_step.GetSecondCount()));
            GetNode().GetRigidBody().AddTorque(torque);
            _Torque = 0.0f;
        }

        GetNode().GetTransform().SetTranslation(basic::Vector3(
            GetNode().GetTransform().GetTranslation().X,
            0.0f,
            GetNode().GetTransform().GetTranslation().Z));
            
        basic::Euler rotation = GetNode().GetTransform().GetRotation();
        rotation.X = 0.0f;
        rotation.Z = 0.0f;
        GetNode().GetTransform().SetRotation(rotation);

        scene::Node* shield = GetNode().FindChild("Shield");
        if (shield!=NULL)
        {
            plugins::ComponentWrapper* component = shield->FindComponent("shield::Component");
            if (component!=NULL)
            {
                uint32* life = component->Grab<uint32>("Life");
                if (life!=NULL && *life<=0)
                    GetNode().GetParent().GetParent().Destroy();
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

    
    //-OPERATIONS-----------------------------------------------------------------------------//

    basic::Vector3 Component::_ComputeMove(real distance)
    {
        basic::Vector3 movement;
        movement = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetRotation().GetZAxis();
        movement *= distance;
        return movement;
    }

}
