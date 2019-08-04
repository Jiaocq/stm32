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

static int32_t ReadAIAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    uint8_t recvData[2] = {0};
    uint8_t recvReg[2] = {0};
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&AIAdcSPIBUS, recvData, AIAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&AIAdcSPIBUS, recvReg, AIAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData[0] != recvReg[0] || sendData[1] != recvReg[1] & 0xf6)
    {
        DEBUG("ReadAIAdc err\r\n");
        return -1;
    }
    return (int32_t)(*((uint16_t *)recvData));
}

static uint16_t ReqAIAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&AIAdcSPIBUS, sendData, AIAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_CS_ADC_GPIO_Port, MCU_1_SPI4_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

static int32_t ReadDIGAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    uint8_t recvData[2] = {0};
    uint8_t recvReg[2] = {0};
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&DIGAdcSPIBUS, recvData, DIGAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&DIGAdcSPIBUS, recvReg, DIGAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData[0] != recvReg[0] || sendData[1] != recvReg[1] & 0xf6)
    {
        DEBUG("ReadDIGAdc err\r\n");
        return -1;
    }
    return (int32_t)(*((uint16_t *)recvData));
}

static uint16_t ReqDIGAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&DIGAdcSPIBUS, sendData, DIGAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_1_SPI4_DIGCS_ADC_GPIO_Port, MCU_1_SPI4_DIGCS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

static int32_t ReadHIOAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    uint8_t recvData[2] = {0};
    uint8_t recvReg[2] = {0};
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Receive(&HIOAdcSPIBUS, recvData, HIOAdcFrameLength, TIMEOUT);
    HAL_SPI_Receive(&HIOAdcSPIBUS, recvReg, HIOAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    if (sendData[0] != recvReg[0] || sendData[1] != recvReg[1] & 0xf6)
    {
        DEBUG("ReadHIOAdc err\r\n");
        return -1;
    }
    return (int32_t)(*((uint16_t *)recvData));
}

static uint16_t ReqHIOAdc(uint8_t channel)
{
    uint8_t sendData[2] = {0xe1 | channel << 1, 0xe0};
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&HIOAdcSPIBUS, sendData, HIOAdcFrameLength, TIMEOUT);
    HAL_GPIO_WritePin(HIO_SPI5_CS_ADC_GPIO_Port, HIO_SPI5_CS_ADC_Pin, GPIO_PIN_SET);
    DelayUs(5);
    return 0;
}

/**return 0 for no err */
int32_t AIAdcInit()
{
    int ret = 0;
    ReqAIAdc(0);
    ReqAIAdc(0);
    ret = ReadAIAdc(0);
    if (0 > ret)
        return ret;
    ReqAIAdc(1);
    ReqAIAdc(1);
    ret = ReadAIAdc(1);
    if (0 > ret)
        return ret;
    ReqAIAdc(2);
    ReqAIAdc(2);
    ret = ReadAIAdc(2);
    if (0 > ret)
        return ret;
    ReqAIAdc(3);
    ReqAIAdc(3);
    ret = ReadAIAdc(3);
    if (0 > ret)
        return ret;
    ReqAIAdc(4);
    ReqAIAdc(4);
    ret = ReadAIAdc(4);
    if (0 > ret)
        return ret;
    ReqAIAdc(5);
    ReqAIAdc(5);
    ret = ReadAIAdc(5);
    if (0 > ret)
        return ret;
    ReqAIAdc(6);
    ReqAIAdc(6);
    ret = ReadAIAdc(6);
    if (0 > ret)
        return ret;
    ReqAIAdc(7);
    ReqAIAdc(7);
    ret = ReadAIAdc(7);
    if (0 > ret)
        return ret;
    return 0;
}

/**return 0 for no err */
int32_t DIGAdcInit()
{
    int ret = 0;
    ReqDIGAdc(0);
    ReqDIGAdc(0);
    ret = ReadDIGAdc(0);
    if (0 > ret)
        return ret;
    ReqDIGAdc(1);
    ReqDIGAdc(1);
    ret = ReadDIGAdc(1);
    if (0 > ret)
        return ret;
    ReqDIGAdc(1);
    ReqDIGAdc(1);
    ret = ReadDIGAdc(2);
    if (0 > ret)
        return ret;
    ReqDIGAdc(3);
    ReqDIGAdc(3);
    ret = ReadDIGAdc(3);
    if (0 > ret)
        return ret;
    ReqDIGAdc(4);
    ReqDIGAdc(4);
    ret = ReadDIGAdc(4);
    if (0 > ret)
        return ret;
    ReqDIGAdc(5);
    ReqDIGAdc(5);
    ret = ReadDIGAdc(5);
    if (0 > ret)
        return ret;
    ReqDIGAdc(6);
    ReqDIGAdc(6);
    ret = ReadDIGAdc(6);
    if (0 > ret)
        return ret;
    ReqDIGAdc(7);
    ReqDIGAdc(7);
    ret = ReadDIGAdc(7);
    if (0 > ret)
        return ret;
    return 0;
}

/**return 0 for no err  */
int32_t HIOAdcInit()
{
    int ret = 0;
    for(uint8_t channel = 8;channel--;){
    ReqHIOAdc(channel);
    ReqHIOAdc(channel);
    if (0 > ReadHIOAdc(channel))
        ret -= 1;
    }
    return 0;
}

/**read adc channel
 * channel : 0-7
 * return -1 or >0 for err and channel value*/
int32_t AIReadCh(uint8_t channel)
{
    int32_t ret = 0;
    ReqAIAdc(channel);
    ReqAIAdc(channel);
    ret = ReadAIAdc(channel);
    return ret;
}

/**read adc channel
 * channel : 0-7
 * return -1 or >0 for err and channel value*/
int32_t HIOReadCh(uint8_t channel)
{
    int32_t ret = 0;
    ReqHIOAdc(channel);
    ReqHIOAdc(channel);
    ret = ReadHIOAdc(channel);
    return ret;
}

/**read adc channel
 * channel : 0-7
 * return -1 or >0 for err and channel value*/
int32_t DIGReadCh(uint8_t channel)
{
    int32_t ret = 0;
    ReqDIGAdc(channel);
    ReqDIGAdc(channel);
    ret = ReadDIGAdc(channel);
    return ret;
}
