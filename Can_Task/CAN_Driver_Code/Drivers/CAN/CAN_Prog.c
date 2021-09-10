/********************************************************************************
 * @file          CAN_Prog.c
 * @brief         Source file for CAN module on TM4C123GH6PM Microcontroller
 * @date          1/9/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - Interrupt Handling
 *                - CAN Testing Modes
 *******************************************************************************/

/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "CAN_Reg.h"
#include "CAN_Priv.h"
#include "CAN_Init.h"

/********************************************************************************
 *                          Static Functions Prototype                          *
 *******************************************************************************/
static void Can_ChooseModule(const Can_Config* ConfigPtr, volatile uint32** Ptr);
static uint8 Can_ChooseMessageObjectType(volatile uint32** Can_Ptr,
                                         const Can_MessageObjectConfig* MessageConfigPtr, uint8 *DataTransmitFlag);

/******************************************************************************************************************/


/*******************************************************************************
 *                              Functions Deceleration                          *
 *******************************************************************************/
/*******************************************************************************
 * @fn              uint8 Can_Init(const Can_Config* ConfigPtr)
 * @brief           Function to initialize CAN Module
 * @note            This function Initialize CAN Module with:
 *                  - Bit Timing Calculations
 *                  - Interrupts (Enabled or Disabled)
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    None
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *******************************************************************************/
uint8 Can_Init(const Can_Config* ConfigPtr)
{
    /* Pointer to Requested CAN Base address Register */
    volatile uint32* Can_Ptr = NULL_PTR;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which CAN Module will be used */
    Can_ChooseModule(ConfigPtr, &Can_Ptr);

    /* First, Enable CAN peripheral Clock from RCGC0 Register */
    SYSCTL_RCGC0_REG |= (ConfigPtr->CanNum << RCGC0_REG_CAN_POS);

    /* Second, Set the INIT Bit in CTL Register */
    /*
     * First, Can_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
     * because if it is not type casted, adding Control Register offset will make it
     * CAN_CTL_REG_OFFSET value * 4 because it will behave as uint32*,
     * so it is a must to type cast the base address to uint8*
     *
     * Second the whole pointer is type casted again to uint32*
     * Lastly the last asterisk on the left is used to dereference the pointer
     */
    SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_INIT_POS);

    /* Wait for Busy Flag to be cleared in IF1CRQ Register */
    while( (BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CRQ_REG_OFFSET) ), (IFCRQ_REG_BUSY_POS) ) ) );

    /* Third, Set CCE Bit in CTL Register to access BIT Register */
    SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_CCE_POS);

    /********** Forth, Set Bit timing values through BIT & BRPE Registers  *********/

    /* Note: Every value subtracted from 1 because as the DataSheet says at page 1063
     * "The four components (TSEG2, TSEG1, SJW, and BRP) have to be programmed
     *  to a numerical value one less than its functional value"
     * Note: here in BRP Section, the least 6 bits of BaudRate value is set,
     * the last 4 bits will be set in BRPE Register */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_BIT_REG_OFFSET) ) = (
            ( ( (ConfigPtr->pCanBitTimingConfig->Phase2Seg         - 1) << BIT_REG_TSEG2_POS ) & BIT_REG_TSEG2_MASK) |
            ( ( (ConfigPtr->pCanBitTimingConfig->SyncPropPhase1Seg - 1) << BIT_REG_TSEG1_POS ) & BIT_REG_TSEG1_MASK) |
            ( ( (ConfigPtr->pCanBitTimingConfig->SJW               - 1) << BIT_REG_SJW_POS   ) & BIT_REG_SJW_MASK  ) |
            ( ( (ConfigPtr->pCanBitTimingConfig->BaudRate          - 1) << BIT_REG_BRP_POS   ) & BIT_REG_BRP_MASK  ) );

    /* Set the last 4 bits of BaudRate in BRPE Register */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_BPRE_REG_OFFSET) ) =
            ( ( ( (ConfigPtr->pCanBitTimingConfig->BaudRate -1) >> BAUDRATE_EXTENSION_SHIFT    ) & BREP_REG_BREP_MASK) );

    /* Clear CCE Bit after setting bit timing values */
    CLEAR_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_CCE_POS);

    /* Fifth -Out of DataSheet instructions-, Set the required interrupts from Configuration structure */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ) |= (ConfigPtr->CanInterrupts);

    /* Finally Configurations finished, exit from Init mode by Clear INIT bit */
    CLEAR_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_INIT_POS);

    return RET_OK;
}


