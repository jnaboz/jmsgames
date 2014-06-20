/***********************************************************************
 * File:   low_level_init.c
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

#include "irq.h"
#include "low_level_init.h"

/***********************************************************************
 *
 * Function: delayMs
 *
 * Purpose: Start the timer delay in micro seconds until elapsed.
 *
 * Processing:
 *
 * Parameters: 	Delay value in micro second
 *
 * Outputs: None
 *
 * Returns: None
 *
 **********************************************************************/
void delayMs(INT32U delayInMs)
{
    T1TCR = 0x02; /* reset timer */
    T1PR  = 0x00; /* set prescaler to zero */
    T1MR0 = delayInMs * (18000000 / 1000); /* PCLK is 1/4 CCLK */ 
//    T1MR0 = delayInMs * (15000000 / 1000); /* PCLK is 1/4 CCLK */ 
//    T1MR0 = delayInMs * (14400000 / 1000); /* PCLK is 1/4 CCLK */ 
//    T1MR0 = delayInMs * (7200000 / 1000); /* PCLK is 1/4 CCLK */ 
//    T1MR0 = delayInMs * (2880000 / 1000); /* PCLK is 1/4 CCLK */ 
//    T1MR0 = delayInMs * (1440000 / 1000); /* PCLK is 1/4 CCLK */ 
    T1IR  = 0xFF; /* reset all interrrupts */
    T1MCR = 0x04; /* stop timer on match */
    T1TCR = 0x01; /* start timer */
  
    /* wait until delay time has elapsed */
    while (T1TCR & 0x01);
}

/***********************************************************************
 *
 * Function: configure_pll
 *
 * Purpose: switching to main OSC from IRC.
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
void configure_pll(void)
{
    INT16U MValue, NValue;

    if (PLLSTAT_bit.PLLC)
    {
        PLLCON_bit.PLLC = 0x0; /* PLL disconnected */
        PLLFEED = 0xaa;
        PLLFEED = 0x55;
    }

    PLLCON_bit.PLLE = 0x0; /* PLL disabled */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    
    SCS_bit.OSCEN = 0x1; /* Enable main OSC */
    while(!SCS_bit.OSCSTAT); /* Wait until main OSC is usable */

    CLKSRCSEL_bit.CLKSRC = 0x1;	/* select main OSC, 12MHz, as the PLL clock source */

    PLLCFG_bit.MSEL = PLL_MValue;
    PLLCFG_bit.NSEL = PLL_NValue;
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
      
    PLLCON_bit.PLLE = 0x1; /* PLL enabled */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;

    CCLKCFG_bit.CCLKSEL = CCLKDivValue;	/* Set clock divider */

    while (!PLLSTAT_bit.PLOCK);	/* Check lock bit status */
    
    MValue = PLLSTAT_bit.MSEL;
    NValue = PLLSTAT_bit.NSEL;
    while ((MValue != PLL_MValue) && (NValue != PLL_NValue));

    PLLCON_bit.PLLC = 0x1; /* PLL connected */
    PLLFEED = 0xaa;
    PLLFEED = 0x55;
    while (!PLLSTAT_bit.PLLC); /* Check connect bit status */
}


