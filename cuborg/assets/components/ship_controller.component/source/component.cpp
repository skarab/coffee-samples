#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(ship_controller::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(real, _MoveSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_Attribute(real, _RollSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
COFFEE_EndType();

namespace ship_controller
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _MoveSpeed(1.0f),
        _RollSpeed(1.0f)
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
                    _Quit();
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
        if (event==input::EVENT_KeyPressed)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;

            if (!parameter->ItIsRepeating)
            {
                if (parameter->Key>=input::KEY_Left && parameter->Key<=input::KEY_Down)
                {
                    _KeyArray[parameter->Key-input::KEY_Left] = true;
                    return true;
                }
            }

            if (parameter->Key==input::KEY_Escape)
            {
                _Quit();
                return true;
            }
        }
        else if (event==input::EVENT_KeyReleased)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;

            if (parameter->Key>=input::KEY_Left && parameter->Key<=input::KEY_Down)
            {
                _KeyArray[parameter->Key-input::KEY_Left] = false;
                return true;
            }
        }
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

    //--------------------------------------------------------------------------------------------//

    void Component::_Quit()
    {
        scene::Resource* scene = scene::World::Get().GetScene("/menu.scene");
        scene::Node* camera = scene->GetRoot().FindChild("Camera");
        camera->Start();
        graphics::ComponentCameraPerspective* component = camera->FindComponent<graphics::ComponentCameraPerspective>();
        ui::WindowManager::Get().GetDesktopWindow().AttachCamera(scene, component);
        scene->GetRoot().FindChild("Loader")->Restart();
    }

}
