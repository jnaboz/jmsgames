/*******************************************************************************************************************************
*	
*	Filename: iojs_cfg.h
*	Rev Date: 2/14/2012
*
*	File Description:
*			Configuration file for IO Joystick.
*
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOJS_CFG_H_VERSION_MAJOR		(1)
#define IOJS_CFG_H_VERSION_MINOR		(2)
#define IOJS_CFG_H_VERSION_PATCH		(1)


#define IOJS_SPEED_VAL				    (8)		                                    /* Highest frequency read on ADC */
#define IOJS_NYQUIST_RATE_CFG			(5)	                                    /* Sample scale value (# * IOJS_SPEED_VAL) */
#define IOJS_SAMPLE_RATE			    (IOJS_SPEED_VAL * IOJS_NYQUIST_RATE_CFG)	/* Sample Rate */

#define IO_JS_NUM			        	(4)

#define IO_JOYSTICK_BUFFER_VAL			(0xA0)

#define LEFT_JOYSTICK_X_FULLLEFT		(0x000)
#define LEFT_JOYSTICK_X_HALFLEFT		(0x600)
#define LEFT_JOYSTICK_X_CENTER_LOW		(0x800)
#define LEFT_JOYSTICK_X_CENTER_HIGH		(0xA00)
#define LEFT_JOYSTICK_X_HALFRIGHT		(0xB50)
#define LEFT_JOYSTICK_X_FULLRIGHT		(0xFFF)

#define LEFT_JOYSTICK_Y_FULLDOWN		(0x000)
#define LEFT_JOYSTICK_Y_HALFDOWN		(0x600)
#define LEFT_JOYSTICK_Y_CENTER_LOW		(0x700)
#define LEFT_JOYSTICK_Y_CENTER_HIGH		(0x900)
#define LEFT_JOYSTICK_Y_HALFUP			(0xA00)
#define LEFT_JOYSTICK_Y_FULLUP			(0xFFF)

#define RIGHT_JOYSTICK_X_FULLLEFT		(0x000)
#define RIGHT_JOYSTICK_X_HALFLEFT		(0x700)
#define RIGHT_JOYSTICK_X_CENTER_LOW		(0x800)
#define RIGHT_JOYSTICK_X_CENTER_HIGH	(0x9A0)
#define RIGHT_JOYSTICK_X_HALFRIGHT		(0xB40)
#define RIGHT_JOYSTICK_X_FULLRIGHT		(0xFFF)

#define RIGHT_JOYSTICK_Y_FULLDOWN		(0x000)
#define RIGHT_JOYSTICK_Y_HALFDOWN		(0x600)
#define RIGHT_JOYSTICK_Y_CENTER_LOW		(0x7D0)
#define RIGHT_JOYSTICK_Y_CENTER_HIGH	(0x8F0)
#define RIGHT_JOYSTICK_Y_HALFUP			(0xA10)
#define RIGHT_JOYSTICK_Y_FULLUP			(0xFFF)


/*******************************************************************************************************************************
*			Global Variables
*******************************************************************************************************************************/
U1 u1_g_left_js_x;
U1 u1_g_left_js_y;
U1 u1_g_right_js_x;
U1 u1_g_right_js_y;


