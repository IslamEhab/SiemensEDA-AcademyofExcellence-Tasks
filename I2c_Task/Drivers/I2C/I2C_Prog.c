/********************************************************************************
 * @file          I2C_Prog.c
 * @brief         Source file for I2C module on TM4C123GH6PM Microcontroller
 * @date          25/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling (Transmit, Receive timeout, ..)
 *******************************************************************************/
/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "I2C_Reg.h"
#include "I2C_Priv.h"
#include "I2C_Init.h"

/********************************************************************************
 *                          Static Functions Prototype                          *
 *******************************************************************************/
static void I2c_ChooseModule(const I2c_Config* ConfigPtr, volatile uint32** Ptr);

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global volatile function pointer to hold the address of the call back function for I2c0 in the application */
static void (*volatile g_callBackPtrI2c0Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for I2c1 in the application */
static void (*volatile g_callBackPtrI2c1Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for I2c2 in the application */
static void (*volatile g_callBackPtrI2c2Interrupt)(void)      = NULL_PTR;

/* Global volatile function pointer to hold the address of the call back function for I2c3 in the application */
static void (*volatile g_callBackPtrI2c3Interrupt)(void)      = NULL_PTR;


/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

/*******************************************************************************
 * @fn              void I2C0_ISR(void)
 * @brief           Interrupt Service Routine for I2C0 (Master and Slave)
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2C0_ISR(void)
{
    /******************************** Errors Checking Before Calling the Callback Function ********************************/
    /* These error checks for the Master mode according to DataSheet instructions (See page 1006 "I2C Master Interrupts") */

    /* First Check for ERROR Bit in MCS to ensure that
     *  that an error didn't occur during the last transaction */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_MCS_REG_OFFSET)), MCR_REG_ERROR_POS) )
    {
        /* There's an error occurred in the last transaction, don't call the callback function */
        /* Future work: There Should be function to handle the error occurred in the last transaction */

        /* use keyword return to get out of the ISR */
        return;
    }
    /* Second, Check for ARBLST bit to ensure that arbitration has not been lost */
    else if (BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_MCS_REG_OFFSET)), MCR_REG_ARBLST_POS) )
    {
        /* The Master lost the Arbitration, don't call the callback function */
        /* Future work: There Should be function to handle the arbitration loss */

        /* use keyword return to get out of the ISR */
        return;
    }

    /******************************** Flags Checking to know which interrupt to be served ********************************/

                /***************************** First, Master Flags Checking *****************************/
    /* Check for MIS Flag in MMIS register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_MIS_POS) )
    {
        /* An unmasked master interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c0Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Master interrupt mode */
            (*g_callBackPtrI2c0Interrupt)();
        }
    }

    /* Check for CLKMIS Flag in MMIS register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_CLKMIS_POS) )
    {
        /* An unmasked clock timeout interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c0Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Clock TimeOut mode */
            (*g_callBackPtrI2c0Interrupt)();
        }
    }

                /***************************** Second, Slave Flags Checking *****************************/
    /* Check for DATAMIS Flag in SIMR register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_DATAMIS_POS) )
    {
        /* An unmasked data received or data requested interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c0Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Slave data interrupt mode */
            (*g_callBackPtrI2c0Interrupt)();
        }
    }

    /* Check for STARTMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STARTMIS_POS) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c0Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Start Condition mode */
            (*g_callBackPtrI2c0Interrupt)();
        }
    }
    /* Check for STOPMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_0_BASE_ADDRESS + I2C_SIMR_REG_OFFSET)) , SIMR_REG_STOPMIS_POS) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c0Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Stop Condition mode */
            (*g_callBackPtrI2c0Interrupt)();
        }
    }

}