/*******************************************************************************
 * @fn              uint8 Can_Transmit(const Can_Config* ConfigPtr, const uint8* DataPtr, uint8 BufferSize)
 *
 * @brief           Function to transmit Data through CAN
 *                  This Function configures:
 *                  - Receive / Transmit Interrupts     - Message ID (Arbitration)
 *                  - Filter Mask                       - Choose filtering options (Filter on Mask, DIR, Extd ID or all)
 *                  - Message Object type (Transmit, Transmit Remote frame, Receive Remote frame with AUTO Transmit)
 *                  - Set Data Length Code (DLC)
 *                  - Choose which message object used to send the message
 *
 * @note            This function work with CANIF1 register as this function used
 *                  to transmit frames
 *
 * @param (in):     ConfigPtr        - Pointer to CAN configuration set
 *                  MessageConfigPtr - Pointer to Message object configuration set
 *
 * @param (out):    None
 *
 * @param (inout):  None
 *
 * @return          Return Status (RET_OK if everything is ok)
 *****************************************************************************/
uint8 Can_Transmit(const Can_Config* ConfigPtr, const Can_MessageObjectConfig* MessageConfigPtr)
{
    /* Pointer to Requested CAN Base address Register */
    volatile uint32* Can_Ptr = NULL_PTR;

    /* Flag to indicate that data will be written on Data registers (DA1, DA2, DB1 and DB2) */
    uint8 DataTransmit = 0;

    /* Variable to iterate through it */
    uint8 Counter = 0;

    /* Variable to save on it CAN Data */
    uint16 TempData = 0;

    /* Variable to hold First register address of data register*/
    uint16 RegAddress = CAN_IF1DA1_REG_OFFSET;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if( (NULL_PTR == ConfigPtr) || (NULL_PTR == MessageConfigPtr) )
    {
        /* ConfigPtr or MessageConfigPtr is a Null Pointer. Return with RET_NOT_OK to avoid segmentation fault */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which CAN Module will be used */
    Can_ChooseModule(ConfigPtr, &Can_Ptr);

    /* Wait for BUSY Flag to be cleared */
    while( (BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), (IFCRQ_REG_BUSY_POS) ) ) );

    /* First, in IF1CMASK Register
     * 1- Set the WRNRD Bit Because it's a write operation
     * 2- set DATAA and DATAB Bits to enable transferring
     *    bytes from message objects to DA1, DA2, DB1, and DB2 Registers
     * 3- Set CONTROL Bit to transfer Control bits to interface registers */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CMSK_REG_OFFSET) ) =  (
            (CMSK_REG_WRNRD_ENABLE << CMSK_REG_WRNRD_POS) | (CMSK_REG_CONTROL_ENABLE << CMSK_REG_CONTROL_POS) |
            (CMSK_REG_DATAA_ENABLE << CMSK_REG_DATAA_POS) | (CMSK_REG_DATAB_ENABLE   << CMSK_REG_DATAB_POS  ) );

    /* Function call to choose the Message Object Type */
    Can_ChooseMessageObjectType(&Can_Ptr, MessageConfigPtr, &DataTransmit);

    /******************** Mask Register Configurations *******************/

    /* Check if the user needs to use extended ID filter */
    if(MessageConfigPtr->MessageObjectSettings & CanSettingsUseIdFilter)
    {
        /* Check if Extended Message ID is used or not */
        if( (MessageConfigPtr->MessageId > ID_11_BIT_MAX_VALUE) && (MessageConfigPtr->MessageObjectSettings & CanSettingsExtendedId) )
        {
            /* Set the 29 Bit of Mask ID */

            /* for the first 16 bits, they will be saved on IF1MSK1 Register */
            (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MSK1_REG_OFFSET) ) =  (
                    (MessageConfigPtr->MessageIdMask & MSK1_REG_MSK_MASK) );

            /* For the rest of bits (the most 13 bits), they will be saved on IF1MSK2 Register*/
            (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MSK2_REG_OFFSET) ) =  (
                    ( (MessageConfigPtr->MessageIdMask >> ID_29_BIT_MSK2_SHIFT_VALUE) & MSK2_REG_MSK_MASK) );

        }
        else{
            /* Set the 11-bit of Mask ID because the Message ID is 11-bit */

            /* The 11-bit of mask ID will be set into MSK2 Register (MSK[12:2] bits) */
            (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MSK2_REG_OFFSET) ) =  (
                    ( (MessageConfigPtr->MessageIdMask << ID_11_BIT_MSK2_SHIFT_VALUE) & MSK2_REG_MSK_MASK) );

        }

    }
    /*********************************************************************/

    /* Check if the User needs to filter on the extended ID bit */
    if( (MessageConfigPtr->MessageObjectSettings
            & CanSettingsUseExtendedFilter) == CanSettingsUseExtendedFilter)
    {
        /* Set the Mask Extended ID Bit (MXTD) in MSK2 Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MSK2_REG_OFFSET) ), MSK2_REG_MXTD_POS);
    }

    /* Check if the user need to filter on the message Direction field */
    if( (MessageConfigPtr->MessageObjectSettings
            & CanSettingsUseDirectionFilter) == CanSettingsUseDirectionFilter)
    {
        /* Set the Mask Message Direction Bit (MDIR) in MSK2 Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MSK2_REG_OFFSET) ), MSK2_REG_MDIR_POS);
    }

    /* Check if the user needs to use Mask Id, Extended ID and Direction into filtering */
    if( MessageConfigPtr->MessageObjectSettings &
            (CanSettingsUseIdFilter | CanSettingsUseExtendedFilter | CanSettingsUseDirectionFilter) )
    {
        /* Set the UMASK Bit in the MCTL Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_UMASK_POS);

        /* Set the MASK bit in CMSK Register to Transfer IDMASK + DIR + MXTD
         * of message object into the interface registers */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CMSK_REG_OFFSET) ), CMSK_REG_MASK_POS);
    }

    /* Set the ARB bit in CMSK Register to Transfer ID + DIR+ XTD + MSGVAL
     * of the message object into the interface register */
    SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CMSK_REG_OFFSET) ), CMSK_REG_ARB_POS);

    /******************** Arbitration (Message ID) Configurations *******************/
    /* Check if Extended Message ID is used or not */
    if( (MessageConfigPtr->MessageId > ID_11_BIT_MAX_VALUE) && (MessageConfigPtr->MessageObjectSettings & CanSettingsExtendedId) )
    {
        /* Set the 29 Bit of Message ID */

        /* for the first 16 bits, they will be saved on IF1ARB1 Register */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB1_REG_OFFSET) ) =  (
                (MessageConfigPtr->MessageId & ARB1_REG_ID_MASK) );

        /* For the rest of bits (the most 13 bits), they will be saved on IF1ARB2 Register*/
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) =  (
                ( (MessageConfigPtr->MessageId >> ID_29_BIT_MSK2_SHIFT_VALUE) & ARB2_REG_ID_MASK) );

        /* Mark that the message is valid and it uses an Extended ID by setting MSGVAL and XTD Bits in ARB2 Reg  */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) |=  (
                (ARB2_REG_MSGVAL_ENABLE << ARB2_REG_MSGVAL_POS) | (ARB2_REG_XTD_ENABLE << ARB2_REG_XTD_POS) );


    }
    else{
        /* Set the 11-bit of Message ID because the Message ID is 11-bit */

        /* The 11-bit of message ID will be set into ARB2 Register (ARB[12:2] bits) */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) =  (
                ( (MessageConfigPtr->MessageId << ID_11_BIT_MSK2_SHIFT_VALUE) & ARB2_REG_ID_MASK) );

        /* Mark the message to be valid by setting MSGVAL Bit in ABR2 Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ), ARB2_REG_MSGVAL_POS);
    }

    /* Set the Data Length Code (DLC) with user configurations in MCTL Register */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ) =  (
            (MessageConfigPtr->DataLengthCode & MCTL_REG_DLC_MASK) );

    /* Set the EOB Bit in MCTL Register if this was the last Message in FIFO */
    if( (MessageConfigPtr->MessageObjectSettings & CanSettingsFIFO) == 0 )
    {
        /* Set the EOB Bit */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_EOB_POS);
    }

    /* Check if Transmit interrupt needs to be enabled */
    if( (ConfigPtr->CanInterrupts & CanInterruptTransmit) )
    {
        /* Check if the Master interrupt enabled or not */
        if(BIT_IS_CLEAR( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ) ) , CanInterruptMasterEnable) )
        {
            /* Master interrupt isn't enabled, enable it first from CTL Register
             * then enable Transmit interrupt from MCTL Register */
            SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_IE_POS);

            /* Enable Transmit Interrupt (TXIE) from MCTL Register*/
            SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_TXIE_POS);
        }
    }
    /* Check if Receive interrupt needs to be enabled */
    else if( (ConfigPtr->CanInterrupts & CanInterruptReceive) )
    {
        /* Check if the Master interrupt enabled or not */
        if(BIT_IS_CLEAR( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ) ) , CanInterruptMasterEnable) )
        {
            /* Master interrupt isn't enabled, enable it first from CTL Register
             * then enable receive interrupt from MCTL Register */
            SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_CTL_REG_OFFSET) ), CTL_REG_IE_POS);

            /* Enable Receive Interrupt (RXIE) from MCTL Register*/
            SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_RXIE_POS);
        }
    }

    /* Check if DataTransmit Flag is Set or Not */
    if(DataTransmit)
    {
        /*********** Send data through Data Registers ***********/

        /* Loop to copy the data from MessageConfigPtr to Data registers */
        for(Counter = 0; Counter < MessageConfigPtr->DataLengthCode;)
        {
            /* Read the first byte into TempData variable */
            TempData = MessageConfigPtr->pMsgData[Counter++];

            /* Since the Data register can hold 2 bytes, check if counter value is
             * less than the DLC to read the second byte  */
            if(Counter < MessageConfigPtr->DataLengthCode)
            {
                /* read the second byte into TempData variable
                 * but shift left the new data by 8 to save the value into the data register correct*/
                TempData |= (MessageConfigPtr->pMsgData[Counter++] << DATA_SHIFT_VALUE);
            }

            /* Save the Value read from user buffer into Data register */
            (*(volatile uint32*)((volatile uint8*)Can_Ptr + (RegAddress) ) ) =  TempData;

            /* Increment the Address by 4 every loop to go to the next data address */
            RegAddress += DATA_REG_OFFSET_VALUE;

        }
    }

    /*  Choose the MessageObject Needed */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CRQ_REG_OFFSET) ) =  (
            (MessageConfigPtr->MessageObjectId & IFCRQ_REG_MNUM_MASK) );

    /* Finally, set TXRQST bit in MCTL Register to indicate that the message object is available
     * to be transmitted, depending on priority and bus availability */
    SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_TXRQST_POS);



    return RET_OK;
}

