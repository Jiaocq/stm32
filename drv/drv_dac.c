#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"

#define SPIBUS hspi3
#define TIMEOUT 1000 /*ms */

#define DAC8568ClrZerio (0x5UL << 24)
#define DAC8568IgnExtClr ((0x5UL << 24) | (0x3UL))
#define DAC8568Rst (0x7UL << 24)
#define DAC8568WrtReg(channel, data) (0x3UL << 24 | channel << 20 | data << 4) /*channel 0-7, data 0-0xffff */
#define DAC8568WrtAllReg(data) (0x3UL << 24 | 0xfUL << 20 | data << 4)
#define DAC8568PwrDwnAll (0x4UL << 24 | 0x0UL << 8 | 0xffUL)
#define DAC8568PwrUpAll (0x4UL << 24 | 0x2UL << 8 | 0xffUL)
#define DAC8568PwrDwnItnRef (0x9UL << 24 | 0xaUL << 17)
#define DAC8568FrameLength 4 /*byte */

#define AD5686Rst ((0x6UL << 20) << 8)
#define AD5686WrtReg(channel, data) ((0x3UL << 20 | channel << 16 | data << 4) << 8) /*channel DCBA */
#define AD5686PwrDwnAll ((0x4UL << 20 | 0xaaUL) << 8)
#define AD5686PwrUpAll ((0x4UL << 20 | 0x00UL) << 8)
#define AD5686ReadBack ((0x9UL << 20) << 8)
#define AD5686FrameLength 3 /*byte */
// #define AD5686PwrDwn(channel)       ((0x4UL<< 20 | 0x2UL << (2*channel)) << 8) /*channel :0-3 */
// #define AD5686PwrUp(channel)        ((0x4UL<< 20 | 0x0UL << (2*channel)) << 8) /*channel :0-3 */

static int32_t WriteDAC8568(uint32_t sendData)
{
    HAL_GPIO_WritePin(SPI3_DAC_AICS_GPIO_Port, SPI3_DAC_AICS_Pin, 0);
    HAL_SPI_Transmit(&SPIBUS, (uint8_t *)&sendData, DAC8568FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_AICS_GPIO_Port, SPI3_DAC_AICS_Pin, 1);
    DelayUs(5);
    return 0;
}

static int32_t WriteAD5686(uint32_t sendData)
{
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, 0);
    HAL_SPI_Transmit(&SPIBUS, (uint8_t *)&sendData, AD5686FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, 1);
    DelayUs(5);

    return 0;
}

static int32_t ReadbackAD5686(uint32_t sendData)
{
    uint32_t recvData = 0;
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, 0);
    HAL_SPI_Receive(&SPIBUS, (uint8_t *)&recvData, AD5686FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, 1);
    DelayUs(5);
    if (recvData ^ sendData)
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
    WriteDAC8568(sendData);
    /*ignore extern clr */
    sendData = DAC8568IgnExtClr;
    WriteDAC8568(sendData);
    /*power down internal referance */
    sendData = DAC8568PwrDwnItnRef;
    WriteDAC8568(sendData);
    /* clrae zero output*/
    sendData = DAC8568ClrZerio;
    WriteDAC8568(sendData);
    /* aet all pin power down */
    sendData = DAC8568PwrDwnAll;
    WriteDAC8568(sendData);
    return 0;
}

int32_t AD5686Init()
{
    uint32_t sendData = 0;
    /*software reset  */
    sendData = AD5686Rst;
    WriteAD5686(sendData);
    /*enable read back  */
    sendData = AD5686ReadBack;
    WriteAD5686(sendData);
    /*power down all dac */
    sendData = AD5686PwrDwnAll;
    WriteAD5686(sendData);
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
    WriteAD5686(sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686(sendData))
    {
        return -1;
    }
    /*write data */
    sendData = AD5686WrtReg(channel, data);
    WriteAD5686(sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686(sendData))
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
    WriteDAC8568(sendData);
    /* write a channel */
    sendData = DAC8568WrtReg(channel, data);
    WriteDAC8568(sendData);
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
    WriteDAC8568(sendData);
    /**write data */
    sendData = DAC8568WrtAllReg(data);
    WriteDAC8568(sendData);
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
    WriteAD5686(sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686(sendData))
    {
        return -1;
    }
    /*write data */
    sendData = AD5686WrtReg(0xfUL, data);
    WriteAD5686(sendData);
    /*readback data last write */
    if (0 != ReadbackAD5686(sendData))
    {
        return -1;
    }
    /*readback data last write */
    return 0;
}
