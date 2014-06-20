/*******************************************************************************************************************************
*	
*	Filename: mainmenu.c
*	Rev Date: 5/2/2012
*
*	File Description:
*			Handle the Main Menu screen
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "iobtn.h"
#include "iojs.h"
#include "mainmenu.h"
#include "mainmenu_cfg.h"
#include "lpc_swim.h"
#include "lpc_swim_font.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define MAINMENU_C_VERSION_MAJOR		(1)
#define MAINMENU_C_VERSION_MINOR		(0)
#define MAINMENU_C_VERSION_PATCH		(0)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static U1 u1_s_selection_state;
static U1 u1_s_selection;
static SWIM_WINDOW_T mmwin;
static U1 u1_s_js_state;
static U1 u1_s_js_state_prev;
static U2 u2_s_js_wait_cntr;
static U1 u1_s_refresh_scrn;

/*
const U1 u1_s_mainmenu1[] = "System Check";
const U1 u1_s_mainmenu2[] = "Pong Demo";
const U1 u1_s_mainmenu3[] = "Options";
*/

/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_AppMainMenuInitScreen(void);
static void vd_s_AppMainMenuRefresh(void);
static void vd_s_AppMainMenuUpdSelection(void);
static void vd_s_AppMainMenuUpdCursor(void);
static void vd_s_AppMainMenuGetDirection(void);
static U1 u1_s_AppMainMenuCheckMove(void);
static void vd_s_AppMainMenuWriteCursor(U1);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((MAINMENU_C_VERSION_MAJOR == MAINMENU_H_VERSION_MAJOR) && (MAINMENU_C_VERSION_MAJOR == MAINMENU_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((MAINMENU_C_VERSION_MINOR == MAINMENU_H_VERSION_MINOR) && (MAINMENU_C_VERSION_MINOR == MAINMENU_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((MAINMENU_C_VERSION_PATCH == MAINMENU_H_VERSION_PATCH) && (MAINMENU_C_VERSION_PATCH == MAINMENU_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppMainMenuInitTask
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize mainmenu screen
*
*******************************************************************************************************************************/
void vd_g_AppMainMenuInitTask(void) 
{
    u1_s_selection = (U1)0;
    u1_s_selection_state = (U1)MAINMENU_SYSCHK;
    u1_s_js_state = (U1)MAINMENU_JS_CENTER;
    u1_s_js_state_prev = (U1)MAINMENU_JS_CENTER;
    u2_s_js_wait_cntr = (U2)0;
    u1_s_refresh_scrn = (U1)0;

    vd_s_AppMainMenuInitScreen();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuInitScreen
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize mainmenu screen
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuInitScreen()
{
    swim_window_open(&mmwin, 480, 272, (COLOR_T *)FRAMEBUFFER_SECONDARY, 0, 0, 479, 271, 0, BLACK, WHITE, WHITE);
    swim_put_text_xy(&mmwin, (const char*)"System Check", MAINMENU_TEXT_X1, MAINMENU_TEXT_SYSCHK);
    swim_put_text_xy(&mmwin, (const char*)"Pong Demo", MAINMENU_TEXT_X1, MAINMENU_TEXT_PONG);
    swim_put_text_xy(&mmwin, (const char*)"Options", MAINMENU_TEXT_X1, MAINMENU_TEXT_OPT);
    vd_s_AppMainMenuWriteCursor(u1_s_selection_state);

    vd_g_IoLcdSetBuffer(FRAMEBUFFER_SECONDARY);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppMainMenuTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Handle Main Menu Tasks
*
*******************************************************************************************************************************/
void vd_g_AppMainMenuTask10ms(void) 
{
    //vd_s_AppMainMenuRefresh();
    vd_s_AppMainMenuUpdCursor();
    vd_s_AppMainMenuUpdSelection();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuRefresh
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Handle Main Menu Tasks
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuRefresh(void)
{
    if(u1_s_refresh_scrn >= (U1)MAINMENU_REFRESH_PERIOD)
    {
        swim_clear_screen(&mmwin, WHITE);
        swim_put_text_xy(&mmwin, (const char*)"System Check", MAINMENU_TEXT_X1, MAINMENU_TEXT_SYSCHK);
        swim_put_text_xy(&mmwin, (const char*)"Pong Demo", MAINMENU_TEXT_X1, MAINMENU_TEXT_PONG);
        swim_put_text_xy(&mmwin, (const char*)"Options", MAINMENU_TEXT_X1, MAINMENU_TEXT_OPT);
        vd_s_AppMainMenuWriteCursor(u1_s_selection_state);

        u1_s_refresh_scrn = (U1)0;
    }
    else
    {
        u1_s_refresh_scrn++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuUpdCursor
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Update Cursor Position
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuUpdCursor(void)
{
    U1 u1_t_move_curs;

    vd_s_AppMainMenuGetDirection();
    u1_t_move_curs = u1_s_AppMainMenuCheckMove();

    u1_s_js_state_prev = u1_s_js_state;

    if(u1_t_move_curs == (U1)MAINMENU_MOVE_CURS_OK)
    {
        if(u1_s_js_state == (U1)MAINMENU_JS_DOWN)
        {
            u1_s_selection_state++;
            if(u1_s_selection_state >= (U1)MAINMENU_NUMOF_ITEMS)
            {
                u1_s_selection_state = (U1)MAINMENU_OPT;
            }
            vd_s_AppMainMenuWriteCursor(u1_s_selection_state);
        }
        else if(u1_s_js_state == (U1)MAINMENU_JS_UP)
        {
            u1_s_selection_state--;
            if(u1_s_selection_state <= (U1)MAINMENU_NOSELECTION)
            {
                u1_s_selection_state = (U1)MAINMENU_SYSCHK;
            }
            vd_s_AppMainMenuWriteCursor(u1_s_selection_state);
        }
        else
        {
            /* Don't move cursor */
        }
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuGetDirection
*	Called By:				vd_s_AppMainMenuUpdCursor
*	Timing:					10ms
*	Description:			Write cursor
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuGetDirection(void)
{
    u1_s_js_state = u1_g_IoGetJsState((U1)JS_LEFTY);

    if(
       (u1_s_js_state == (U1)HALFDOWN) ||
       (u1_s_js_state == (U1)FULLDOWN)
       )
    {
        u1_s_js_state = (U1)MAINMENU_JS_DOWN;
    }
    else if(
            (u1_s_js_state == (U1)HALFUP) ||
            (u1_s_js_state == (U1)FULLUP)
            )
    {
        u1_s_js_state = (U1)MAINMENU_JS_UP;
    }
    else
    {
        u1_s_js_state = (U1)MAINMENU_JS_CENTER;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    u1_s_AppMainMenuCheckMove
*	Called By:				vd_s_AppMainMenuUpdCursor
*	Timing:					10ms
*	Description:			Write cursor
*
*******************************************************************************************************************************/
static U1 u1_s_AppMainMenuCheckMove(void)
{
    U1 u1_t_tmp;

    if(u1_s_js_state == u1_s_js_state_prev)
    {
        u2_s_js_wait_cntr++;
        u1_t_tmp = (U1)MAINMENU_MOVE_CURS_NOT_OK;

        if(u2_s_js_wait_cntr >= MAINMENU_CURSOR_LONG_PRESS)
        {
            u1_t_tmp = (U1)MAINMENU_MOVE_CURS_OK;
            u2_s_js_wait_cntr = (U2)0;
        }
    }
    else
    {
        u1_t_tmp = (U1)MAINMENU_MOVE_CURS_OK;
    }

    return u1_t_tmp;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuWriteCursor
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Write cursor
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuWriteCursor(U1 u1_a_state)
{
    /* Clear Cursor */
    swim_set_pen_color(&mmwin, WHITE);
    swim_set_fill_color(&mmwin, WHITE);
    swim_put_box(&mmwin, MAINMENU_CURSOR_X1, MAINMENU_CURSOR_SYSCHK, (MAINMENU_CURSOR_X1+MAINMENU_CURSOR_SIZE), (MAINMENU_CURSOR_OPT+MAINMENU_CURSOR_SIZE));

    /* Re-enable Cursor Color */
    swim_set_pen_color(&mmwin, MAINMENU_CURS_COLOR);
    swim_set_fill_color(&mmwin, MAINMENU_CURS_COLOR);

    switch(u1_a_state)
    {
        case MAINMENU_SYSCHK:
            swim_put_box(&mmwin, MAINMENU_CURSOR_X1, MAINMENU_CURSOR_SYSCHK, (MAINMENU_CURSOR_X1 + MAINMENU_CURSOR_SIZE), (MAINMENU_CURSOR_SYSCHK + MAINMENU_CURSOR_SIZE));
            break;

        case MAINMENU_PONG:
            swim_put_box(&mmwin, MAINMENU_CURSOR_X1, MAINMENU_CURSOR_PONG, (MAINMENU_CURSOR_X1 + MAINMENU_CURSOR_SIZE), (MAINMENU_CURSOR_PONG + MAINMENU_CURSOR_SIZE));
            break;

        case MAINMENU_OPT:
            swim_put_box(&mmwin, MAINMENU_CURSOR_X1, MAINMENU_CURSOR_OPT, (MAINMENU_CURSOR_X1 + MAINMENU_CURSOR_SIZE), (MAINMENU_CURSOR_OPT + MAINMENU_CURSOR_SIZE));
            break;

        default:
            swim_put_box(&mmwin, MAINMENU_CURSOR_X1, MAINMENU_CURSOR_SYSCHK, (MAINMENU_CURSOR_X1 + MAINMENU_CURSOR_SIZE), (MAINMENU_CURSOR_SYSCHK + MAINMENU_CURSOR_SIZE));
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppMainMenuUpdSelection
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Update Main Menu Selection Value
*
*******************************************************************************************************************************/
static void vd_s_AppMainMenuUpdSelection(void)
{
    U1 u1_t_btn_a;
    U1 u1_t_btn_start;

    u1_t_btn_a = u1_g_IoGetBtnA();
    u1_t_btn_start = u1_g_IoGetBtnStart();

    if(
       (u1_t_btn_a == (U1)IO_BUTTON_PRESSED)     ||
       (u1_t_btn_start == (U1)IO_BUTTON_PRESSED)
      )
    {
        u1_s_selection = u1_s_selection_state;
    }
    else
    {
        u1_s_selection = (U1)MAINMENU_NOSELECTION;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    u1_g_AppMainMenuGetSelection
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Return Main Menu Selection
*
*******************************************************************************************************************************/
U1 u1_g_AppMainMenuGetSelection(void)
{
    return u1_s_selection;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppMainMenuExit
*	Called By:				StateMgr
*	Timing:					10ms
*	Description:			Exit Main Menu Screen
*
*******************************************************************************************************************************/
void vd_g_AppMainMenuExit(void)
{
    swim_window_close(&mmwin);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author		Change Description
*	------	------		----------	------------------------------
*	1.0.0	5/2/2012	J. Nabozny	Created
*
*******************************************************************************************************************************/