/*******************************************************************************
 * @fn              uint8 Can_Receive(const Can_Config* ConfigPtr, const uint8* DataPtr, uint8 BufferSize)
 *
 * @brief           Function to Receive Data through CAN
 *                  This Function reads the configurations of the following
 *                  and return them into the empty configuration structure:
 *                  - Receive / Transmit Interrupts     - Message ID (Arbitration)
 *                  - Filter Mask                       - filtering options chosen (Filter on Mask, DIR, Extd ID or all)
 *                  - Data Length Code configured (DLC)
 *
 *                  But also, the configuration structure has some configurations like
 *                  - Message Object type (Receive, Receive Remote frame)
 *                  - Message Object Number
 *
 * @note            This function works with CANIF2 register as this function used to
 *                  recevie frames
 *
 * @param (in):     ConfigPtr - Pointer to configuration set
 *                  MessageConfigPtr - Pointer to Message object configuration set
 *
 * @param (out):    None
 *
 * @param (inout):  None
 *
 * @return          Return Status (RET_OK if everything is ok)
 *****************************************************************************/
uint8 Can_Receive(const Can_Config* ConfigPtr, Can_MessageObjectConfig* MessageConfigPtr)
{
    /* Pointer to Requested CAN Base address Register */
    volatile uint32* Can_Ptr = NULL_PTR;

    /* Variable to iterate through it */
    uint8 Counter = 0;

    /* Variable to save on it CAN Data */
    uint16 TempData = 0;

    /* Variable to hold First register address of data register*/
    uint16 RegAddress = CAN_IF2DA1_REG_OFFSET;

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer. Return with RET_NOT_OK */
        return RET_NOT_OK;
    }
    /* There is no need for else because if the if statement occurred, a return will happened */

    /* Function Call to choose which CAN Module will be used */
    Can_ChooseModule(ConfigPtr, &Can_Ptr);

    /*
     * First, in IF2CMASK Register
     * 1- set DATAA and DATAB Bits to enable receiving
     *    bytes from DA1, DA2, DB1, and DB2 Registers to message objects
     * 2- Set CONTROL Bit to transfer Control bits to interface registers
     * 3- Set ARB Bit to Transfer ID + DIR+ XTD+ MSGVAL of message object into interface registers
     * 4- Set MASK Bit to Transfer IDMASK + DIR + MXTD of message object into interface registers
     */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CMSK_REG_OFFSET) ) =  (
            (CMSK_REG_DATAA_ENABLE   << CMSK_REG_DATAA_POS  ) | (CMSK_REG_DATAB_ENABLE << CMSK_REG_DATAB_POS) |
            (CMSK_REG_CONTROL_ENABLE << CMSK_REG_CONTROL_POS) | (CMSK_REG_ARB_ENABLE   << CMSK_REG_ARB_POS ) |
            (CMSK_REG_MASK_ENABLE    << CMSK_REG_MASK_POS) );

    /* Clear Pending Interrupt if requested */
    if( (MessageConfigPtr->MessageObjectSettings &
            CanSettingsClearPendingInterrupt) == CanSettingsClearPendingInterrupt)
    {
        /* User Chose to clear Pending Interrupt.
         * Clear it by Setting INTPND Bit in CMSK Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CMSK_REG_OFFSET) ), CMSK_REG_CLRINTPND_POS);
    }

    /* Set the message object selected from the user using IF2CRQ Register */
    (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CRQ_REG_OFFSET) ) =  (
            (MessageConfigPtr->MessageObjectId & IFCRQ_REG_MNUM_MASK) );

    /* Wait for Busy Flag to be cleared in IF2CRQ Register */
    while( (BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CRQ_REG_OFFSET) ), (IFCRQ_REG_BUSY_POS) ) ) );

    /* Check if this a remote frame or not by checking TXRQST & DIR Bits */
    if( ( BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_TXRQST_POS) )  &&
            BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET  ) ), (ARB2_REG_DIR_POS   ) )   ) ||
            (   BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_TXRQST_POS) )  &&
                    BIT_IS_CLEAR( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET  ) ), (ARB2_REG_DIR_POS   ) )   ) )
    {
        /* Set the MessageObjectSetting Variable to Indicate that Remote frame Happened */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsRemoteFrame;
    }

    /* Check if Extended Frame Format used or not by checking XTD Bit in ARB2 REg*/
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ), (ARB2_REG_XTD_POS) ) )
    {
        /* Set the 29-Bit Message ID into the MessageObjectID variable */
        MessageConfigPtr->MessageId = (
                ( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ) & ARB2_REG_ID_MASK) << ID_29_BIT_MSK2_SHIFT_VALUE ) |
                ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB1_REG_OFFSET) ) ) );

        /* Set the MessageObjectSetting Variable to indicate that Extended ID is used  */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsExtendedId;

    }
    else
    {
        /* Use Standard 11-Bit */

        /* Set the 11-Bit Message ID into the MessageObjectID variable */
        MessageConfigPtr->MessageId = (
                ( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ) & ARB2_REG_ID_MASK) << ID_11_BIT_MSK2_SHIFT_VALUE ) );

    }

    /* Check if data lost happened by checking MSGLST Bit in MCTL Reg*/
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_MSGLST_POS) ) )
    {
        /* Set the MessageObjectSetting Variable to indicate that there's message lost situation */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsDataLost;
    }

    /* Check if ID Masking used by Checking UMASK Bit in MCTL Register */
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_UMASK_POS) ) )
    {
        /* Check if Extended ID is used by checking XTD Bit in ARB2 Register */
        if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ), (ARB2_REG_XTD_POS) ) )
        {
            /* Extended ID is used, set its value into MessageIdMask variable  */
            MessageConfigPtr->MessageIdMask = (
                    ( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ) &
                            MSK2_REG_MSK_MASK) << ID_29_BIT_MSK2_SHIFT_VALUE) | (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB1_REG_OFFSET) ) );

            /* Check if the ID Mask value is fully specified mask and if it's a remote frame */
            if( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ) != ID_29_BIT_FULLY_SPECIFIED ) ||
                    ( (MessageConfigPtr->MessageIdMask & CanSettingsRemoteFrame) == 0) )
            {
                /* Set the MessageObjectSetting Variable to indicate that ID Filtering enabled */
                MessageConfigPtr->MessageObjectSettings |= CanSettingsUseIdFilter;
            }
        }
        else{

            /* Standard ID is used, set its value into MessageIdMask Variable */
            MessageConfigPtr->MessageIdMask = (
                    ( ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2ARB2_REG_OFFSET) ) &
                            MSK2_REG_MSK_MASK) << ID_11_BIT_MSK2_SHIFT_VALUE) );

            /* Check if the ID Mask value is fully specified mask and if it's a remote frame */
            if( ( (MessageConfigPtr->MessageIdMask)          != ID_11_BIT_FULLY_SPECIFIED ) ||
                    ( (MessageConfigPtr->MessageObjectSettings & CanSettingsRemoteFrame) == 0) )
            {
                /* Set the MessageObjectSetting Variable to indicate that ID Filtering enabled */
                MessageConfigPtr->MessageObjectSettings |= CanSettingsUseIdFilter;
            }
        }

        /* Check if Extended Bit used in Filtering by checking MXTD bit in MSK2 Register */
        if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MSK2_REG_OFFSET) ), (MSK2_REG_MXTD_POS) ) )
        {
            /* Set the MessageObjectSetting Variable to indicate that Extended ID Filtering enabled */
            MessageConfigPtr->MessageObjectSettings |= CanSettingsUseExtendedFilter;
        }

        /* Check if Direction used in Filtering by checking MDIR bit in MSK2 Register */
        if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MSK2_REG_OFFSET) ), (MSK2_REG_MDIR_POS) ) )
        {
            /* Set the MessageObjectSetting Variable to indicate that Direction Filtering enabled */
            MessageConfigPtr->MessageObjectSettings |= CanSettingsUseDirectionFilter;
        }
    }

    /* Check if Transmit Interrupt was enabled or not by checking TXIE Bit in MCTL Register */
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_TXIE_POS) ) )
    {
        /* Set the MessageObjectSetting Variable to indicate that Transmit Interrupt enabled */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsTransmitInterruptEnable;
    }

    /* Check if Receive Interrupt was enabled or not by checking RXIE Bit in MCTL Register */
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_RXIE_POS) ) )
    {
        /* Set the MessageObjectSetting Variable to indicate that Receive Interrupt enabled */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsReceiveInterruptEnable;
    }

    /* Check if there's new data available by checking NEWDAT Bit in MCTL Register */
    if( BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ), (MCTL_REG_NEWDAT_POS) ) )
    {
        /* Get the Data Length Needed by reading DLC Bits in MCTL Register */
        MessageConfigPtr->DataLengthCode = (
                ( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2MCTL_REG_OFFSET) ) & MCTL_REG_DLC_POS) );

        /*********** Read data from Data Registers ***********/

        /* Loop through Data */
        for(Counter = 0; Counter < MessageConfigPtr->DataLengthCode;)
        {
            /* Read Data From Data Registers 16 bit at a time */
            TempData = (*(volatile uint32*)((volatile uint8*)Can_Ptr + (RegAddress) ) );

            /* Increment RegAddress by 4 to point to next Data Register */
            RegAddress+=RegAddress;

            /* Store the first byte into MessageObject Buffer */
            MessageConfigPtr->pMsgData[Counter++] = (uint8)TempData;

            /* Since the Data register can hold 2 bytes, check if counter value is
             * less than the DLC to read the second byte  */
            if(Counter < MessageConfigPtr->DataLengthCode)
            {
                /* read the second byte from TempData variable to pMsgData Buffer
                 * but shift right the new data by 8 to save the value into the buffer correctly */
                MessageConfigPtr->pMsgData[Counter++] = (uint8)(TempData >> DATA_SHIFT_VALUE);
            }
        }
        /* Clear New Data Flag because the data is already read now by setting NEWDAT Bit in CMSK Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CMSK_REG_OFFSET) ), CMSK_REG_NEWDAT_TXRQST_POS);

        /* Set the message object selected from the user using IF2CRQ Register */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CRQ_REG_OFFSET) ) =  (
                (MessageConfigPtr->MessageObjectId & IFCRQ_REG_MNUM_MASK) );

        /* Wait for Busy Flag to be cleared in IF2CRQ Register */
        while( (BIT_IS_SET( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF2CRQ_REG_OFFSET) ), (IFCRQ_REG_BUSY_POS) ) ) );

        /* Set the MessageObjectSetting Variable to indicate that there's new data */
        MessageConfigPtr->MessageObjectSettings |= CanSettingsNewData;
    }
    else{
        /* There's no data to be read, Set the DataLengthCode Variable to 0 */
        MessageConfigPtr->DataLengthCode = 0;
    }
    return RET_OK;
}


