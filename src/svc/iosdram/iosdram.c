/*******************************************************************************************************************************
*	
*	Filename: iosdram.c
*	Rev Date: 3/28/2012
*
*	File Description:
*			Perform SDRAM Tasks Here
*
*******************************************************************************************************************************/

/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/
#include "lpc_types.h"
#include "vardef.h"
#include "pinmacro.h"
#include "iosdram.h"
#include "iosdram_cfg.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_timer.h"
#include "system_LPC177x_8x.h"
#include "lpc_colors.h"


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOSDRAM_C_VERSION_MAJOR			(1)
#define IOSDRAM_C_VERSION_MINOR			(0)
#define IOSDRAM_C_VERSION_PATCH			(2)


/*******************************************************************************************************************************
*			Static Variables
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Static Function Prototypes
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Function Definitions
*******************************************************************************************************************************/

/* Check version numbers */
#if(!((IOSDRAM_C_VERSION_MAJOR == IOSDRAM_H_VERSION_MAJOR) && (IOSDRAM_C_VERSION_MAJOR == IOSDRAM_CFG_H_VERSION_MAJOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOSDRAM_C_VERSION_MINOR == IOSDRAM_H_VERSION_MINOR) && (IOSDRAM_C_VERSION_MINOR == IOSDRAM_CFG_H_VERSION_MINOR)))
#error "Software Version Numbers do not match"
#endif

#if(!((IOSDRAM_C_VERSION_PATCH == IOSDRAM_H_VERSION_PATCH) && (IOSDRAM_C_VERSION_PATCH == IOSDRAM_CFG_H_VERSION_PATCH)))
#error "Software Version Numbers do not match"
#endif


