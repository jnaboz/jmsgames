/*******************************************************************************************************************************
*	
*	Filename: splash.c
*	Rev Date: 2/7/2012
*
*	File Description:
*			Perform LCD Screen update for splash screen
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "splash.h"
#include "splash_cfg.h"
#include "lpc_swim.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define SPLASH_C_VERSION_MAJOR		(1)
#define SPLASH_C_VERSION_MINOR		(0)
#define SPLASH_C_VERSION_PATCH		(0)

#define SPLASH_FRAME_BUF            (0xA0000000)
#define APP_SPLASH_INIT_TIME        (5)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static U1 u1_s_init_flag;
static U1 u1_s_init_cntr;

static SWIM_WINDOW_T win1;


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_AppSplashInitScreen(void);

/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((SPLASH_C_VERSION_MAJOR == SPLASH_H_VERSION_MAJOR) && (SPLASH_C_VERSION_MAJOR == SPLASH_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((SPLASH_C_VERSION_MINOR == SPLASH_H_VERSION_MINOR) && (SPLASH_C_VERSION_MINOR == SPLASH_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((SPLASH_C_VERSION_PATCH == SPLASH_H_VERSION_PATCH) && (SPLASH_C_VERSION_PATCH == SPLASH_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppSplashInitTask
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize splash screen
*
*******************************************************************************************************************************/
void vd_g_AppSplashInitTask(void) 
{
    u1_s_init_flag = (U1)0;
    u1_s_init_cntr = (U1)0;
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppSplashTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to perform routine LCD screen tasks
*
*******************************************************************************************************************************/
void vd_g_AppSplashTask10ms(void) 
{
    if(u1_s_init_cntr >= (U1)APP_SPLASH_INIT_TIME)
    {
        if(u1_s_init_flag < (U1)4)
        {
            vd_g_IoLcdSetBuffer(FRAMEBUFFER_PRIMARY);
            vd_s_AppSplashInitScreen();
            u1_s_init_flag++;
        }
    }
    else
    {
        u1_s_init_cntr++;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppSplashInitScreen
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to perform routine LCD screen tasks
*
*******************************************************************************************************************************/
static void vd_s_AppSplashInitScreen(void)
{
    U2 u2_t_vt;
    U2 u2_t_hz;
    uint32_t u4_t_idx;

    switch(u1_s_init_flag)
    {
        case 0:                                             /* Init Black screen with Yellow Box Border */
            swim_window_open(&win1, 480, 272, (COLOR_T *)FRAMEBUFFER_PRIMARY, 0, 0, 479, 271, 0, WHITE, BLACK, WHITE);
            swim_put_box(&win1, 60, 30, 420, 40);           /* Draw Top Border */
            swim_put_box(&win1, 60, 230, 420, 240);         /* Draw Bottom Border */
            swim_put_box(&win1, 60, 30, 70, 240);           /* Draw Left Border */
            swim_put_box(&win1, 410, 30, 420, 240);         /* Draw Right Border */
            break;

        case 1:                                             /* Draw 'S' to the screen */
            swim_set_pen_color(&win1, GREEN);
            swim_set_fill_color(&win1, GREEN);
            swim_put_box(&win1, 90, 68, 150, 102);
            swim_put_box(&win1, 90, 102, 120, 136);
            swim_put_box(&win1, 120, 136, 150, 170);
            swim_put_box(&win1, 90, 170, 150, 204);
            break;

        case 2:                                             /* Draw 'M' to the screen */
            swim_set_pen_color(&win1, RED);
            swim_set_fill_color(&win1, RED);
            swim_put_box(&win1, 180, 68, 204, 204);
            swim_put_box(&win1, 204, 85, 228, 119);
            swim_put_box(&win1, 228, 102, 252, 136);
            swim_put_box(&win1, 252, 85, 276, 119);
            swim_put_box(&win1, 276, 68, 300, 204);
            break;

        case 3:                                             /* Draw 'J' to the screen */
            swim_set_pen_color(&win1, CYAN);
            swim_set_fill_color(&win1, CYAN);
            swim_put_box(&win1, 360, 68, 390, 170);
            swim_put_box(&win1, 330, 170, 390, 204);
            break;

        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppSplashExit
*	Called By:				StateMgr
*	Timing:					StateMgr
*	Description:			Close the Splash screen
*
*******************************************************************************************************************************/
void vd_g_AppSplashExit(void)
{
    swim_window_close(&win1);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author		Change Description
*	------	------		----------	------------------------------
*	1.0.0	2/7/2012	J. Nabozny	Created
*
*******************************************************************************************************************************/

