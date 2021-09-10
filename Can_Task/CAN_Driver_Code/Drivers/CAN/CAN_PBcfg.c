/********************************************************************************
 * @file          CAN_PBcfg.c
 *
 * @brief         Source file for CAN Peripheral Post Build configurations
 *                on TM4C123GH6PM Microcontroller
 *
 *                This file contains a global structures variables used to initialize
 *                CAN module with configured values using Configurator tool
 *                (In AUTOSAR)
 *
 * @date          4/9/2021
 *
 * @author        Islam Ehab Ezzat
 *
 * @version       1.0.0
 *
 * @note          This driver still under development, so it doesn't support:
 *                - Interrupt Handling
 *                - CAN Testing Modes
 *******************************************************************************/
/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "CAN_Init.h"


/*********************************************************************
 * @var  CanConfiguration:
 *       Global Variable holds Can Configurations used in Can_Init()
 *
 * @note &(Can_BitTimingConfig) this line of code put to
 *       dereference the pCanBitTimingConfig to its structure.
 *
 * @note For Can Bit timing, i used http://www.bittiming.can-wiki.info/
 *       to calculate the values
 *       CAN Bit rate desired = 500Kbps, CAN Clock = 16MHz then
 *       Baudrate = 2       Phase2 = 2
 *       Sync     = 13      SJW    = 1
 *********************************************************************/
Can_Config CanConfiguration = {                                             /* Sync, Phase2, SJW, BaudRate */
                               .pCanBitTimingConfig = &(Can_BitTimingConfig){13    ,   2   ,  1 , 2},
                               .CanBitRate          = 500000,               /* Bit Rate used = 500Kbps */
                               .CanInterrupts       = CanInterruptsDisable, /* No Interrupt Enabled */
                               .CanNum              = CAN_MODULE_0,         /* Use CAN Module 0 */
                               .ClkValue            = 16000000              /* CAN_Clk = 16MHz */
};






