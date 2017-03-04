#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(spawner::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace spawner
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
        _SpawnTime = 0.0f;
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        _SpawnTime += time_step;
        if (GetNode().GetParent().HasParent() && _SpawnTime.GetSecondCount()>0.8f
            && GetNode().GetRoot().GetChildCount()<26)
        {
            // check if player is near
            bool it_is_near = false;
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
                        it_is_near = distance < 240.0f;
                    }
                }
            }

            if (it_is_near)
            {
                _SpawnTime = 0.0f;
                scene::Instance* alien = COFFEE_New(scene::Instance, "/alien_ship.scene");
                alien->AddComponent(COFFEE_New(scene::Transform));
                alien->AddComponent(COFFEE_New(scene::Bounding));
                GetNode().GetRoot().Attach(*alien);

                basic::Vector3 position(10.0f, 0.0f, 0.0f);
                basic::Euler rotation(0.0f, basic::GetRandom(360)*2.0f*Pi/360.0f, 0.0f);
                position *= basic::Quaternion(rotation);

                alien->GetTransform().SetTranslation(
                    GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation()
                    + position);
            }
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {
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

}
