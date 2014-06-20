/*******************************************************************************************************************************
*	
*	Filename: iospkr.c
*	Rev Date: 3/13/2012
*
*	File Description:
*			Perform IO Tasks here for audio speaker
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pinmacro.h"
#include "iospkr.h"
#include "iospkr_cfg.h"
#include "lpc177x_8x_pwm.h"
#include "lpc177x_8x_pinsel.h"

/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOSPKR_C_VERSION_MAJOR			(1)
#define IOSPKR_C_VERSION_MINOR			(0)
#define IOSPKR_C_VERSION_PATCH			(1)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/
static PWM_TIMERCFG_Type PWMCfgDat;
static PWM_MATCHCFG_Type PWMMatchCfgDat;


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/
static void vd_s_IoSpkrInitPwm(void);
static void vd_s_IoSpkrInitBase(void);
static void vd_s_IoSpkrInitChannel(void);


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOSPKR_C_VERSION_MAJOR == IOSPKR_H_VERSION_MAJOR) && (IOSPKR_C_VERSION_MAJOR == IOSPKR_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOSPKR_C_VERSION_MINOR == IOSPKR_H_VERSION_MINOR) && (IOSPKR_C_VERSION_MINOR == IOSPKR_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOSPKR_C_VERSION_PATCH == IOSPKR_H_VERSION_PATCH) && (IOSPKR_C_VERSION_PATCH == IOSPKR_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoSpkrInitTask
*	Called By:			vd_g_gameSystemInit
*	Timing:				Initialization
*	Description:		Task to initialize IO
*
*******************************************************************************************************************************/
void vd_g_IoSpkrInitTask(void) 
{
	vd_s_IoSpkrInitPwm();
	vd_s_IoSpkrInitBase();
	vd_s_IoSpkrInitChannel();
}


/*******************************************************************************************************************************
*	Function Name:		vd_s_IoSpkrInitPwm
*	Called By:			vd_g_IoSpkrInitTask
*	Timing:				Initialization
*	Description:		Task to initialize IO Speaker Pin Values
*
*******************************************************************************************************************************/
static void vd_s_IoSpkrInitPwm(void)
{
	PWMCfgDat.PrescaleOption = PWM_TIMER_PRESCALE_TICKVAL;
	PWMCfgDat.PrescaleValue = 1;
	PWM_Init(IO_PWM_PORT_NO, PWM_MODE_TIMER, (void *) &PWMCfgDat);
	
	PINSEL_ConfigPin(PWM_SPEAKER_PORT, PWM_SPEAKER_PIN, PWM_SPEAKER_FUNCTION);
}


/*******************************************************************************************************************************
*	Function Name:		vd_s_IoSpkrInitBase
*	Called By:			vd_g_IoSpkrInitTask
*	Timing:				Initialization
*	Description:		Task to initialize IO Speaker Base Values
*
*******************************************************************************************************************************/
static void vd_s_IoSpkrInitBase(void)
{
	PWM_MatchUpdate(IO_PWM_PORT_NO, IO_PWM_BASE_MATCH_CHNL, (U4)0, PWM_MATCH_UPDATE_NOW);
	
	/* PWM Timer/Counter will be reset when channel 0 matching
	* no interrupt when match
	* no stop when match */
	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = IO_PWM_BASE_MATCH_CHNL;
	PWMMatchCfgDat.ResetOnMatch = ENABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(IO_PWM_PORT_NO, &PWMMatchCfgDat);
}


/*******************************************************************************************************************************
*	Function Name:		vd_s_IoSpkrInitChannel
*	Called By:			vd_g_IoSpkrInitTask
*	Timing:				Initialization
*	Description:		Task to initialize IO Speaker Channel Values
*
*******************************************************************************************************************************/
static void vd_s_IoSpkrInitChannel(void)
{
	PWM_ChannelConfig(IO_PWM_PORT_NO, IO_PWM_PORT_CHNL, PWM_CHANNEL_SINGLE_EDGE);	/* Configure PWM Channel */
}


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoSpkrTask10ms
*	Called By:				Scheduler
*	Timing:					10ms
*	Description:			Called every 10ms to update values in the IO layer.
*
*******************************************************************************************************************************/
void vd_g_IoSpkrTask10ms(void) 
{
	
}


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoSpkrMatchUpd
*	Called By:				Application
*	Timing:					Application
*	Description:			Called by application to update match value
*
*******************************************************************************************************************************/
void vd_g_IoSpkrMatchUpd(U4 u4_a_note) 
{
	U4 u4_t_duty_cycle_50;

	u4_t_duty_cycle_50 = (u4_a_note / (U4)2);

	PWM_MatchUpdate(IO_PWM_PORT_NO, IO_PWM_BASE_MATCH_CHNL, u4_a_note, PWM_MATCH_UPDATE_NOW);
	
	/* PWM Timer/Counter will be reset when channel 0 matching
	* no interrupt when match
	* no stop when match */
	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = IO_PWM_BASE_MATCH_CHNL;
	PWMMatchCfgDat.ResetOnMatch = ENABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(IO_PWM_PORT_NO, &PWMMatchCfgDat);
	
	
	PWM_MatchUpdate(IO_PWM_PORT_NO, IO_PWM_PORT_CHNL, u4_t_duty_cycle_50, PWM_MATCH_UPDATE_NOW);
	
	/* Configure match option */
	PWMMatchCfgDat.IntOnMatch = DISABLE;
	PWMMatchCfgDat.MatchChannel = IO_PWM_PORT_CHNL;
	PWMMatchCfgDat.ResetOnMatch = DISABLE;
	PWMMatchCfgDat.StopOnMatch = DISABLE;
	PWM_ConfigMatch(IO_PWM_PORT_NO, &PWMMatchCfgDat);
	
	/* Enable PWM Channel Output */
	PWM_ChannelCmd(IO_PWM_PORT_NO, IO_PWM_PORT_CHNL, ENABLE);
	
	/* Reset and Start counter */
	PWM_ResetCounter(IO_PWM_PORT_NO);

	PWM_CounterCmd(IO_PWM_PORT_NO, ENABLE);
	
	/* Start PWM now */
	PWM_Cmd(IO_PWM_PORT_NO, ENABLE);
}


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoSpkrStopSound
*	Called By:				Application
*	Timing:					Application
*	Description:			Called by application to update match value
*
*******************************************************************************************************************************/
void vd_g_IoSpkrStopSound(void) 
{
	/* Enable PWM Channel Output */
	PWM_ChannelCmd(IO_PWM_PORT_NO, IO_PWM_PORT_CHNL, DISABLE);
	
	/* Reset and Start counter */
	PWM_ResetCounter(IO_PWM_PORT_NO);

	PWM_CounterCmd(IO_PWM_PORT_NO, DISABLE);
	
	/* Start PWM now */
	PWM_Cmd(IO_PWM_PORT_NO, DISABLE);
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author			Change Description
*	------	------		----------		------------------------------
*	0		3/13/2012	J. Nabozny		Created
*	1.0.0	3/16/2012	J. Nabozny		Add in version control
*	1.0.1	3/16/2012	J. Nabozny		Edit vd_g_IoSpkrMatchUpd to accept inputs from the application layer
*
*******************************************************************************************************************************/

