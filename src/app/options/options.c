/*******************************************************************************************************************************
*	
*	Filename: options.c
*	Rev Date: 5/2/2012
*
*	File Description:
*			Handle the gameplay for Pong
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "options.h"
#include "options_cfg.h"
#include "lpc_swim.h"
#include "iojs.h"
#include "iobtn.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define OPTIONS_C_VERSION_MAJOR		(1)
#define OPTIONS_C_VERSION_MINOR		(0)
#define OPTIONS_C_VERSION_PATCH		(0)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static SWIM_WINDOW_T optwin;
static U1 u1_s_opt_curs;
static U1 u1_s_opt_sel;
static U1 u1_s_js_dir;
static U1 u1_s_js_dir_prev;
static U2 u2_s_js_dir_cntr;
static U1 u1_s_opt_rfrsh;


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_AppOptionsInitScreen(void);
static void vd_s_AppOptionsRefresh(void);
static void vd_s_AppOptionsUpdCursor(void);
static void vd_s_AppOptionsGetDirection(void);
static U1 u1_s_AppOptionsCheckMove(void);
static void vd_s_AppOptionsUpdSelection(void);
static void vd_s_AppOptionsWriteCursor(U1);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((OPTIONS_C_VERSION_MAJOR == OPTIONS_H_VERSION_MAJOR) && (OPTIONS_C_VERSION_MAJOR == OPTIONS_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((OPTIONS_C_VERSION_MINOR == OPTIONS_H_VERSION_MINOR) && (OPTIONS_C_VERSION_MINOR == OPTIONS_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((OPTIONS_C_VERSION_PATCH == OPTIONS_H_VERSION_PATCH) && (OPTIONS_C_VERSION_PATCH == OPTIONS_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppOptionsInitTask
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize options screen
*
*******************************************************************************************************************************/
void vd_g_AppOptionsInitTask(void) 
{
    u1_s_opt_sel = (U1)OPTIONS_NOSELECTION;
    u1_s_opt_curs = (U1)OPTIONS_RTN;
    u1_s_js_dir = (U1)OPTIONS_JS_CENTER;
    u1_s_js_dir_prev = (U1)OPTIONS_JS_CENTER;
    u2_s_js_dir_cntr = (U2)0;
    u1_s_opt_rfrsh = (U1)0;

    vd_s_AppOptionsInitScreen();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppOptionsInitScreen
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize options screen
*
*******************************************************************************************************************************/
static void vd_s_AppOptionsInitScreen(void) 
{
    swim_window_open(&optwin, 480, 272, (COLOR_T *)FRAMEBUFFER_SECONDARY, 0, 0, 479, 271, 0, BLUE, WHITE, WHITE);
    swim_put_text_xy(&optwin, (const char*)"Return", OPTIONS_TEXT_X1, OPTIONS_TEXT_RTN);
    swim_put_text_xy(&optwin, (const char*)"Main Menu", OPTIONS_TEXT_X1, OPTIONS_TEXT_MM);
    vd_s_AppOptionsWriteCursor(u1_s_opt_curs);

    vd_g_IoLcdSetBuffer(FRAMEBUFFER_SECONDARY);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppOptionsTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Handles Options menu
*
*******************************************************************************************************************************/
void vd_g_AppOptionsTask10ms(void) 
{
    //vd_s_AppOptionsRefresh();
    vd_s_AppOptionsUpdCursor();
    vd_s_AppOptionsUpdSelection();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppOptionsRefresh
*	Called By:				vd_g_AppOptionsTask10ms
*	Timing:					10ms
*	Description:			Refresh Options Screen
*
*******************************************************************************************************************************/
static void vd_s_AppOptionsRefresh(void)
{
    if(u1_s_opt_rfrsh >= (U1)OPTIONS_REFRESH_PERIOD)
    {
        swim_clear_screen(&optwin, WHITE);
        swim_put_text_xy(&optwin, (const char*)"Return", OPTIONS_TEXT_X1, OPTIONS_TEXT_RTN);
        swim_put_text_xy(&optwin, (const char*)"Main Menu", OPTIONS_TEXT_X1, OPTIONS_TEXT_MM);
        vd_s_AppOptionsWriteCursor(u1_s_opt_curs);

        u1_s_opt_rfrsh = (U1)0;
    }
    else
    {
        u1_s_opt_rfrsh++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppOptionsUpdCursor
*	Called By:				vd_g_AppOptionsTask10ms
*	Timing:					10ms
*	Description:			Handles Options menu
*
*******************************************************************************************************************************/
static void vd_s_AppOptionsUpdCursor()
{
    U1 u1_t_move_curs;

    vd_s_AppOptionsGetDirection();
    u1_t_move_curs = u1_s_AppOptionsCheckMove();

    if(u1_t_move_curs == (U1)OPTIONS_MOVE_CURS_OK)
    {
        if(u1_s_js_dir == (U1)OPTIONS_JS_DOWN)
        {
            u1_s_opt_curs++;
            if(u1_s_opt_curs >= (U1)OPTIONS_NUMOF_ITEMS)
            {
                u1_s_opt_curs = (U1)OPTIONS_MM;
            }
            vd_s_AppOptionsWriteCursor(u1_s_opt_curs);
        }
        else if(u1_s_js_dir == (U1)OPTIONS_JS_UP)
        {
            u1_s_opt_curs--;
            if(u1_s_opt_curs <= (U1)OPTIONS_NOSELECTION)
            {
                u1_s_opt_curs = (U1)OPTIONS_RTN;
            }
            vd_s_AppOptionsWriteCursor(u1_s_opt_curs);
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
static void vd_s_AppOptionsGetDirection(void)
{
    u1_s_js_dir = u1_g_IoGetJsState((U1)JS_LEFTY);

    if(
       (u1_s_js_dir == (U1)HALFDOWN) ||
       (u1_s_js_dir == (U1)FULLDOWN)
       )
    {
        u1_s_js_dir = (U1)OPTIONS_JS_DOWN;
    }
    else if(
            (u1_s_js_dir == (U1)HALFUP) ||
            (u1_s_js_dir == (U1)FULLUP)
            )
    {
        u1_s_js_dir = (U1)OPTIONS_JS_UP;
    }
    else
    {
        u1_s_js_dir = (U1)OPTIONS_JS_CENTER;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    u1_s_AppMainMenuCheckMove
*	Called By:				vd_s_AppMainMenuUpdCursor
*	Timing:					10ms
*	Description:			Write cursor
*
*******************************************************************************************************************************/
static U1 u1_s_AppOptionsCheckMove(void)
{
    U1 u1_t_tmp;

    if(u1_s_js_dir == u1_s_js_dir_prev)
    {
        u2_s_js_dir_cntr++;
        u1_t_tmp = (U1)OPTIONS_MOVE_CURS_NOT_OK;

        if(u2_s_js_dir_cntr >= OPTIONS_CURSOR_LONG_PRESS)
        {
            u1_t_tmp = (U1)OPTIONS_MOVE_CURS_OK;
            u2_s_js_dir_cntr = (U2)0;
        }
    }
    else
    {
        u1_t_tmp = (U1)OPTIONS_MOVE_CURS_OK;
    }

    return u1_t_tmp;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppOptionsUpdSelection
*	Called By:				vd_g_AppOptionsTask10ms
*	Timing:					10ms
*	Description:			Handles Options menu
*
*******************************************************************************************************************************/
static void vd_s_AppOptionsUpdSelection()
{
    U1 u1_t_btn_a;
    U1 u1_t_btn_b;
    U1 u1_t_btn_start;

    u1_t_btn_a = u1_g_IoGetBtnA();
    u1_t_btn_b = u1_g_IoGetBtnB();
    u1_t_btn_start = u1_g_IoGetBtnStart();

    if(
       (u1_t_btn_a == (U1)IO_BUTTON_PRESSED)     ||
       (u1_t_btn_start == (U1)IO_BUTTON_PRESSED)
      )
    {
        u1_s_opt_sel = u1_s_opt_curs;
    }
    else if(u1_t_btn_b == (U1)IO_BUTTON_PRESSED)
    {
        u1_s_opt_sel = (U1)OPTIONS_RTN;
    }
    else
    {
        u1_s_opt_sel = (U1)OPTIONS_NOSELECTION;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppOptionsWriteCursor
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Set cursor position
*
*******************************************************************************************************************************/
static void vd_s_AppOptionsWriteCursor(U1 u1_a_state)
{
    /* Clear Cursor */
    swim_set_pen_color(&optwin, WHITE);
    swim_set_fill_color(&optwin, WHITE);
    swim_put_box(&optwin, OPTIONS_CURSOR_X1, OPTIONS_CURSOR_RET, (OPTIONS_CURSOR_X1 + OPTIONS_CURSOR_SIZE), (OPTIONS_CURSOR_MM + OPTIONS_CURSOR_SIZE));

    /* Re-enable Cursor Color */
    swim_set_pen_color(&optwin, OPTIONS_CURS_COLOR);
    swim_set_fill_color(&optwin, OPTIONS_CURS_COLOR);

    switch(u1_a_state)
    {
        case OPTIONS_RTN:
            swim_put_box(&optwin, OPTIONS_CURSOR_X1, OPTIONS_CURSOR_RET, (OPTIONS_CURSOR_X1 + OPTIONS_CURSOR_SIZE), (OPTIONS_CURSOR_RET + OPTIONS_CURSOR_SIZE));
            break;

        case OPTIONS_MM:
            swim_put_box(&optwin, OPTIONS_CURSOR_X1, OPTIONS_CURSOR_MM, (OPTIONS_CURSOR_X1 + OPTIONS_CURSOR_SIZE), (OPTIONS_CURSOR_MM + OPTIONS_CURSOR_SIZE));
            break;

        default:
            swim_put_box(&optwin, OPTIONS_CURSOR_X1, OPTIONS_CURSOR_RET, (OPTIONS_CURSOR_X1 + OPTIONS_CURSOR_SIZE), (OPTIONS_CURSOR_RET + OPTIONS_CURSOR_SIZE));
            break;
    }
}

/*******************************************************************************************************************************
*	Function Name:		    u1_g_AppOptionsGetSelection
*	Called By:				StateMgr
*	Timing:					10ms
*	Description:			Handles Options menu
*
*******************************************************************************************************************************/
U1 u1_g_AppOptionsGetSelection(void)
{
    return u1_s_opt_sel;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppOptionsExit
*	Called By:				StateMgr
*	Timing:					StateMgr
*	Description:			Exit the Options Menu
*
*******************************************************************************************************************************/
void vd_g_AppOptionsExit(void)
{
    swim_window_close(&optwin);
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

