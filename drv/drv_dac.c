#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"

#define SPIBUS hspi3
#define TIMEOUT 1000 /*ms */

#define DAC8568ClrZerio (0x5UL << 8 * 0)
#define DAC8568IgnExtClr ((0x5UL << 8 * 0) | (0x3UL) << 8 * 3)
#define DAC8568Rst (0x7UL << 8 * 0)
#define DAC8568WrtReg(channel, data) (0x3UL << 8 * 0 | (channel << 4  | (data & 0xf000) >> 12 ) << 8 * 1 | ((data & 0x0ff0) >> 4) << 8 * 2 | ((data & 0x000f) << 4) << 8*3) /*channel 0-7, data 0-0xffff */
#define DAC8568WrtAllReg(data) (0x3UL << 8 * 0 | (0xf0UL | (data & 0xf000) >> 12 ) << 8 * 1 | ((data & 0x0ff0) >> 4) << 8 * 2 | ((data & 0x000f) << 4) << 8*3)
#define DAC8568PwrDwnAll (0x4UL << 8 * 0 | 0x2UL << 8 * 2 | 0xffUL << 8 * 3)
#define DAC8568PwrUpAll  (0x4UL << 8 * 0 | 0x0UL << 8 * 2 | 0xffUL << 8 * 3)
#define DAC8568PwrUpCh(channel)  (0x4UL << 8 * 0 | 0x0UL << 8 * 2 | 0x01UL << (8 * 3 + channel))
#define DAC8568PwrDwnItnRefFlx (0x9UL << 8 * 0 | 0x0cUL << 8 * 1)
#define DAC8568PwrDwnItnRefStc (0x8UL << 8 * 0 )
#define DAC8568FrameLength 4 /*byte */
#define DAC8568Gain 2UL

#define AD5686Rst (0x60UL << 8 * 0)
#define AD5686WrtReg(channel, data) (0x30UL << 8 * 0 | channel << 8 * 0 | (data & 0xffUL) << 8 * 2 | (data & 0xff00UL) << 8 * 0) /*channel DCBA */
#define AD5686PwrDwnAll (0x40UL << 8 * 0 | 0x55UL << 8 * 2)
#define AD5686PwrUpAll (0x40UL << 8 * 0)
#define AD5686PwrUpCh(channel) (0x40UL << 8 * 0 | (0xaaUL & ~(0x03UL << channel * 2)) << 8 * 2)
#define AD5686ReadBack (0x90UL << 8 * 0)
#define AD5686FrameLength 3 /*byte */
#define AD5686Gain 1UL

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

#if 0
static int32_t ReadbackAD5686(uint8_t *sendData)
{
    uint8_t recvData[4] = {0, 0, 0, 0};
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&SPIBUS, sendData, recvData, AD5686FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(SPI3_DAC_HIOCS_GPIO_Port, SPI3_DAC_HIOCS_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (recvData[0] != sendData[0] || recvData[1] != sendData[1] || recvData[2] != sendData[2])
    {
        ERROR("readback AD5686 err\r\n");
        return -recvData[0];
    }
    return 0;
}
#endif

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
    sendData = DAC8568PwrDwnItnRefStc;
    WriteDAC8568((uint8_t *)&sendData);
    sendData = DAC8568PwrDwnItnRefFlx;
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
    /*power up all dac */
    sendData = AD5686PwrUpCh(channel);
    WriteAD5686((uint8_t *)&sendData);
    /*write data */
    channel = 1 << channel;
    data &= 0xffffUL;
    data /= AD5686Gain;
    sendData = AD5686WrtReg(channel, data);
    WriteAD5686((uint8_t *)&sendData);
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
    sendData = DAC8568PwrDwnAll;
    WriteDAC8568((uint8_t *)&sendData);
    sendData = DAC8568PwrUpCh(channel);
    WriteDAC8568((uint8_t *)&sendData);
    /* write a channel */
    data &= 0xffffUL;
    data /= DAC8568Gain;
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
    data &= 0xffffUL;
    data /= DAC8568Gain;
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
    WriteDAC8568((uint8_t *)&sendData);
    /*write data */
    data &= 0xffffUL;
    data /= AD5686Gain;
    sendData = AD5686WrtReg(0xfUL, data);
    WriteAD5686((uint8_t *)&sendData);
    return 0;
}
