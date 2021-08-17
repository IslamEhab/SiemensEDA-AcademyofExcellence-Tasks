/********************************************************************************
 * @file          UART_Prog.c
 * @brief         Source file for UART module on TM4C123GH6PM Microcontroller
 * @date          16/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *                - Handling Interrupts from UART1 -> UART7
 *                - FIFO Mode
 *                - 9-Bit Mode
 *
 *******************************************************************************/

/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "UART_Reg.h"
#include "UART_Priv.h"
#include "UART_Init.h"


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the address of the call back function for UART0 in the application */
static volatile void (*g_callBackPtrUart0Interrupt)(void)      = NULL_PTR;

///* Global variables to hold the address of the call back function for UART Receive in the application */
//static volatile void (*g_callBackPtrUartReceive)(void)          = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Transmit in the application */
//static volatile void (*g_callBackPtrUartTransmit)(void)         = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Receive Time-Out in the application */
//static volatile void (*g_callBackPtrUartReceiveTimeOut)(void)   = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Framing Error in the application */
//static volatile void (*g_callBackPtrUartFramingError)(void)     = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Parity Error in the application */
//static volatile void (*g_callBackPtrUartParityError)(void)      = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Break Error in the application */
//static volatile void (*g_callBackPtrUartBreakError)(void)       = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART Overrun Error in the application */
//static volatile void (*g_callBackPtrUartOverrunError)(void)     = NULL_PTR;
//
///* Global variables to hold the address of the call back function for UART 9-Bit Mode in the application */
//static volatile void (*g_callBackPtrUart9_BitMode)(void)       = NULL_PTR;
//
//


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*******************************************************************************
 * @fn              void UART0ISR(void)
 * @brief           Interrupt Service Routine for UART0
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void UART0_ISR(void)
{
    /*** Clear to Send Interrupt is used only in UART1 (See DataSheet Page 929) ***/

    /* Check if Receive Interrupt Occurred */
    if(BIT_IS_SET( (*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_RXRIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Receive mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if Transmit Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_TXRIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Transmit mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if Receive Time-Out Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_RTRIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Receive Time-Out mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if Framing Error Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_FERIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Framing Error mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if Parity Error Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_PERIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Parity Error mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if Break Error Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_BERIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 Break Error mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if OverRun Error Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_OERIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 OverRun Error mode */
            (*g_callBackPtrUart0Interrupt)();
        }
    }
    /* Check if 9-Bit Mode Interrupt Occurred */
    else if(BIT_IS_SET((*(volatile uint32*)(UART_0_BASE_ADDRESS + UART_RIS_REG_OFFSET)), RIS_REG_9BITRIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrUart0Interrupt != NULL_PTR){

            /* Call the Call Back function for Uart0 9-Bit Mode mode */
            (*g_callBackPtrUart0Interrupt )();
        }
    }

}



/*******************************************************************************
 * @fn              void Uart_Init(const Uart_Config* ConfigPtr)
 * @brief           Function to initialize UART Module
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *******************************************************************************/
uint8 Uart_Init(const Uart_Config* ConfigPtr)
{
    /* Variable used to Operate with BaudRate Given by the used in Structure */
    uint32 BaudRateValue = 0;
    uint32 BaudRateDiv = 0;

    /* Pointer to Requested UART Base address Register */
    volatile uint32* Uart_Ptr = NULL_PTR;

    /* Variable to waste time to ensure clock stability */
    volatile uint32  delay = 0;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Switch case to decide which UART will operate */
    switch (ConfigPtr->UartNum) {
    case Uart0:
        /* Point the pointer to UART0 Base Address */
        Uart_Ptr = (volatile uint32*)UART_0_BASE_ADDRESS;
        break;
    case Uart1:
        /* Point the pointer to UART1 Base Address */
        Uart_Ptr = (volatile uint32*)UART_1_BASE_ADDRESS;
        break;
    case Uart2:
        /* Point the pointer to UART2 Base Address */
        Uart_Ptr = (volatile uint32*)UART_2_BASE_ADDRESS;
        break;
    case Uart3:
        /* Point the pointer to UART3 Base Address */
        Uart_Ptr = (volatile uint32*)UART_3_BASE_ADDRESS;
        break;
    case Uart4:
        /* Point the pointer to UART4 Base Address */
        Uart_Ptr = (volatile uint32*)UART_4_BASE_ADDRESS;
        break;
    case Uart5:
        /* Point the pointer to UART5 Base Address */
        Uart_Ptr = (volatile uint32*)UART_5_BASE_ADDRESS;
        break;
    case Uart6:
        /* Point the pointer to UART6 Base Address */
        Uart_Ptr = (volatile uint32*)UART_6_BASE_ADDRESS;
        break;
    case Uart7:
        /* Point the pointer to UART7 Base Address */
        Uart_Ptr = (volatile uint32*)UART_7_BASE_ADDRESS;
        break;
    }

    /* Enable clock for requested UART Module (MUST BE TESTED) */
    SYSCTL_RCGCUART_REG |= (1 << ConfigPtr->UartNum);

    /* Delay to waste sometime to ensure clock stability */
    delay = SYSCTL_RCGCUART_REG;

    /*********************** UART Configurations **********************/

    /* First, Disable UART by clearing First bit in CTL Reg */
    /*
     * First, Uart_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
     * because if it is not type casted, adding Control Register offset will make it
     * UART_CTL_REG_OFFSET value * 4 because it will behave as uint32*,
     * so it is a must to type cast the base address to uint8*
     *
     * Second the whole pointer is type casted again to uint32*
     * Lastly the last asterisk on the left is used to dereference the pointer
     */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_CTL_REG_OFFSET) &= ~(CTL_REG_UARTEN_ENABLE << CTL_REG_UARTEN_POS);

    /* Second, BaudRate Calculations */
    /********************* BaudRate Calculations **********************
     *                  BRD = Freq / ClkDiv* BaudRate                 *
     *                  Freq = System Clock or POISC                  *
     *                  ClkDiv = 16 (if HSE is disabled) or           *
     *                           8  (if HSE is enabled)               *
     ******************************************************************/
    /* Save the BaudRate given by the user */
    BaudRateValue = ConfigPtr->BaudRate;

    /* First, check if BaudRate Value needs HSE to be Enabled */
    if( ( (ConfigPtr->BaudRate) * 16) > (ConfigPtr->ClkValue) )
    {
        /* Enable HSE (High Speed Mode) */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_CTL_REG_OFFSET) ), CTL_REG_HSE_POS);

        /* Divide the baud rate by 2 to be able to calculate it correctly */
        BaudRateValue/=2;
    }
    else{
        /* Disable HSE */
        CLEAR_BIT( (*(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_CTL_REG_OFFSET) ), CTL_REG_HSE_POS);
    }

    /* Calculate BaudRate Fractional */
    BaudRateDiv = ( ( (ConfigPtr->ClkValue * 8) / BaudRateValue) + 1) / 2;

    /* Set Integer BaudRate value */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_IBRD_REG_OFFSET) = BaudRateDiv/64;


    /* Set Fractional BaudRate value */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_FBRD_REG_OFFSET) = BaudRateDiv%64;

    /********************** Set UART Configurations *************************/
    /* 1- Set Stop bits (1 or 2 stop Bits)
     * 2- Select FIFOs Mode (Enable or disable)
     */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) =
            ( ( (ConfigPtr->StopBits)<<LCRH_REG_SPS_POS) | ((ConfigPtr->FifoMode)<<LCRH_REG_FEN_POS) );

    /****** Parity Mode Selection (Even, Odd or disable) *********/
    if(ConfigPtr->ParityMode != PARITY_MODE_DISABLE)
    {
        /* Enable Parity Check */
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) |= (ConfigPtr->ParityMode << LCRH_REG_PEN_POS);

        /* Select Even or Odd Parity */
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) |= (ConfigPtr->ParityMode << LCRH_REG_EPS_POS);
    }
    /* Parity Check Disabled */
    else
    {
        /* Disable Parity Check */
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) &= ~(LCRH_REG_PEN_ENABLE << LCRH_REG_PEN_POS);

    }
    /****************** Word Length Selection *******************/
    if(ConfigPtr->WordLength != NineBits)
    {
        /* Set desired WordLength */
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) |= (ConfigPtr->WordLength << LCRH_REG_WLEN_POS);
    }
    /* 9 Bit Mode selected */
    else
    {
        /* Enable 9-bit mode from 9BITADDRESS Register*/
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_9BITADDR_REG_OFFSET) = (NINEBITADDR_REG_9BITEN_ENABLE << NINEBITADDR_REG_9BITEN_POS);

        /* Disable parity check (See Data sheet page 900) */
        *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_LCRH_REG_OFFSET) &= ~(LCRH_REG_PEN_ENABLE << LCRH_REG_PEN_POS);

    }

    /* Set Interrupts Enabled from configuration structure */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_IM_REG_OFFSET) = (ConfigPtr->UartInterrupts);

    /* Set Clock Source to the Uart Module */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_CC_REG_OFFSET) = (ConfigPtr->ClkSrc);

    /* Enable UART Tx, RX */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_CTL_REG_OFFSET) |= ( (CTL_REG_TXE_ENABLE<<CTL_REG_TXE_POS) |
            (CTL_REG_UARTEN_ENABLE<<CTL_REG_UARTEN_POS) | (CTL_REG_RXE_ENABLE<<CTL_REG_RXE_POS) );

    /* Return OK */
    return RET_OK;
}

