/********************************************************************************
 * @file          main.c
 *
 * @brief         Source file for the main CAN Task on TM4C123GH6PM
 *
 * @date          4/9/2021
 *
 * @author        Islam Ehab Ezzat
 *
 * @version       1.0.0
 *
 * @note          This task is on of the tasks in
 *                "SiemensEDA Academy of Excellence" Program
 *                from Eng.Youssef Toma
 *
 * @note          GPIO and System Control Drivers didn't implement due to lack
 *                of time, the whole concentration was on CAN driver
 *
 * @note          This driver didn't tested yet due to lack of the hardware,
 *                so it might have some logical issues
 *******************************************************************************/
/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "main.h"

/*****************************************************************************
                                    Global Variables
*****************************************************************************/
/* Variable used to wait until clock is stable */
volatile uint32 delay;

/*********************************************************************
 * @var  CanMessageObjectConfigurationSend
 *       Global Variable holds Can Message Object Configurations
 *       for sending frames
 *
 * @note This Variable is an example of usage of Can_MessageObjectConfig
 *       Here the configurations set is:
 *       - Message Object type is : Transmit
 *       - Message Object Settings: Use ID filter and Direction Filter (both chosen by logical OR them together)
 *       - Message ID of CAN Frame: 0x01
 *       - Message ID Mask        : 0x01
 *       - Message to be sent     : Hello String
 *       - Data Length Code       : 6 bytes
 *       - Message Object ID      : 1
 *********************************************************************/
Can_MessageObjectConfig CanMessageObjectConfigurationSend = {
                               .MessageObjectType     = MessageObjectTypeTransmit,
                               .MessageObjectSettings = (Can_MessageObjectSettings)(CanSettingsUseIdFilter | CanSettingsUseDirectionFilter),
                               .MessageId             = 0x01,
                               .MessageIdMask         = 0x01,
                               .pMsgData              = {"Hello"},
                               .DataLengthCode        = 6,
                               .MessageObjectId       = 1,
};

uint8 ReceviedData[8] = {0};

/*********************************************************************
 * @var  CanMessageObjectConfigurationReceive
 *       Global Variable holds Can Message Object Configurations
 *       for receiving frames
 *
 * @note This Variable is an example of usage of Can_MessageObjectConfig
 *       In receiving, this configuration set is filled using Can_Receive()
 *       but there're some configurations needs to be set like:
 *       - Message Object type is : Receive
 *       - Message Object ID      : 1
 *       - pMsgData               : Holds the address of that empty array
 *                                  to save on it the received data
 *********************************************************************/
Can_MessageObjectConfig CanMessageObjectConfigurationReceive = {
                               .MessageObjectType   = MessageObjectTypeReceive,
                               .MessageObjectId     = 2,
                               .pMsgData            = (uint8*)&ReceviedData,
};


/***************************************************************************/

/*****************************************************************************
                           Static Functions Prototype
*****************************************************************************/

static void Can0_PinsConfigurations(void);
int main(void)
{
    /* CAN0 Pins Configurations */
    Can0_PinsConfigurations();

    /* Call Can_Init() API.
     * Note: Function argument is defined in CAN_PBcfg.c and externd into CAN_Init.h */
    Can_Init(&CanConfiguration);

    /* Call Can_Transmit() API as an example to sending data */
    Can_Transmit(&CanConfiguration, &CanMessageObjectConfigurationSend);

    /* Call Can_Receive() API as an exam.
     * ple of receiving frame */
	Can_Receive(&CanConfiguration, &CanMessageObjectConfigurationReceive);
    return 0;
}


static void Can0_PinsConfigurations(void)
{
    /* Enable GPIOB Clock (Second Bit in Register)*/
    SYSCTL_REGCGC2_REG |= ( (GPIOB_MODULE_CLK_ENABLE << GPIOB_MODULE_CLK_POS) );

    /* Dummy operation to give clock time to start */
    delay = SYSCTL_REGCGC2_REG;

    /*************** CAN0 Pins Assignment *************/
    /* Set GPIO AFSEL Bits for Pins 4 and 5 */
    GPIO_PORTB_AFSEL_REG |= ( (CAN_RX_PB4_ENABLE << CAN_RX_PB4_POS) |
                              (CAN_TX_PB5_ENABLE << CAN_TX_PB5_POS) );

    /* Configure GPIO PCTL bits to select Pin 4 and 5 as CAN (Alternative Function 8)*/
    GPIO_PORTB_PCTL_REG  |= ( (CAN_PCTL_VAL << CAN_RX_PCTL_POS) |
                              (CAN_PCTL_VAL << CAN_TX_PCTL_POS));

    /* Enable Corresponding bits in Digital Enable Register */
    GPIO_PORTB_DEN_REG   |= ( (CAN_DIGITAL_ENABLE << CAN_RX_PB4_POS) |
                              (CAN_DIGITAL_ENABLE << CAN_TX_PB5_POS) );

}
