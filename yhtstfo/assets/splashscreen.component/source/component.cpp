#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(splashscreen::Component);
    COFFEE_Ancestor(plugins::Component);
    COFFEE_Attribute(graphics::Texture, _SplashImage, meta::MODE_Serializeable | meta::MODE_Editable);
COFFEE_EndType();

namespace splashscreen
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _FullScreenWindow(NULL),
        _Image(NULL),
        _StartLevel(NULL),
        _CameraScene(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        if (_SplashImage.GetFilePath().IsEmpty())
            _SplashImage = resource::Manager::Get().Load("/coffee/import/textures/default.texture");
    
        if (!Engine::Get().HasMode(RUN_MODE_Editor))
        {
            _FullScreenWindow = COFFEE_New(ui::Window);
            _FullScreenWindow->Create(NULL, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            _FullScreenWindow->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand
                | ui::LAYOUT_STYLE_VerticalCanvas
                | ui::LAYOUT_STYLE_StickChildren);

            ui::Window* space = COFFEE_New(ui::Window);
            space->Create(_FullScreenWindow, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            space->GetLayout().SetCanvas(100.0f, true);

            _Image = COFFEE_New(ui::widget::Image);
            _Image->Create(_FullScreenWindow, basic::Vector2i(), basic::Vector2i(), ui::widget::IMAGE_STYLE_AutoSize);
            _Image->SetImage(_SplashImage);
            _Image->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);

            space = COFFEE_New(ui::Window);
            space->Create(_FullScreenWindow, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            space->GetLayout().SetCanvas(100.0f, true);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnStop()
    {
        if (_FullScreenWindow!=NULL)
        {
            _FullScreenWindow->Destroy();
            _FullScreenWindow = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnUpdate(const basic::Time& time_step)
    {
        if (_FullScreenWindow!=NULL && _StartLevel==NULL)
        {
            if (input::Keyboard::Get().IsButtonPressed(input::KEY_Space))
            {
                _StartLevel = COFFEE_New(scene::Instance, "/levels/level_0.scene");
                _StartLevel->AddComponent(COFFEE_New(scene::Transform));
                _StartLevel->AddComponent(COFFEE_New(scene::Bounding));
                GetNode().GetRoot().Attach(*_StartLevel);

                _CameraScene = COFFEE_New(scene::Instance, "/default.scene");
                _CameraScene->SetName("Camera");
                _CameraScene->AddComponent(COFFEE_New(scene::Transform));
                _CameraScene->AddComponent(COFFEE_New(scene::Bounding));
                GetNode().GetRoot().Attach(*_CameraScene);
            }
        }

        if (_StartLevel!=NULL && _StartLevel->HasChildren()
            && _CameraScene!=NULL && _CameraScene->HasChildren())
        {
            GetNode().Destroy();
            graphics::ComponentCameraPerspective* camera =
                _CameraScene->GetChild(0).FindChild("Camera")->FindComponent<graphics::ComponentCameraPerspective>();
            resource::Handler<scene::Resource> scene(scene::World::Get().GetScene("/splashscreen.scene"));
            ui::WindowManager::Get().GetDesktopWindow().AttachCamera(scene, camera);
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnFixedUpdate(const basic::Time& time_step)
    {        
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

}
