/*******************************************************************************************************************************
*	
*	Filename: syscheck.c
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
#include "syscheck.h"
#include "syscheck_cfg.h"
#include "lpc_swim.h"
#include "iobtn.h"
#include "iolcd.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define SYSCHECK_C_VERSION_MAJOR		(1)
#define SYSCHECK_C_VERSION_MINOR		(0)
#define SYSCHECK_C_VERSION_PATCH		(0)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static SWIM_WINDOW_T syswin;
static U1 u1_s_sound_state;
static U4 u4_s_spkr_cntr;
static U4 u4_s_curr_note;

/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_AppSysCheckUpdBgnd(void);
static void vd_s_AppSysCheckUpdAudio(void);
static void vd_s_AppSysCheckUpdAudioState(void);
static void vd_s_AppSpkrMatchUpd(U1);
static void vd_s_AppSysCheckBeginSound(U1);
static void vd_s_AppSysCheckStartAudio(void);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((SYSCHECK_C_VERSION_MAJOR == SYSCHECK_H_VERSION_MAJOR) && (SYSCHECK_C_VERSION_MAJOR == SYSCHECK_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((SYSCHECK_C_VERSION_MINOR == SYSCHECK_H_VERSION_MINOR) && (SYSCHECK_C_VERSION_MINOR == SYSCHECK_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((SYSCHECK_C_VERSION_PATCH == SYSCHECK_H_VERSION_PATCH) && (SYSCHECK_C_VERSION_PATCH == SYSCHECK_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppSysCheckInitTask
*	Called By:				Initialization
*	Timing:					Initialization
*	Description:			Called to initialize syscheck screen
*
*******************************************************************************************************************************/
void vd_g_AppSysCheckInitTask(void) 
{
    u1_s_sound_state = (U1)SYSCHK_NO_SOUND;
    swim_window_open(&syswin, 480, 272, (COLOR_T *)FRAMEBUFFER_PRIMARY, 0, 0, 479, 271, 0, WHITE, BLACK, BLACK);
    vd_g_IoLcdSetBuffer(FRAMEBUFFER_PRIMARY);
}


