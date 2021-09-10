/********************************************************************************
 * @headerfile    CAN_Init.h
 * @brief         Header file for CAN module on TM4C123GH6PM Microcontroller
 * @date          1/9/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - Interrupt Handling
 *                - CAN Testing Modes
 *******************************************************************************/


#ifndef DRIVERS_CAN_CAN_INIT_H_
#define DRIVERS_CAN_CAN_INIT_H_

/*******************************************************************************
 *                                 Includes Needed                              *
 *******************************************************************************/
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                  Bits defines of CAN Interrupts in Registers                 *
 *******************************************************************************/

#define INTERRUPT_ENABLE_POS            ((uint8)0x1)    /* CAN Interrupt Enable Bit Position in CAN_CTL         */
#define STATUS_INTERRUPT_ENABLE_POS     ((uint8)0x2)    /* Status Interrupt Enable Bit Position in CAN_CTL      */
#define ERROR_INTERRUPT_ENABLE_POS      ((uint8)0x3)    /* Error Interrupt Enable Bit Position in CAN_CTL       */

#define INTERRUPT_ENABLE_VAL            ((uint8)0x1)    /* Interrupts enabled Value */

#define STATUS_INTERRUPT_ENABLE_VAL     ((uint8)0x1)    /* A change in the TXOK, RXOK or LEC bits in the
                                                          CANSTS register generates an interrupt                */

#define ERROR_INTERRUPT_ENABLE_VAL      ((uint8)0x1)    /* A change in the BOFF or EWARN bits in the CANSTS
                                                          register generates an interrupt                       */

#define RECEIVE_INTERRUPT_ENABLE_VAL    ((uint8)0x1)    /* Set INTPND Bit in MCTL reg after receiving frame     */
#define TRANSMIT_INTERRUPT_ENABLE_VAL   ((uint8)0x1)    /* Set INTPND Bit in MCTL reg after Tx frame            */

#define RECEIVE_INTERRUPT_ENABLE_POS    ((uint8)0xA)    /* Receive Interrupt Enable Bit Position                */
#define TRANSMIT_INTERRUPT_ENABLE_POS   ((uint8)0xB)    /* Transmit Interrupt Enable Bit Position               */

/*******************************************************************************
 *                     Defines used in Structures variables                     *
 *******************************************************************************/
/* Define used to choose whether using CAN0 or CAN1 Peripheral  */
#define CAN_MODULE_0               ((uint8)0x1)
#define CAN_MODULE_1               ((uint8)0x2)

/*******************************************************************************
 *                              User Defined Data Types                        *
 *******************************************************************************/

/*******************************************************************************
 * @enum    Can_MessageObjectSettings
 * @brief   Enum Holds the values of Message object settings to be set
 *******************************************************************************/
typedef enum{

        CanSettingsTransmitInterruptEnable  = 0x001,    /* Transmit Interrupt Enabled                                */
        CanSettingsReceiveInterruptEnable   = 0x002,    /* Receive Interrupt Enabled                                 */
        CanSettingsExtendedId               = 0x004,    /* Message object is using Extended ID                       */
        CanSettingsUseIdFilter              = 0x008,    /* Message object is using ID Filtering                      */
        CanSettingsNewData                  = 0x080,    /* New Data was available in Message Object                  */
        CanSettingsDataLost                 = 0x100,    /* Data was lost since this message object was last read     */
        CanSettingsUseDirectionFilter       = 0x018,    /* use direction filtering (ID filtering must be enabled)    */
        CanSettingsUseExtendedFilter        = 0x028,    /* use extended ID filtering (ID filtering must be enabled)  */
        CanSettingsRemoteFrame              = 0x040,    /* Message object is a remote frame                          */
        CanSettingsFIFO                     = 0x200,    /* This Message object is part of FIFO and not the final msg */
        CanSettingsNoSettingsSet            = 0x000,    /* Message object has no flags to set                        */
        CanSettingsClearPendingInterrupt    = 0x400     /* Clear Pending interrupt for this msg object
                                                           (This option is used in Can_Receive() structure only)     */
}Can_MessageObjectSettings;

/*******************************************************************************
 * @enum    Can_Interrupts
 * @brief   Enum Holds interrupt bits location in the register
 * @note    If any interrupt needed to be enabled, the Master Interrupt should be
 *          Enabled also to enable any other interrupt
 *******************************************************************************/
