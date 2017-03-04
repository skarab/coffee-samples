#ifndef _MINESWEEPER_H_
#define _MINESWEEPER_H_

#include "coffee.h"
using namespace coffee;

//-IMPORT-EXPORT----------------------------------------------------------------------------------//
#ifndef USE_MINESWEEPER
    #define MINESWEEPER_API __declspec(dllexport)
    #define MINESWEEPER_TEMPLATE_API __declspec(dllexport)
#else
    #define MINESWEEPER_API __declspec(dllimport)
    #define MINESWEEPER_TEMPLATE_API
#endif

#ifdef USE_MINESWEEPER
    #define MINESWEEPER_EXPORT_STATICS false
#else
    #define MINESWEEPER_EXPORT_STATICS true
#endif
//------------------------------------------------------------------------------------------------//

namespace minesweeper
{
    //--------------------------------------------------------------------------------------------//
    /// Button states
    //--------------------------------------------------------------------------------------------//
    enum BUTTON_STATE
    {
        BUTTON_STATE_Closed = 0,
        BUTTON_STATE_Open = 1,
        BUTTON_STATE_Flagged = 2
    };

    //--------------------------------------------------------------------------------------------//
    /// minesweeper::Library
    //--------------------------------------------------------------------------------------------//
    class MINESWEEPER_API Library : public plugins::Library
    {
        COFFEE_Type(Library);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Library();
        ~Library();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize();
        void Finalize();
        void Update(const basic::Time& time_step);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareExternEventHandler(Library, OnLevelEasy);
        COFFEE_DeclareExternEventHandler(Library, OnLevelMedium);
        COFFEE_DeclareExternEventHandler(Library, OnLevelHard);
        COFFEE_DeclareExternEventHandler(Library, OnOpenButton);
        COFFEE_DeclareExternEventHandler(Library, OnFlagButton);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _GenerateGrid(basic::Vector2i grid_size=basic::Vector2i(), uint32 mine_count=0);
        void _GameOver();
        void _CheckWin();
        void _OpenEmptyButtons(int32 x, int32 y, int32 sens, basic::Array<bool>& fill_grid);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::Dialog* _MainDialog;
        basic::Vector2i _GridSize;
        uint32 _MineCount;
        int32 _MineNotFlaggedCount;
        ui::Window* _Canvas;
        basic::Array<int32> _Grid;
        basic::Prow<ui::widget::Button*> _Buttons;
        basic::Array<uint32> _ButtonStates;
        ui::widget::Button* _EasyButton;        
        ui::widget::Button* _MediumButton;        
        ui::widget::Button* _HardButton;
        ui::widget::Label* _FlaggedLabel;
        ui::widget::Button* _SmileyButton;        
        ui::widget::Label* _TimeLabel;
        bool _ItIsGameOver;
        bool _ItIsStarted;
        basic::Time _Time;
    };

    COFFEE_RegisterType(MINESWEEPER_EXPORT_STATICS, Library);
}

COFFEE_RegisterPlugin(minesweeper::Library);

#endif
