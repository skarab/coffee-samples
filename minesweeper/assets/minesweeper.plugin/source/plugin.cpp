#include "plugin.h"

//-META-------------------------------------------------------------------------------------------//

COFFEE_BeginType(minesweeper::Library);
    COFFEE_Ancestor(plugins::Library);
COFFEE_EndType();

namespace minesweeper
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Library::Library() :
        _MainDialog(NULL),
        _Canvas(NULL),
        _ItIsGameOver(false),
        _ItIsStarted(false),
        _EasyButton(NULL),
        _MediumButton(NULL),
        _HardButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Library::~Library()
    {
    }    

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Library::Initialize()
    {
        srand((uint32)(core::Platform::Get().GetTime()*1000.0f));

        _MainDialog = COFFEE_New(ui::widget::Dialog);
        _MainDialog->Create(NULL, basic::Vector2i(), basic::Vector2i(360,400), ui::widget::DIALOG_STYLE_None);
        _MainDialog->PositionToCenter();
        _MainDialog->SetTitleBarText("Minesweeper");

        _GenerateGrid(basic::Vector2i(9, 9), 10);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::Finalize()
    {
        _MainDialog->Destroy();
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::Update(const basic::Time& time_step)
    {
        if (!_ItIsGameOver && _ItIsStarted)
        {
            _FlaggedLabel->SetText(basic::String("%04d", _MineNotFlaggedCount));
            _TimeLabel->SetText(basic::String("%04d", (uint32)_Time.GetSecondCount()));
            _Time += time_step;
            if (_Time.GetSecondCount()>1200.0f)
                _GameOver();
        }
    }
    
    //-EVENTS-------------------------------------------------------------------------------------//

    bool Library::OnLevelEasy(shell::Event& event)
    {
        _GenerateGrid(basic::Vector2i(9, 9), 10);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Library::OnLevelMedium(shell::Event& event)
    {
        _GenerateGrid(basic::Vector2i(12, 12), 24);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Library::OnLevelHard(shell::Event& event)
    {
        _GenerateGrid(basic::Vector2i(18, 18), 68);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Library::OnOpenButton(shell::Event& event)
    {
        ui::widget::Button* button = static_cast<ui::widget::Button*>(event.GetTarget());
        uint32 index = (uint32)button->GetData();
        if (index==9999)
        {
            _GenerateGrid();
            return true;
        }
        if (index==10000)
            return true;

        if (_ItIsGameOver)
        {
            button->SetState(ui::widget::BUTTON_STATE_Off);
            return true;
        }

        _ItIsStarted = true;

        if (_ButtonStates[index]==BUTTON_STATE_Closed)
        {
            _ButtonStates[index] = BUTTON_STATE_Open;
            button->SetState(ui::widget::BUTTON_STATE_On);

            if (_Grid[index]==-1)
            {
                _GameOver();
            }
            else if (_Grid[index]>0)
            {
                button->SetText(basic::String("%d", _Grid[index]));
                _CheckWin();
            }
            else
            {
                int32 y = (int32)index/_GridSize.X;
                int32 x = (int32)index-y*_GridSize.X;
                basic::Array<bool> fill_grid;
                fill_grid.Resize(_GridSize.X*_GridSize.Y);
                _OpenEmptyButtons(x, y, -1, fill_grid);
                _OpenEmptyButtons(x+1, y, 1, fill_grid);
            }
        }
        else if (_ButtonStates[index]==BUTTON_STATE_Flagged)
        {
            _ButtonStates[index] = BUTTON_STATE_Closed;
            button->SetState(ui::widget::BUTTON_STATE_Off);
            button->SetNoImage();
            ++_MineNotFlaggedCount;
        }
        else
        {
            button->SetState(ui::widget::BUTTON_STATE_On);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Library::OnFlagButton(shell::Event& event)
    {
        ui::widget::Button* button = static_cast<ui::widget::Button*>(event.GetTarget());
        uint32 index = (uint32)button->GetData();
        if (_ItIsGameOver)
            return true;
        if (index>=9999)
            return true;

        if (_ButtonStates[index]==BUTTON_STATE_Closed)
        {
            _ButtonStates[index] = BUTTON_STATE_Flagged;
            button->SetImage("/import/flag.texture");
            --_MineNotFlaggedCount;
            _CheckWin();
        }
        else if (_ButtonStates[index]==BUTTON_STATE_Flagged)
        {
            _ButtonStates[index] = BUTTON_STATE_Closed;
            button->SetNoImage();
            ++_MineNotFlaggedCount;
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Library::_GenerateGrid(basic::Vector2i grid_size, uint32 mine_count)
    {
        if (mine_count>0)
        {
            _GridSize = grid_size;
            _MineCount = mine_count;
        }

        _ItIsGameOver = false;
        _ItIsStarted = false;
        _Time = 0.0f;
        _MineNotFlaggedCount = _MineCount;
        
        _Buttons.Erase();
        _Buttons.Resize(_GridSize.X*_GridSize.Y);
        _Grid.Erase();
        _Grid.Resize(_GridSize.X*_GridSize.Y);
        
        basic::Array<uint32> free_positions;
        free_positions.Resize(_GridSize.X*_GridSize.Y);
        uint32 index;
        for (index=0 ; index<free_positions.GetSize() ; ++index)
            free_positions[index] = index;

        for (index=0 ; index<_MineCount ; ++index)
        {
            uint32 random = basic::GetRandom(free_positions.GetSize()-1);
            uint32 position = free_positions[random];
            free_positions.Remove(random);

            int32 y = (int32)position/_GridSize.X;
            int32 x = (int32)position-y*_GridSize.X;
            
            for (int32 j=0 ; j<3 ; ++j)
            {
                int32 v = y+j-1;
                if (v>=0 && v<_GridSize.Y)
                {
                    for (int32 i=0 ; i<3 ; ++i)
                    {
                        int32 u = x+i-1;
                        if (u>=0 && u<_GridSize.X)
                        {
                            uint32 id = v*_GridSize.X+u;
                            if (_Grid[id]>=0)
                                ++_Grid[id];
                        } 
                    }
                }
            }
            _Grid[position] = -1;
        }
        
        _ButtonStates.Erase();
        _ButtonStates.Resize(_GridSize.X*_GridSize.Y);

        if (_Canvas!=NULL)
            _Canvas->Destroy();
        _Canvas = COFFEE_New(ui::Window);
        _Canvas->Create(_MainDialog, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        _Canvas->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_Expand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        ui::Window* header = COFFEE_New(ui::Window);
        header->Create(_Canvas, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        header->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        header->GetLayout().SetCanvas(45, false);

        _EasyButton = COFFEE_New(ui::widget::Button);
        _EasyButton->Create(header, basic::Vector2i(), basic::Vector2i());
        _EasyButton->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _EasyButton->GetLayout().SetCanvas(15, true);
        _EasyButton->SetData((void*)10000);
        _EasyButton->SetImage("/import/level_easy.texture");
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *_EasyButton, OnLevelEasy);
        _MediumButton = COFFEE_New(ui::widget::Button);
        _MediumButton->Create(header, basic::Vector2i(), basic::Vector2i());
        _MediumButton->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _MediumButton->GetLayout().SetCanvas(15, true);
        _MediumButton->SetData((void*)10000);
        _MediumButton->SetImage("/import/level_medium.texture");
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *_MediumButton, OnLevelMedium);
        _HardButton = COFFEE_New(ui::widget::Button);
        _HardButton->Create(header, basic::Vector2i(), basic::Vector2i());
        _HardButton->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _HardButton->GetLayout().SetCanvas(15, true);
        _HardButton->SetData((void*)10000);
        _HardButton->SetImage("/import/level_hard.texture");
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *_HardButton, OnLevelHard);
        
        _FlaggedLabel = COFFEE_New(ui::widget::Label);
        _FlaggedLabel->Create(header, basic::Vector2i(), basic::Vector2i());
        _FlaggedLabel->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _FlaggedLabel->GetLayout().SetCanvas(15, true);
        _FlaggedLabel->SetText(basic::String("%04d", _MineNotFlaggedCount));

        _SmileyButton = COFFEE_New(ui::widget::Button);
        _SmileyButton->Create(header, basic::Vector2i(), basic::Vector2i());
        _SmileyButton->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _SmileyButton->GetLayout().SetCanvas(20, true);
        _SmileyButton->SetData((void*)9999);
        _SmileyButton->SetImage("/import/smiley_ok.texture");

        _TimeLabel = COFFEE_New(ui::widget::Label);
        _TimeLabel->Create(header, basic::Vector2i(), basic::Vector2i());
        _TimeLabel->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        _TimeLabel->GetLayout().SetCanvas(20, true);
        _TimeLabel->SetText("0000");

        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *_Canvas, OnOpenButton);
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_ContextMenu,
            ui::widget::Widget::GetClassMetaType(), *_Canvas, OnFlagButton);

        ui::Window* space = COFFEE_New(ui::Window);
        space->Create(_Canvas, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        space->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        space->GetLayout().SetCanvas(5, false);

        for (int32 j=0 ; j<_GridSize.Y ; ++j)
        {
            ui::Window* horizontal_line = COFFEE_New(ui::Window);
            horizontal_line->Create(_Canvas, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            horizontal_line->GetLayout().SetStyle(
                ui::LAYOUT_STYLE_HorizontalExpand
                | ui::LAYOUT_STYLE_HorizontalCanvas
                | ui::LAYOUT_STYLE_StickChildren);
            horizontal_line->GetLayout().SetCanvas(100.0f/_GridSize.Y, true);

            for (int32 i=-1 ; i<=_GridSize.X ; ++i)
            {
                if (i==-1 || i==_GridSize.X)
                {
                    ui::Window* space = COFFEE_New(ui::Window);
                    space->Create(horizontal_line, basic::Vector2i(), basic::Vector2i(),
                        ui::WINDOW_STYLE_None);
                    space->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
                    space->GetLayout().SetCanvas(20, false);
                }
                else
                {
                    // Create buttons
                    ui::widget::Button* button = COFFEE_New(ui::widget::Button);
                    button->Create(horizontal_line, basic::Vector2i(), basic::Vector2i(), ui::widget::BUTTON_STYLE_PushLike);
                    button->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
                    button->GetLayout().SetCanvas(100.0f/_GridSize.X, true);
                    button->SetData((void*)(j*_GridSize.X+i));
                    _Buttons[j*_GridSize.X+i] = button;
                }
            }
        }

        ui::Window* footer = COFFEE_New(ui::Window);
        footer->Create(_Canvas, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        footer->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        footer->GetLayout().SetCanvas(20, false);
    }

    //--------------------------------------------------------------------------------------------//
    
    void Library::_GameOver()
    {
        for (int32 i=0 ; i<_GridSize.X*_GridSize.Y ; ++i)
        {
            if (_Grid[i]==-1)
            {
                _Buttons[i]->SetState(ui::widget::BUTTON_STATE_On);
                _Buttons[i]->SetImage("/import/mine.texture");
            }
        }
        _SmileyButton->SetImage("/import/smiley_over.texture");
        _ItIsGameOver = true;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Library::_CheckWin()
    {
        for (int32 i=0 ; i<_GridSize.X*_GridSize.Y ; ++i)
        {
            if ((_ButtonStates[i]==BUTTON_STATE_Closed || _ButtonStates[i]==BUTTON_STATE_Flagged) && _Grid[i]>=0)
                return;
        }
        _ItIsStarted = false;
        _MineNotFlaggedCount = 0;
    }

    //--------------------------------------------------------------------------------------------//

    void Library::_OpenEmptyButtons(int32 x, int32 y, int32 sens, basic::Array<bool>& fill_grid)
    {
        uint32 index = y*_GridSize.X+x;
        while (x>=0 && x<_GridSize.X && y>=0 && y<_GridSize.Y && _Grid[index]==0 && !fill_grid[index])
        {
            if (_ButtonStates[index]==BUTTON_STATE_Flagged)
                ++_MineNotFlaggedCount;

            _Buttons[index]->SetState(ui::widget::BUTTON_STATE_On);
            _Buttons[index]->SetNoImage();
            _ButtonStates[index] = BUTTON_STATE_Open;
            fill_grid[index] = true;
            for (int32 v=-1 ; v<2 ; ++v)
            for (int32 u=-1 ; u<2 ; ++u)
                _OpenEmptyButtons(x+u, y+v, sens, fill_grid);
            index +=sens;
            x+=sens;
        }
        if (x>=0 && x<_GridSize.X && y>=0 && y<_GridSize.Y && _Grid[index]>0)
        {
            if (_ButtonStates[index]==BUTTON_STATE_Flagged)
                ++_MineNotFlaggedCount;

            _Buttons[index]->SetState(ui::widget::BUTTON_STATE_On);
            _Buttons[index]->SetText(basic::String("%d", _Grid[index]));
            _ButtonStates[index] = BUTTON_STATE_Open;
        }
    }

}
