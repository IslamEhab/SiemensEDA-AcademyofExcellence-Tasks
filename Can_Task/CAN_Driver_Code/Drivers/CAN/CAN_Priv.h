/********************************************************************************
 * @headerfile    CAN_Priv.h
 * @brief         Header file for CAN Defines on TM4C123GH6PM Microcontroller
 * @date          1/9/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - Interrupt Handling
 *                - CAN Testing Modes
 *******************************************************************************/
#ifndef DRIVERS_CAN_CAN_PRIV_H_
#define DRIVERS_CAN_CAN_PRIV_H_

/********************************************************************************
 *                                  Bits Defines                                *
 *******************************************************************************/

/************************** CAN_CTL Register defines *****************************/
#define CTL_REG_INIT_POS                ((uint8)0x0)       /* Initialization Bit Position                       */
#define CTL_REG_IE_POS                  ((uint8)0x1)       /* CAN Interrupt Enable Bit Position                 */
#define CTL_REG_SIE_POS                 ((uint8)0x2)       /* Status Interrupt Enable Bit Position              */
#define CTL_REG_EIE_POS                 ((uint8)0x3)       /* Error Interrupt Enable Bit Position               */
#define CTL_REG_DAR_POS                 ((uint8)0x5)       /* Disable Automatic-Retransmission Bit Position     */
#define CTL_REG_CCE_POS                 ((uint8)0x6)       /* Configuration Change Enable Bit Position          */
#define CTL_REG_TEST_POS                ((uint8)0x7)       /* Test Mode Enable Bit Position                     */

#define CTL_REG_INIT_ENABLE             ((uint8)0x1)       /* Initialization started Value                      */
#define CTL_REG_IE_ENABLE               ((uint8)0x1)       /* Interrupts enabled Value */
#define CTL_REG_SIE_ENABLE              ((uint8)0x1)       /* A change in the TXOK, RXOK or LEC bits in the
                                                              CANSTS register generates an interrupt            */
#define CTL_REG_EIE_ENABLE              ((uint8)0x1)       /* A change in the BOFF or EWARN bits in the CANSTS
                                                              register generates an interrupt                   */
#define CTL_REG_DAR_ENABLE              ((uint8)0x1)       /* Auto-retransmission is disabled                   */
#define CTL_REG_CCE_ENABLE              ((uint8)0x1)       /* Write accesses to the CANBIT register are
                                                              allowed if the INIT bit is 1                      */
#define CTL_REG_TEST_ENABLE             ((uint8)0x1)       /* CAN controller is in test mode                    */

/************************** CAN_IFnCRQ Register defines *****************************/
#define IFCR1_REG_MNUM_POS              ((uint8)0x0)       /* Message Object Number Bit Position                */
#define IFCRQ_REG_BUSY_POS              ((uint8)0xF)       /* Busy Flag bit position                            */

#define IFCRQ_REG_MNUM_MASK             ((uint8)0x3F)      /* Message Object Number Mask Value                  */
#define IFCRQ_REG_BUSY_ENABLE           ((uint8)0x1)       /* Set when a write occurs to the message number     */

/************************** CAN_IFnCMK Register defines *****************************/
#define CMSK_REG_DATAB_POS              ((uint8)0x0)       /* Access Data Byte 4 to 7 Bit Position              */
#define CMSK_REG_DATAA_POS              ((uint8)0x1)       /* Access Data Byte 0 to 3 Bit Position              */
#define CMSK_REG_NEWDAT_TXRQST_POS      ((uint8)0x2)       /* NEWDAT / TXRQST Bit Bit Position                  */
#define CMSK_REG_CLRINTPND_POS          ((uint8)0x3)       /* Clear Interrupt Pending Bit Bit Position          */
#define CMSK_REG_CONTROL_POS            ((uint8)0x4)       /* Access Control Bit Bit Position                   */
#define CMSK_REG_ARB_POS                ((uint8)0x5)       /* Access Arbitration Bits Bit Position              */
#define CMSK_REG_MASK_POS               ((uint8)0x6)       /* Access Mask Bits Bit Position                     */
#define CMSK_REG_WRNRD_POS              ((uint8)0x7)       /* Write, Not Read Bit Position                      */

#define CMSK_REG_DATAB_ENABLE           ((uint8)0x1)       /* if WRNRD=0, Tx data bytes 4->7 to msg object
                                                              if WRNRD=1, Tx data bytes 4->7 to DA, DB Regs     */
#define CMSK_REG_DATAA_ENABLE           ((uint8)0x1)       /* if WRNRD=0, Tx data bytes 0->3 to msg object
                                                              if WRNRD=1, Tx data bytes 0->3 to DA, DB Regs     */