/*******************************************************************************
 * @fn              void I2C1_ISR(void)
 * @brief           Interrupt Service Routine for I2C1 (Master and Slave)
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2C1_ISR(void)
{
    /******************************** Errors Checking Before Calling the Callback Function ********************************/
    /* These error checks for the Master mode according to DataSheet instructions (See page 1006 "I2C Master Interrupts") */

    /* First Check for ERROR Bit in MCS to ensure that
     *  that an error didn't occur during the last transaction */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ERROR_POS) )
    {
        /* There's an error occurred in the last transaction, don't call the callback function */
        /* Future work: There Should be function to handle the error occurred in the last transaction */

        /* use keyword return to get out of the ISR */
        return;
    }
    /* Second, Check for ARBLST bit to ensure that arbitration has not been lost */
    else if (BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ARBLST_POS) )
    {
        /* The Master lost the Arbitration, don't call the callback function */
        /* Future work: There Should be function to handle the arbitration loss */

        /* use keyword return to get out of the ISR */
        return;
    }

    /******************************** Flags Checking to know which interrupt to be served ********************************/

                /***************************** First, Master Flags Checking *****************************/
    /* Check for MIS Flag in MMIS register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_MIS_POS) )
    {
        /* An unmasked master interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c1Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Master interrupt mode */
            (*g_callBackPtrI2c1Interrupt)();
        }
    }

    /* Check for CLKMIS Flag in MMIS register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_CLKMIS_POS) )
    {
        /* An unmasked clock timeout interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c1Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Clock TimeOut mode */
            (*g_callBackPtrI2c1Interrupt)();
        }
    }

                /***************************** Second, Slave Flags Checking *****************************/
    /* Check for DATAMIS Flag in SIMR register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_DATAMIS_POS) )
    {
        /* An unmasked data received or data requested interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c1Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Slave data interrupt mode */
            (*g_callBackPtrI2c1Interrupt)();
        }
    }

    /* Check for STARTMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STARTMIS_POS) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c1Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Start Condition mode */
            (*g_callBackPtrI2c1Interrupt)();
        }
    }
    /* Check for STOPMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_1_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STOPMIS_POS) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c1Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Stop Condition mode */
            (*g_callBackPtrI2c1Interrupt)();
        }
    }

}

/*******************************************************************************
 * @fn              void I2C2_ISR(void)
 * @brief           Interrupt Service Routine for I2C2 (Master and Slave)
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2C2_ISR(void)
{
    /******************************** Errors Checking Before Calling the Callback Function ********************************/
    /* These error checks for the Master mode according to DataSheet instructions (See page 1006 "I2C Master Interrupts") */

    /* First Check for ERROR Bit in MCS to ensure that
     *  that an error didn't occur during the last transaction */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ERROR_POS) )
    {
        /* There's an error occurred in the last transaction, don't call the callback function */
        /* Future work: There Should be function to handle the error occurred in the last transaction */

        /* use keyword return to get out of the ISR */
        return;
    }
    /* Second, Check for ARBLST bit to ensure that arbitration has not been lost */
    else if (BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ARBLST_POS ) )
    {
        /* The Master lost the Arbitration, don't call the callback function */
        /* Future work: There Should be function to handle the arbitration loss */

        /* use keyword return to get out of the ISR */
        return;
    }

    /******************************** Flags Checking to know which interrupt to be served ********************************/

                /***************************** First, Master Flags Checking *****************************/
    /* Check for MIS Flag in MMIS register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_MIS_POS ) )
    {
        /* An unmasked master interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c2Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Master interrupt mode */
            (*g_callBackPtrI2c2Interrupt)();
        }
    }

    /* Check for CLKMIS Flag in MMIS register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_CLKMIS_POS ) )
    {
        /* An unmasked clock timeout interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c2Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Clock TimeOut mode */
            (*g_callBackPtrI2c2Interrupt)();
        }
    }

                /***************************** Second, Slave Flags Checking *****************************/
    /* Check for DATAMIS Flag in SIMR register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_DATAMIS_POS ) )
    {
        /* An unmasked data received or data requested interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c2Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Slave data interrupt mode */
            (*g_callBackPtrI2c2Interrupt)();
        }
    }

    /* Check for STARTMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STARTMIS_POS ) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c2Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Start Condition mode */
            (*g_callBackPtrI2c2Interrupt)();
        }
    }
    /* Check for STOPMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_2_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STOPMIS_POS ) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c2Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Stop Condition mode */
            (*g_callBackPtrI2c2Interrupt)();
        }
    }

}