/***********************************************************************
 *
 * Function: configure_emc
 *
 * Purpose: configure emc.
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
 #ifdef _EMC_ENABLE
void configure_emc(void)
{
    INT16U dummy;

    PINSEL5_bit.P2_16 = 0x1; /* enable /CAS */
    PINSEL5_bit.P2_17 = 0x1; /* enable /RAS */
    PINSEL5_bit.P2_18 = 0x1; /* enable CLKOUT0 */
    PINSEL5_bit.P2_20 = 0x1; /* enable /DYCS0 */
    PINSEL5_bit.P2_24 = 0x1; /* enable CKEOUT0 */
    PINSEL5_bit.P2_28 = 0x1; /* enable DQMOUT0 */
    PINSEL5_bit.P2_29 = 0x1; /* enable DQMOUT1 */

    PINSEL6_bit.P3_0 = 0x1; /* enable D0 */
    PINSEL6_bit.P3_1 = 0x1; /* enable D1 */
    PINSEL6_bit.P3_2 = 0x1; /* enable D2 */
    PINSEL6_bit.P3_3 = 0x1; /* enable D3 */
    PINSEL6_bit.P3_4 = 0x1; /* enable D4 */
    PINSEL6_bit.P3_5 = 0x1; /* enable D5 */
    PINSEL6_bit.P3_6 = 0x1; /* enable D6 */
    PINSEL6_bit.P3_7 = 0x1; /* enable D7 */
    PINSEL6_bit.P3_8 = 0x1; /* enable D8 */
    PINSEL6_bit.P3_9 = 0x1; /* enable D9 */
    PINSEL6_bit.P3_10 = 0x1; /* enable D10 */
    PINSEL6_bit.P3_11 = 0x1; /* enable D11 */
    PINSEL6_bit.P3_12 = 0x1; /* enable D12 */
    PINSEL6_bit.P3_13 = 0x1; /* enable D13 */
    PINSEL6_bit.P3_14 = 0x1; /* enable D14 */
    PINSEL6_bit.P3_15 = 0x1; /* enable D15 */

    PINSEL7_bit.P3_16 = 0x1; /* enable D16 */
    PINSEL7_bit.P3_17 = 0x1; /* enable D17 */
    PINSEL7_bit.P3_18 = 0x1; /* enable D18 */
    PINSEL7_bit.P3_19 = 0x1; /* enable D19 */
    PINSEL7_bit.P3_20 = 0x1; /* enable D20 */
    PINSEL7_bit.P3_21 = 0x1; /* enable D21 */
    PINSEL7_bit.P3_22 = 0x1; /* enable D22 */
    PINSEL7_bit.P3_23 = 0x1; /* enable D23 */
    PINSEL7_bit.P3_24 = 0x1; /* enable D24 */
    PINSEL7_bit.P3_25 = 0x1; /* enable D25 */
    PINSEL7_bit.P3_26 = 0x1; /* enable D26 */
    PINSEL7_bit.P3_27 = 0x1; /* enable D27 */
    PINSEL7_bit.P3_28 = 0x1; /* enable D28 */
    PINSEL7_bit.P3_29 = 0x1; /* enable D29 */
    PINSEL7_bit.P3_30 = 0x1; /* enable D30 */
    PINSEL7_bit.P3_31 = 0x1; /* enable D31 */

    PINSEL8_bit.P4_0 = 0x1; /* enable A0 */
    PINSEL8_bit.P4_1 = 0x1; /* enable A1 */
    PINSEL8_bit.P4_2 = 0x1; /* enable A2 */
    PINSEL8_bit.P4_3 = 0x1; /* enable A3 */
    PINSEL8_bit.P4_4 = 0x1; /* enable A4 */
    PINSEL8_bit.P4_5 = 0x1; /* enable A5 */
    PINSEL8_bit.P4_6 = 0x1; /* enable A6 */
    PINSEL8_bit.P4_7 = 0x1; /* enable A7 */
    PINSEL8_bit.P4_8 = 0x1; /* enable A8 */
    PINSEL8_bit.P4_9 = 0x1; /* enable A9 */
    PINSEL8_bit.P4_10 = 0x1; /* enable A10 */
    PINSEL8_bit.P4_11 = 0x1; /* enable A11 */
    PINSEL8_bit.P4_12 = 0x1; /* enable A12 */
    PINSEL8_bit.P4_13 = 0x1; /* enable A13 */
    PINSEL8_bit.P4_14 = 0x1; /* enable A14 */
    PINSEL8_bit.P4_15 = 0x1; /* enable A15 */

    PINSEL9_bit.P4_16 = 0x1; /* enable A16 */
    PINSEL9_bit.P4_17 = 0x1; /* enable A17 */
    PINSEL9_bit.P4_18 = 0x1; /* enable A18 */
    PINSEL9_bit.P4_19 = 0x1; /* enable A19 */
    PINSEL9_bit.P4_20 = 0x1; /* enable A20 */
    PINSEL9_bit.P4_21 = 0x1; /* enable A21 */
    PINSEL9_bit.P4_22 = 0x1; /* enable A22 */
    PINSEL9_bit.P4_23 = 0x1; /* enable A23 */
    PINSEL9_bit.P4_24 = 0x1; /* enable /OE */
    PINSEL9_bit.P4_25 = 0x1; /* enable /WE */
    PINSEL9_bit.P4_26 = 0x1; /* enable BLS0 */
    PINSEL9_bit.P4_27 = 0x1; /* enable BLS1 */
//    PINSEL9_bit.P4_28 = 0x1; /* enable BLS2 */
//    PINSEL9_bit.P4_29 = 0x1; /* enable BLS3 */
    PINSEL9_bit.P4_30 = 0x1; /* enable /CS0 */
    PINSEL9_bit.P4_31 = 0x1; /* enable /CS1 */

    SCS_bit.EMCRD = 0x1; /*  EMC reset disable */

    PCONP |= 0x00000800; /* Power Control for External Memory Controller */

    EMCCONTROL = 0x00000001; /* Enabled, Normal memory map, Normal mode */

    EMCCONFIG = 0x00000000;

     /***********************************************************************
      * Initialize EMC and SDRAM ( Micron's MT48LC16M16A2P-75 )
      **********************************************************************/

    EMCDYNAMICCFG0 = 0x00001680; /* 256MB, 16Mx16, 4 banks, row=13, column=9 */

    EMCDYNAMICRASCAS0 = 0x00000202; /* 2 RAS, 2 CAS latency */
//    EMCDYNAMICRASCAS0 = 0x00000302; /* 2 RAS, 3 CAS latency */

//    EMCDINAMICRDCFG = 0x00000000; /* Clock out delayed strategy, using CLKOUT */
    EMCDINAMICRDCFG = 0x00000001; /* Command delayed strategy, using EMCCLKDELAY */
