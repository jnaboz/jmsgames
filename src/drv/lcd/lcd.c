/***********************************************************************
 * File:   lcd.c
 * Rev:    1.0
 * Date:   March 26 2007
 *
 * Description:
 *     This example shows how to use LCD driver
 *
 * Revision History:
 * Rev 1.0 March 26 2007
 * Initial revision.
 * 
 **********************************************************************/

#if(0)
#include <intrinsics.h>


#include "lcd_driver.h"
#include "lcd_params.h"
#include "low_level_init.h"
#include "irq.h"

#if(0)
#define _PORTRAIT_EXAMPLES
#include "sunset_portrait.h"
#include "winter_portrait.h"
#endif

#define LCD_DISPLAY sharp_lq035_portrait

static INT32S dev_lcd;
static INT32U num_frms;
static INT32U x_pos, y_pos;
static BOOL first_frm;

/***********************************************************************
 *
 * Function: irq_handler
 *
 * Purpose: IRQ handler.
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
__irq __arm void irq_handler (void)
{
    void (*interrupt_function)();
    INT32S vector;

    vector = VICAddress;     // Get interrupt vector.
    interrupt_function = (void(*)())vector;
    if(interrupt_function != NULL)
    {
        interrupt_function();  // Call vectored interrupt function.
    }
    else
    {
        VICAddress = 0;      // Clear interrupt in VIC.
    }
}

/***********************************************************************
 *
 * Function: clcdc_handler
 *
 * Purpose: CLCDC interrupt handler.
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
void clcdc_handler(void)
{		
    INT32S status;

    /* Get masked interrupt statu */
    status = lcd_ioctl(dev_lcd, LCD_GET_STATUS, LCD_GET_INTERRUPT);

    if (status & CLCDC_LCD_INTERRUPT_FUF)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_FUF);
    }
    if (status & CLCDC_LCD_INTERRUPT_LNBU)
    {
        num_frms++;

        if ((num_frms & 0x7F) == 0x0)
        {
           if (first_frm)
           {
              first_frm = FALSE;

              /* Set LCD display pointer */
              lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SRAM_BASE);
              x_pos += 32;
              if (x_pos > 224)
              {  
                 x_pos = 0;
                 y_pos += 32;
                 if (y_pos > 288)
                 {
                    y_pos = 0;
                 }  
              }   
              lcd_ioctl(dev_lcd, LCD_CRSR_XY, (INT32S)(((y_pos & 0x3FF) << 16) + (x_pos & 0x3FF)));
           }
           else
           {
              first_frm = TRUE;

              /* Set LCD display pointer */
              lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SDRAM_BASE);
              x_pos += 32;
              if (x_pos > 224)
              {  
                 x_pos = 0;
                 y_pos += 32;
                 if (y_pos > 288)
                 {
                    y_pos = 0;
                 }  
              }   
              lcd_ioctl(dev_lcd, LCD_CRSR_XY, (INT32S)(((y_pos & 0x3FF) << 16) + (x_pos & 0x3FF)));
           }
        }        

        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_LNBU);
    }
    if (status & CLCDC_LCD_INTERRUPT_VCOMP)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_VCOMP);
    }
    if (status & CLCDC_LCD_INTERRUPT_MBERROR)
    {
        lcd_ioctl(dev_lcd, LCD_CLR_INTERRUPT, CLCDC_LCD_INTERRUPT_MBERROR);
    }

    VICAddress = 0; /* Acknowledge Interrupt */
}

/***********************************************************************
 *
 * Function: main
 *
 * Purpose: Function entry point from the startup code.
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
INT32S main(void)
{
    INT32U i, j;
    INT32U palette0, palette1;
    INT32U cursorimage[256];

    palette0 = 0x0000FCFC;
    palette1 = 0x00FC00FC;
    
    low_level_init();

    /* Initialize the image pointer */
        i = 0;
        while (i < sunset_portrait_w * sunset_portrait_h)
        {
            *(volatile INT16U *)(SDRAM_BASE + i * 2) = *(INT16U *)(&sunset_portrait[i]);
            i += 1;
        }

        i = 0;
        while (i < winter_portrait_w * winter_portrait_h)
        {
            *(volatile INT32U *)(SRAM_BASE + i * 2) = *(INT32U *)(&winter_portrait[i]);
            i += 2;
        }

    for(i = 0; i < 256; i++)
    {
       cursorimage[i] = 0x55555555;
    }
    
    /* Install CLCDC interrupt handler */
    if (install_irq(VIC_CLCDC, (void *)clcdc_handler, HIGHEST_PRIORITY) == FALSE)
    {
        /* Error installing CLCDC interrupt handler */
        return 0;
    }

    /* Open LCD */
    if ((dev_lcd = lcd_open(CLCDC, (INT32S)&LCD_DISPLAY)) == 0x0)
    {
        /* Error opening the device */
        return 0;
    }

    /* Set LCD display pointer */
    lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SDRAM_BASE);

    lcd_ioctl(dev_lcd, LCD_CRSR_SET_BUFFER, (INT32S)&cursorimage[0]);
    lcd_ioctl(dev_lcd, LCD_CRSR_LOAD_PALETTE0, (INT32S)palette0);
    lcd_ioctl(dev_lcd, LCD_CRSR_LOAD_PALETTE1, (INT32S)palette1);
    lcd_ioctl(dev_lcd, LCD_CRSR_SYNC, (INT32S)1);
    
    /* Enable LCD */
    lcd_ioctl(dev_lcd, LCD_ENABLE, 1);

//    lcd_ioctl(dev_lcd, LCD_CRSR_ENABLE, (INT32S)1);

    /* Enable CLCDC Interrupt */
    lcd_ioctl(dev_lcd, LCD_SET_INTERRUPT, CLCDC_LCD_INTERRUPT_FUF);
    lcd_ioctl(dev_lcd, LCD_SET_INTERRUPT, CLCDC_LCD_INTERRUPT_LNBU);
    lcd_ioctl(dev_lcd, LCD_SET_INTERRUPT, CLCDC_LCD_INTERRUPT_VCOMP);
    lcd_ioctl(dev_lcd, LCD_SET_INTERRUPT, CLCDC_LCD_INTERRUPT_MBERROR);

    /* Enable interrupts */
    __enable_interrupt();

    /* Turn on LCD */
    lcd_ioctl(dev_lcd, LCD_PWR_ON, 1);

    /* Set LCD display pointer */
    lcd_ioctl(dev_lcd, LCD_SET_BUFFER, (INT32S)SDRAM_BASE);
    
    num_frms = 0;
    first_frm = TRUE;
    x_pos = 0;
    y_pos = 0;
    while(num_frms < 0x10000);
    
    /* Turn off LCD */
    lcd_ioctl(dev_lcd, LCD_PWR_ON, 0);

    /* Disable LCD */
    lcd_ioctl(dev_lcd, LCD_ENABLE, 0);

    /* Close LCD */
    lcd_close(dev_lcd);
    
    return 1;
}


#endif