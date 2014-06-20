/***********************************************************************
 * File:   irq.c
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains Initialization of interrupt controller.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#include "irq.h"

/***********************************************************************
 *
 * Function: init_vic
 *
 * Purpose: Initialize VIC interrupt controller.
 *
 * Processing:
 *
 * Parameters: 	None
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void init_vic(void) 
{
    INT32U i = 0;
    INT32U *vect_addr, *vect_cntl;
   	
    /* initialize VIC*/
    VICIntEnClear = 0xFFFFFFFF;
    VICAddress = 0;
    VICIntSelect = 0;

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
        vect_addr = (INT32U *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
        vect_cntl = (INT32U *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
        *vect_addr = 0x0;
        *vect_cntl = 0xF;
    }
}

/***********************************************************************
 *
 * Function: install_irq
 *
 * Purpose: Install interrupt handler.
 *
 * Processing:
 *
 * Parameters: Interrupt number, interrupt handler address, interrupt priority
 *
 * Outputs: None
 *
 * Returns: return false if IntNum is out of range, otherwise true
 *
 **********************************************************************/
INT32U install_irq(INT32U IntNumber, void *HandlerAddr, INT32U Priority)
{
    INT32U *vect_addr;
    INT32U *vect_cntl;
      
    VICIntEnClear = 1 << IntNumber; /* Disable Interrupt */
    if ( IntNumber >= VIC_SIZE )
    {
        return FALSE;
    }
    else
    {
        /* find first un-assigned VIC address for the handler */
        vect_addr = (INT32U *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + IntNumber*4);
        vect_cntl = (INT32U *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + IntNumber*4);
        *vect_addr = (INT32U)HandlerAddr; /* set interrupt vector */
        *vect_cntl = Priority;
        VICIntEnable = 1 << IntNumber; /* Enable Interrupt */
        return TRUE;
    }
}
