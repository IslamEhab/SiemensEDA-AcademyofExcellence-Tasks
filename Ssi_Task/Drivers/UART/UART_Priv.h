/********************************************************************************
 * @headerfile    UART_Priv.h
 * @brief         Header file for UART Defines and bits on TM4C123GH6PM Microcontroller
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


#ifndef DRIVERS_UART_UART_PRIV_H_
#define DRIVERS_UART_UART_PRIV_H_


/************************** UART_CTL Register defines *****************************/
#define CTL_REG_UARTEN_POS              ((uint8) 0x0)   /* Uart Enable Bit Position                 */
#define CTL_REG_SIREN_POS               ((uint8) 0x1)   /* UART SIR Bit Position                    */
#define CTL_REG_SIRLP_POS               ((uint8) 0x2)   /* UART SIR Low Power Bit Position          */
#define CTL_REG_SMART_POS               ((uint8) 0x3)   /* ISO 7816 Smart Card Support Bit Position */
#define CTL_REG_EOT_POS                 ((uint8) 0x4)   /* End of Transmission Bit Position         */
#define CTL_REG_HSE_POS                 ((uint8) 0x5)   /* High-Speed Enable Bit Position           */
#define CTL_REG_LBE_POS                 ((uint8) 0x7)   /* UART Loop Back Enable Bit Position       */
#define CTL_REG_TXE_POS                 ((uint8) 0x8)   /* UART Transmit Enable Bit Position        */
#define CTL_REG_RXE_POS                 ((uint8) 0x9)   /* UART Receive Enable Bit Position         */
#define CTL_REG_RTS_POS                 ((uint8) 0xB)   /* Request to Send Bit Position             */
#define CTL_REG_RTSEN_POS               ((uint8) 0xE)   /* Enable Request to Send Bit Position      */
#define CTL_REG_CTSEN_POS               ((uint8) 0xF)   /* Enable Clear To Send Bit Position        */

#define CTL_REG_UARTEN_ENABLE           ((uint8) 0x1)   /* Uart Enable Value                        */
#define CTL_REG_SIREN_ENABLE            ((uint8) 0x1)   /* UART SIR Enable value                    */
#define CTL_REG_SIRLP_ENABLE            ((uint8) 0x1)   /* UART SIR Low Power Enable value          */
#define CTL_REG_SMART_ENABLE            ((uint8) 0x1)   /* ISO 7816 Smart Card Support Enable value */
#define CTL_REG_EOT_ENABLE              ((uint8) 0x1)   /* End of Transmission Enable value         */
#define CTL_REG_HSE_ENABLE              ((uint8) 0x1)   /* High-Speed Enable value                  */
#define CTL_REG_LBE_ENABLE              ((uint8) 0x1)   /* UART Loop Back Enable value              */
#define CTL_REG_TXE_ENABLE              ((uint8) 0x1)   /* UART Transmit Enable value               */
#define CTL_REG_RXE_ENABLE              ((uint8) 0x1)   /* UART Receive Enable value                */
#define CTL_REG_RTS_ENABLE              ((uint8) 0x1)   /* Request to Send                          */
#define CTL_REG_RTSEN_ENABLE            ((uint8) 0x1)   /* Enable Request to Send                   */
#define CTL_REG_CTSEN_ENABLE            ((uint8) 0x1)   /* Enable Clear To Send                     */


/************************** UART_LCRH Register defines *****************************/
#define LCRH_REG_BRK_POS                ((uint8) 0x0)   /* UART Send Break Bit Position             */
#define LCRH_REG_PEN_POS                ((uint8) 0x1)   /* UART Parity Enable bit position          */
#define LCRH_REG_EPS_POS                ((uint8) 0x2)   /* UART Even Parity Select Bit position     */
#define LCRH_REG_STP2_POS               ((uint8) 0x3)   /* UART Two Stop Bits Select Bit position   */
#define LCRH_REG_FEN_POS                ((uint8) 0x4)   /* UART Enable FIFOs Bit position           */
#define LCRH_REG_WLEN_POS               ((uint8) 0x5)   /* UART Word Length Bit position            */
#define LCRH_REG_SPS_POS                ((uint8) 0x7)   /* UART Stick Parity Select Bit position    */


