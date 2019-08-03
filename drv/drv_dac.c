#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"

#define SPIBUS hspi3
#define TIMEOUT 1000 /*ms */

#define DAC8568ClrZerio (0x5UL << 8 * 0)
#define DAC8568IgnExtClr ((0x5UL << 8 * 0) | (0x3UL) << 8 * 3)
#define DAC8568Rst (0x7UL << 8 * 0)
#define DAC8568WrtReg(channel, data) (0x3UL << 8 * 0 | channel << 8 * 1 + 4 | data << 8 * 3 + 4) /*channel 0-7, data 0-0xffff */
#define DAC8568WrtAllReg(data) (0x3UL << 8 * 0 | 0xfUL << 8 * 1 + 4 | data << 8 * 3 + 4)
#define DAC8568PwrDwnAll (0x4UL << 8 * 0 | 0x0UL << 8 * 2 | 0xffUL << 8 * 3)
#define DAC8568PwrUpAll (0x4UL << 8 * 0 | 0x2UL << 8 * 2 | 0xffUL << 8 * 3)
#define DAC8568PwrDwnItnRef (0x9UL << 8 * 0 | 0xaUL << 8 * 1 + 1)
#define DAC8568FrameLength 4 /*byte */

#define AD5686Rst (0x6UL << 8 * 0 + 4)
#define AD5686WrtReg(channel, data) (0x3UL << 8 * 0 + 4 | channel << 8 * 0 | data << 8 * 2 + 4) /*channel DCBA */
#define AD5686PwrDwnAll (0x4UL << 8 * 0 + 4 | 0xaaUL << 8 * 2)
#define AD5686PwrUpAll (0x4UL << 8 * 0 + 4 | 0x00UL << 8 * 2)
#define AD5686ReadBack (0x9UL << 8 * 0 + 4)
#define AD5686FrameLength 3 /*byte */
// #define AD5686PwrDwn(channel)       ((0x4UL<< 20 | 0x2UL << (2*channel)) << 8) /*channel :0-3 */
// #define AD5686PwrUp(channel)        ((0x4UL<< 20 | 0x0UL << (2*channel)) << 8) /*channel :0-3 */

static int32_t WriteDAC8568(uint8_t *sendData)
{
    HAL_GPIO_WritePin(SPI3_DAC_AICS_GPIO_Port, SPI3_DAC_AICS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&SPIBUS, sendData, DAC8568FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_AICS_GPIO_Port, SPI3_DAC_AICS_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

static int32_t WriteAD5686(uint8_t *sendData)
{
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&SPIBUS, sendData, AD5686FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

static int32_t ReadbackAD5686(uint8_t *sendData)
{
    uint8_t recvData[4] = {0, 0, 0, 0};
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&SPIBUS, recvData, AD5686FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (recvData[0] != sendData[0] || recvData[1] != sendData[1] || recvData[2] != sendData[2])
    {
        ERROR("readback AD5686 err\r\n");
        return -1;
    }
    return 0;
}

int32_t DAC8568Init()
{
    uint32_t sendData = 0;
    /*reset dac8568 */
    sendData = DAC8568Rst;
    WriteDAC8568((uint8_t *)&sendData);
    /*ignore extern clr */
    sendData = DAC8568IgnExtClr;
    WriteDAC8568((uint8_t *)&sendData);
    /*power down internal referance */
    sendData = DAC8568PwrDwnItnRef;
    WriteDAC8568((uint8_t *)&sendData);
    /* clrae zero output*/
    sendData = DAC8568ClrZerio;
    WriteDAC8568((uint8_t *)&sendData);
    /* aet all pin power down */
    sendData = DAC8568PwrDwnAll;
    WriteDAC8568((uint8_t *)&sendData);
    return 0;
}

int32_t AD5686Init()
{
    uint32_t sendData = 0;
    /*software reset  */
    sendData = AD5686Rst;
    WriteAD5686((uint8_t *)&sendData);
    /*enable read back  */
    sendData = AD5686ReadBack;
    WriteAD5686((uint8_t *)&sendData);
    /*power down all dac */
    sendData = AD5686PwrDwnAll;
    WriteAD5686((uint8_t *)&sendData);
    return 0;
}

/**
 * write a dac channel
 * channel 0-3
 * data 0-0xffff
 * return 0,-1: success ,failure
 * */
int32_t WriteAD5686Value(uint32_t channel, uint32_t data)
{
    uint32_t sendData = 0;
    channel = 1 << channel;
    /*power up all dac */
    sendData = AD5686PwrUpAll;
    WriteAD5686((uint8_t *)&sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686((uint8_t *)&sendData))
    {
        return -1;
    }
    /*write data */
    sendData = AD5686WrtReg(channel, data);
    WriteAD5686((uint8_t *)&sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686((uint8_t *)&sendData))
    {
        return -1;
    }
    /*readback data last write */
    return 0;
}

/**input parameter 
 * channel 0-7
 * data 0-0xffff
 */
int32_t WriteDAC8568Value(uint32_t channel, uint32_t data)
{
    uint32_t sendData = 0;
    /**power up */
    sendData = DAC8568PwrUpAll;
    WriteDAC8568((uint8_t *)&sendData);
    /* write a channel */
    sendData = DAC8568WrtReg(channel, data);
    WriteDAC8568((uint8_t *)&sendData);
    return 0;
}

/**write all ch using the same value
 * data 0-0xffff
 * return 0
 */
int32_t WriteDAC8568AllCh(uint32_t data)
{
    uint32_t sendData = 0;
    /**power up */
    sendData = DAC8568PwrUpAll;
    WriteDAC8568((uint8_t *)&sendData);
    /**write data */
    sendData = DAC8568WrtAllReg(data);
    WriteDAC8568((uint8_t *)&sendData);
    return 0;
}

/**data : 0-0xffff
 * return : 0,-1 : success, failure
 */
int32_t WriteAD5686AllCh(uint32_t data)
{
    uint32_t sendData = 0;
    /*power up all dac */
    sendData = AD5686PwrUpAll;
    WriteAD5686((uint8_t *)&sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686((uint8_t *)&sendData))
    {
        return -1;
    }
    /*write data */
    sendData = AD5686WrtReg(0xfUL, data);
    WriteAD5686((uint8_t *)&sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686((uint8_t *)&sendData))
    {
        return -1;
    }
    /*readback data last write */
    return 0;
}