/*******************************************************************************************************************************
*			Constant Definitions
*******************************************************************************************************************************/
const st_IO_JS_HYST_Type st_tp_g_Joysticks[IO_JS_NUM] =
{
    (U1)ADC_JOYSTICK_LX_CHANNEL,
    (U1)ADC_JOYSTICK_LX_INTERRUPT,
    &u1_g_left_js_x,
    {
        {(U2)LEFT_JOYSTICK_X_FULLLEFT                                , (U2)(LEFT_JOYSTICK_X_HALFLEFT + IO_JOYSTICK_BUFFER_VAL)},
    	{(U2)(LEFT_JOYSTICK_X_HALFLEFT - IO_JOYSTICK_BUFFER_VAL)     , (U2)(LEFT_JOYSTICK_X_CENTER_LOW + IO_JOYSTICK_BUFFER_VAL)},
    	{(U2)(LEFT_JOYSTICK_X_CENTER_LOW - IO_JOYSTICK_BUFFER_VAL)   , (U2)(LEFT_JOYSTICK_X_CENTER_HIGH + IO_JOYSTICK_BUFFER_VAL)},
    	{(U2)(LEFT_JOYSTICK_X_CENTER_HIGH - IO_JOYSTICK_BUFFER_VAL)  , (U2)(LEFT_JOYSTICK_X_HALFRIGHT + IO_JOYSTICK_BUFFER_VAL)},
    	{(U2)(LEFT_JOYSTICK_X_HALFRIGHT - IO_JOYSTICK_BUFFER_VAL)    , (U2)LEFT_JOYSTICK_X_FULLRIGHT}
    },

    (U1)ADC_JOYSTICK_LY_CHANNEL,
    (U1)ADC_JOYSTICK_LY_INTERRUPT,
    &u1_g_left_js_y,
    {
        {(U2)LEFT_JOYSTICK_Y_FULLDOWN                                , (U2)(LEFT_JOYSTICK_Y_HALFDOWN + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(LEFT_JOYSTICK_Y_HALFDOWN - IO_JOYSTICK_BUFFER_VAL)     , (U2)(LEFT_JOYSTICK_Y_CENTER_LOW + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(LEFT_JOYSTICK_Y_CENTER_LOW - IO_JOYSTICK_BUFFER_VAL)   , (U2)(LEFT_JOYSTICK_Y_CENTER_HIGH + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(LEFT_JOYSTICK_Y_CENTER_HIGH - IO_JOYSTICK_BUFFER_VAL)  , (U2)(LEFT_JOYSTICK_Y_HALFUP + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(LEFT_JOYSTICK_Y_HALFUP - IO_JOYSTICK_BUFFER_VAL)       , (U2)LEFT_JOYSTICK_Y_FULLUP}
    },

    (U1)ADC_JOYSTICK_RX_CHANNEL,
    (U1)ADC_JOYSTICK_RX_INTERRUPT,
    &u1_g_right_js_x,
    {
        {(U2)RIGHT_JOYSTICK_X_FULLLEFT                               , (U2)(RIGHT_JOYSTICK_X_HALFLEFT + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_X_HALFLEFT - IO_JOYSTICK_BUFFER_VAL)    , (U2)(RIGHT_JOYSTICK_X_CENTER_LOW + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_X_CENTER_LOW - IO_JOYSTICK_BUFFER_VAL)  , (U2)(RIGHT_JOYSTICK_X_CENTER_HIGH + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_X_CENTER_HIGH - IO_JOYSTICK_BUFFER_VAL) , (U2)(RIGHT_JOYSTICK_X_HALFRIGHT + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_X_HALFRIGHT - IO_JOYSTICK_BUFFER_VAL)   , (U2)RIGHT_JOYSTICK_X_FULLRIGHT}
    },

    (U1)ADC_JOYSTICK_RY_CHANNEL,
    (U1)ADC_JOYSTICK_RY_INTERRUPT,
    &u1_g_right_js_y,
    {
        {(U2)RIGHT_JOYSTICK_Y_FULLDOWN                               , (U2)(RIGHT_JOYSTICK_Y_HALFDOWN + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_Y_HALFDOWN - IO_JOYSTICK_BUFFER_VAL)    , (U2)(RIGHT_JOYSTICK_Y_CENTER_LOW + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_Y_CENTER_LOW - IO_JOYSTICK_BUFFER_VAL)  , (U2)(RIGHT_JOYSTICK_Y_CENTER_HIGH + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_Y_CENTER_HIGH - IO_JOYSTICK_BUFFER_VAL) , (U2)(RIGHT_JOYSTICK_Y_HALFUP + IO_JOYSTICK_BUFFER_VAL)},
        {(U2)(RIGHT_JOYSTICK_Y_HALFUP - IO_JOYSTICK_BUFFER_VAL)      , (U2)RIGHT_JOYSTICK_Y_FULLUP}
    }
};

	
/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.1.1		3/16/2012		J. Nabozny			Add in version control
*   1.1.2		3/30/2012		J. Nabozny			Add in new sample rate for ADC conversion
*   1.2.0       4/9/2012        S. Cieslik          Add in code for hysteresis on joysticks
*   1.2.1       5/3/2012        J. Nabozny          Remove unused code
*
*******************************************************************************************************************************/
