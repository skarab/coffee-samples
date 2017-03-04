#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(top_camera::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable);
COFFEE_EndType();

namespace top_camera
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Height(40.0f)
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
        scene::Node* ship_scene = GetNode().GetParent().FindChild("CubeShip");
        if (ship_scene!=NULL)
        {
            scene::Node* ship_root = ship_scene->FindChild("Root");
            if (ship_root!=NULL)
            {
                scene::Node* ship = ship_root->FindChild("Ship");
                if (ship!=NULL)
                {
                    const basic::Matrix& matrix = ship->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
                    basic::Vector3 translation = matrix.GetTranslation();
                    GetNode().GetTransform().SetTranslation(
                        basic::Vector3(translation.X, _Height, translation.Z));
                    GetNode().GetTransform().SetRotation(
                        basic::Euler(Pi/2.0f, 0.0f, 0.0f));
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