/*******************************************************************************
 * @fn              void UART0ISR(void)
 * @brief           Function callback to serve UART0 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Uart0_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrUart0Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              uint8 Uart_ReceiveIT(void)
 * @brief           Function to receive UART data using interrupt
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Received Byte
 *******************************************************************************/
uint8 Uart_ReceiveIT(const Uart_Config* ConfigPtr)
{
    /* Pointer to Requested UART Base address Register */
    volatile uint32* Uart_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Switch case to decide which UART will operate */
    switch (ConfigPtr->UartNum) {
    case Uart0:
        /* Point the pointer to UART0 Base Address */
        Uart_Ptr = (volatile uint32*)UART_0_BASE_ADDRESS;
        break;
    case Uart1:
        /* Point the pointer to UART1 Base Address */
        Uart_Ptr = (volatile uint32*)UART_1_BASE_ADDRESS;
        break;
    case Uart2:
        /* Point the pointer to UART2 Base Address */
        Uart_Ptr = (volatile uint32*)UART_2_BASE_ADDRESS;
        break;
    case Uart3:
        /* Point the pointer to UART3 Base Address */
        Uart_Ptr = (volatile uint32*)UART_3_BASE_ADDRESS;
        break;
    case Uart4:
        /* Point the pointer to UART4 Base Address */
        Uart_Ptr = (volatile uint32*)UART_4_BASE_ADDRESS;
        break;
    case Uart5:
        /* Point the pointer to UART5 Base Address */
        Uart_Ptr = (volatile uint32*)UART_5_BASE_ADDRESS;
        break;
    case Uart6:
        /* Point the pointer to UART6 Base Address */
        Uart_Ptr = (volatile uint32*)UART_6_BASE_ADDRESS;
        break;
    case Uart7:
        /* Point the pointer to UART7 Base Address */
        Uart_Ptr = (volatile uint32*)UART_7_BASE_ADDRESS;
        break;
    }

    /******** Check if Received Interrupt Mask is enabled or not ********/
    if(BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_IM_REG_OFFSET)), IM_REG_RXIM_POS) )
    {
        /* Interrupt Receive Mask isn't enabled, return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /****** Interrupt Receive Mask is enabled, Read the received data *****/
    /* Read Received byte */
    uint8 c = (*(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_DATA_REG_OFFSET) );

    /* Clear the Receive Flag by writing 1 on it */
    *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_FR_REG_OFFSET) |= (1 << 4);
    /* return Received byte */
    return c;
}

