#include "cyhal.h"
#include "cybsp.h"
#include "cy_pdl.h"
#include "cy_retarget_io.h"
#include "GUI.h"
#include "SPI_st7789v.h"
#include "LCDConf.h"
const SPI_st7789v_pins_t tft_pins =
{
    .MOSI = P6_0,
    .MISO = P6_1,
    .SCK = P6_2,
    .SS = P6_3,
    .dc = P9_7,
	.rst= P9_4,
	.frec= 8000000
/*  .MOSI = P5_0,
    .MISO = P5_1,
    .SCK = P5_2,
    .SS = P5_7,
    .dc = P9_7,
    .rst= P9_4,*/
};
int main(void)
{
    cy_rslt_t result;

#if defined (CY_DEVICE_SECURE)
    cyhal_wdt_t wdt_obj;

    /* Clear watchdog timer so that it doesn't trigger a reset */
    result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    cyhal_wdt_free(&wdt_obj);
#endif

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();
   // cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);
    result = SPI_st7789v_init8(&tft_pins);
    CY_ASSERT(result == CY_RSLT_SUCCESS);

    GUI_Init();
    GUI_SetFont(GUI_FONT_20B_1);
    GUI_SetBkColor(GUI_BLACK);
    GUI_Clear();
    GUI_SetColor(GUI_WHITE);
    GUI_DispStringAt("TECNICAS DIGITALES 2", 15, 20);
    GUI_DrawRect(10, 10, LCD_GetXSize() - 10, LCD_GetYSize() - 10);

    while(1)
    {
       // Infinite loop...
    }
}

