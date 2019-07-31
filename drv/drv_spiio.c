/**for mcp23s17 */
#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"
#include "drv_spiio.h"

#define IOSPIBUS hspi2
#define TIMEOUT 1000 /*ms */
#define FrameLength 3

#define ReadReg(devId, regId) (0x4UL << 28 | devId << 25 | 0x01UL << 24 | regId << 16)
#define WriteReg(devId, regId, data) (0x4UL << 28 | devId << 25 | 0x00UL << 24 | regId << 16 | data << 8)
/* register address*/
#define IODIRA 0x00U /* I/O DIRECTION REGISTER: 1-input, 0-output*/
#define IODIRB 0x01U
#define IPOLA 0x02U /*INPUT POLARITY PORT REGISTER: 1-opposite logic, 0-same logic*/ * /
#define IPOLB 0x03U
#define GPINTENA 0x04U /*INTERRUPT-ON-CHANGE PINS*/
#define GPINTENB 0x05U
#define DEFVALA 0x06U /*DEFAULT VALUE REGISTER*/
#define DEFVALB 0x07U
#define INTCONA 0x08U /*INTERRUPT-ON-CHANGE CONTROL REGISTER*/
#define INTCONB 0x09U
#define IOCONA 0x0AU /*I/O EXPANDER CONFIGURATION REGISTER*/
#define IOCONB 0x0BU
#define GPPUA 0x0CU /*GPIO PULL-UP RESISTOR REGISTER*/
#define GPPUB 0x0DU
#define INTFA 0x0EU /*INTERRUPT FLAG REGISTER*/
#define INTFB 0x0FU
#define INTCAPA 0x10U /*INTERRUPT CAPTURED VALUE FOR PORT REGISTER*/
#define INTCAPB 0x11U
#define IOA 0x12U /*GENERAL PURPOSE I/O PORT REGISTER:1-high, 0-low*/
#define IOB 0x13U
#define OLATA 0x14U /*OUTPUT LATCH REGISTER: 1-high, 0-low*/
#define OLATB 0x15U

/**init status */
static int initStatus = 0;

static uint8_t ReadDIDO(uint32_t sendData)
{
    uint32_t readData = 0;
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 0);
    HAL_SPI_TransmitReceive(&IOSPIBUS, (uint8_t *)&readData, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 1);
    DelayUs(5);
    return (uint8_t)((0xffUL) & (readData >> 8));
}

static uint8_t ReadAIHIO(uint32_t sendData)
{
    uint32_t readData = 0;
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 0);
    HAL_SPI_TransmitReceive(&IOSPIBUS, (uint8_t *)&readData, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 1);
    DelayUs(5);
    return (uint8_t)((0xffUL) & (readData >> 8));
}

static int32_t WriteDIDO(uint32_t sendData)
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

/**deinit spi io */
static void MCP23S17DIDODeinit(uint8_t devAddr)
{
    /** set FROMDO's IOCON , input mode */
    WriteDIDO(WriteReg(devAddr, IOCONA, 0x38));
    WriteDIDO(WriteReg(devAddr, IOCONB, 0x38));
    WriteDIDO(WriteReg(devAddr, IODIRA, 0xff));
    WriteDIDO(WriteReg(devAddr, IODIRB, 0xff));
}

static void MCP23S17AIHIODeinit(uint8_t devAddr)
{
    /** set FROMDO's IOCON , input mode */
    WriteAIHIO(WriteReg(devAddr, IOCONA, 0x38));
    WriteAIHIO(WriteReg(devAddr, IOCONB, 0x38));
    WriteAIHIO(WriteReg(devAddr, IODIRA, 0xff));
    WriteAIHIO(WriteReg(devAddr, IODIRB, 0xff));
}

/**reaet all mcp23s17 */
int SpiioDeinit()
{
    /** configure  */
    /**reset all gpio */
    HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port, MCU_SPI2_RESET_MCP23S17_Pin, 0);
    DelayUs(5);
    HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port, MCU_SPI2_RESET_MCP23S17_Pin, 1);
    /** set DIDO , input mode */
    MCP23S17DIDODeinit(FROMDO);
    MCP23S17DIDODeinit(TODI);
    MCP23S17DIDODeinit(TODO);
    MCP23S17DIDODeinit(FROMDI);
    /** set AIHIO , input mode */
    MCP23S17AIHIODeinit(FROMHIO);
    MCP23S17AIHIODeinit(TOFROMHIO);
    MCP23S17AIHIODeinit(TOAI);
    initStatus = 0;
    return 0;
}