#define CMSK_REG_NEWDAT_TXRQST_ENABLE   ((uint8)0x1)       /* if WRNRD=0, New Data status clrd in msg buffer
                                                              if WRNRD=1, Tx is requested                       */
#define CMSK_REG_CLRINTPND_ENABLE       ((uint8)0x1)       /* if WRNRD=0,INT Pending status clrd in msg buffer
                                                              if WRNRD=1,INTPND Bit is cleared in msg object    */
#define CMSK_REG_CONTROL_ENABLE         ((uint8)0x1)       /* Tx Control bits from MCTL Reg to IF Regs          */
#define CMSK_REG_ARB_ENABLE             ((uint8)0x1)       /* Tx ID+DIR+XTD+MSGVAL of msg object to IF Regs     */
#define CMSK_REG_MASK_ENABLE            ((uint8)0x1)       /* Tx IDMASK, DIR, MXTD of msg object to IF Regs     */
#define CMSK_REG_WRNRD_ENABLE           ((uint8)0x1)       /* Tx Data in IF Regs to CAN Msg Object              */
/************************** CAN_MCTL Register defines *****************************/
#define MCTL_REG_DLC_POS                ((uint8)0x0)       /* Data Length Code Bit Position                     */
#define MCTL_REG_EOB_POS                ((uint8)0x7)       /* End of Buffer Bit Position                        */
#define MCTL_REG_TXRQST_POS             ((uint8)0x8)       /* Transmit Request Bit Position                     */
#define MCTL_REG_RMTEN_POS              ((uint8)0x9)       /* Remote Enable Bit Position                        */
#define MCTL_REG_RXIE_POS               ((uint8)0xA)       /* ReceiveInterrupt Enable Bit Position              */
#define MCTL_REG_TXIE_POS               ((uint8)0xB)       /* Transmit Interrupt Enable Bit Position            */
#define MCTL_REG_UMASK_POS              ((uint8)0xC)       /* Use Acceptance Mask Bit Position                  */
#define MCTL_REG_INTPND_POS             ((uint8)0xD)       /* Interrupt Pending Bit Position                    */
#define MCTL_REG_MSGLST_POS             ((uint8)0xE)       /* Message Lost Bit Position                         */
#define MCTL_REG_NEWDAT_POS             ((uint8)0xF)       /* New Data Bit Position                             */

#define MCTL_REG_DLC_MASK               ((uint8)0xF)       /* Data Length Code Mask Value                       */
#define MCTL_REG_EOB_ENABLE             ((uint8)0x1)       /* Single or last message object of a FIFO Buffer    */
#define MCTL_REG_TXRQST_ENABLE          ((uint8)0x1)       /* Transmission of Msg object is req.& not yet done  */
#define MCTL_REG_RMTEN_ENABLE           ((uint8)0x1)       /* Set TXRQST Bit when remote frame received         */
#define MCTL_REG_RXIE_ENABLE            ((uint8)0x1)       /* Set INTPND Bit after receiving a frame            */
#define MCTL_REG_TXIE_ENABLE            ((uint8)0x1)       /* Set INTPND Bit after Transmitting frame           */
#define MCTL_REG_UMASK_ENABLE           ((uint8)0x1)       /* Use mask (MSK, MXTD, MDIR) for acceptance filter  */
#define MCTL_REG_INTPND_ENABLE          ((uint8)0x1)       /* This message object. is the source of Interrupt   */
#define MCTL_REG_MSGLST_ENABLE          ((uint8)0x1)       /* This msg handler stored new msg into this object
                                                              When NEWDAT Was Set, The CPU has LOST A MESSAGE   */
#define MCTL_REG_NEWDAT_ENABLE          ((uint8)0x1)       /* Msg Handler or CPU write new data into msg object */

/************************** CAN_ARB1 Register defines *****************************/
#define ARB1_REG_ID_POS                 ((uint8)0x0)       /* Message ID Bit Position                           */

#define ARB1_REG_ID_MASK                ((uint16)0xFFFF)   /* Message ID Mask Value                             */
/************************** CAN_ARB2 Register defines *****************************/
#define ARB2_REG_ID_POS                 ((uint8)0x0)       /* Message ID Bit Position                           */
#define ARB2_REG_DIR_POS                ((uint8)0xD)       /* Message Direction Bit Position                    */
#define ARB2_REG_XTD_POS                ((uint8)0xE)       /* Extended ID Bit Position                          */
#define ARB2_REG_MSGVAL_POS             ((uint8)0xF)       /* Message Valid Bit Position                        */