/*******************************************************************************
 * @fn              void I2C3_ISR(void)
 * @brief           Interrupt Service Routine for I2C3 (Master and Slave)
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2C3_ISR(void)
{
    /******************************** Errors Checking Before Calling the Callback Function ********************************/
    /* These error checks for the Master mode according to DataSheet instructions (See page 1006 "I2C Master Interrupts") */

    /* First Check for ERROR Bit in MCS to ensure that
     *  that an error didn't occur during the last transaction */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ERROR_POS ) )
    {
        /* There's an error occurred in the last transaction, don't call the callback function */
        /* Future work: There Should be function to handle the error occurred in the last transaction */

        /* use keyword return to get out of the ISR */
        return;
    }
    /* Second, Check for ARBLST bit to ensure that arbitration has not been lost */
    else if (BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_MCS_REG_OFFSET))  , MCR_REG_ARBLST_POS ) )
    {
        /* The Master lost the Arbitration, don't call the callback function */
        /* Future work: There Should be function to handle the arbitration loss */

        /* use keyword return to get out of the ISR */
        return;
    }

    /******************************** Flags Checking to know which interrupt to be served ********************************/

                /***************************** First, Master Flags Checking *****************************/
    /* Check for MIS Flag in MMIS register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_MIS_POS ) )
    {
        /* An unmasked master interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c3Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Master interrupt mode */
            (*g_callBackPtrI2c3Interrupt)();
        }
    }

    /* Check for CLKMIS Flag in MMIS register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_MMIS_REG_OFFSET))  , MMIS_REG_CLKMIS_POS ) )
    {
        /* An unmasked clock timeout interrupt was signaled and is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c3Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Clock TimeOut mode */
            (*g_callBackPtrI2c3Interrupt)();
        }
    }

                /***************************** Second, Slave Flags Checking *****************************/
    /* Check for DATAMIS Flag in SIMR register */
    if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_DATAMIS_POS ) )
    {
        /* An unmasked data received or data requested interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c3Interrupt != NULL_PTR){

            /* Call the Call Back function for I2C Slave data interrupt mode */
            (*g_callBackPtrI2c3Interrupt)();
        }
    }

    /* Check for STARTMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STARTMIS_POS ) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c3Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Start Condition mode */
            (*g_callBackPtrI2c3Interrupt)();
        }
    }
    /* Check for STOPMIS Flag in SMIR register */
    else if( BIT_IS_SET( (*(volatile uint32*)(I2C_3_BASE_ADDRESS + I2C_SIMR_REG_OFFSET))  , SIMR_REG_STOPMIS_POS ) )
    {
        /* An unmasked START condition interrupt was signaled is pending */
        /*
         * Check if the Pointer not a Null one
         * To avoid segmentation fault
         */
        if(g_callBackPtrI2c3Interrupt != NULL_PTR){

            /* Call the Call Back function for Slave Stop Condition mode */
            (*g_callBackPtrI2c3Interrupt)();
        }
    }

}
/******************************************************************************************************************/

/*******************************************************************************
 *                        Callback Functions for Interrupts                     *
 *******************************************************************************/

/*******************************************************************************
 * @fn              void I2c0_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve I2c0 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2c0_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrI2c0Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void I2c1_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve I2c1 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2c1_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrI2c1Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void I2c2_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve I2c2 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2c2_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrI2c2Interrupt = f_ptr;
}

/*******************************************************************************
 * @fn              void I2c3_SetCallBack(volatile void (*f_ptr)(void))
 * @brief           Function callback to serve I2c3 Receive
 * @param (in):     f_ptr: Pointer to void function
                    which will save address of ISR Handler Function in main
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void I2c3_SetCallBack(void (*f_ptr)(void)){
    g_callBackPtrI2c3Interrupt = f_ptr;
}
/******************************************************************************************************************/