/*******************************************************************************************************************************
*	Function Name:		vd_g_IoSdramInitTask
*	Called By:			vd_g_IoMgrInitTask
*	Timing:				Initialization
*	Description:		Task to initialize IO
*
*******************************************************************************************************************************/
void vd_g_IoSdramInitTask(void) 
{
    uint32_t Temp;
    uint32_t u2_t_idx;
	uint32_t u4_t_idx;

#ifdef WRITE_16
  	volatile uint16_t *short_wr_ptr;
#else
    volatile uint32_t *short_wr_ptr;
#endif

	/* Initialize EMC */
	EMC_Init();
	
	//Configure memory layout, but MUST DISABLE BUFFERs during configuration
				
    LPC_EMC->DynamicConfig0 = (U4)SDRAM_MEM_CONFIG_VAL;     /* 16Mbit, 1Mx16, 2 banks, row=11, column=8 */

	/*Configure timing for  ISSI SDRAM IC42S16100E */

	//Timing for 80MHz Bus
    LPC_EMC->DynamicRasCas0    = (U4)DYNAMIC_RAS_CAS; 		        /* Dynamic Ras Cas Latency Register */
    LPC_EMC->DynamicReadConfig = (U4)DYNAMIC_READ_CONFIG; 	        /* Dynamic Read Config Register     */
	LPC_EMC->DynamicRP         = (U4)DYNAMIC_TRP_CONFIG;	        /* Dynamic tRP Config Register      */
	LPC_EMC->DynamicRAS        = (U4)DYNAMIC_TRAS_CONFIG;	        /* Dynamic tRAS Config Register     */
	LPC_EMC->DynamicSREX       = (U4)DYNAMIC_TSREX_CONFIG; 	        /* Dynamic tSREX Config Register    */
	LPC_EMC->DynamicAPR        = (U4)DYNAMIC_TAPR_CONFIG; 	        /* Dynamic tAPR Config Register     */
	LPC_EMC->DynamicDAL        = (U4)DYNAMIC_TDAL_CONFIG; 	        /* Dynamic tDAL Config Register     */
	LPC_EMC->DynamicWR         = (U4)DYNAMIC_TWR_CONFIG; 	        /* Dynamic tWR Config Register      */
	LPC_EMC->DynamicRC         = (U4)DYNAMIC_TRC_CONFIG; 			/* Dynamic tRC Config Register      */
	LPC_EMC->DynamicRFC        = (U4)DYNAMIC_TRFC_CONFIG; 			/* Dynamic tRFC Config Register     */
	LPC_EMC->DynamicXSR        = (U4)DYNAMIC_TXSR_CONFIG; 			/* Dynamic tXSR Config Register     */
	LPC_EMC->DynamicRRD        = (U4)DYNAMIC_TRRD_CONFIG; 			/* Dynamic tRRD Config Register     */
	LPC_EMC->DynamicMRD        = (U4)DYNAMIC_TMRD_CONFIG; 			/* Dynamic tMRD Config Register     */

    //for(u4_t_idx = (U4)0; u4_t_idx < (U4)0x1F40; u4_t_idx++);	                    /* wait ~100usec */

    //LPC_EMC->DynamicControl    = (U4)(SDRAM_NOP_COMMAND | SDRAM_CLK_CKE_HIGH);      /* Issue NOP command */

    for(u4_t_idx = (U4)0; u4_t_idx < (U4)0x12BF; u4_t_idx++);	                    /* wait ~200usec */
	
    LPC_EMC->DynamicControl    = (U4)(SDRAM_PALL_COMMAND | SDRAM_CLK_CKE_HIGH);     /* Issue PALL command */
    LPC_EMC->DynamicRefresh    = 0x00000001; 				                        /* ( n * 16 ) -> 16 clock cycles */

	for(u4_t_idx = (U4)0; u4_t_idx < (U4)0x80; u4_t_idx++);	                        /* wait 128 AHB clock cycles */

    LPC_EMC->DynamicRefresh    = (U4)DYNAMIC_REFRESH_RATE; 		                    /* 1248 clock cycles -> 15.6uS at 80MHz <= 15.625uS ( 32ms / 2048 row ) */
	
	for(u4_t_idx = (U4)0; u4_t_idx < 0x80; u4_t_idx++);	                            /* wait 128 AHB clock cycles */
	
    LPC_EMC->DynamicControl    = (U4)(SDRAM_MODE_COMMAND | SDRAM_CLK_CKE_HIGH); 	/* Issue MODE command */

    Temp = *((volatile uint32_t *)(SDRAM_BASE_ADDR | (U4)SDRAM_MODE_COMMAND_VAL));  /* Set MODE on SDRAM chip with READ cycle */
	
	for(u4_t_idx = (U4)0; u4_t_idx < 0x80; u4_t_idx++);	                            /* wait 128 AHB clock cycles */
	
    LPC_EMC->DynamicControl    = (U4)SDRAM_NORMAL_COMMAND; 	/* Issue NORMAL command */

	LPC_EMC->DynamicConfig0 |= (U4)SDRAM_BUFFER_ENABLE; 					        /* Re-Enable Buffers */

    for(u4_t_idx = (U4)0; u4_t_idx < 0x80; u4_t_idx++);                             /* Wait 128 AHB clock cycles */


    /**********************/
    /* Clear RAM Location */
    /**********************/

#ifdef WRITE_16
    short_wr_ptr = (uint16_t *)SDRAM_BASE_ADDR;                                     /* Set Pointer to beginning of RAM */
    for (u4_t_idx = (U4)0; u4_t_idx < (SDRAM_SIZE_U2/2); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U2)GREEN;
        *short_wr_ptr++ = (U2)GREEN;
    }
#else
    short_wr_ptr = (uint32_t *)SDRAM_BASE_ADDR;
    for (u4_t_idx = (U4)0; u4_t_idx < (SDRAM_SIZE_U4/4); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U4)0x00000000;
    }
    /*for (u4_t_idx = (U4)0; u4_t_idx < ((SDRAM_SIZE_U4/8)); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U4)0xFFFFFFFF;
    }
    for (u4_t_idx = (U4)0; u4_t_idx < ((SDRAM_SIZE_U4/16)); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U4)0xFFFFFFFF;
    }
    for (u4_t_idx = (U4)0; u4_t_idx < ((SDRAM_SIZE_U4/16)); u4_t_idx++ )
    {
        *short_wr_ptr++ = (U4)0xFFFFFFFF;
    }*/
#endif
}


/*******************************************************************************************************************************
*	Function Name:			vd_g_IoSdramTask10ms
*	Called By:				vd_g_IoMgrTask10ms
*	Timing:					10ms
*	Description:			Called every 10ms to perform routine SDRAM tasks.
*
*******************************************************************************************************************************/
void vd_g_IoSdramTask10ms(void) 
{
    /* No tasks to perform */
}


/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev		Date		Author			Change Description
*	------	------		----------		------------------------------
*	1.0.0	3/28/2012	J. Nabozny		Created
*   1.0.1	4/1/2012	J. Nabozny		Finish initialization
*   1.0.2   4/16/2012   J. Nabozny      Edit Initialization to use macros instead of magic numbers
*
*******************************************************************************************************************************/

