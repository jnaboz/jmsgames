/***********************************************************************
 * File:   irq.h
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

#ifndef __IRQ_H 
#define __IRQ_H

//#include <iolpc2468.h>
#include "data_types.h"

#define HIGHEST_PRIORITY	0x01
#define LOWEST_PRIORITY		0x0F

#define VIC_CLCDC               16 /* EINT2 and CLCDC share VIC slot */

#define VIC_SIZE		32

#define VIC_BASE_ADDR	0xFFFFF000
#define VECT_ADDR_INDEX	0x100
#define VECT_CNTL_INDEX 0x200

void init_vic(void);
INT32U install_irq(INT32U IntNumber, void *HandlerAddr, INT32U Priority);

#endif /* __IRQ_H */