/*******************************************************************************
 *                              Functions Deceleration                          *
 *******************************************************************************/

/*******************************************************************************
 * @fn              uint8 I2c_Init(const I2c_Config* ConfigPtr)
 * @brief           Function to initialize I2c Module
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *******************************************************************************/
uint8 I2c_Init(const I2c_Config* ConfigPtr)
{
    /* Variable used to calculate TPR in it */
    uint32 Tpr = 0;

    /* Pointer to Requested I2c Base address Register */
    volatile uint32* I2c_Ptr = NULL_PTR;

    /* Variable to waste time to ensure clock stability */
    volatile uint32  delay = 0;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which I2c Module will be used */
    I2c_ChooseModule(ConfigPtr, &I2c_Ptr);

    /* Enable Clock for the requested I2C Module */
    SYSCTL_RCGCI2C_REG |= (1 << ConfigPtr->I2cNum);

    /* Delay to waste sometime to ensure clock stability */
    delay = SYSCTL_RCGCI2C_REG;

    /*********************** I2C Configurations **********************/

    /* First, Set the Mode of I2C module in MCR Register */
    /*
     * First, I2c_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
     * because if it is not type casted, adding Control Register offset will make it
     * I2C_MCR_REG_OFFSET value * 4 because it will behave as uint32*,
     * so it is a must to type cast the base address to uint8*
     *
     * Second the whole pointer is type casted again to uint32*
     * Lastly the last asterisk on the left is used to dereference the pointer
     */
    *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCR_REG_OFFSET) = ( (ConfigPtr->I2cMode) );

    /* Check if the slaved is enabled or not from the configuration */
    if( ( (ConfigPtr->I2cMode) & I2C_MODE_SLAVE) == I2C_MODE_SLAVE)
    {
        /* Enable the Slave Module from Slave Registers */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SCSR_REG_OFFSET) = ( SCSR_REG_DA_ENABLE << SCSR_REG_DA_POS );

    }

    /* Second, TPR Calculations */
    /********************* Frequency Calculations **********************
     *            TPR = (Freq / (2*(SCL_LP + SCL_HP)*SCL_CLK)          *
     *                   Freq = System Clock Frequency                 *
     *                   TPR = Timer Period (0->127)                   *
     *              SCL_LP = Serial Clock Line Low Phase               *
     *         (SCL_LP = 0x6 in Standard, Fast and FastPlus Modes)     *
     *                  (SCL_LP = 0x2 in High Speed Mode)              *
     *                                                                 *
     *              SCL_HP = Serial Clock Line High Phase              *
     *         (SCL_HP = 0x4 in Standard, Fast and FastPlus Modes)     *
     *                  (SCL_HP = 0x1 in High Speed Mode)              *
     *           SCL_CLK= Serial Clock Line Frequency needed           *
     ******************************************************************/
    /* Check if the I2C Freq is bigger than 1 MHz then High Speed mode selected */
    if(ConfigPtr->I2cFreq > ONE_MEGA_HERTZ_CLK_VALUE)
    {
        /* Calculate the TPR Value using LP & HP Values for High Speed Mode */
        Tpr = ( ( (ConfigPtr->ClkValue) / (2 *(SCL_LP_HIGH_SPEED + SCL_HP_HIGH_SPEED) * (ConfigPtr->I2cFreq) ) ) - 1 );

        /* Enable High Speed Mode */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MTPR_REG_OFFSET) = (MTPR_REG_HS_ENABLE << MTPR_REG_HS_POS );

    }
    else
    {
        /* Calculate the TPR Value using LP & HP Values for Standard, Fast and FastPlus Modes */
        Tpr = ( ( (ConfigPtr->ClkValue) / (2 *(SCL_LP_NORMAL + SCL_HP_NORMAL) * (ConfigPtr->I2cFreq) ) ) - 1 );

    }

    /* Write the corresponding TPR Value */
    *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MTPR_REG_OFFSET) |= Tpr;

    /* Check which mode is selected to enable the corresponding interrupts of it */
    if( ( (ConfigPtr->I2cMode) && I2C_MODE_MASTER) == TRUE )
    {
        /* Enable the Configured Master Interrupts */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MIMR_REG_OFFSET)  = (ConfigPtr->I2cInterrupts);
    }
    else if ( ( (ConfigPtr->I2cMode) && I2C_MODE_SLAVE) == TRUE )
    {
        /* Enable the Configured Slave Interrupts */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SIMR_REG_OFFSET) = (ConfigPtr->I2cInterrupts);
    }

    return RET_OK;
}