/*******************************************************************************
 * @fn              uint8 Uart_Transmit(const Uart_Config* ConfigPtr, const uint8 Data)
 * @brief           Function to Transmit Byte (Wordlength) using UART
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  Data: Byte which will be sent using UART
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status
 *******************************************************************************/
uint8 Uart_Transmit(const Uart_Config* ConfigPtr, const uint8 Data)
{
    /* Pointer to Requested UART Base address Register */
    volatile uint32* Uart_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Switch case to decide which UART will operate */
    switch (ConfigPtr->UartNum) {
    case Uart0:
        /* Point the pointer to UART0 Base Address */
        Uart_Ptr = (volatile uint32*)UART_0_BASE_ADDRESS;
        break;
    case Uart1:
        /* Point the pointer to UART1 Base Address */
        Uart_Ptr = (volatile uint32*)UART_1_BASE_ADDRESS;
        break;
    case Uart2:
        /* Point the pointer to UART2 Base Address */
        Uart_Ptr = (volatile uint32*)UART_2_BASE_ADDRESS;
        break;
    case Uart3:
        /* Point the pointer to UART3 Base Address */
        Uart_Ptr = (volatile uint32*)UART_3_BASE_ADDRESS;
        break;
    case Uart4:
        /* Point the pointer to UART4 Base Address */
        Uart_Ptr = (volatile uint32*)UART_4_BASE_ADDRESS;
        break;
    case Uart5:
        /* Point the pointer to UART5 Base Address */
        Uart_Ptr = (volatile uint32*)UART_5_BASE_ADDRESS;
        break;
    case Uart6:
        /* Point the pointer to UART6 Base Address */
        Uart_Ptr = (volatile uint32*)UART_6_BASE_ADDRESS;
        break;
    case Uart7:
        /* Point the pointer to UART7 Base Address */
        Uart_Ptr = (volatile uint32*)UART_7_BASE_ADDRESS;
        break;
    }
    /* Wait until transmit holding register is NOT Full (when = 1 then the Transmit reg is full)*/
    while( ( *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_FR_REG_OFFSET) & (1 << 5) ) != 0 );

    /* Send the Char */
    (*(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_DATA_REG_OFFSET) ) = Data;


    return RET_OK;
}

