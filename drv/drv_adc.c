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
    if (sendData[0] != recvReg[0] || sendData[1] != (recvReg[1] & 0xfc))
    {
        DEBUG("ReadAIAdc err\r\n");
        return -1;
    }
    return ((int32_t )recvData[0] << 8 | (int32_t) recvData[1] );
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
    if (sendData[0] != recvReg[0] || sendData[1] != (recvReg[1] & 0xfc))
    {
        DEBUG("ReadDIGAdc err\r\n");
        return -1;
    }
    return ((int32_t )recvData[0] << 8 | (int32_t) recvData[1] );
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
    if (sendData[0] != recvReg[0] || sendData[1] != (recvReg[1] & 0xfc))
    {
        DEBUG("ReadHIOAdc err\r\n");
        return -1;
    }
    return ((int32_t )recvData[0] << 8 | (int32_t) recvData[1] );
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
    for (uint8_t channel = 8; channel--;)
    {
        ReqAIAdc(channel);
        ReqAIAdc(channel);
        if (0 > ReadAIAdc(channel))
            ret -= 1;
    }
    return ret;
}

/**return 0 for no err */
int32_t DIGAdcInit()
{
    int ret = 0;
    for (uint8_t channel = 8; channel--;)
    {
        ReqDIGAdc(channel);
        ReqDIGAdc(channel);
        if (0 > ReadDIGAdc(channel))
            ret -= 1;
    }
    return ret;
}

/**return 0 for no err  */
int32_t HIOAdcInit()
{
    int ret = 0;
    for (uint8_t channel = 8; channel--;)
    {
        ReqHIOAdc(channel);
        ReqHIOAdc(channel);
        if (0 > ReadHIOAdc(channel))
            ret -= 1;
    }
    return ret;
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
