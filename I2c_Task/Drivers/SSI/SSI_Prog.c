/********************************************************************************
 * @file          SSI_Prog.c
 * @brief         Source file for SSI module on TM4C123GH6PM Microcontroller
 * @date          23/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling (Transmit, Receive timeout, ..)
 *                - FIFO Mode
 *                - TI & MICROWIRE Frames Format Handling
 *******************************************************************************/
/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "Ssi_Reg.h"
#include "Ssi_Priv.h"
#include "Ssi_Init.h"

/********************************************************************************
 *                          Static Functions Prototype                          *
 *******************************************************************************/
static void Ssi_ChooseModule(const Ssi_Config* ConfigPtr, volatile uint32** Ptr);


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global volatile function pointer to hold the address of the call back function for Ssi0 in the application */
static void (*volatile g_callBackPtrSsi0Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for Ssi1 in the application */
static void (*volatile g_callBackPtrSsi1Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for Ssi2 in the application */
static void (*volatile g_callBackPtrSsi2Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for Ssi3 in the application */
static void (*volatile g_callBackPtrSsi3Interrupt)(void)      = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*******************************************************************************
 * @fn              void SSI0_ISR(void)
 * @brief           Interrupt Service Routine for SSI0
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void SSI0_ISR(void)
{
    /* Check if Receive Overrun Interrupt Occurred */
    if(BIT_IS_SET( (*(volatile uint32*)(SSI_0_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RORMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi0Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Overrun mode */
            (*g_callBackPtrSsi0Interrupt)();
        }
    }

    /* Check if Receive Time-Out Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_0_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RTMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi0Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Time-Out mode */
            (*g_callBackPtrSsi0Interrupt)();
        }
    }

    /* Check if Receive FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_0_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi0Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive FIFO mode */
            (*g_callBackPtrSsi0Interrupt)();
        }
    }

    /* Check if Transmit FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_0_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_TXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi0Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Transmit FIFO Interrupt mode */
            (*g_callBackPtrSsi0Interrupt)();
        }
    }
}

/*******************************************************************************
 * @fn              void SSI1_ISR(void)
 * @brief           Interrupt Service Routine for SSI1
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void SSI1_ISR(void)
{
    /* Check if Receive Overrun Interrupt Occurred */
    if(BIT_IS_SET( (*(volatile uint32*)(SSI_1_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RORMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi1Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Overrun mode */
            (*g_callBackPtrSsi1Interrupt)();
        }
    }

    /* Check if Receive Time-Out Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_1_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RTMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi1Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Time-Out mode */
            (*g_callBackPtrSsi1Interrupt)();
        }
    }

    /* Check if Receive FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_1_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi1Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive FIFO mode */
            (*g_callBackPtrSsi1Interrupt)();
        }
    }

    /* Check if Transmit FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_1_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_TXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi1Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Transmit FIFO Interrupt mode */
            (*g_callBackPtrSsi1Interrupt)();
        }
    }
}

/*******************************************************************************
 * @fn              void SSI2_ISR(void)
 * @brief           Interrupt Service Routine for SSI2
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void SSI2_ISR(void)
{
    /* Check if Receive Overrun Interrupt Occurred */
    if(BIT_IS_SET( (*(volatile uint32*)(SSI_2_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RORMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi2Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Overrun mode */
            (*g_callBackPtrSsi2Interrupt)();
        }
    }

    /* Check if Receive Time-Out Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_2_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RTMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi2Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Time-Out mode */
            (*g_callBackPtrSsi2Interrupt)();
        }
    }

    /* Check if Receive FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_2_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi2Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive FIFO mode */
            (*g_callBackPtrSsi2Interrupt)();
        }
    }

    /* Check if Transmit FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_2_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_TXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi2Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Transmit FIFO Interrupt mode */
            (*g_callBackPtrSsi2Interrupt)();
        }
    }
}