#define LCRH_REG_BRK_ENABLE             ((uint8) 0x1)   /* UART Send Break enable value             */
#define LCRH_REG_PEN_ENABLE             ((uint8) 0x1)   /* UART Parity enable value                 */
#define LCRH_REG_EPS_EVEN               ((uint8) 0x1)   /* UART Even Parity enable value            */
#define LCRH_REG_EPS_OVEN               ((uint8) 0x0)   /* UART Odd Parity enable value             */
#define LCRH_REG_STP2_ENABLE            ((uint8) 0x1)   /* UART Two Stop Bits enable value          */
#define LCRH_REG_FEN_ENABLE             ((uint8) 0x1)   /* UART FIFOs enable value                  */

/************************** UART_9BITADDR Register defines *****************************/
#define NINEBITADDR_REG_9BITEN_POS      ((uint8) 0xF)   /* UART Enable 9-Bit Mode Bit Position      */

#define NINEBITADDR_REG_9BITEN_ENABLE   ((uint8) 0x1)   /* UART 9-Bit Mode enable value             */

/************************** UART_IM Register defines *****************************/
#define IM_REG_RXIM_POS                 ((uint8) 0x4)

/************************** UART_RIS Register defines *****************************/
#define RIS_REG_CTSRIS_POS              ((uint8) 0x1)   /* UART Clear to Send Modem Raw Interrupt Status Bit Position   */
#define RIS_REG_RXRIS_POS               ((uint8) 0x4)   /* Receive Raw Interrupt Status Bit Position                    */
#define RIS_REG_TXRIS_POS               ((uint8) 0x5)   /* Transmit Raw Interrupt Status Bit Position                   */
#define RIS_REG_RTRIS_POS               ((uint8) 0x6)   /* Receive Time-Out Raw Interrupt Status Bit Position           */
#define RIS_REG_FERIS_POS               ((uint8) 0x7)   /* Framing Error Raw Interrupt Status Bit Position              */
#define RIS_REG_PERIS_POS               ((uint8) 0x8)   /* Parity Error Raw Interrupt Status Bit Position               */
#define RIS_REG_BERIS_POS               ((uint8) 0x9)   /* Break Error Raw Interrupt Status Bit Position                */
#define RIS_REG_OERIS_POS               ((uint8) 0xA)   /* Overrun Error Raw Interrupt Status Bit Position              */
#define RIS_REG_9BITRIS_POS             ((uint8) 0xC)   /* 9-Bit Mode Raw Interrupt Status Bit Position                 */


/************************** UART_FR Register defines *****************************/
#define FR_REG_CTS_POS                  ((uint8) 0x0)   /* Clear To Send Flag Bit Position                              */
#define FR_REG_BUSY_POS                 ((uint8) 0x3)   /* UART Busy Flag Bit Position                                  */
#define FR_REG_RXFE_POS                 ((uint8) 0x4)   /* Receive FIFO Empty Flag Bit Position                         */
#define FR_REG_TXFF_POS                 ((uint8) 0x5)   /* Transmit FIFO Full Flag Bit Position                         */
#define FR_REG_RXFF_POS                 ((uint8) 0x6)   /* Receive FIFO Full Flag Bit Position                          */
#define FR_REG_TXFE_POS                 ((uint8) 0x7)   /* Transmit FIFO Empty Flag Bit Position                        */


#define FR_REG_CTS_ENABLE               ((uint8) 0x1)   /* Clear To Send Flag Enable Value                              */
#define FR_REG_BUSY_ENABLE              ((uint8) 0x1)   /* UART Busy Flag Enable Value                                  */
#define FR_REG_RXFE_ENABLE              ((uint8) 0x1)   /* Receive FIFO Empty Flag Enable Value                         */
#define FR_REG_TXFE_ENABLE              ((uint8) 0x1)   /* Transmit FIFO Full Flag Enable Value                         */
#define FR_REG_RXFF_ENABLE              ((uint8) 0x1)   /* Receive FIFO Full Flag Enable Value                          */
#define FR_REG_TXFE_ENABLE              ((uint8) 0x1)   /* Transmit FIFO Empty Flag Enable Value                        */


#endif /* DRIVERS_UART_UART_PRIV_H_ */
