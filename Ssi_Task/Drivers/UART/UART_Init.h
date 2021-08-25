/********************************************************************************
 * @headerfile    UART_Init.h
 * @brief         Header file for UART module on TM4C123GH6PM Microcontroller
 * @date          15/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *                - Handling Interrupts from UART1 -> UART7
 *                - FIFO Mode
 *                - 9-Bit Mode
 *******************************************************************************/

#ifndef DRIVERS_UART_UART_INIT_H_
#define DRIVERS_UART_UART_INIT_H_

#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                     Defines used in Uart_Config Variables                   *
 *******************************************************************************/
/* Define used to choose how many stop bits needed  */
#define STOP_BITS_1_BIT             (0U)
#define STOP_BITS_2_BITS            (1U)

/* Define used to choose Parity mode                */
#define PARITY_MODE_DISABLE         (0U)
#define PARITY_MODE_EVEN            (1U)
#define PARITY_MODE_ODD             (2U)

/* Define used to choose FIFO Mode (Future work)    */
#define FIFO_MODE_DISABLE           (0U)
#define FIFO_MODE_ENABLE            (1U)

/* Define used to choose Baud Rate Clock source     */
#define UART_CLOCK_SRC_SYSTEM       (0U)
#define UART_CLOCK_SRC_PIOSC        (5U)    /* Value on Data sheet */

/* Defines used for portability only */
#define CLOCK_SRC_SYSTEM            UART_CLOCK_SRC_SYSTEM
#define CLOCK_SRC_PIOSC             UART_CLOCK_SRC_PIOSC

/*******************************************************************************
 *                              User Defined Data Types                        *
 *******************************************************************************/

/*******************************************************************************
 * @enum    Uart_Instance
 * @brief   Enum Holds UART Instances in TM4C123GH6PM
 *******************************************************************************/
typedef enum{
    Uart0,//!< UART0
    Uart1,//!< UART1
    Uart2,//!< UART2
    Uart3,//!< UART3
    Uart4,//!< UART4
    Uart5,//!< UART5
    Uart6,//!< UART6
    Uart7 //!< UART7
}Uart_Instance;


/*******************************************************************************
 * @enum    Uart_WordLength
 * @brief   Enum holds Word length for UART Tx/Rx
 ******************************************************************************/
typedef enum{
    FiveBits, //!< FiveBits
    SixBits,  //!< SixBits
    SevenBits,//!< SevenBits
    EightBits,//!< EightBits
    NineBits  //!< NineBits
}Uart_WordLength;

/*******************************************************************************
 * @enum    Uart_Interrupts
 * @brief   Enum Holds interrupt bits location in the register
 *******************************************************************************/
typedef enum{
    InterruptsDisbaled,                     //!< InterruptsDisbaled
    InterruptMaskClearToSendModem = (1<<1), //!< InterruptMaskClearToSendModem
    InterruptMaskReceive          = (1<<4), //!< InterruptMaskReceive
    InterruptMaskTransmit         = (1<<5), //!< InterruptMaskTransmit
    InterruptMaskReceiveTimeOut   = (1<<6), //!< InterruptMaskReceiveTimeOut
    InterruptMaskFramingError     = (1<<7), //!< InterruptMaskFramingError
    InterruptMaskParityError      = (1<<8), //!< InterruptMaskParityError
    InterruptMaskBreakError       = (1<<9), //!< InterruptMaskBreakError
    InterruptMaskOverRunError     = (1<<10),//!< InterruptMaskOverRunError
    InterruptMask9BitMode         = (1<<12) //!< InterruptMask9BitMode
}Uart_Interrupts;


/*******************************************************************************
 * @struct Uart_Config
 *
 * @brief  Structure holds UART Configuration Parameters
 *
 * @var    Uart_Config::UartNum
 *         Member 'UartNum' used to indicate which UART needs to be configured
 *         You can find its value @ref Uart_Instance
 *
 * @var    Uart_Config::WordLength
 *         Member 'WordLength' used to decide how many bits needed for UART Tx/Rx
 *         You can find this value @ref WordLength
 *
 * @var    Uart_Config::ClkValue
 *         Member 'ClkValue' used to calculate the required BaudRate
 *         @note This value should given by a API used to get system clk (Future work)
 *
 * @var    Uart_Config::BaudRate
 *         Member 'BaudRate' used to decide which Baud Rate the used needs it
 *
 * @var    Uart_Config::StopBits
 *         Member 'StopBits' is used to choose how many Stop bits needed for UART Frame
           You can find this value @ref STOP_BITS
 *
 * @var    Uart_Config::ParityMode
 *         Member 'ParityMode' used to choose Parity mode (Disabled, Even, or odd parity)
 *         You can find this value @ref PARITY_MODE
 *
 * @var    Uart_Config::FifoMode
 *         Member 'FifoMode' used to enable or disable FIFO Tx, Rx
 *         you can find this value @ref FIFO_MODE
 *
 * @var    Uart_Config::ClkSrc
 *         Member 'ClkSrc' used to decide what is the baud rate clock
 *         source (system clk or PIOSC)
 *         You can find this value @ref UART_CLOCK_SRC
 ******************************************************************************/
typedef struct{

    Uart_Instance   UartNum;        /** Member 'UartNum' used to indicate which UART
                                        needs to be configured
                                        You can find its value @ref Uart_Instance     */

    Uart_WordLength WordLength;     /** Member 'WordLength' used to decide how many
                                        bits needed for UART Tx/Rx
                                        You can find this value @ref WordLength       */

    Uart_Interrupts UartInterrupts; /** Member 'UartInterrupts' used to choose
                                        Interrupts enabled from UART module or disable
                                        all interrupts
                                        You can find this value @ref Uart_Interrupts  */

    uint32          ClkValue;       /** Member 'ClkValue' used to calculate the
                                        required BaudRate
                                        @note This value should given by a API used to
                                        get system clk (Future work)                  */

    uint32          BaudRate;       /** Member 'BaudRate' used to decide which Baud
                                        Rate the used needs it                        */

    uint8           StopBits;       /** Member 'StopBits' is used to choose how many
                                        Stop bits needed for UART Frame
                                        You can find this value @ref STOP_BITS        */

    uint8           ParityMode;     /** Member 'ParityMode' used to choose Parity mode
                                        Disabled, Even, or odd parity
                                        You can find this value @ref PARITY_MODE      */

    uint8           FifoMode;       /** Member 'FifoMode' used to enable or disable
                                        FIFO Tx, Rx
                                        you can find this value @ref FIFO_MODE        */

    uint8           ClkSrc;         /** Member 'ClkSrc' used to decide what is the baud
                                        rate clock source (system clk or PIOSC)
                                        You can find this value @ref UART_CLOCK_SRC        */
}Uart_Config;


//void UART0ISR(void);
uint8 Uart_Init(const Uart_Config* ConfigPtr);
void Uart0_SetCallBack(void (*f_ptr)(void));
uint8 Uart_ReceiveIT(const Uart_Config* ConfigPtr);
uint8 Uart_Receive(const Uart_Config* ConfigPtr);
uint8 Uart_Transmit(const Uart_Config* ConfigPtr, const uint8 Data);
void Uart_SendString (const Uart_Config* ConfigPtr, const uint8* String);
#endif /* DRIVERS_UART_UART_INIT_H_ */