/*******************************************************************************
 * @fn              void SSI3_ISR(void)
 * @brief           Interrupt Service Routine for SSI3
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void SSI3_ISR(void)
{
    /* Check if Receive Overrun Interrupt Occurred */
    if(BIT_IS_SET( (*(volatile uint32*)(SSI_3_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RORMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi3Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Overrun mode */
            (*g_callBackPtrSsi3Interrupt)();
        }
    }

    /* Check if Receive Time-Out Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_3_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RTMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi3Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive Time-Out mode */
            (*g_callBackPtrSsi3Interrupt)();
        }
    }

    /* Check if Receive FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_3_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_RXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi3Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Receive FIFO mode */
            (*g_callBackPtrSsi3Interrupt)();
        }
    }

    /* Check if Transmit FIFO Interrupt Occurred */
    else if(BIT_IS_SET( (*(volatile uint32*)(SSI_3_BASE_ADDRESS + SSI_MIS_REG_OFFSET)), MIS_REG_TXMIS_POS) )
    {
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrSsi3Interrupt != NULL_PTR){

            /* Call the Call Back function for SSI Transmit FIFO Interrupt mode */
            (*g_callBackPtrSsi3Interrupt)();
        }
    }
}
/******************************************************************************************************************/

/*******************************************************************************
 *                        Callback Functions for Interrupts                     *
 *******************************************************************************/

/*******************************************************************************
 * @fn              void Ssi0_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve SSI0 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Ssi0_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrSsi0Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void Ssi1_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve SSI1 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Ssi1_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrSsi1Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void Ssi2_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve SSI2 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Ssi2_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrSsi2Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void Ssi3_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve SSI3 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Ssi3_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrSsi3Interrupt = f_ptr;
}

/******************************************************************************************************************/

/*******************************************************************************
 *                              Functions Deceleration                          *
 *******************************************************************************/