/**init all mcp23s17 */
int SpiioIinit()
{
    /** configure  */
    /** reset all gpio */
    SpiioDeinit();
    /*init FROMDO in inputmode, but nothing to be done,high to high*/
    if (0x38 == ReadDIDO(ReadReg(FROMDO, IOCONA)))
        return -1;
    if (0x38 == ReadDIDO(ReadReg(FROMDO, IOCONB)))
        return -1;
    if (0xff == ReadDIDO(ReadReg(FROMDO, IODIRA)))
        return -1;
    if (0xff == ReadDIDO(ReadReg(FROMDO, IODIRB)))
        return -1;
    /*init TODI in output mode, and high level to close dev*/
    WriteDIDO(WriteReg(TODI, OLATA, 0xff));
    WriteDIDO(WriteReg(TODI, OLATB, 0xff));
    WriteDIDO(WriteReg(TODI, IODIRA, 0x00));
    WriteDIDO(WriteReg(TODI, IODIRB, 0x00));
    WriteDIDO(WriteReg(TODI, OLATA, 0xff));
    WriteDIDO(WriteReg(TODI, OLATB, 0xff));
    if (0x38 == ReadDIDO(ReadReg(TODI, IOCONA)))
        return -1;
    if (0x38 == ReadDIDO(ReadReg(TODI, IOCONB)))
        return -1;
    if (0x00 == ReadDIDO(ReadReg(TODI, IODIRA)))
        return -1;
    if (0x00 == ReadDIDO(ReadReg(TODI, IODIRB)))
        return -1;
    if (0xff == ReadDIDO(ReadReg(TODI, OLATA)))
        return 0;
    if (0xff == ReadDIDO(ReadReg(TODI, OLATB)))
        return 0;
    /*init TODO  in output mode, and high level to close */
    WriteDIDO(WriteReg(TODO, OLATA, 0xff));
    WriteDIDO(WriteReg(TODO, OLATB, 0xff));
    WriteDIDO(WriteReg(TODO, IODIRA, 0x00));
    WriteDIDO(WriteReg(TODO, IODIRB, 0x00));
    WriteDIDO(WriteReg(TODO, OLATA, 0xff));
    WriteDIDO(WriteReg(TODO, OLATB, 0xff));
    if (0x38 != ReadDIDO(ReadReg(TODO, IOCONA)))
        return -1;
    if (0x38 != ReadDIDO(ReadReg(TODO, IOCONB)))
        return -1;
    if (0x00 != ReadDIDO(ReadReg(TODO, IODIRA)))
        return -1;
    if (0x00 != ReadDIDO(ReadReg(TODO, IODIRB)))
        return -1;
    if (0xff != ReadDIDO(ReadReg(TODO, OLATA)))
        return -1;
    if (0xff != ReadDIDO(ReadReg(TODO, OLATB)))
        return -1;
    /*init FROMDI in inputmode, but nothing to be done, hirh to high*/
    if (0x38 != ReadDIDO(ReadReg(FROMDI, IOCONA)))
        return -1;
    if (0x38 != ReadDIDO(ReadReg(FROMDI, IOCONB)))
        return -1;
    if (0xff != ReadDIDO(ReadReg(FROMDI, IODIRA)))
        return -1;
    if (0xff != ReadDIDO(ReadReg(FROMDI, IODIRB)))
        return -1;
    /**init FROMHIO in inputmode, but nothing to be done, high to high*/
    if (0x38 != ReadAIHIO(ReadReg(FROMDI, IOCONA)))
        return -1;
    if (0x38 != ReadAIHIO(ReadReg(FROMDI, IOCONB)))
        return -1;
    if (0xff != ReadAIHIO(ReadReg(FROMDI, IODIRA)))
        return -1;
    if (0xff != ReadAIHIO(ReadReg(FROMDI, IODIRB)))
        return -1;
    /**init TOFROMHIO IOB0-7 :output, low level to close other dev
    * IOA 0-7 : input , if high level input ,it is high level */
    WriteAIHIO(WriteReg(TOFROMHIO, IODIRA, 0x0f));
    WriteAIHIO(WriteReg(TOFROMHIO, OLATB, 0x00));
    WriteAIHIO(WriteReg(TOFROMHIO, IODIRB, 0x00));
    WriteAIHIO(WriteReg(TOFROMHIO, OLATB, 0x00));
    if (0x38 != ReadAIHIO(ReadReg(TOFROMHIO, IOCONA)))
        return -1;
    if (0x38 != ReadAIHIO(ReadReg(TOFROMHIO, IOCONB)))
        return -1;
    if (0x0f != ReadAIHIO(ReadReg(TOFROMHIO, IODIRA)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TOFROMHIO, IODIRB)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TOFROMHIO, OLATA)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TOFROMHIO, OLATB)))
        return -1;
    /*init TOAI output, low level to close other dev*/
    WriteAIHIO(WriteReg(TODI, OLATA, 0x00));
    WriteAIHIO(WriteReg(TODI, OLATB, 0x00));
    WriteAIHIO(WriteReg(TODI, IODIRA, 0x00));
    WriteAIHIO(WriteReg(TODI, IODIRB, 0x00));
    WriteAIHIO(WriteReg(TODI, OLATA, 0x00));
    WriteAIHIO(WriteReg(TODI, OLATB, 0x00));
    if (0x38 != ReadAIHIO(ReadReg(TODI, IOCONA)))
        return -1;
    if (0x38 != ReadAIHIO(ReadReg(TODI, IOCONB)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TODI, IODIRA)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TODI, IODIRB)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TODI, OLATA)))
        return -1;
    if (0x00 != ReadAIHIO(ReadReg(TODI, OLATB)))
        return -1;
    initStatus = 1;
    return 0;
}