/*******************************************************************************
 * @fn              uint8 I2c_Transmit(const I2c_Config* ConfigPtr, const uint8* DataPtr, uint8 BufferSize)
 * @brief           Function to transmit Data through I2C (For both Master or Slave)
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  DataPtr   - Pointer to data that will be sent
 *                  BufferSize- Number of bytes that will be sent in multiple mode (Master mode only)
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *****************************************************************************/
uint8 I2c_Transmit(const I2c_Config* ConfigPtr, const uint8* DataPtr, uint8 BufferSize)
{
    /* Pointer to Requested I2c Base address Register */
    volatile uint32* I2c_Ptr = NULL_PTR;

    /* Variable to iterate through it */
    uint8 iteration = 0;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which I2c Module will be used */
    I2c_ChooseModule(ConfigPtr, &I2c_Ptr);

    /* Check if the I2cMode is master or slave to operate with the right registers */
    if( ( (ConfigPtr->I2cMode) & I2C_MODE_MASTER) == I2C_MODE_MASTER )
    {
        /* Master mode selected, operate with Master registers */

        /* Check if the Transmit Mode is Single or multiple data transmission */
        if( (ConfigPtr->I2cTransmitMode) == I2C_TRANSMIT_MODE_SINGLE )
        {
            /*
             * Single Data transmission selected
             * Follow the Master Single TRANSMIT Flow chart in DataSheet (Page 1008)
             */

            /* First, write the slave address to MSA Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MSA_REG_OFFSET) =  (ConfigPtr->I2cSlaveAddress << 1);

            /* Second, Write the data on the MDR Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET) = (*DataPtr);

            /* Third, Wait until BUSBSY bit in MCS Register = 0*/
            while(BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) , MCR_REG_BUSBSY_POS) );


            /* Forth, write the RUN, START, and STOP Bits in MCS Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (0b00111) );

            /* Fifth, Wait until BUSY bit in MCS Register = 0*/
            while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);


            /* Sixth, Check for ERROR But in MCS Register */
            if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) & (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
            {
                /* There are no errors occurred, return with RET_Ok */
                return RET_OK;
            }
            else
            {
                /* There is an error occurred, return with RET_NOT_OK */
                /* Future work: There should be an Error Service Algorithm Function
                 * which will be called here to operate with this error */
                return RET_NOT_OK;
            }
        }

        else if( (ConfigPtr->I2cTransmitMode) == I2C_TRANSMIT_MODE_MULTIPLE)
        {
            /*
             * Multiple Data transmission selected
             * Follow the Master TRANSMIT of Multiple Data Bytes Flow chart in DataSheet (Page 1010)
             */

            /* First, write the slave address to MSA Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MSA_REG_OFFSET) =  ConfigPtr->I2cSlaveAddress;

            /* Second, Write the data on the MDR Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET) = (*DataPtr);

            /* Third, Wait until BUSBSY bit in MCS Register = 0*/
            while( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) , MCR_REG_BUSBSY_POS) );

            /* Forth, write the RUN, and START Bits only in MCS Register
             * STOP Bit didn't set because Repeated start is used right now */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_START_ENABLE << MCR_REG_START_POS)|
                    (MCR_REG_RUN_ENABLE   << MCR_REG_RUN_POS) );

            /* For loop to iterate till BufferSize value
             * Iteration starts from 1 because the first byte is already sent in the second operation in the algorithm */
            for(iteration = 1; iteration < BufferSize; iteration++)
            {
                /* Fifth, Wait until BUSY bit in MCS Register = 0*/
                while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);

                /* Sixth, Check for ERROR But in MCS Register */
                if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
                {
                    /*
                     * There are no errors occurred,
                     * Increment the pointer to the next element of the Buffer
                     * then send this byte
                     */
                    DataPtr++;

                    /* Write the data on the MDR Register */
                    *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET) = (*DataPtr);

                    /* Seventh, Write the RUN Bit in MCS Register */
                    *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_RUN_ENABLE << MCR_REG_RUN_POS) );

                }
                else
                {
                    /*
                     * There is an error occurred,
                     * Check for Arbitration Lost Bit in MCS Register = 0
                     * note: in DataSheet they check on 1, i'm checking here on 0 to save the else instructions
                     */
                    if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ARBLST_ENABLE << MCR_REG_ARBLST_POS) ) == FALSE)
                    {
                        /* Write the STOP Bit in MCS Register */
                        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_STOP_ENABLE << MCR_REG_STOP_POS) );
                    }

                    /* if the 'if condition' didn't happen, then the I2C Controller Lost Arbitration, return with RET_NOT_OK */
                    /* Future work: There should be an Error Service Algorithm Function
                     * which will be called here to operate with this error */
                    return RET_NOT_OK;

                }
            }
            /* Data should be sent successfully or there's an error happened which stopped the data transfer
             * if there's an error occurred then this piece of code won't be accessed */

            /* Write the STOP and RUN Bits in MCS Register  */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_STOP_ENABLE << MCR_REG_STOP_POS) |
                    (MCR_REG_RUN_ENABLE  << MCR_REG_RUN_POS ) );
            /* Wait until BUSY bit in MCS Register = 0*/
            while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);


            /* Check for ERROR But in MCS Register */
            if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
            {
                /* There are no errors occurred, return with RET_Ok */
                return RET_OK;
            }
            else
            {
                /* There is an error occurred, return with RET_NOT_OK */
                /* Future work: There should be an Error Service Algorithm Function
                 * which will be called here to operate with this error */
                return RET_NOT_OK;
            }

        }
    }
    else if( ( (ConfigPtr->I2cMode) & I2C_MODE_SLAVE) == I2C_MODE_SLAVE )
    {
        /* Slave mode selected, operate with Slave registers */
        /* Note: There's no Multiple data transmission in slave mode */

        /* First, write the OWN slave address to SOAR */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SOAR_REG_OFFSET) = (ConfigPtr->I2cSlaveAddress);

        /* Second, Enable I2C Slave Operation from SCSR Register */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SCSR_REG_OFFSET) = ( SCSR_REG_DA_ENABLE << SCSR_REG_DA_POS );

        /* Third, Wait until TREQ Bit in SCSR Register = 1 */
        while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SCSR_REG_OFFSET) ) && (SCSR_REG_TREQ_ENABLE << SCSR_REG_TREQ_POS ) ) == TRUE);

        /* Write data to SDR register */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SDR_REG_OFFSET) = (*DataPtr);
    }
    return RET_OK;
}