//    EMCDINAMICRDCFG = 0x00000002; /* Command delayed strategy plus one clock cycle, using EMCCLKDELAY*/
//    EMCDINAMICRDCFG = 0x00000003; /* Command delayed strategy plus two clock cycles, using EMCCLKDELAY*/

    EMCDYNAMICRP = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCDYNAMICRAS = 0x00000003; /* ( n + 1 ) -> 4 clock cycles */

    EMCDYNAMICSREX = 0x00000005; /* ( n + 1 ) -> 6 clock cycles */

    EMCDYNAMICAPR = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCDYNAMICDAL = 0x00000005; /* ( n ) -> 5 clock cycles */

    EMCDYNAMICWR = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCDYNAMICRC = 0x00000005; /* ( n + 1 ) -> 6 clock cycles */

    EMCDYNAMICRFC = 0x00000005; /* ( n + 1 ) -> 6 clock cycles */

    EMCDYNAMICXSR = 0x00000005; /* ( n + 1 ) -> 6 clock cycles */

    EMCDYNAMICRRD = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCDYNAMICMRD = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCDINAMICCTRL = 0x00000183; /* Issue NOP command */
    delayMs(100);

    EMCDINAMICCTRL = 0x00000103; /* Issue PALL command */

    EMCDINAMICRFR = 0x00000002;  /* ( n * 16 ) -> 32 clock cycles */
    delayMs(100);

    EMCDINAMICRFR = 0x00000046;  /* ( n * 16 ) -> 1120 clock cycles -> 15.556uS at 72MHz <= 15.625uS ( 64ms / 4096 row ) */
//    EMCDINAMICRFR = 0x00000048;  /* ( n * 16 ) -> 1152 clock cycles */
  
    EMCDYNAMICRASCAS0 = 0x00000202; /* 2 RAS, 2 CAS latency */
//    EMCDYNAMICRASCAS0 = 0x00000302; /* 2 RAS, 3 CAS latency */

    EMCDYNAMICCFG0 = 0x00001680; /* 256MB, 16Mx16, 4 banks, row=13, column=9 */
    
    EMCDINAMICCTRL = 0x00000083; /* Issue MODE command */

    dummy = *((volatile INT16U *)(SDRAM_BASE | 0x00008C00)); /* 2 CAS latency */
//    dummy = *((volatile INT16U *)(SDRAM_BASE | 0x0000CC00)); /* 3 CAS latency */

    EMCDINAMICCTRL = 0x00000000; /* Issue NORMAL command */

    EMCDYNAMICCFG0 = 0x00081680; /* 256MB, 16Mx16, 4 banks, row=13, column=9 */

     /***********************************************************************
      * Initialize EMC and SRAM
      **********************************************************************/
    EMCSTATICCNFG0 = 0x00000082;

    EMCSTATICWAITWEN0 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

    EMCSTATICWAITOEN0 = 0x00000000; /* ( n ) -> 0 clock cycles */

    EMCSTATICWAITRD0 = 0x00000001; /* ( n + 1 ) -> 2 clock cycles */

    EMCSTATICWAITPG0 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

    EMCSTATICWAITWR0 = 0x00000000; /* ( n + 2 ) -> 2 clock cycles */

    EMCSTATICWAITTURN0 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

    EMCSTATICCNFG1 = 0x00000081;

    EMCSTATICWAITWEN1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

    EMCSTATICWAITOEN1 = 0x00000000; /* ( n ) -> 0 clock cycles */
//    EMCSTATICWAITOEN1 = 0x00000001; /* ( n ) -> 1 clock cycles */
    
    EMCSTATICWAITRD1 = 0x00000004; /* ( n + 1 ) -> 5 clock cycles */
//    EMCSTATICWAITRD1 = 0x00000005; /* ( n + 1 ) -> 6 clock cycles */
    
    EMCSTATICWAITPG1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */

    EMCSTATICWAITWR1 = 0x00000003; /* ( n + 2 ) -> 5 clock cycles */
//    EMCSTATICWAITWR1 = 0x00000005; /* ( n + 2 ) -> 7 clock cycles */

    EMCSTATICWAITTURN1 = 0x00000000; /* ( n + 1 ) -> 1 clock cycles */
}
#endif

/***********************************************************************
 *
 * Function: low_level_init
 *
 * Purpose: initialize the chip.
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
void low_level_init(void)
{
    /* Configure PLL, switch from IRC to Main OSC */
    configure_pll();

    PCLKSEL0 = 0x00000000;	/* PCLK is 1/4 CCLK */
    PCLKSEL1 = 0x00000000;

    /* Configure EMC */
    configure_emc();
    
    PCONP |= 0x00100000;        /* Power Control for CLCDC */ 

    /* Set memory accelerater module*/
    MAMCR = 0;
    MAMTIM = 3; /* Fcclk > 40MHz */
//    MAMTIM = 2; /* Fcclk >= 20MHz */
//    MAMTIM = 1; /* Fcclk < 20MHz */
    MAMCR = 2;

    init_vic();
}
