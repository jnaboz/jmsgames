/*******************************************************************************************************************************
*	
*	Filename: iosdram_cfg.h
*	Rev Date: 3/28/2012
*
*	File Description:
*			Configuration file for SDRAM. Alter characteristics here as needed.
*
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Include Files
*******************************************************************************************************************************/


/*******************************************************************************************************************************
*			Macros
*******************************************************************************************************************************/
#define IOSDRAM_CFG_H_VERSION_MAJOR			(1)
#define IOSDRAM_CFG_H_VERSION_MINOR			(0)
#define IOSDRAM_CFG_H_VERSION_PATCH			(2)

/* SDRAM Register Values */
#define SDRAM_BUFFER_ENABLE                 (0x00080000)                /* Buffer Enable Bit                                    */
#define SDRAM_DYNAMIC_RAS                   (0x3)                       /* 0: Reserved, 1: One CCLK, 2: Two CCLK, 3: Three CCLK */
#define SDRAM_DYNAMIC_CAS                   (0x3)                       /* 0: Reserved, 1: One CCLK, 2: Two CCLK, 3: Three CCLK */

#define DYNAMIC_RAS_CAS                     (SDRAM_DYNAMIC_RAS | (SDRAM_DYNAMIC_CAS << 8))
#define DYNAMIC_READ_CONFIG                 (0x1)                       /* 0: CLKOUT delayed, 1: CMD Delayed, 2: CMD Delayed + one EMCCLK, 3: CMD Delayed + two EMCCLK                      */
#define DYNAMIC_TRP_CONFIG                  (0x2)                       /* (n + 1) EMCCLK - Precharge Command Period                                          : Max = 0xF                   */
#define DYNAMIC_TRAS_CONFIG                 (0x5)                       /* (n + 1) EMCCLK - Active to Precharge Command Period                                : Max = 0xF                   */
#define DYNAMIC_TSREX_CONFIG                (0x0)                       /* (n + 1) CCLK - Self-Refresh Exit Time                                              : Max = 0xF                   */
#define DYNAMIC_TAPR_CONFIG                 (0x4)                       /* (n + 1) CCLK - Last Data Out to Active Command Time                                : Max = 0xF                   */
#define DYNAMIC_TDAL_CONFIG                 (0x5)                       /* (n) CCLK - Data In to Active Command Time                                          : Max = 0xF                   */
#define DYNAMIC_TWR_CONFIG                  (0x2)                       /* (n + 1) CCLK - Write Recover Time                                                  : Max = 0xF                   */
#define DYNAMIC_TRC_CONFIG                  (0x8)                       /* (n + 1) CCLK - Active to Active Command Period                                     : Max = 0x1F                  */
#define DYNAMIC_TRFC_CONFIG                 (0x8)                       /* (n + 1) CCLK - Auto Refresh Period and Auto Refresh to Active Command Period       : Max = 0x1F                  */
#define DYNAMIC_TXSR_CONFIG                 (0x0)                       /* (n + 1) CCLK - Exit Self Refresh to Active Command Time                            : Max = 0x1F                  */
#define DYNAMIC_TRRD_CONFIG                 (0x1)                       /* (n + 1) CCLK - Active Bank A to Active Bank B Latency Time                         : Max = 0xF                   */
#define DYNAMIC_TMRD_CONFIG                 (0x1)                       /* (n + 1) CCLK - Load Mode Register to Active Command Time                           : Max = 0xF                   */

#define DYNAMIC_REFRESH_RATE                (0x20)                      /* (n * 16) CCLK - Dynamic Refresh Rate                                                                             */

/* SDRAM Initialization Commands */
#define SDRAM_NOP_COMMAND                   (0x00000180)                /* Issue NOP Command - To be set in EMCDynamicControl Register    */
#define SDRAM_PALL_COMMAND                  (0x00000100)                /* Issue PALL Command - To be set in EMCDynamicControl Register   */
#define SDRAM_MODE_COMMAND                  (0x00000080)                /* Issue MODE Command - To be set in EMCDynamicControl Register   */
#define SDRAM_NORMAL_COMMAND                (0x00000000)                /* Issue NORMAL Command - To be set in EMCDynamicControl Register */
#define SDRAM_CLK_CKE_HIGH                  (0x00000003)                /* Set Clock Enable and Chip Select values to ALWAYS ON           */

