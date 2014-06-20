/***********************************************************************
 * File:   low_level_init.h
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This file contains low level initialization of the LPC2478.
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#ifndef __LOW_LEVEL_INIT_H 
#define __LOW_LEVEL_INIT_H

//#include "lpc2478.h"

/***********************************************************************
 *
 * Main Osc.    CCLKCFG    Fcco    Fcclk    M   N
 *    12MHz     3          288MHz  72.0MHz  12  1
 *    12MHz     5          360MHz  60.0MHz  15  1
 *    12MHz     4          288MHz  57.6MHz  12  1
 *    12MHz     9          288MHz  28.8MHz  12  1
 *    12MHz     24         288MHz  11.52MHz 12  1
 *    12MHz     49         288MHz  5.76MHz  12  1
 **********************************************************************/
#define PLL_MValue 11
//#define PLL_MValue 14
//#define PLL_MValue 11
#define PLL_NValue 0
#define CCLKDivValue 3
//#define CCLKDivValue 5
//#define CCLKDivValue 4
//#define CCLKDivValue 9
//#define CCLKDivValue 24
//#define CCLKDivValue 49

void configure_pll(void);
void configure_emc(void);
void low_level_init(void);

#endif /* __LOW_LEVEL_INIT_H */