/******************************************************************************************************************/

/*******************************************************************************
 *                        Static Functions Deceleration                        *
 *******************************************************************************/

/*******************************************************************************
 * @fn              static void CAN_ChooseModule(const Can_Config* ConfigPtr, volatile uint32** Ptr)
 * @brief           Function to choose which CAN module base address to work with
 * @param (in):     ConfigPtr - Pointer to configuration set
 * @param (out):    Ptr: Pointer to the CAN Pointer base address
 * @param (inout):  None
 * @return          Return Status (RET_OK if everything is ok)
 *******************************************************************************/
static void Can_ChooseModule(const Can_Config* ConfigPtr, volatile uint32** Ptr)
{
    /* Switch case to decide which I2C will operate */
    switch (ConfigPtr->CanNum) {
    case CAN_MODULE_0:
        /* Point the pointer to CAN0 Base Address */
        *Ptr = (volatile uint32*)CAN_0_BASE_ADDRESS;
        break;
    case CAN_MODULE_1:
        /* Point the pointer to CAN1 Base Address */
        *Ptr = (volatile uint32*)CAN_1_BASE_ADDRESS;
        break;

    }

}

/*******************************************************************************
 * @fn              static uint8 Can_ChooseMessageObjectType(const Can_Config* ConfigPtr, const Can_MessageObjectConfig* MessageConfigPtr, uint8 *DataTransmitFlag)
 * @brief           Function to choose Message Object Type
 * @param (in):     Can_Ptr:         - Pointer to the CAN Pointer base address
 *                  MessageConfigPtr - Pointer to Message Object Configuration Set
 * @param (out):    DataTransmitFlag:  Pointer to the Data Transmit Flag
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
static uint8 Can_ChooseMessageObjectType(volatile uint32** Can_Ptr, const Can_MessageObjectConfig* MessageConfigPtr, uint8 *DataTransmitFlag)
{
    /* Switch State to choose which type of Message should be Transmitted */
    switch (MessageConfigPtr->MessageObjectType) {

    /* Message object type is normal transmit */
    case MessageObjectTypeTransmit:

        /* Set TXRQST Bit in MCTL Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_TXRQST_POS);

        /* Set Message Direction as Transmit by setting DIR bit in ARB2 Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ), ARB2_REG_DIR_POS);

        /* Set DataTransmit Flag to 1 to indicate that data will be written into data registers to be send */
        *DataTransmitFlag = 1;

        break;

        /* Message object type is Transmission of Remote Frame */
    case MessageObjectTypeTransmitRemote:

        /* Set TXRQST Bit in MCTL Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_TXRQST_POS);

        /* Clear ARB2 Register */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) =  0;

        break;

        /* Message object type is receive */
    case MessageObjectTypeReceive:

        /* Clear the DIR Reg and ARB2 Register */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) =  0;
        break;

        /* Message Object type is Receive remote request */
    case MessageObjectTypeReceiveRemote:

        /* Set DIR Bit in ARB2 Register to indicate that remote frame received */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ), ARB2_REG_DIR_POS);

        /* Clear TXRQST bit in MCTL Register to indicate that this is a receive operation */
        CLEAR_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_TXRQST_POS);

        /* Set UMASK Bit in MCTL to use MASK, MXTD, and MDIR Bits in MSK register for acceptance filter */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ), MCTL_REG_UMASK_POS);

        /* Use the full IDs by Default */
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB1_REG_OFFSET) ) =  ARB1_REG_FULL_ID;
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ) =  ARB2_REG_FULL_ID;

        /* Set MASK Bit in CMASK Register  to transfer IDMASK + DIR + MXTD
         * Bits of message object into the interface registers */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1CMSK_REG_OFFSET) ), CMSK_REG_MASK_POS);

        break;

        /* Message Object type is Receive remote but with Auto transmit */
    case MessageObjectTypeReceiveRemoteAutoTransmit:

        /* Set Message Direction as Transmit by setting DIR bit in ARB2 Register */
        SET_BIT( (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1ARB2_REG_OFFSET) ), ARB2_REG_DIR_POS);

        /* Set the message object to  auto respond if a matching ID is read on the bus
         * by setting the RMTEN and UMASK Bits in MCTL Register*/
        (*(volatile uint32*)((volatile uint8*)Can_Ptr + CAN_IF1MCTL_REG_OFFSET) ) |=  (
                (MCTL_REG_RMTEN_ENABLE << MCTL_REG_RMTEN_POS) | (MCTL_REG_UMASK_ENABLE << MCTL_REG_UMASK_POS) );

        /* Set DataTransmit Flag to 1 to indicate that data will be written into data registers to be send */
        *DataTransmitFlag = 1;
        break;

        /* If the user entered wrong message object type, return with RET_NOT_OK */
    default:
        return RET_NOT_OK;

    }
    return RET_OK;
}
