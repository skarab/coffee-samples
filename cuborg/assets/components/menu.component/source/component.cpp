#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(menu::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace menu
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
        basic::Vector2i size(80, 120);

        _Frame = COFFEE_New(ui::Window);
        _Frame->Create(GAME_WINDOW, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_None);
        _Frame->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        ui::Window* space = COFFEE_New(ui::Window);
        space->Create(_Frame, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        space->GetLayout().SetCanvas(70, true);

        ui::Window* window = COFFEE_New(ui::Window);
        window->Create(_Frame, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        window->GetLayout().SetCanvas(20, true);
        window->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        {
            space = COFFEE_New(ui::Window);
            space->Create(window, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            space->GetLayout().SetCanvas(10, true);

            ui::Window* center = COFFEE_New(ui::Window);
            center->Create(window, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            center->GetLayout().SetCanvas(80, true);
            center->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
                | ui::LAYOUT_STYLE_HorizontalCanvas
                | ui::LAYOUT_STYLE_StickChildren);

            {
                space = COFFEE_New(ui::Window);
                space->Create(center, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
                space->GetLayout().SetCanvas(30, true);

                ui::widget::Button* button;
                button = COFFEE_New(ui::widget::Button);
                button->Create(center, basic::Vector2i(), basic::Vector2i());
                button->GetLayout().SetCanvas(40, true);
                button->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
                button->SetImage("/import/textures/start.texture");

                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *button, OnStart);
        
                space = COFFEE_New(ui::Window);
                space->Create(center, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
                space->GetLayout().SetCanvas(30, true);
            }

            space = COFFEE_New(ui::Window);
            space->Create(window, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            space->GetLayout().SetCanvas(10, true);
        }

        space = COFFEE_New(ui::Window);
        space->Create(_Frame, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        space->GetLayout().SetCanvas(10, true);
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
        _Frame->Destroy();

        if (_Scene.GetState()!=resource::HANDLER_STATE_Null)
        {
            //ui::WindowManager::Get().GetDesktopWindow().DetachCamera();
            scene::World::Get().Unload(_Scene);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        if (!IsPlaying())
        {
            if (input::Keyboard::Get().IsJustButtonPressed(input::KEY_Space))
            {
                shell::Event ev;
                OnStart(ev);
            }

            if (_Scene.Update()==resource::HANDLER_STATE_EndLoading)
            {
                ui::WindowManager::Get().GetDesktopWindow().GetCamera().GetComponent().GetNode().Stop();
                _Frame->Show(false);
                scene::Node& root = _Scene.Get().GetRoot();
                scene::Node* camera_node = NULL;
                root.Restart();
                camera_node = root.FindChild("TopCamera");
                graphics::ComponentCameraPerspective* camera = camera_node->FindComponent<graphics::ComponentCameraPerspective>();
                ui::WindowManager::Get().GetDesktopWindow().AttachCamera(_Scene, camera);
            }
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {
        if (!IsPlaying())
        {
            _Time += time_step;

            scene::Node* light = GetNode().GetParent().FindChild("Light");
            if (light!=NULL)
            {
                graphics::ComponentLightDirectional* component =
                    light->FindComponent<graphics::ComponentLightDirectional>();
                if (component!=NULL)
                    component->SetIntensity(Sin(_Time.GetSecondCount()*20.0f)*0.02f+0.1f);
            
                basic::Euler rotation(34.0f, 40.5f, 0.0f);
                basic::Euler roll(0.0f, Sin(_Time.GetSecondCount()/10.0f)*5.0f, 0.0f);
                light->GetTransform().SetRotation(rotation+roll);

                light = light->FindChild("Spot");
                graphics::ComponentLightSpot* spot =
                    light->FindComponent<graphics::ComponentLightSpot>();
                if (spot!=NULL)
                    spot->SetIntensity(Cos(_Time.GetSecondCount()*40.0f)*5.0f+50.0f);
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

    //-EVENTS-------------------------------------------------------------------------------------//

    bool Component::OnStart(shell::Event& event)
    {
        if (!IsPlaying() && _Scene.GetState()==resource::HANDLER_STATE_Null)
            _Scene = scene::World::Get().Load("/levels/cube_zone.scene");
        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//
        
    bool Component::IsPlaying() const
    {
        return ui::WindowManager::Get().GetDesktopWindow().HasCamera()
            && ui::WindowManager::Get().GetDesktopWindow().GetCamera().GetComponent().GetNode().GetName()
            =="TopCamera";
    }


}