/*******************************************************************************
 * @fn              uint8 I2c_Receive(const I2c_Config* ConfigPtr, uint8* DataPtr, uint8 BufferSize)
 * @brief           Function to Receive Data through I2C (For both Master or Slave)
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  BufferSize- Number of bytes that will be received in multiple mode (Master mode only)
 * @param (out):    DataPtr   - Pointer to data that will be received
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *****************************************************************************/
uint8 I2c_Receive(const I2c_Config* ConfigPtr, uint8* DataPtr, uint8 BufferSize)
{
    /* Pointer to Requested SSI Base address Register */
    volatile uint32* I2c_Ptr = NULL_PTR;

    /* Variable to iterate through it */
    uint8 iteration = 0;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which I2c Module will be used */
    I2c_ChooseModule(ConfigPtr, &I2c_Ptr);

    /* Check if the I2cMode is master or slave to operate with the right registers */
    if( ( (ConfigPtr->I2cMode) & I2C_MODE_MASTER) == I2C_MODE_MASTER )
    {
        /* Master mode selected, operate with Master registers */

        /* Check if the Receive Mode is Single or multiple data transmission */
        if( (ConfigPtr->I2cReceiveMode) == I2C_RECEIVE_MODE_SINGLE )
        {
            /*
             * Single Data reception selected
             * Follow the Master Single RECEIVE Flow chart in DataSheet (Page 1009)
             */

            /* First, write the slave address to MSA Register and write 1 on R/W bit to tell I2C Controller that Master will receive data */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MSA_REG_OFFSET) =  ( (ConfigPtr->I2cSlaveAddress << 1) | (1 << 0) ) ;



            /* Second, Wait until BUSBSY bit in MCS Register = 0*/
            while(BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET)), MCR_REG_BUSBSY_POS));

            /* Third, write the RUN, START, and STOP Bits in MCS Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_START_ENABLE << MCR_REG_START_POS)|
                    (MCR_REG_RUN_ENABLE << MCR_REG_RUN_POS) | (MCR_REG_STOP_ENABLE << MCR_REG_STOP_POS) );



            /* Forth, Wait until BUSY bit in MCS Register = 0*/
            while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);


            /* Fifth, Check for ERROR But in MCS Register */
            if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) & (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
            {
                /* There are no errors occurred */

                /* Sixth, Read the data from MDR Register */
                *DataPtr = (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET));

                /* return with RET_Ok */
                return RET_OK;
            }
            else
            {
                /* There is an error occurred, return with RET_NOT_OK */
                /* Future work: There should be an Error Service Algorithm Function
                 * which will be called here to operate with this error */
                return RET_NOT_OK;
            }
        }
        else if( (ConfigPtr->I2cReceiveMode) == I2C_RECEIVE_MODE_MULTIPLE)
        {
            /*
             * Multiple Data reception selected
             * Follow the Master RECEIVE of Multiple Data Bytes Flow chart in DataSheet (Page 1011)
             */

            /* First, write the slave address to MSA Register */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MSA_REG_OFFSET) =  ConfigPtr->I2cSlaveAddress;

            /* Second, Wait until BUSBSY bit in MCS Register = 0*/
            while(BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ), MCR_REG_BUSBSY_POS) );

            /* Third Forth, write the RUN, START and ACK Bits only in MCS Register
             * STOP Bit didn't set because Repeated start is used right now */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_START_ENABLE << MCR_REG_START_POS)|
                    (MCR_REG_RUN_ENABLE << MCR_REG_RUN_POS) | (MCR_REG_ACK_ENABLE  << MCR_REG_ACK_POS) );

            /* For loop to iterate till BufferSize value
             * Iteration starts from 0 because No data has been read yet
             * Note: this loop will iterate till (BufferSize - 1) because
             * the last byte will be read after the loop as the DataSheet said in the flow chart */
            for(iteration = 0; iteration < (BufferSize-1); iteration++)
            {
                /* Fifth, Wait until BUSY bit in MCS Register = 0*/
                while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);

                /* Sixth, Check for ERROR But in MCS Register */
                if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
                {
                    /* There are no errors occurred */

                    /* read the data from the MDR Register */
                    (*DataPtr) = ( *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET) );

                    /* Increment the pointer to the next element of the Buffer */
                    DataPtr++;

                    /* Seventh, Write the RUN and ACK Bits in MCS Register */
                    *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_RUN_ENABLE << MCR_REG_RUN_POS) |
                            (MCR_REG_ACK_ENABLE << MCR_REG_ACK_POS) );
                }
                else
                {
                    /*
                     * There is an error occurred,
                     * Check for Arbitration Lost Bit in MCS Register = 0
                     * note: in DataSheet they check on 1, i'm checking here on 0 to save the else instructions
                     */
                    if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ARBLST_ENABLE << MCR_REG_ARBLST_POS) ) == FALSE)
                    {
                        /* Write the STOP Bit in MCS Register */
                        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_STOP_ENABLE << MCR_REG_STOP_POS) );
                    }

                    /* if the 'if condition' didn't happen, then the I2C Controller Lost Arbitration, return with RET_NOT_OK */
                    /* Future work: There should be an Error Service Algorithm Function
                     * which will be called here to operate with this error */
                    return RET_NOT_OK;

                }
            }
            /* Data should be sent successfully or there's an error happened which stopped the data transfer
             * if there's an error occurred then this piece of code won't be accessed */

            /* Write the STOP and RUN Bits in MCS Register  */
            *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) = ( (MCR_REG_STOP_ENABLE << MCR_REG_STOP_POS) |
                    (MCR_REG_RUN_ENABLE  << MCR_REG_RUN_POS ) );

            /* Wait until BUSY bit in MCS Register = 0*/
            while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_BUSY_ENABLE << MCR_REG_BUSY_POS) ) == FALSE);


            /* Check for ERROR But in MCS Register */
            if( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MCS_REG_OFFSET) ) && (MCR_REG_ERROR_ENABLE << MCR_REG_ERROR_POS) ) == FALSE)
            {
                /* There are no errors occurred,
                 * increment the buffer pointer then read the last byte */
                DataPtr++;

                (*DataPtr) = ( *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_MDR_REG_OFFSET) );

                /* return with RET_Ok */
                return RET_OK;
            }
            else
            {
                /* There is an error occurred, return with RET_NOT_OK */
                /* Future work: There should be an Error Service Algorithm Function
                 * which will be called here to operate with this error */
                return RET_NOT_OK;
            }

        }
    }
    else if( ( (ConfigPtr->I2cMode) & I2C_MODE_SLAVE) == I2C_MODE_SLAVE )
    {
        /* Slave mode selected, operate with Slave registers */
        /* Note: There's no Multiple data reception in slave mode */

        /* First, write the OWN slave address to SOAR */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SOAR_REG_OFFSET) = (ConfigPtr->I2cSlaveAddress);

        /* Second, Enable I2C Slave Operation from SCSR Register */
        *(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SCSR_REG_OFFSET) = ( SCSR_REG_DA_ENABLE << SCSR_REG_DA_POS );

        /* Third, Wait until RREQ Bit in SCSR Register = 1 */
        while( ( (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SCSR_REG_OFFSET) ) && (SCSR_REG_RREQ_ENABLE << SCSR_REG_RREQ_POS ) ) == TRUE);

        /* Read data from SDR register */
        (*DataPtr) = (*(volatile uint32*)((volatile uint8*)I2c_Ptr + I2C_SDR_REG_OFFSET) );
    }
    return RET_OK;
}


/*******************************************************************************
 *                        Static Functions Deceleration                        *
 *******************************************************************************/

/*******************************************************************************
 * @fn              static void I2C_ChooseModule(const I2c_Config* ConfigPtr, volatile uint32** Ptr)
 * @brief           Function to choose which I2C module base address to work with
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    Ptr: Pointer to the I2C Pointer base address
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
static void I2c_ChooseModule(const I2c_Config* ConfigPtr, volatile uint32** Ptr)
{
    /* Switch case to decide which I2C will operate */
    switch (ConfigPtr->I2cNum) {
    case I2c0:
        /* Point the pointer to I2C0 Base Address */
        *Ptr = (volatile uint32*)I2C_0_BASE_ADDRESS;
        break;
    case I2c1:
        /* Point the pointer to I2C1 Base Address */
        *Ptr = (volatile uint32*)I2C_1_BASE_ADDRESS;
        break;
    case I2c2:
        /* Point the pointer to I2C2 Base Address */
        *Ptr = (volatile uint32*)I2C_2_BASE_ADDRESS;
        break;
    case I2c3:
        /* Point the pointer to I2C3 Base Address */
        *Ptr = (volatile uint32*)I2C_3_BASE_ADDRESS;
        break;
    }

}
