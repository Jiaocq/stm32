#include "stm32f4xx_hal.h"
#include "init.h"
#include "drv_adc.h"
#include "drv_dac.h"
#include "drv_io.h"
#include "drv_key.h"
#include "drv_mode.h"
#include "drv_spiio.h"
#include "drv_time.h"
#include "drv_uart.h"
#include "common.h"
#include "main.h"
#include "spi.h"

int cunit()
{
    uint64_t time0 = 0;
    uint64_t keeptime = 0;
    int32_t adcValue[30];
    int32_t channel = 0;
    int32_t key;
    int32_t a = 0;
    int32_t pinstate[4];
    int32_t spicount = 0;
    /**harsware init */
    HardwareInit();
    LEDInit();
    WriteLED(LED5, 1); /**power led on*/
    uint8_t readData[4] = {
        0xff,
        0xff,
        0xff,
        0xff,
    };
    uint8_t sendData[4] = {
        0x41,
        0x01,
        0x00,
        0x00,
    };

    while (0)
    {
        /**recv 0xff */
        sendData[1] = 0x01;
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, GPIO_PIN_RESET);
        DelayUs(5);
        HAL_SPI_TransmitReceive(&hspi2, sendData, readData, 3, 1000);
        DelayUs(5);
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
        DEBUG("recv : %d\r\n", readData[2]);
        /**recv 0x00 */

        sendData[1] = 0x02;
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, GPIO_PIN_RESET);
        DelayUs(5);
        HAL_SPI_TransmitReceive(&hspi2, sendData, readData, 3, 1000);
        DelayUs(5);
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
        DEBUG("recv : %d\r\n", readData[2]);
    }

    while (0)
    {
        /**recv 0xff */
        sendData[1] = 0x01;
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_RESET);
        DelayUs(5);
        HAL_SPI_TransmitReceive(&hspi2, sendData, readData, 3, 1000);
        DelayUs(5);
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
        DEBUG("recv : %d\r\n", readData[2]);
        /**recv 0x00 */

        sendData[1] = 0x02;
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_RESET);
        DelayUs(5);
        HAL_SPI_TransmitReceive(&hspi2, sendData, readData, 3, 1000);
        DelayUs(5);
        HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, GPIO_PIN_SET);
        HAL_Delay(10);
        DEBUG("recv : %d\r\n", readData[2]);
    }
    // hw_init();
    /**debug */
    // DEBUG("test start\r\n");

    /**time ms */
    // time0 = TimeMs();
    // HAL_Delay(1000);
    // keeptime = TimeMs() - time0;
    // DEBUG("TimeMs = %ld\r\n",(uint32_t)keeptime);

    /**time us */
    // time0 = 0;
    // keeptime = 0;
    // time0 = TimeUs();
    // HAL_Delay(100);
    // keeptime = TimeUs() - time0;
    // DEBUG("TimeUs = %lu .\r\n",(uint32_t)keeptime);
    while (0)
    {
        AIAdcInit();
        adcValue[0] = AIReadCh(0);
        adcValue[1] = AIReadCh(1);
        adcValue[2] = AIReadCh(2);
        adcValue[3] = AIReadCh(3);
        adcValue[4] = AIReadCh(4);
        adcValue[5] = AIReadCh(5);
        adcValue[6] = AIReadCh(6);
        adcValue[7] = AIReadCh(7);
        DEBUG("adcvalue = \t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t \r\n",
              adcValue[0], adcValue[1], adcValue[2], adcValue[3], adcValue[4], adcValue[5], adcValue[6], adcValue[7]);
        HAL_Delay(50);
    }
    while (0)/**u90 */
    {
        // AIAdcInit();
        DIGAdcInit();
        adcValue[0] = DIGReadCh(0);
        adcValue[1] = DIGReadCh(1);
        adcValue[2] = DIGReadCh(2);
        adcValue[3] = DIGReadCh(3);
        adcValue[4] = DIGReadCh(4);
        adcValue[5] = DIGReadCh(5);
        adcValue[6] = DIGReadCh(6);
        adcValue[7] = DIGReadCh(7);
        DEBUG("adcvalue = \t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t \r\n",
              adcValue[0], adcValue[1], adcValue[2], adcValue[3], adcValue[4], adcValue[5], adcValue[6], adcValue[7]);
        HAL_Delay(50);
    }

    while (0)
    {
        // AIAdcInit();
        // DIGAdcInit();
        HIOAdcInit();
        adcValue[0] = HIOReadCh(0);
        adcValue[1] = HIOReadCh(1);
        adcValue[2] = HIOReadCh(2);
        adcValue[3] = HIOReadCh(3);
        adcValue[4] = HIOReadCh(4);
        adcValue[5] = HIOReadCh(5);
        adcValue[6] = HIOReadCh(6);
        adcValue[7] = HIOReadCh(7);
        DEBUG("adcvalue = \t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t \r\n",
              adcValue[0], adcValue[1], adcValue[2], adcValue[3], adcValue[4], adcValue[5], adcValue[6], adcValue[7]);
        HAL_Delay(50);
    }

    /**ad5686 */
        AD5686Init();
    for(;;)
    {
        WriteAD5686Value(0, 0xffff);
        WriteAD5686Value(1, 0xffff);
        WriteAD5686Value(2, 0xffff);
        WriteAD5686Value(3, 0xffff);
        HAL_Delay(50);
    }

    while(0){
    for (channel = 4; channel;)
    {
        channel--;
        WriteAD5686Value(channel, 0);
        WriteAD5686Value(channel, 0xffff);
    }
    }
    WriteAD5686AllCh(0);
    WriteAD5686AllCh(0xffff);

    /**dac8568 */
    DAC8568Init();
    for (channel = 8; channel;)
    {
        channel--;
        WriteDAC8568Value(channel, 0);
        WriteDAC8568Value(channel, 0xffff);
    }
    WriteDAC8568AllCh(0);
    WriteDAC8568AllCh(0xffff);

    /**led  */
    //     LEDInit();
    // WriteLED(LEDDI(0),1);

    //     WriteLED(LED5, 0);
    //     WriteLED(LED6, 0);
    //     WriteLED(LED7, 0);
    //     WriteLED(LED8, 0);
    //     WriteLED(LED10, 0);
    //     WriteLED(LED11, 0);
    //     WriteLED(LED12, 0);
    //     WriteLED(LED13, 0);
    //     WriteLED(LED14, 0);
    //     WriteLED(LED15, 0);
    //     WriteLED(LED16, 0);
    //     WriteLED(LED17, 0);
    //     WriteLED(LED18, 0);
    //     WriteLED(LED19, 0);
    //     WriteLED(LED20, 0);
    //     WriteLED(LED21, 0);
    //     WriteLED(LED22, 0);
    //     WriteLED(LED23, 0);
    //     WriteLED(LED24, 0);
    //     WriteLED(LED25, 0);
    //     WriteLED(LED26, 0);
    //     WriteLED(LED27, 0);
    //     WriteLED(LED28, 0);
    //     WriteLED(LED29, 0);
    //     WriteLED(LED30, 0);
    //     WriteLED(LED31, 0);
    //     WriteLED(LED32, 0);
    //     WriteLED(LED33, 0);
    //     WriteLED(LED34, 0);
    //     WriteLED(LED35, 0);
    //     WriteLED(LED36, 0);
    //     WriteLED(LED37, 0);
    //     WriteLED(LED38, 0);
    //     WriteLED(LED39, 0);
    //     WriteLED(LED40, 0);
    //     WriteLED(LED41, 0);
    //     WriteLED(LED42, 0);
    //     WriteLED(LED43, 0);
    //     WriteLED(LED44, 0);
    //     WriteLED(LED45, 0);
    //     WriteLED(LED46, 0);
    //     WriteLED(LED47, 0);
    //     WriteLED(LED48, 0);
    //     WriteLED(LED49, 0);
    //     WriteLED(LED50, 0);
    //     WriteLED(LED51, 0);
    //     WriteLED(LED52, 0);
    //     WriteLED(LED53, 0);
    //     WriteLED(LED54, 0);
    //     WriteLED(LED55, 0);
    //     WriteLED(LED56, 0);
    //     WriteLED(LED57, 0);
    //     WriteLED(LED58, 0);
    //     WriteLED(LED59, 0);
    //     WriteLED(LED60, 0);
    //     WriteLED(LED61, 0);
    //     WriteLED(LED62, 0);
    //     WriteLED(LED63, 0);
    //     WriteLED(LED64, 0);
    //     WriteLED(LED65, 0);
    //     WriteLED(LED66, 0);
    //     WriteLED(LED67, 0);
    //     WriteLED(LED68, 0);
    //     WriteLED(LED69, 0);

    //     WriteLED(LED5, 1);
    //     WriteLED(LED6, 1);
    //     WriteLED(LED7, 1);
    //     WriteLED(LED8, 1);
    //     WriteLED(LED10, 1);
    //     WriteLED(LED11, 1);
    //     WriteLED(LED12, 1);
    //     WriteLED(LED13, 1);
    //     WriteLED(LED14, 1);
    //     WriteLED(LED15, 1);
    //     WriteLED(LED16, 1);
    //     WriteLED(LED17, 1);
    //     WriteLED(LED18, 1);
    //     WriteLED(LED19, 1);
    //     WriteLED(LED20, 1);
    //     WriteLED(LED21, 1);
    //     WriteLED(LED22, 1);
    //     WriteLED(LED23, 1);
    //     WriteLED(LED24, 1);
    //     WriteLED(LED25, 1);
    //     WriteLED(LED26, 1);
    //     WriteLED(LED27, 1);
    //     WriteLED(LED28, 1);
    //     WriteLED(LED29, 1);
    //     WriteLED(LED30, 1);
    //     WriteLED(LED31, 1);
    //     WriteLED(LED32, 1);
    //     WriteLED(LED33, 1);
    //     WriteLED(LED34, 1);
    //     WriteLED(LED35, 1);
    //     WriteLED(LED36, 1);
    //     WriteLED(LED37, 1);
    //     WriteLED(LED38, 1);
    //     WriteLED(LED39, 1);
    //     WriteLED(LED40, 1);
    //     WriteLED(LED41, 1);
    //     WriteLED(LED42, 1);
    //     WriteLED(LED43, 1);
    //     WriteLED(LED44, 1);
    //     WriteLED(LED45, 1);
    //     WriteLED(LED46, 1);
    //     WriteLED(LED47, 1);
    //     WriteLED(LED48, 1);
    //     WriteLED(LED49, 1);
    //     WriteLED(LED50, 1);
    //     WriteLED(LED51, 1);
    //     WriteLED(LED52, 1);
    //     WriteLED(LED53, 1);
    //     WriteLED(LED54, 1);
    //     WriteLED(LED55, 1);
    //     WriteLED(LED56, 1);
    //     WriteLED(LED57, 1);
    //     WriteLED(LED58, 1);
    //     WriteLED(LED59, 1);
    //     WriteLED(LED60, 1);
    //     WriteLED(LED61, 1);
    //     WriteLED(LED62, 1);
    //     WriteLED(LED63, 1);
    //     WriteLED(LED64, 1);
    //     WriteLED(LED65, 1);
    //     WriteLED(LED66, 1);
    //     WriteLED(LED67, 1);
    //     WriteLED(LED68, 1);
    //     WriteLED(LED69, 1);

    /** start key */
    /*read press */
    // key = 0;
    // for (a = 1000; a--;)
    // {
    //     if (getStartKey())
    //         key = 1L;
    //     HAL_Delay(2);
    // }
    // DEBUG("key = %d\r\n", key);
    // /**read release */
    // for (a = 1000; a--;)
    // {
    //     if (!getStartKey())
    //         key = 0;
    //     HAL_Delay(2);
    // }
    // DEBUG("key = %d\r\n", key);

    // /** mode */
    // /**read 0 */
    // for (a = 1000; a--;)
    // {
    //     key = getModeValue();
    //     HAL_Delay(2);
    // }
    // /**read 1 */
    // for (a = 1000; a--;)
    // {
    //     key = getModeValue();
    //     HAL_Delay(2);
    // }
    // /**read 2 */
    // for (a = 1000; a--;)
    // {
    //     key = getModeValue();
    //     HAL_Delay(2);
    // }
    // /**read 3 */
    // for (a = 1000; a--;)
    // {
    //     key = getModeValue();
    //     HAL_Delay(2);
    // }
    // /**read 4 */
    // for (a = 1000; a--;)
    // {
    //     key = getModeValue();
    //     HAL_Delay(2);
    // }

    /** spi io*/
    // DEBUG("spiio : %d",SpiioIinit());
    while (0)
    {
        ReadDIDOPin(FROMDI, 0);
        HAL_Delay(10);
    }
    /**write 0 */
    uint32_t u32t = 0x12345678UL;
    uint8_t *u8t = (uint8_t *)&u32t;
    uint8_t aaa[4] = {*(u8t + 0), *(u8t + 1), *(u8t + 2), *(u8t + 3)};
    for (spicount = 16; spicount--;)
    {
        WriteDIDOPin(TODI, spicount, 0);
        WriteDIDOPin(TODI, spicount, 1);
        WriteDIDOPin(TODO, spicount, 0);
        WriteDIDOPin(TODO, spicount, 1);
        WriteAIHIOPin(TOAI, spicount, 0);
        WriteAIHIOPin(TOAI, spicount, 1);
        WriteAIHIOPin(TOFROMHIO, spicount, 0);
        WriteAIHIOPin(TOFROMHIO, spicount, 1);
    }
    /**write 1 */
    for (spicount = 16; spicount--;)
    {
        WriteAIHIOPin(TOAI, spicount, 1);
        WriteAIHIOPin(TOFROMHIO, spicount, 1);
        WriteDIDOPin(TODI, spicount, 1);
        WriteDIDOPin(TODO, spicount, 1);
    }

    /**read 0 */
    for (spicount = 16; spicount--;)
    {
        pinstate[0] = ReadDIDOPin(FROMDI, spicount);
        pinstate[1] = ReadDIDOPin(FROMDO, spicount);
        pinstate[2] = ReadAIHIOPin(FROMHIO, spicount);
        pinstate[3] = ReadAIHIOPin(TOFROMHIO, spicount);
        DEBUG("pinstate = %d\t%d\t%d\t%d\r\n", pinstate[0], pinstate[1], pinstate[2], pinstate[3]);
    }
    /**read 1 */
    for (spicount = 16; spicount--;)
    {
        pinstate[0] = ReadDIDOPin(FROMDI, spicount);
        pinstate[1] = ReadDIDOPin(FROMDO, spicount);
        pinstate[2] = ReadAIHIOPin(FROMHIO, spicount);
        pinstate[3] = ReadAIHIOPin(TOFROMHIO, spicount);
        DEBUG("pinstate = %d\t%d\t%d\t%d\r\n", pinstate[0], pinstate[1], pinstate[2], pinstate[3]);
    }

    return 0;
}