/* SDRAM Mode Command Values */
#define BANK_ROW_COL
//#define BUS_SIZE_32

#define SDRAM_BURST_LENGTH_1                (0x0)                       /* Burst Length = 1    */
#define SDRAM_BURST_LENGTH_2                (0x1)                       /* Burst Length = 2    */
#define SDRAM_BURST_LENGTH_4                (0x2)                       /* Burst Length = 4    */
#define SDRAM_BURST_LENGTH_8                (0x3)                       /* Burst Length = 8    */
#define SDRAM_BURST_LENGTH_PAGE             (0x7)                       /* Burst Length = Page */
#define SDRAM_BURST_LENGTH                  (SDRAM_BURST_LENGTH_8)
#define SDRAM_BURST_LENGTH_SHIFT            (0)
#define BURST_LENGTH_CMD                    (SDRAM_BURST_LENGTH << SDRAM_BURST_LENGTH_SHIFT)

#define SDRAM_BURST_TYPE_SEQ                (0x0)                       /* Burst Type Sequential  */
#define SDRAM_BURST_TYPE_INT                (0x1)                       /* Burst Type Interleaved */
#define SDRAM_BURST_TYPE                    (SDRAM_BURST_TYPE_SEQ)
#define SDRAM_BURST_TYPE_SHIFT              (3)
#define BURST_TYPE_CMD                      (SDRAM_BURST_TYPE << SDRAM_BURST_TYPE_SHIFT)

#define SDRAM_CAS_LATENCY                   (SDRAM_DYNAMIC_CAS)
#define SDRAM_CAS_LATENCY_SHIFT             (4)
#define CAS_LATENCY_CMD                     (SDRAM_CAS_LATENCY << SDRAM_CAS_LATENCY_SHIFT)

#define SDRAM_WRITE_MODE_BRSW               (0x4)                       /* Burst Read, Single Write */
#define SDRAM_WRITE_MODE_BRBW               (0x0)                       /* Burst Read/Write */
#define SDRAM_WRITE_MODE                    (SDRAM_WRITE_MODE_BRBW)
#define SDRAM_WRITE_MODE_SHIFT              (7)
#define WRITE_MODE_CMD                      (SDRAM_WRITE_MODE << SDRAM_WRITE_MODE_SHIFT)

#define SDRAM_MODE_CMD                      (BURST_LENGTH_CMD | BURST_TYPE_CMD | CAS_LATENCY_CMD | WRITE_MODE_CMD)

#ifdef BANK_ROW_COL
    #define SDRAM_MODE_COMMAND_VAL          (SDRAM_MODE_CMD << 9)
    #ifdef BUS_SIZE_32
        #define SDRAM_MEM_CONFIG_VAL        (0x00005080)                /* 32-bit bus */
    #else
        #define SDRAM_MEM_CONFIG_VAL        (0x00001080)                /* 16-bit bus */
    #endif
#else
	#define SDRAM_MODE_COMMAND_VAL          (SDRAM_MODE_CMD << 10)
    #ifdef BUS_SIZE_32
        #define SDRAM_MEM_CONFIG_VAL        (0x00004080)                /* 32-bit bus */
    #else
        #define SDRAM_MEM_CONFIG_VAL        (0x00000080)                /* 16-bit bus */
    #endif
#endif


/*******************************************************************************************************************************
*			Constant Definitions
*******************************************************************************************************************************/






/*******************************************************************************************************************************
*
*	Revisions:
*
*	Rev			Date			Author				Change Description
*	------		--------		----------			------------------------------
*	1.0.0		3/28/2012		J. Nabozny			Created
*   1.0.1		4/1/2012		J. Nabozny			Finish initialization
*   1.0.2       4/16/2012       J. Nabozny          Edit Initialization to use macros instead of magic numbers
*
*******************************************************************************************************************************/