typedef enum{

        CanInterruptsDisable        = 0,                                                                       //!< CanInterruptsDisable
        CanInterruptMasterEnable    = ((INTERRUPT_ENABLE_VAL)          << (INTERRUPT_ENABLE_POS)),             //!< CanInterruptMasterEnable
        CanInterruptStatusEnable    = ((STATUS_INTERRUPT_ENABLE_VAL)   << (STATUS_INTERRUPT_ENABLE_POS)),      //!< CanInterruptStatusEnable
        CanInterruptErrorEnable     = ((ERROR_INTERRUPT_ENABLE_VAL)    << (ERROR_INTERRUPT_ENABLE_POS)),       //!< CanInterruptErrorEnable
        CanInterruptTransmit        = ((TRANSMIT_INTERRUPT_ENABLE_VAL) << (TRANSMIT_INTERRUPT_ENABLE_POS)),    //!< CanInterruptTransmit
        CanInterruptReceive         = ((RECEIVE_INTERRUPT_ENABLE_VAL)  << (RECEIVE_INTERRUPT_ENABLE_POS))      //!< CanInterruptReceive

}Can_Interrupts;


/*******************************************************************************
 * @enum    Can_MessageObjectType
 * @brief   Enum hold Types of different message objects in TM4C123Gh6PM CAN Module
 * @note    This enum is member of Can_MessageObjectConfig Structure
 *******************************************************************************/
typedef enum{
        MessageObjectTypeTransmit,                  //!< MessageObjectTypeTransmit
        MessageObjectTypeTransmitRemote,            //!< MessageObjectTypeTransmitRemote
        MessageObjectTypeReceive,                   //!< MessageObjectTypeReceive
        MessageObjectTypeReceiveRemote,             //!< MessageObjectTypeReceiveRemote
        MessageObjectTypeReceiveRemoteAutoTransmit  //!< MessageObjectTypeReceiveRemoteAutoTransmit
}Can_MessageObjectType;

/*******************************************************************************
 * @struct  Can_MessageObjectConfig
 *
 * @brief   Structure holds Message Object configuration
 *
 * @var     Can_MessageObjectConfig::Can_MessageObjectType
 *          Member 'Can_MessageObjectType' used to decide which
 *          Message object type should be used
 *          @note: you can find this value @ref Can_MessageObjectType
 *
 * @var     Can_MessageObjectConfig::MessageObjectSettings
 *          Member 'MessageObjectSettings' used to hold several settings of
 *          the message object defined by the user
 *          @note: You can find this value @ref Can_MessageObjectSettings
 *
 * @var     Can_MessageObjectConfig::MessageId
 *          Member 'MessageId' used as the CAN Message identifier which
 *          is in the CAN Frame. This ID Can be 11 or 29 bit (Extended)
 *
 * @var     Can_MessageObjectConfig::MessageIdMask
 *          Member 'MessageIdMask' used when identifier filtering is enabled
 *
 * @var     Can_MessageObjectConfig::pMsgData
 *          Member 'pMsgData' used as a pointer to message object's data
 *
 * @var     Can_MessageObjectConfig::DataLengthCode
 *          Member 'DataLengthCode' used to decide the data length needed
 *
 * @var     Can_MessageObjectConfig::MessageObjectId
 *          Member 'MessageObjectId' holds the message id
 *          @note: this value should be from 1 -> 32
 *******************************************************************************/
typedef struct{

    Can_MessageObjectType       MessageObjectType;      /** Member 'Can_MessageObjectType' used to decide which
                                                            Message object type should be used
                                                            @note: you can find this value @ref Can_MessageObjectType       */

    Can_MessageObjectSettings   MessageObjectSettings;  /** Member 'MessageObjectSettings' used to hold several settings
                                                            of the message object defined by the user
                                                            @note: You can find this value @ref Can_MessageObjectSettings   */

    uint32                      MessageId;              /** Member 'MessageId' used as the CAN Message identifier which
                                                            is in the CAN Frame. This ID Can be 11 or 29 bit (Extended)     */

    uint32                      MessageIdMask;          /** Member 'MessageIdMask' used when identifier filtering
                                                            is enabled                                                      */

    uint8*                      pMsgData;               /** Member 'pMsgData' used as a pointer to message object's data    */

    uint8                       DataLengthCode;         /** Member 'DataLengthCode' used to decide the data length needed   */


    uint8                       MessageObjectId;        /** Member 'MessageObjectId' holds the message id
                                                            @note: this value should be from 1 -> 32                        */
}Can_MessageObjectConfig;