/**read a pin
 * devId : FROMDO   TODI     TODO     FROMDI       
 * pinId : 0-15
 * return -1,0 ,1 : err , 0,  1
 * */
int ReadDIDOPin(uint8_t devId, uint8_t pinId)
{
    uint8_t ioState = 0;
    if (0 == initStatus)
        SpiioIinit();
    if (pinId < 8)
    {
        ioState = ReadDIDO(ReadReg(devId, IOA));
    }
    else if (pinId < 16)
    {
        ioState = ReadDIDO(ReadReg(devId, IOB));
        pinId -= 8;
    }
    else
        return -1;
    return ioState & (0x1 << pinId);
}

/**write a pin
 * devId : FROMDO   TODI     TODO     FROMDI      
 * pinId : 0-15
 */
int WriteDIDOPin(uint8_t devId, uint8_t pinId, uint8_t pinState)
{
    uint8_t ioState = 0;
    if (0 == initStatus)
        SpiioIinit();
    if (pinId < 8)
    {
        ioState = ReadDIDO(ReadReg(devId, OLATA));
        if (pinState)
            ioState |= (0x1 << pinId);
        else
            ioState &= (~(0x1 << pinId));
        WriteDIDO(WriteReg(devId, OLATA, ioState));
        if (ioState != ReadDIDO(ReadReg(devId, OLATA)))
            return -1;
        if (ioState != ReadDIDO(ReadReg(devId, IOA)))
            return -2;
    }
    else if (pinId < 16)
    {
        ioState = ReadDIDO(ReadReg(devId, OLATB));
        pinId -= 8;
        if (pinState)
            ioState |= (0x1 << pinId);
        else
            ioState &= (~(0x1 << pinId));
        WriteDIDO(WriteReg(devId, OLATB, ioState));
        if (ioState != ReadDIDO(ReadReg(devId, OLATB)))
            return -1;
        if (ioState != ReadDIDO(ReadReg(devId, IOB)))
            return -2;
    }
    else
        return -1;
    return 0;
}

/**read a pin
 * devId : FROMHIO  TOFROMHIO TOAI     
 * pinId : 0-15
 * return -1,0 ,1 : err , 0,  1
 * */
int ReadAIHIOPin(uint8_t devId, uint8_t pinId)
{
    uint8_t ioState = 0;
    if (0 == initStatus)
        SpiioIinit();
    if (pinId < 8)
    {
        ioState = ReadAIHIO(ReadReg(devId, IOA));
    }
    else if (pinId < 16)
    {
        ioState = ReadAIHIO(ReadReg(devId, IOB));
        pinId -= 8;
    }
    else
        return -1;
    return ioState & (0x1 << pinId);
}

/**write a pin
 * devId :  FROMHIO  TOFROMHIO TOAI     
 * pinId : 0-15
 * pinState : 0,1
 */
int WriteAIHIOPin(uint8_t devId, uint8_t pinId, uint8_t pinState)
{
    uint8_t ioState = 0;
    if (0 == initStatus)
        SpiioIinit();
    if (pinId < 8)
    {
        ioState = ReadAIHIO(ReadReg(devId, OLATA));
        if (pinState)
            ioState |= (0x1 << pinId);
        else
            ioState &= (~(0x1 << pinId));
        WriteAIHIO(WriteReg(devId, OLATA, ioState));
        if (ioState != ReadAIHIO(ReadReg(devId, OLATA)))
            return -1;
        if (ioState != ReadAIHIO(ReadReg(devId, IOA)))
            return -2;
    }
    else if (pinId < 16)
    {
        ioState = ReadAIHIO(ReadReg(devId, OLATB));
        pinId -= 8;
        if (pinState)
            ioState |= (0x1 << pinId);
        else
            ioState &= (~(0x1 << pinId));
        WriteAIHIO(WriteReg(devId, OLATB, ioState));
        if (ioState != ReadAIHIO(ReadReg(devId, OLATB)))
            return -1;
        if (ioState != ReadAIHIO(ReadReg(devId, IOB)))
            return -2;
    }
    else
        return -1;
    return 0;
}
