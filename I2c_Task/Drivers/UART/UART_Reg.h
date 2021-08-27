/********************************************************************************
 * @headerfile    UART_Reg.h
 * @brief         Header file for UART Registers on TM4C123GH6PM Microcontroller
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

#ifndef DRIVERS_UART_UART_REG_H_
#define DRIVERS_UART_UART_REG_H_


/*******************************************************************************
 *                        UART(s) Registers Base Address                       *
 *******************************************************************************/
#define UART_0_BASE_ADDRESS     0x4000C000  /* UART0 Base Address */
#define UART_1_BASE_ADDRESS     0x4000D000  /* UART1 Base Address */
#define UART_2_BASE_ADDRESS     0x4000E000  /* UART2 Base Address */
#define UART_3_BASE_ADDRESS     0x4000F000  /* UART3 Base Address */
#define UART_4_BASE_ADDRESS     0x40010000  /* UART4 Base Address */
#define UART_5_BASE_ADDRESS     0x40011000  /* UART5 Base Address */
#define UART_6_BASE_ADDRESS     0x40012000  /* UART6 Base Address */
#define UART_7_BASE_ADDRESS     0x40013000  /* UART7 Base Address */
/*******************************************************************************/

/*******************************************************************************
 *                       UART(s) Registers Offset Address                      *
 *******************************************************************************/

#define UART_DATA_REG_OFFSET        0x000    /* UART Data                        */
#define UART_RSR_ECR_REG_OFFSET     0x004    /* UART Receive Status/Error Clear  */
#define UART_FR_REG_OFFSET          0x018    /* UART Flag                        */
#define UART_ILPR_REG_OFFSET        0x020    /* UART IrDA Low-Power Register     */
#define UART_IBRD_REG_OFFSET        0x024    /* UART Integer Baud-Rate Divisor   */
#define UART_FBRD_REG_OFFSET        0x028    /* UART Fractional BaudRate Divisor */
#define UART_LCRH_REG_OFFSET        0x02C    /* UART Line Control                */
#define UART_CTL_REG_OFFSET         0x030    /* UART Control                     */
#define UART_IFLS_REG_OFFSET        0x034    /* UART Interrupt FIFO Level Select */
#define UART_IM_REG_OFFSET          0x038    /* UART Interrupt Mask              */
#define UART_RIS_REG_OFFSET         0x03C    /* UART Raw Interrupt Status        */
#define UART_MIS_REG_OFFSET         0x040    /* UART Masked Interrupt Status     */
#define UART_ICR_REG_OFFSET         0x044    /* UART Interrupt Clear             */
#define UART_DMACTL_REG_OFFSET      0x048    /* UART DMA Control                 */
#define UART_9BITADDR_REG_OFFSET    0x0A4    /* UART 9-Bit Self Address          */
#define UART_9BITAMASK_REG_OFFSET   0x0A8    /* UART 9-Bit Self Address Mask     */
#define UART_PP_REG_OFFSET          0xFC0    /* UART Peripheral Properties       */
#define UART_CC_REG_OFFSET          0xFC8    /* UART Clock Configuration         */
#define UART_PERIPHID4_REG_OFFSET   0xFD0    /* UART Peripheral Identification 4 */
#define UART_PERIPHID5_REG_OFFSET   0xFD4    /* UART Peripheral Identification 5 */
#define UART_PERIPHID6_REG_OFFSET   0xFD8    /* UART Peripheral Identification 6 */
#define UART_PERIPHID7_REG_OFFSET   0xFDC    /* UART Peripheral Identification 7 */
#define UART_PERIPHID0_REG_OFFSET   0xFE0    /* UART Peripheral Identification 0 */
#define UART_PERIPHID1_REG_OFFSET   0xFE4    /* UART Peripheral Identification 1 */
#define UART_PERIPHID2_REG_OFFSET   0xFE8    /* UART Peripheral Identification 2 */
#define UART_PERIPHID3_REG_OFFSET   0xFEC    /* UART Peripheral Identification 3 */
#define UART_CELLID0_REG_OFFSET     0xFF0    /* UART PrimeCell Identification 0  */
#define UART_CELLID1_REG_OFFSET     0xFF4    /* UART PrimeCell Identification 1  */
#define UART_CELLID2_REG_OFFSET     0xFF8    /* UART PrimeCell Identification 2  */
#define UART_CELLID3_REG_OFFSET     0xFFC    /* UART PrimeCell Identification 3  */

/**********************************************************************************/


/*******************************************************************************
 *                   System Control UART Enable Clock Register                  *
 *******************************************************************************/
#define SYSCTL_RCGCUART_REG        (*((volatile unsigned long *)0x400FE618))


#endif /* DRIVERS_UART_UART_REG_H_ */