/*******************************************************************************************************************************
*	Function Name:		    vd_g_AppSysCheckTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Handles Syscheck Screen
*
*******************************************************************************************************************************/
void vd_g_AppSysCheckTask10ms(void) 
{
    vd_s_AppSysCheckUpdBgnd();
    vd_s_AppSysCheckUpdAudio();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppSysCheckUpdBgnd
*	Called By:				vd_g_AppSysCheckTask10ms
*	Timing:					10ms
*	Description:			Update Syscheck Background
*
*******************************************************************************************************************************/
static void vd_s_AppSysCheckUpdBgnd(void)
{
    U1 u1_t_btn;

    u1_t_btn = u1_g_IoGetBtnA();
    if(!(u1_t_btn))
    {
        swim_clear_screen(&syswin, GREEN);
    }


    u1_t_btn = u1_g_IoGetBtnB();
    if(!(u1_t_btn))
    {
        swim_clear_screen(&syswin, RED);
    }


    u1_t_btn = u1_g_IoGetBtnC();
    if(!(u1_t_btn))
    {
        swim_clear_screen(&syswin, YELLOW);
    }


    u1_t_btn = u1_g_IoGetBtnD();
    if(!(u1_t_btn))
    {
        swim_clear_screen(&syswin, BLUE);
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppSysCheckUpdAudio
*	Called By:				vd_g_AppSysCheckTask10ms
*	Timing:					10ms
*	Description:			Update Audio
*
*******************************************************************************************************************************/
static void vd_s_AppSysCheckUpdAudio(void)
{
    vd_s_AppSysCheckUpdAudioState();
    vd_s_AppSysCheckStartAudio();
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppSysCheckUpdAudioState
*	Called By:				vd_s_AppSysCheckUpdAudio
*	Timing:					10ms
*	Description:			Update Audio State
*
*******************************************************************************************************************************/
static void vd_s_AppSysCheckUpdAudioState(void)
{
    U1 u1_t_btn;

    if(u1_s_sound_state == (U1)SYSCHK_NO_SOUND)
    {
        u1_t_btn = u1_g_IoGetBtnR();
        if(!(u1_t_btn))
        {
            u1_s_sound_state = (U1)SYSCHK_R_SOUND;
        }

        u1_t_btn = u1_g_IoGetBtnL();
        if(!(u1_t_btn))
        {
            u1_s_sound_state = (U1)SYSCHK_L_SOUND;
        }
		
		vd_s_AppSysCheckBeginSound(u1_s_sound_state);
    }
}


/*******************************************************************************************************************************
*	Function Name:		    vd_s_AppSysCheckStartAudio
*	Called By:				vd_s_AppSysCheckUpdAudio
*	Timing:					10ms
*	Description:			Update Audio State
*
*******************************************************************************************************************************/
static void vd_s_AppSysCheckStartAudio(void)
{
    switch(u1_s_sound_state)
    {
        case SYSCHK_R_SOUND:
            if(u4_s_spkr_cntr < st_tp_g_rt_spkr[(u4_s_curr_note-(U4)1)].u4_note_length)
    		{
    			u4_s_spkr_cntr++;
    		}
    		else
    		{
    			if(u4_s_curr_note == (U4)SYSCHK_RT_SPKR_NUMOF_NOTES)
    			{
                    vd_g_AppSysCheckStopSound();
    			}
    			else
    			{
    				vd_s_AppSpkrMatchUpd(SYSCHK_R_SOUND);
    			}
    			u4_s_spkr_cntr = (U4)OFF;
    		}
            break;

        case SYSCHK_L_SOUND:
            if(u4_s_spkr_cntr < st_tp_g_lt_spkr[(u4_s_curr_note-(U4)1)].u4_note_length)
    		{
    			u4_s_spkr_cntr++;
    		}
    		else
    		{
    			if(u4_s_curr_note == (U4)SYSCHK_LT_SPKR_NUMOF_NOTES)
    			{
    				vd_g_AppSysCheckStopSound();
    			}
    			else
    			{
    				vd_s_AppSpkrMatchUpd(SYSCHK_L_SOUND);
    			}
    			u4_s_spkr_cntr = (U4)OFF;
    		}
            break;

        case SYSCHK_NO_SOUND:
        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:			vd_s_AppSpkrStartSound
*	Called By:				vd_g_AppSpkrTask10ms
*	Timing:					20ms
*	Description:			Application to determine what new match value should be
*
*******************************************************************************************************************************/
static void vd_s_AppSysCheckBeginSound(U1 u1_a_state)
{
    vd_s_AppSpkrMatchUpd(u1_a_state);
}


/*******************************************************************************************************************************
*	Function Name:			vd_s_AppSpkrMatchUpd
*	Called By:				vd_g_AppSpkrTask10ms
*	Timing:					20ms
*	Description:			Application to determine what new match value should be
*
*******************************************************************************************************************************/
static void vd_s_AppSpkrMatchUpd(U1 u1_a_state) 
{
    switch(u1_a_state)
    {
        case SYSCHK_R_SOUND:
            vd_g_IoSpkrMatchUpd(st_tp_g_rt_spkr[u4_s_curr_note].u4_note);
            u4_s_curr_note++;
            break;

        case SYSCHK_L_SOUND:
            vd_g_IoSpkrMatchUpd(st_tp_g_lt_spkr[u4_s_curr_note].u4_note);
            u4_s_curr_note++;
            break;

        default:
            break;
    }
}


/*******************************************************************************************************************************
*	Function Name:			vd_s_AppSysCheckStopSound
*	Called By:				vd_s_AppSysCheckStartAudio
*	Timing:					20ms
*	Description:			Application to determine what new match value should be
*
*******************************************************************************************************************************/
void vd_g_AppSysCheckStopSound(void)
{
    u4_s_curr_note = (U4)0;
    u1_s_sound_state = (U1)SYSCHK_NO_SOUND;
    vd_g_IoSpkrStopSound();
}


/*******************************************************************************************************************************
*	Function Name:			u1_g_AppSysCheckPause
*	Called By:				vd_g_AppStateMgrTask10ms
*	Timing:					20ms
*	Description:			Application to determine what new match value should be
*
*******************************************************************************************************************************/
U1 u1_g_AppSysCheckPause(void)
{
    U1 u1_t_btn;

    u1_t_btn = u1_g_IoGetBtnStart();
    
    if(u1_t_btn == (U1)IO_BUTTON_PRESSED)
    {
        return SYSCHK_PAUSE;
    }
    else
    {
        return SYSCHK_NO_PAUSE;
    }
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