/*******************************************************************************
 * @fn              void Uart_SendString (const Uart_Config* ConfigPtr, const uint8* String)
 * @brief           Function to Transmit String using UART
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  Data: Data which will be sent using UART
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Uart_SendString (const Uart_Config* ConfigPtr, const uint8* String)
{
    /* When String is Not Null */
    while(*String != '\0')
    {
        /* Send the corresponding Byte */
        Uart_Transmit(ConfigPtr ,*String);

        /* Increment the pointer to point to next element of the given string */
        String++;
    }
}

/*******************************************************************************
 * @fn              uint8 Uart_Receive(void)
 * @brief           Function to receive UART data using Polling Mode
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Received Byte
 *******************************************************************************/
uint8 Uart_Receive(const Uart_Config* ConfigPtr)
{
    /* Variable to save the received byte on it */
    uint8 c;
    /* Pointer to Requested UART Base address Register */
    volatile uint32* Uart_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Switch case to decide which UART will operate */
    switch (ConfigPtr->UartNum) {
    case Uart0:
        /* Point the pointer to UART0 Base Address */
        Uart_Ptr = (volatile uint32*)UART_0_BASE_ADDRESS;
        break;
    case Uart1:
        /* Point the pointer to UART1 Base Address */
        Uart_Ptr = (volatile uint32*)UART_1_BASE_ADDRESS;
        break;
    case Uart2:
        /* Point the pointer to UART2 Base Address */
        Uart_Ptr = (volatile uint32*)UART_2_BASE_ADDRESS;
        break;
    case Uart3:
        /* Point the pointer to UART3 Base Address */
        Uart_Ptr = (volatile uint32*)UART_3_BASE_ADDRESS;
        break;
    case Uart4:
        /* Point the pointer to UART4 Base Address */
        Uart_Ptr = (volatile uint32*)UART_4_BASE_ADDRESS;
        break;
    case Uart5:
        /* Point the pointer to UART5 Base Address */
        Uart_Ptr = (volatile uint32*)UART_5_BASE_ADDRESS;
        break;
    case Uart6:
        /* Point the pointer to UART6 Base Address */
        Uart_Ptr = (volatile uint32*)UART_6_BASE_ADDRESS;
        break;
    case Uart7:
        /* Point the pointer to UART7 Base Address */
        Uart_Ptr = (volatile uint32*)UART_7_BASE_ADDRESS;
        break;
    }

    /* Wait until receive holding register is NOT empty (when = 1 then the receive reg is empty). */
    while( ( *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_FR_REG_OFFSET) & (FR_REG_RXFE_ENABLE << FR_REG_RXFE_POS) ) != 0 );

    /* Read Received byte */
    c = *(volatile uint32*)((volatile uint8*)Uart_Ptr + UART_DATA_REG_OFFSET);

    return c;
}
