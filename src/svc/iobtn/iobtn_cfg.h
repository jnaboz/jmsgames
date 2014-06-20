/*******************************************************************************************************************************
*	
*	Filename: iobtn_cfg.h
*	Rev Date: 2/14/2012
*
*	File Description:
*			Configuration file for IO Buttons.
*
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOBTN_CFG_H_VERSION_MAJOR			(1)
#define IOBTN_CFG_H_VERSION_MINOR			(1)
#define IOBTN_CFG_H_VERSION_PATCH			(0)

#define IO_BUTTON_NUMOF_PINS				(7)
#define IO_NUMOF_DEBOUNCE					(3)


/*******************************************************************************************************************************
*			Global Variables
*******************************************************************************************************************************/
U1 u1_g_button_A;
U1 u1_g_button_B;
U1 u1_g_button_C;
U1 u1_g_button_D;
U1 u1_g_button_R;
U1 u1_g_button_L;
U1 u1_g_button_START;

U1 u1_g_button_A_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_B_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_C_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_D_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_R_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_L_array[IO_NUMOF_DEBOUNCE];
U1 u1_g_button_START_array[IO_NUMOF_DEBOUNCE];

U1 u1_g_index_A;
U1 u1_g_index_B;
U1 u1_g_index_C;
U1 u1_g_index_D;
U1 u1_g_index_R;
U1 u1_g_index_L;
U1 u1_g_index_START;


/*******************************************************************************************************************************
*			Constant Definitions
*******************************************************************************************************************************/
const st_IO_BTN_DBNC_Type st_tp_g_Buttons[IO_BUTTON_NUMOF_PINS] =
{
	&u1_g_button_A,
	(U1)GPIO_BUTTON_A_PORT,
	(U1)GPIO_BUTTON_A_PIN,
	(U4)GPIO_BUTTON_A_MASK,
	(U1)GPIO_BUTTON_A_FUNCTION,
	&u1_g_button_A_array[0],
	&u1_g_index_A,
	
	&u1_g_button_B,
	(U1)GPIO_BUTTON_B_PORT,
	(U1)GPIO_BUTTON_B_PIN,
	(U4)GPIO_BUTTON_B_MASK,
	(U1)GPIO_BUTTON_B_FUNCTION,
	&u1_g_button_B_array[0],
	&u1_g_index_B,
	
	&u1_g_button_C,
	(U1)GPIO_BUTTON_C_PORT,
	(U1)GPIO_BUTTON_C_PIN,
	(U4)GPIO_BUTTON_C_MASK,
	(U1)GPIO_BUTTON_C_FUNCTION,
	&u1_g_button_C_array[0],
	&u1_g_index_C,
	
	&u1_g_button_D,
	(U1)GPIO_BUTTON_D_PORT,
	(U1)GPIO_BUTTON_D_PIN,
	(U4)GPIO_BUTTON_D_MASK,
	(U1)GPIO_BUTTON_D_FUNCTION,
	&u1_g_button_D_array[0],
	&u1_g_index_D,
	
	&u1_g_button_R,
	(U1)GPIO_BUTTON_R_PORT,
	(U1)GPIO_BUTTON_R_PIN,
	(U4)GPIO_BUTTON_R_MASK,
	(U1)GPIO_BUTTON_R_FUNCTION,
	&u1_g_button_R_array[0],
	&u1_g_index_R,
	
	&u1_g_button_L,
	(U1)GPIO_BUTTON_L_PORT,
	(U1)GPIO_BUTTON_L_PIN,
	(U4)GPIO_BUTTON_L_MASK,
	(U1)GPIO_BUTTON_L_FUNCTION,
	&u1_g_button_L_array[0],
	&u1_g_index_L,
	
	&u1_g_button_START,
	(U1)GPIO_BUTTON_START_PORT,
	(U1)GPIO_BUTTON_START_PIN,
	(U4)GPIO_BUTTON_START_MASK,
	(U1)GPIO_BUTTON_START_FUNCTION,
	&u1_g_button_START_array[0],
	&u1_g_index_START
};


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	0			2/14/2012		J. Nabozny			Created
*	1.0.1		3/16/2012		J. Nabozny			Add in version control
*	1.1.0		3/23/2012		S. Cieslik			Add lookup table for button debouncing
*
*******************************************************************************************************************************/
