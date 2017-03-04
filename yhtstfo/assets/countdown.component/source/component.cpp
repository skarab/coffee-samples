#include "component.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(countdown::Component);
    COFFEE_Ancestor(plugins::Component);
COFFEE_EndType();

namespace countdown
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component() :
        _Time(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::OnStart()
    {
        _Time = 11.9f;
        _InitializeLevel();
        _InitializeVoice();
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
        real old_time = _Time;
        real count = Floor(old_time);
        _Time -= time_step.GetSecondCount()*0.8f;
        
        if (old_time>count && _Time<count)
        {
            basic::String speach("%d", (uint32)count-1);
            if (count==1)
                speach = "Over!";

            if (count>=1)
            {
                if (!Engine::Get().HasMode(RUN_MODE_Editor))
                    _Speak(speach);
            }
            else if (count<=0 && !Engine::Get().HasMode(RUN_MODE_Editor))
            {
                _RestartGame();                
            }
        }

        if (GetNode().HasTransform())
        {
            basic::Euler rotation(time_step.GetSecondCount()*0.8f,
                time_step.GetSecondCount()*1.2f, time_step.GetSecondCount()*1.8f);
            GetNode().GetTransform().SetRotation(GetNode().GetTransform().GetRotation()*rotation);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Component::OnRender(const graphics::Viewport& viewport)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    void Component::OnCollisionBegin(const physics::Collision& collision)
    {
        scene::Node& root = GetNode().GetRoot();
        if (!GetNode().HasParent() || !GetNode().GetParent().HasParent())
            return;
        scene::Node& countdown_instance = GetNode().GetParent().GetParent();
        if (!countdown_instance.HasParent())
            return;
        scene::Node& level_root = countdown_instance.GetParent();
        if (!level_root.HasParent())
            return;
        scene::Instance& level_instance = static_cast<scene::Instance&>(level_root.GetParent());

        // Check if next level is available
        basic::String level_path("/levels/level_%d.scene", _LevelIndex+1);
        bool it_has_next_level = storage::System::Get().HasPath(level_path);
        
        if (it_has_next_level)
        {
            // Destroy old countdown platforms
            for (int32 i=(int32)root.GetChildCount()-1 ; i>=0 ; --i)
            {
                scene::Node& child = root.GetChild(i);
                if (child.GetName()!="Camera" && &child!=&level_instance)
                    child.Destroy();
            }

            // Destroy current level nodes, keeping the countdown platform
            for (int32 i=(int32)level_root.GetChildCount()-1 ; i>=0 ; --i)
            {
                scene::Node& child = level_root.GetChild(i);
                if (&child!=&countdown_instance)
                    child.Destroy();
            }

            _Speak("Checkpoint!");

            scene::Instance* new_level = COFFEE_New(scene::Instance, level_path);
            new_level->AddComponent(COFFEE_New(scene::Transform));
            new_level->AddComponent(COFFEE_New(scene::Bounding));
            root.Attach(*new_level);
        }
        else
        {
            _Speak("Mission complete.");
        }

        // Finally destroy this node.
        GetNode().Destroy();
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

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Component::_InitializeLevel()
    {
        _LevelIndex = 0;
        scene::Node& root = GetNode().GetRoot();
        if (GetNode().HasParent() && GetNode().GetParent().HasParent())
        {
            scene::Node& countdown_instance = GetNode().GetParent().GetParent();
            if (countdown_instance.HasParent())
            {
                scene::Node& level_root = countdown_instance.GetParent();
                if (level_root.HasParent())
                {
                    scene::Instance& level_instance = static_cast<scene::Instance&>(level_root.GetParent());

                    basic::String level_path(level_instance.GetSource().GetFilePath());
                    uint32 count_start = level_path.Find('_')+1;
                    uint32 count_end = level_path.Find('.')-1;
                    _LevelIndex = level_path.GetCenter(count_start, count_end).GetInteger();
                }
            }
        }
    }
      
    //--------------------------------------------------------------------------------------------//

    void Component::_InitializeVoice()
    {
        _Voice.ItIs3D = _LevelIndex==3;
        _Voice.Pitch = 1.3f;
        _Voice.Gain = 1.0f;
        _Voice.Gender = voice_synthesizer::VOICE_GENDER_Female;
        _Voice.Language = voice_synthesizer::VOICE_LANGUAGE_English;
        _Voice.Age = 0;
        _Voice.Variant = 0;
        _Voice.Effect = voice_synthesizer::VOICE_EFFECT_None;
    }    
    
    //--------------------------------------------------------------------------------------------//

    void Component::_Speak(const basic::String& speach)
    {
        voice_synthesizer::Synthesizer::Get().Speak(speach, _Voice,
            GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation());
    }
       
    //--------------------------------------------------------------------------------------------//

    void Component::_RestartGame()
    {
        ui::WindowManager::Get().GetDesktopWindow().DetachCamera();

        scene::Node& root = GetNode().GetRoot();
        for (int32 i=root.GetChildCount()-1 ; i>=0 ; --i)
            root.GetChild(i).Destroy();
    
        scene::Instance* splash_screen = COFFEE_New(scene::Instance, "/splashscreen.scene");
        splash_screen->AddComponent(COFFEE_New(scene::Transform));
        splash_screen->AddComponent(COFFEE_New(scene::Bounding));
        root.Attach(*splash_screen);
    }
        
}
