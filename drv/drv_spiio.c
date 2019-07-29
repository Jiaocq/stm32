/**for mcp23s17 */
#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"

#define IOSPIBUS hspi2
#define TIMEOUT 1000 /*ms */
#define FrameLength 3

#define ReadReg(devId,regId)        (0x4UL << 28 | devId << 25 | 0x01UL << 24 | regId << 16)
#define WriteReg(devId,regId,data)  (0x4UL << 28 | devId << 25 | 0x00UL << 24 | regId << 16 | data << 8)
/* register address*/
#define IODIRA      0x00U    /* I/O DIRECTION REGISTER: 1-input, 0-output*/
#define IODIRB      0x01U
#define IPOLA       0x02U    /*INPUT POLARITY PORT REGISTER: 1-opposite logic, 0-same logic*/                                      */
#define IPOLB       0x03U
#define GPINTENA    0x04U    /*INTERRUPT-ON-CHANGE PINS*/
#define GPINTENB    0x05U
#define DEFVALA     0x06U    /*DEFAULT VALUE REGISTER*/
#define DEFVALB     0x07U
#define INTCONA     0x08U    /*INTERRUPT-ON-CHANGE CONTROL REGISTER*/
#define INTCONB     0x09U
#define IOCONA      0x0AU    /*I/O EXPANDER CONFIGURATION REGISTER*/
#define IOCONB      0x0BU
#define GPPUA       0x0CU    /*GPIO PULL-UP RESISTOR REGISTER*/
#define GPPUB       0x0DU
#define INTFA       0x0EU    /*INTERRUPT FLAG REGISTER*/
#define INTFB       0x0FU
#define INTCAPA     0x10U   /*INTERRUPT CAPTURED VALUE FOR PORT REGISTER*/
#define INTCAPB     0x11U
#define IOA         0x12U   /*GENERAL PURPOSE I/O PORT REGISTER:1-high, 0-low*/
#define IOB         0x13U
#define OLATA       0x14U   /*OUTPUT LATCH REGISTER: 1-high, 0-low*/
#define OLATB       0x15U

/** cs = MCU_SPI2_CS_DIDO_MCP23S17 */
#define FROMDO      0x0/**u17 */
#define TODI        0x4/**u18 */
#define TODO        0x5/**u21 */
#define FROMDI      0x3/**u20 */

/** cs = MCU_SPI2_CS_AIHIO_MCP23S17 */
#define FROMHIO     0x0 /**u93 */
#define TOFROMHIO   0x4/**u94 */
#define TOAI        0x3 /**u96 */

#define IOCONDATA   0x18

static uint32_t WriteDIDO(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 0);
    HAL_SPI_Transmit(&IOSPIBUS, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 1);
    DelayUs(5);
    return 0;
}

static uint32_t WriteAIHIO(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 0);
    HAL_SPI_Transmit(&IOSPIBUS, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 1);
    DelayUs(5);
    return 0;
}

int SpiioInit()
{

// 54     /*Configure all GPIO signed as SW1*/
//  255     Write23s17(MCP23S17_ADDR_0, IOCONA, 0x38U);
//  256     Write23s17(MCP23S17_ADDR_0, IODIRA, 0x00U);  /*Set GPA7~0 direction: output*/
//  257     Write23s17(MCP23S17_ADDR_0, OLATA, 0x00U);  /*Set GPA7~0 output: 1 */ /*Turn on SW1(Point_8~Point_15)*/
//  258     Write23s17(MCP23S17_ADDR_0, IOCONB, 0x38U);
//  259     Write23s17(MCP23S17_ADDR_0, IODIRB, 0x00U); /*GPB7~0: output*/
//  260     Write23s17(MCP23S17_ADDR_0, OLATB, 0x00U);  /*Turn on SW1(Point_0~Point_7)*/



    return 0;
}