/*******************************************************************************
 * @fn              uint8 Ssi_Init(const Ssi_Config* ConfigPtr)
 * @brief           Function to initialize SSI Module
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *******************************************************************************/
uint8 Ssi_Init(const Ssi_Config* ConfigPtr)
{
    /* Variable to Calculate on it Max Freq Value */
    uint32 MaxFreq = 0;

    /* Variable to count on it the CPSDVR value     */
    uint32 PreScaler = 0;

    /* Variable to calculate on it SCR Value    */
    uint32 SCR = 0;

    /* Pointer to Requested SSI Base address Register */
    volatile uint32* Ssi_Ptr = NULL_PTR;

    /* Variable to waste time to ensure clock stability */
    volatile uint32  delay = 0;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which SSI Module will be used */
    Ssi_ChooseModule(ConfigPtr, &Ssi_Ptr);

    /* Enable clock for requested SSI Module */
    SYSCTL_RCGCSSI_REG |= (1 << ConfigPtr->SsiNum);

    /* Delay to waste sometime to ensure clock stability */
    delay = SYSCTL_RCGCSSI_REG;

    /*********************** SSI Configurations **********************/

    /* First, Disable SSI by clearing Second bit in CR1 Reg */
    /*
     * First, Ssi_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
     * because if it is not type casted, adding Control Register offset will make it
     * SSI_CR1_REG_OFFSET value * 4 because it will behave as uint32*,
     * so it is a must to type cast the base address to uint8*
     *
     * Second the whole pointer is type casted again to uint32*
     * Lastly the last asterisk on the left is used to dereference the pointer
     */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR1_REG_OFFSET) &= ~(CR1_REG_SSE_ENABLE << CR1_REG_SSE_POS);

    /* Second, Choose Master or Slave (or LoopBack for testing) */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR1_REG_OFFSET) = ConfigPtr->SsiMode;

    /* Third, Configure SSI Clock Source */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CC_REG_OFFSET) = ConfigPtr->ClkSrc;

    /********************* Frequency Calculations **********************
     *                   SSICLK = Freq / CPSDVSR*(1+SCR)               *
     *                   Freq = System Clock or POISC                  *
     *               CPSDVSR = Even Prescaler Value (2->254)           *
     *                  SCR = Serial Clock Rate (0->255)               *
     ******************************************************************/
    /* Calculate Maximum Frequency */
    MaxFreq = ( (ConfigPtr->ClkValue) / (ConfigPtr->SsiFreq) );

    do{
        /* Increment PreScaler Value by 2 every time because it must be an even number */
        PreScaler +=2;

        /* Calculate SCR Value */
        SCR = ( (MaxFreq / PreScaler) - 1);

        /* Loop until SCR Value < 255 (Increase PreScaler Divisor Value by 2) */
    }while(SCR > 255);

    /* Fourth, Configure Clock PreScaler Value */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CPSR_REG_OFFSET) = PreScaler;

    /*
     * Fifth, Configure CR0 Register
     * 1- SCR Value
     * 2- Protocol Mode (Frame Format)
     * 3- Data Size
     * 4- Clock Polarity and Phase (if FreeScale SSI Mode is selected)
     */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR0_REG_OFFSET) = ( (SCR << CR0_REG_SCR_POS)
            | ( (ConfigPtr->SsiFrameFormat) << CR0_REG_FRF_POS) | ( (ConfigPtr->WordLength) << CR0_REG_DSS_POS) );

    /* Check if FreeScale SPI Mode is selected or not to set Clock Polarity and Clock Phase Configurations */
    if( (ConfigPtr->SsiFrameFormat) == SSI_FRAME_FORMAT_FREESCALE_SSI)
    {
        /* Set Clock Phase and Clock Polarity Configurations */
        *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR0_REG_OFFSET) |= ( ( (ConfigPtr->SsiClkPhase) << CR0_REG_SPH_POS)
                | ( (ConfigPtr->SsiClkPolarity) << CR0_REG_SPO_POS ) );
    }

    /********** Configure uDMA for SSI (Future Work) **********/

    /***** Set Interrupts Enabled from Configuration Structure ******/
    /* First, Check if End of Transmission Interrupt is enabled or not */
    if( ( (ConfigPtr->SsiInterrupts) && SsiInterruptMaskEndofTransmission) == TRUE )
    {
        /* Enable EOT Interrupt from CR1 Reg */
        *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR1_REG_OFFSET) |=
                ( (ConfigPtr->SsiInterrupts) & SsiInterruptMaskEndofTransmission);
    }
    /* Set the remains interrupts from IM Reg */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_IM_REG_OFFSET) = ((ConfigPtr->SsiInterrupts));

    /* Finally, Enable SSI Module by setting SSE Bit in CR1 Reg */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_CR1_REG_OFFSET) |= (CR1_REG_SSE_ENABLE << CR1_REG_SSE_POS);

    /* Return OK */
    return RET_OK;
}

/*******************************************************************************
 * @fn              uint8 Ssi_Transmit(const Ssi_Config* ConfigPtr, const uint8 Data)
 * @brief           Function to Transmit Byte (Wordlength) using SSI
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  Data: Data which will be sent using SSI
 *                  (uint16 because data size vary from 4 bits to 16 bits)
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status
 *******************************************************************************/
uint8 Ssi_Transmit(const Ssi_Config* ConfigPtr, const uint16 Data)
{    /* Pointer to Requested SSI Base address Register */
    volatile uint32* Ssi_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which SSI Module will be used */
    Ssi_ChooseModule(ConfigPtr, &Ssi_Ptr);

    /* Wait until Transmit FIFO Flag is Empty to send again */
    while(BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_SR_REG_OFFSET)), (SR_REG_TNF_POS) ) );

    /* Send Data */
    *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_DR_REG_OFFSET) = Data;

    return RET_OK;
}