/*************************************************************************************
 *
 * @struct      Can_BitTimingConfig
 *
 * @brief       This structure used to hold CAN Bit timing configuration
 *              Which will be a member of Can_Config Structure
 *
 * @var         Can_BitTimingConfig::SyncPropPhase1Seg
 *              Member 'SyncPropPhase1Seg' used to hold the sum of
 *              Sync. , Propagation and Phase Buffer 1 Segments
 *              @note: This value is from 2 to 16
 *
 * @var         Can_BitTimingConfig::Phase2Seg
 *              Member 'Phase2Seg' used to hold the value of
 *              Phase Buffer 2 Segment in time quanta.
 *              @note: This value is from 1 to 8
 *
 * @var         Can_BitTimingConfig::SJW
 *              Member 'SJW' used to hold (Re-)Sync. Jump Width value
 *              @note: This value is from 1 to 4
 *
 * @var         Can_BitTimingConfig::BaudRate
 *              Member 'BaudRate' used to hold the Clock Divisor
 *              used to determine time quanta.
 *              @note:  This value is from 1 to 1023 through the extension register
 *
 **************************************************************************************/
typedef struct{

    uint32      SyncPropPhase1Seg;      /** Member 'SyncPropPhase1Seg' used to hold the sum of
                                            Sync. , Propagation and Phase Buffer 1 Segments
                                            @note: This value is from 2 to 16                   */

    uint32      Phase2Seg;              /** Member 'Phase2Seg' used to hold the value of Phase
                                            Buffer 2 Segment in time quanta.
                                            @note: This value is from 1 to 8                    */

    uint32      SJW;                    /** Member 'SJW' used to hold (Re-)Sync. Jump Width value
                                            @note: This value is from 1 to 4                    */

    uint32      BaudRate;               /** Member 'BaudRate' used to hold the Clock Divisor used
                                            to determine time quanta.
                                            @note:  This value is from 1 to 1023 through the
                                            extension register                                  */

}Can_BitTimingConfig;

/*************************************************************************************
 * @struct      Can_Config
 *
 * @brief       This structure used to hold CAN configurations Parameters
 *
 * @var         Can_Config::pCanBitTimingConfig
 *              Member 'pCanBitTimingConfig' is a pointer to BitTiming structure
 *              used to hold CAN Bit Timing values
 *
 * @var         Can_Config::CanInterrupts
 *              Member 'CanInterrupts' used to decide which interrupts should be used in CAN Module
 *              You can find this value @ref Can_Interrupts
 *
 * @var         Can_Config::ClkValue
 *              Member 'ClkValue' used to calculate the required Bit Rate for CAN Module
 *              @note This value should given by a API used to get system clk (Future work)
 *
 * @var         Can_Config::CanBitRate
 *              Member 'CanBitRate' used to indicate the required bit rate for CAN Module
 *
 * @var         Can_Config::CanNum
 *              Member 'CanNum' used to decide which CAN instance will be used
 *              You Can find this value @ref CAN_MODULE
 *************************************************************************************/
typedef struct{

    Can_BitTimingConfig*    pCanBitTimingConfig;    /** Member 'pCanBitTimingConfig' is a pointer to BitTiming structure
                                                        used to hold CAN Bit Timing values                                  */

    Can_Interrupts          CanInterrupts;          /** Member 'CanInterrupts' used to decide which interrupts should be
                                                        used in CAN Module
                                                        You can find this value @ref Can_Interrupts                         */

    uint32                  ClkValue;               /** Member 'ClkValue' used to calculate the
                                                        required Bit Rate for CAN Module
                                                        @note This value should given by a API used to
                                                        get system clk (Future work)                                        */

    uint32                  CanBitRate;             /** Member 'CanBitRate' used to indicate the required bit rate for CAN  */

    uint8                   CanNum;                 /** Member 'CanNum' used to decide which CAN instance will be used
                                                        You Can find this value @ref CAN_MODULE                             */

}Can_Config;

/*******************************************************************************
 *                              Functions Prototypes                          *
 *******************************************************************************/
uint8 Can_Init(const Can_Config* ConfigPtr);
uint8 Can_Transmit(const Can_Config* ConfigPtr, const Can_MessageObjectConfig* MessageConfigPtr);
uint8 Can_Receive(const Can_Config* ConfigPtr, Can_MessageObjectConfig* MessageConfigPtr);


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* External Pre-Build structure used by CAN APIs to configure CAN Module */
extern Can_Config CanConfiguration;


#endif /* DRIVERS_CAN_CAN_INIT_H_ */
