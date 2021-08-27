/********************************************************************************
 * @headerfile    I2C_Init.h
 * @brief         Header file for I2C module on TM4C123GH6PM Microcontroller
 * @date          25/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *******************************************************************************/

#ifndef DRIVERS_I2C_I2C_INIT_H_
#define DRIVERS_I2C_I2C_INIT_H_

#include "std_types.h"
#include "common_macros.h"

/*******************************************************************************
 *                     Defines used in I2c_Config Variables                   *
 *******************************************************************************/
/* Define used to choose which mode is the I2C is operating with    */
#define I2C_MODE_MASTER               (0x10)    /* Master Mode Enable value in MCR Reg */
#define I2C_MODE_SLAVE                (0x20)    /* Slave  Mode Enable value in MCR Reg */
#define I2C_MODE_LOOPBACK             (0x01)    /* LoopBack Enable value in MCR Reg    */

/* Define used to indicate which transmit mode the I2C will operate
 * Note: Multiple Mode is supported on Master Mode only */
#define I2C_TRANSMIT_MODE_SINGLE      (0x0)
#define I2C_TRANSMIT_MODE_MULTIPLE    (0x1)

/* Define used to indicate which receive mode the I2C will operate
 * Note: Multiple Mode is supported on Master Mode only */
#define I2C_RECEIVE_MODE_SINGLE       (0x0)
#define I2C_RECEIVE_MODE_MULTIPLE     (0x1)

/*******************************************************************************
 *                              User Defined Data Types                        *
 *******************************************************************************/
/*******************************************************************************
 * @enum    I2c_Instance
 * @brief   Enum Holds I2C Instances in TM4C123GH6PM
 *******************************************************************************/
typedef enum{
    I2c0,//!< I2c0
    I2c1,//!< I2c1
    I2c2,//!< I2c2
    I2c3 //!< I2c3
}I2c_Instance;


/*******************************************************************************
 * @enum    I2c_Interrupts
 * @brief   Enum Holds interrupt bits location in the register
 *******************************************************************************/
typedef enum{
    I2cInterruptsDisabled,                                   //!< I2cInterruptsDisabled
    I2cInterruptMaskMasterInterrupt                 = (1<<0),//!< I2cInterruptMaskMasterInterrupt
    I2cInterruptMaskMasterClockTimeoutInterrupt     = (1<<1),//!< I2cInterruptMaskMasterClockTimeoutInterrupt
    I2cInterruptMaskSlaveDataInterrupt              = (1<<0),//!< I2cInterruptMaskSlaveDataInterrupt
    I2cInterruptMaskSlaveStartConditionInterrupt    = (1<<1),//!< I2cInterruptMaskSlaveStartConditionInterrupt
    I2cInterruptMaskSlaveStopConditionInterrupt     = (1<<2) //!< I2cInterruptMaskSlaveStopConditionInterrupt
}I2c_Interrupts;


/*********************************************************************************************************
 * @struct  I2c_Config
 *
 * @brief   Structure Holds I2C Configuration Parameters
 *
 * @var     I2c_Config::I2cNum
 *          Member 'I2cNum' used to indicate which SSI needs to be configured
 *          You can find its value @ref I2c_Instance
 *
 * @var     I2c_Config::I2cInterrupts
 *          Member 'I2cInterrupts' used to choose Interrupts enabled from SSI module or disable all interrupts
 *          You can find this value @ref I2cInterrupts
 *
 * @var     I2c_Config::I2cFreq
 *          Member 'I2cFreq' used to indicate the Required frequency needed for I2C to operate with
 *
 * @var     I2c_Config::ClkValue
 *          Member 'ClkValue' used to calculate the required Frequency for I2C
 *           @note This value should given by a API used to get system clk (Future work)
 *
 * @var     I2c_Config::I2cMode
 *          Member 'I2cMode' used to choose which mode is the I2C is operating with (Master, Slave)
 *          You can find this value @ref I2C_MODE
 *
 * @var     I2c_Config::I2cSlaveAddress
 *          Member 'I2cSlaveAddress' used to set the slave address of the master node or the slave node itself
 *
 * @var     I2c_Config::I2cTransmitMode
 *          Member 'I2cTransmitMode' used to decide if The master will transmit with Single Transmit or Multiple Data
 *          You can find this value @ref I2C_TRANSMIT_MODE
 *
 * @var     I2c_Config::I2cReceiveMode
 *          Member 'I2cReceiveMode' used to decide if The master will Receive with Single Receive or Multiple Data
 *          You can find this value @ref I2C_RECEIVE_MODE
 ***************************************************************************************************************/
typedef struct{

    I2c_Instance    I2cNum;             /** Member 'I2cNum' used to indicate which SSI
                                            needs to be configured
                                            You can find its value @ref I2c_Instance            */

    I2c_Interrupts  I2cInterrupts;      /** Member 'I2cInterrupts' used to choose
                                            Interrupts enabled from SSI module or disable
                                            all interrupts
                                            You can find this value @ref I2cInterrupts          */

    uint32          I2cFreq;            /** Member 'I2cFreq' used to indicate the
                                            Required frequency needed for I2C to operate with   */


    uint32          ClkValue;           /** Member 'ClkValue' used to calculate the
                                            required Frequency for I2C
                                            @note This value should given by a API used to
                                            get system clk (Future work)                        */

    uint8           I2cMode;            /** Member 'I2cMode' used to choose which mode
                                            is the I2C is operating with (Master, Slave)
                                            You can find this value @ref I2C_MODE               */

    uint8           I2cSlaveAddress;    /** Member 'I2cSlaveAddress' used to set the slave
                                            address of the master node or the slave node itself */

    uint8           I2cTransmitMode;    /** Member 'I2cTransmitMode' used to decide if
                                            The master will transmit with Single Transmit or
                                            Multiple Data
                                            You can find this value @ref I2C_TRANSMIT_MODE      */

    uint8           I2cReceiveMode;    /** Member 'I2cReceiveMode' used to decide if
                                            The master will Receive with Single Receive or
                                            Multiple Data
                                            You can find this value @ref I2C_RECEIVE_MODE      */

}I2c_Config;


/*******************************************************************************
 *                              Functions Prototypes                          *
 *******************************************************************************/
void I2c0_SetCallBack(void (*f_ptr)(void));
void I2c1_SetCallBack(void (*f_ptr)(void));
void I2c2_SetCallBack(void (*f_ptr)(void));
void I2c3_SetCallBack(void (*f_ptr)(void));
uint8 I2c_Init(const I2c_Config* ConfigPtr);
uint8 I2c_Transmit(const I2c_Config* ConfigPtr, const uint8* DataPtr, uint8 BufferSize);
uint8 I2c_Receive(const I2c_Config* ConfigPtr, uint8* DataPtr, uint8 BufferSize);
#endif /* DRIVERS_I2C_I2C_PRIV_H_ */
