#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(shield::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(uint32, _Life, meta::MODE_Serializeable | meta::MODE_Editable);
COFFEE_EndType();

namespace shield
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Life(1)
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
        for (uint32 i=0 ; i<10 ; ++i)
        {
            basic::String name("life%d", i+1);
            scene::Node* node = GetNode().FindChild(name);
            if (node!=NULL)
            {
                if (i+1>_Life)
                {
                    if (node->IsRunning())
                        node->Stop();
                }
                else
                {
                    if (!node->IsRunning())
                        node->Start();
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