/*******************************************************************************
 * @fn              void Ssi_SendString (const Ssi_Config* ConfigPtr, const uint8* String)
 * @brief           Function to Transmit String using Ssi
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  String: String which will be sent using SSI
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Ssi_SendString (const Ssi_Config* ConfigPtr, const uint8* String)
{
    /* When String is Not Null */
    while(*String != '\0')
    {
        /* Send the corresponding Byte */
        Ssi_Transmit(ConfigPtr ,*String);

        /* Increment the pointer to point to next element of the given string */
        String++;
    }
}

/*******************************************************************************
 * @fn              uint8 Ssi_Receive(const Ssi_Config* ConfigPtr)
 * @brief           Function to receive UART data using Polling Mode
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Received Data
 *                  (uint16 because data size vary from 4 bits to 16 bits)
 *******************************************************************************/
uint16 Ssi_Receive(const Ssi_Config* ConfigPtr)
{
    /* Variable to save the received byte on it */
    uint16 c;

    /* Pointer to Requested UART Base address Register */
    volatile uint32* Ssi_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }

    /* Function Call to choose which SSI Module will be used */
    Ssi_ChooseModule(ConfigPtr, &Ssi_Ptr);

    /* Wait until Receive FIFO Flag is Empty to Receive the data correctly*/
    while(BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_SR_REG_OFFSET)), (SR_REG_RNE_POS) ) );

    /* Read received data */
    c = *(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_DR_REG_OFFSET);

    /* Return the received data */
    return c;

}

/*******************************************************************************
 * @fn              uint8 Ssi_ReceiveIT(const Ssi_Config* ConfigPtr)
 * @brief           Function to receive SSI data using interrupt
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Received Data
 *                  (uint16 because data size vary from 4 bits to 16 bits)
 *******************************************************************************/
uint16 Ssi_ReceiveIT(const Ssi_Config* ConfigPtr)
{
    /* Variable used to read the received byte on it */
    uint16 c = 0;

    /* Pointer to Requested UART Base address Register */
    volatile uint32* Ssi_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* Function Call to choose which SSI Module will be used */
    Ssi_ChooseModule(ConfigPtr, &Ssi_Ptr);

    /******** Check if Received FIFO Interrupt Mask is enabled or not ********/
    if(BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_IM_REG_OFFSET)), IM_REG_RXIM_POS) )
    {
        /* Interrupt Receive Mask isn't enabled, return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /****** Interrupt Receive Mask is enabled, Read the received data *****/
    /* Read Received byte */
    c = (*(volatile uint32*)((volatile uint8*)Ssi_Ptr + SSI_DR_REG_OFFSET) );

    /* return received data */
    return c;

}

/******************************************************************************************************************/

/*******************************************************************************
 *                        Static Functions Deceleration                        *
 *******************************************************************************/

/*******************************************************************************
 * @fn              static void Ssi_ChooseModule(const Ssi_Config* ConfigPtr, uint32** Ptr)
 * @brief           Function to choose which SSI module base address to work with
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    Ptr: Pointer to the SSI Pointer base address
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
static void Ssi_ChooseModule(const Ssi_Config* ConfigPtr, volatile uint32** Ptr)
{
    /* Switch case to decide which SSI will operate */
    switch (ConfigPtr->SsiNum) {
    case Ssi0:
        /* Point the pointer to SSI0 Base Address */
        *Ptr = (volatile uint32*)SSI_0_BASE_ADDRESS;
         break;
    case Ssi1:
        /* Point the pointer to SSI1 Base Address */
        *Ptr = (volatile uint32*)SSI_1_BASE_ADDRESS;
         break;
    case Ssi2:
        /* Point the pointer to SSI2 Base Address */
        *Ptr = (volatile uint32*)SSI_2_BASE_ADDRESS;
         break;
    case Ssi3:
        /* Point the pointer to SSI3 Base Address */
        *Ptr = (volatile uint32*)SSI_3_BASE_ADDRESS;
         break;
    }

}
