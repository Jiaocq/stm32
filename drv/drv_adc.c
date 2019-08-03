/**for AD7689
 * 
 */
#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"
#include "main.h"

#define AIAdcSPIBUS hspi4  /**u88 u91 */
#define DIGAdcSPIBUS hspi4 /**u88 u91 */
#define HIOAdcSPIBUS hspi5
#define TIMEOUT 1000 /*ms */
#define AIAdcFrameLength 2
#define DIGAdcFrameLength 2
#define HIOAdcFrameLength 2

#define __AD7689ReadCfg(channel) ((0x1UL << 13 | 0x6UL << 10 | channel << 7 | 0x1UL << 6 | 0x7UL << 3 | 0x1UL << 1) << 2) /**channel 0-7 */
#define AD7689ReadCfg(channel) (__AD7689ReadCfg(channel) >> 8 | __AD7689ReadCfg(channel) << 8)/**format to big endian channel 0-7 */

struct CFG
{
    uint16_t nop : 2;
    uint16_t readBack : 1;
    uint16_t channelSequencer : 2;
    uint16_t reference : 3;
    uint16_t lowPassFilter : 1;
    uint16_t channel : 3;
    uint16_t channelConfig : 3;
    uint16_t cfgUpdate : 1;
};

static int32_t ReadAIAdc(uint32_t sendData)
{
    uint32_t recvData = 0;
    uint32_t recvReg = 0;
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&AIAdcSPIBUS, (uint8_t *)&recvData, AIAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&AIAdcSPIBUS, (uint8_t *)&recvReg, AIAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData ^ recvReg)
    {
        DEBUG("ReadAIAdc err\r\n");
        return -1;
    }
    return (int32_t)recvData;
}

static uint16_t ReqAIAdc(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&AIAdcSPIBUS, (uint8_t *)&sendData, AIAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

static int32_t ReadDIGAdc(uint32_t sendData)
{
    uint32_t recvData = 0;
    uint32_t recvReg = 0;
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&DIGAdcSPIBUS, (uint8_t *)&recvData, DIGAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&DIGAdcSPIBUS, (uint8_t *)&recvReg, DIGAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData ^ recvReg)
    {
        DEBUG("ReadDIGAdc err\r\n");
        return -1;
    }
    return (int32_t)recvData;
}

static uint16_t ReqDIGAdc(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&DIGAdcSPIBUS, (uint8_t *)&sendData, DIGAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);

    return 0;
}

static int32_t ReadHIOAdc(uint32_t sendData)
{
    uint32_t recvData = 0;
    uint32_t recvReg = 0;
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&HIOAdcSPIBUS, (uint8_t *)&recvData, HIOAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&HIOAdcSPIBUS, (uint8_t *)&recvReg, HIOAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData ^ recvReg)
    {
        DEBUG("ReadHIOAdc err\r\n");
        return -1;
    }
    return (int32_t)recvData;
}

static uint16_t ReqHIOAdc(uint32_t sendData)
{
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&HIOAdcSPIBUS, (uint8_t *)&sendData, HIOAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

/**return 0 for no err */
int32_t AIAdcInit()
{
    int ret = 0;
    ReqAIAdc(AD7689ReadCfg(0));
    ret = ReadAIAdc(AD7689ReadCfg(0));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(1));
    ret = ReadAIAdc(AD7689ReadCfg(1));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(2));
    ret = ReadAIAdc(AD7689ReadCfg(2));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(3));
    ret = ReadAIAdc(AD7689ReadCfg(3));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(4));
    ret = ReadAIAdc(AD7689ReadCfg(4));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(5));
    ret = ReadAIAdc(AD7689ReadCfg(5));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(6));
    ret = ReadAIAdc(AD7689ReadCfg(6));
    if (0 > ret)
        return ret;
    ReqAIAdc(AD7689ReadCfg(7));
    ret = ReadAIAdc(AD7689ReadCfg(7));
    if (0 > ret)
        return ret;
    return 0;
}

/**return 0 for no err */
int32_t DIGAdcInit()
{
    int ret = 0;
    ReqDIGAdc(AD7689ReadCfg(0));
    ret = ReadDIGAdc(AD7689ReadCfg(0));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(1));
    ret = ReadDIGAdc(AD7689ReadCfg(1));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(2));
    ret = ReadDIGAdc(AD7689ReadCfg(2));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(3));
    ret = ReadDIGAdc(AD7689ReadCfg(3));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(4));
    ret = ReadDIGAdc(AD7689ReadCfg(4));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(5));
    ret = ReadDIGAdc(AD7689ReadCfg(5));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(6));
    ret = ReadDIGAdc(AD7689ReadCfg(6));
    if (0 > ret)
        return ret;
    ReqDIGAdc(AD7689ReadCfg(7));
    ret = ReadDIGAdc(AD7689ReadCfg(7));
    if (0 > ret)
        return ret;
    return 0;
}

/**return 0 for no err  */
int32_t HIOAdcInit()
{
    int ret = 0;
    ReqHIOAdc(AD7689ReadCfg(0));
    ret = ReadHIOAdc(AD7689ReadCfg(0));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(1));
    ret = ReadHIOAdc(AD7689ReadCfg(1));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(2));
    ret = ReadHIOAdc(AD7689ReadCfg(2));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(3));
    ret = ReadHIOAdc(AD7689ReadCfg(3));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(4));
    ret = ReadHIOAdc(AD7689ReadCfg(4));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(5));
    ret = ReadHIOAdc(AD7689ReadCfg(5));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(6));
    ret = ReadHIOAdc(AD7689ReadCfg(6));
    if (0 > ret)
        return ret;
    ReqHIOAdc(AD7689ReadCfg(7));
    ret = ReadHIOAdc(AD7689ReadCfg(7));
    if (0 > ret)
        return ret;
    return 0;
}

/**read adc channel 
 * channel : 0-7 
 * return -1 or >0 for err and channel value*/
int32_t AIReadCh(uint32_t channel)
{
    int32_t ret = 0;
    ReqAIAdc(AD7689ReadCfg(channel));
    ret = ReadAIAdc(AD7689ReadCfg(channel));
    return ret;
}

/**read adc channel
 * channel : 0-7 
 * return -1 or >0 for err and channel value*/
int32_t HIOReadCh(uint32_t channel)
{
    int32_t ret = 0;
    ReqHIOAdc(AD7689ReadCfg(channel));
    ret = ReadHIOAdc(AD7689ReadCfg(channel));
    return ret;
}

/**read adc channel
 * channel : 0-7 
 * return -1 or >0 for err and channel value*/
int32_t DIGReadCh(uint32_t channel)
{
    int32_t ret = 0;
    ReqDIGAdc(AD7689ReadCfg(channel));
    ret = ReadDIGAdc(AD7689ReadCfg(channel));
    return ret;
}
