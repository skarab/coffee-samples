#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(bullet::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace bullet
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
            scene::Node* ship = GetNode().GetParent().GetParent().GetParent().FindChild("Ship");
            if (ship!=NULL)
            {
                const scene::Node& root = ship->GetParent().GetParent();
                const basic::Matrix& inverse = root.GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);

                _Velocity = ship->GetRigidBody().GetVelocity()*3.0f
                    + (ship->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)*inverse).GetRotation().GetZAxis()*300.0f;

                scene::Node* weapon = ship->FindChild("Weapon");        
                GetNode().GetTransform().SetTranslation(
                    (weapon->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)*inverse).GetTranslation());
                GetNode().GetTransform().SetRotation(
                    (weapon->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World)*inverse).GetRotation());

                GetNode().GetRigidBody().Start();
            }
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
            if (_Time.GetSecondCount()>2.0f)
                GetNode().GetParent().GetParent().Destroy();

            if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
                GetNode().GetRigidBody().SetVelocity(_Velocity);
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnRender(const graphics::Viewport& viewport)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollisionBegin(const physics::Collision& collision)
    {
        GetNode().GetParent().GetParent().Destroy();

        scene::Node* shield = collision.OtherBody->GetNode().FindChild("Shield");
        if (shield!=NULL)
        {
            plugins::ComponentWrapper* component = shield->FindComponent("shield::Component");
            if (component!=NULL)
            {
                uint32* life = component->Grab<uint32>("Life");
                if (life!=NULL)
                    (*life)--;
            }
        
            for (uint32 i=0 ; i<6 ; ++i)
            {
                scene::Instance* explosion = COFFEE_New(scene::Instance, "/explode.scene");
                explosion->AddComponent(COFFEE_New(scene::Transform));
                explosion->AddComponent(COFFEE_New(scene::Bounding));
                GetNode().GetRoot().FindChild("Explosions")->Attach(*explosion);
                explosion->GetTransform().SetTranslation(
                    GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
                explosion->GetTransform().SetScale(basic::GetRandom(300)/100.0f+0.1f);
            }

            audio::Device::Get().PlaySound("/import/sounds/explode.sound", true, 1.0f, 100.0f,
                GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
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

    bool Component::OnInputEvent(const input::EVENT& event, const void* parameters)
    {
        return false;
    }

}