#define ARB2_REG_ID_MASK                ((uint16)0x1FFF)   /* Message ID Mask Value                             */
#define ARB2_REG_DIR_ENABLE             ((uint8)0x1)       /* Message Direction is Transmit                     */
#define ARB2_REG_XTD_ENABLE             ((uint8)0x1)       /* Use Extended ID (29 bits)                         */
#define ARB2_REG_MSGVAL_ENABLE          ((uint8)0x1)       /* This Message object is ready for msg handler      */

/************************** CAN_MSK1 Register defines *****************************/
#define MSK1_REG_MSK_POS                ((uint8)0x0)       /* Mask ID Bit Position                              */

#define MSK1_REG_MSK_MASK               ((uint16)0xFFFF)   /* Mask ID Masking Value                             */

/************************** CAN_MSK2 Register defines *****************************/
#define MSK2_REG_MSK_POS                ((uint8)0x0)       /* Mask ID Bit Position                              */
#define MSK2_REG_MDIR_POS               ((uint8)0xE)       /* Mask Message Direction Bit Position               */
#define MSK2_REG_MXTD_POS               ((uint8)0xF)       /* Mask Extended ID Bit Position                     */

#define MSK2_REG_MSK_MASK               ((uint16)0x1FFF)   /* Mask Id Masking Value                             */
#define MSK2_REG_MDIR_ENABLE            ((uint8)0x1)       /* DIR bit is used for acceptance filtering          */
#define MSK2_REG_MXTD_ENABLE            ((uint8)0x1)       /* XTD bit is used for acceptance filtering          */

/************************** CAN_BIT Register defines *****************************/
#define BIT_REG_BRP_POS                 ((uint8)0x0)       /* Baud Rate PreScaler Bit Position                  */
#define BIT_REG_SJW_POS                 ((uint8)0x6)       /* (Re)Synchronization Jump Width Bit Position       */
#define BIT_REG_TSEG1_POS               ((uint8)0x8)       /* Time Segment Before Sample Point Bit Position     */
#define BIT_REG_TSEG2_POS               ((uint8)0xC)       /* Time Segment after Sample Point Bit Position      */

#define BIT_REG_BRP_MASK                ((uint8)0x3F)      /* Baud Rate Mask value                              */
#define BIT_REG_SJW_MASK                ((uint8)0xC0)      /* (Re)Synchronization Jump Width Mask value         */
#define BIT_REG_TSEG1_MASK              ((uint16)0x0F00)   /* Time Segment Before Sample Mask value             */
#define BIT_REG_TSEG2_MASK              ((uint16)0x7000)   /* Time Segment After Sample Mask value              */

/************************** CAN_BRPE Register defines *****************************/
#define BRPE_REG_BRPE_POS               ((uint8)0x0)       /* Baud Rate PreScaler Extension bit position        */

#define BREP_REG_BREP_MASK              ((uint8)0xF)       /* Baud Rate PreScaler Extension Mask Value          */

/********************************************************************************
 *                           Preprocessor Macros                                *
 *******************************************************************************/
#define RCGC0_REG_CAN_POS               ((uint8)0x18)     /* CAN Clock Bit Position (Bit 24)                    */
#define BAUDRATE_EXTENSION_SHIFT        ((uint8)0x6)      /* CAN Bit timing baud rate extension shift value     */
#define ID_11_BIT_MAX_VALUE             ((uint16)0x7FF)   /* ID 11-bit Mode Max Value                           */
#define ID_29_BIT_MSK2_SHIFT_VALUE      ((uint8)0x10)     /* ID 29-Bit Shift value for MSK2 Register            */
#define ID_11_BIT_MSK2_SHIFT_VALUE      ((uint8)0x02)     /* ID 11-Bit Shift value for MSK2 Register            */
#define DATA_SHIFT_VALUE                ((uint8)0x08)     /* Reading data from user buffer shift left value     */
#define ARB1_REG_FULL_ID                ARB1_REG_ID_MASK  /* use Full ID in Arbitration ARB1 Reg value          */
#define ARB2_REG_FULL_ID                ARB2_REG_ID_MASK  /* Use Full ID in Arbitration ARB2 Reg value          */
#define ID_29_BIT_FULLY_SPECIFIED       0x1FFFFFFF        /* ID 29-Bit Fully Specified Mask Value               */
#define ID_11_BIT_FULLY_SPECIFIED       0x7FF             /* ID 11-Bit Fully Specified Mask Value               */
#define DATA_REG_OFFSET_VALUE           ((uint8)0x04)     /* Data Register offset value                         */

#endif /* DRIVERS_CAN_CAN_PRIV_H_ */
