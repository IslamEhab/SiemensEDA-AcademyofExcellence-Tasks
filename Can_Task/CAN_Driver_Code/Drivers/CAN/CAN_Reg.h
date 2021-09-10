/********************************************************************************
 * @headerfile    CAN_Reg.h
 * @brief         Header file for CAN Registers on TM4C123GH6PM Microcontroller
 * @date          1/9/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - Interrupt Handling
 *                - CAN Testing Modes
 *******************************************************************************/

#ifndef DRIVERS_CAN_CAN_REG_H_
#define DRIVERS_CAN_CAN_REG_H_

/*******************************************************************************
 *                         I2C(s) Registers Base Address                       *
 *******************************************************************************/
#define CAN_0_BASE_ADDRESS          0x40040000
#define CAN_1_BASE_ADDRESS          0x40041000

/*******************************************************************************
 *                        I2C(s) Registers Offset Address                      *
 *******************************************************************************/
#define CAN_CTL_REG_OFFSET          0x000             /* CAN Control                        */
#define CAN_STS_REG_OFFSET          0x004             /* CAN Status                         */
#define CAN_ERR_REG_OFFSET          0x008             /* CAN Error Counter                  */
#define CAN_BIT_REG_OFFSET          0x00C             /* CAN Bit Timing                     */
#define CAN_INT_REG_OFFSET          0x010             /* CAN Interrupt                      */
#define CAN_TST_REG_OFFSET          0x014             /* CAN Test                           */
#define CAN_BPRE_REG_OFFSET         0x018             /* CAN Baud Rate PreScaler Extension  */
#define CAN_IF1CRQ_REG_OFFSET       0x020             /* CAN IF1 Command Request            */
#define CAN_IF1CMSK_REG_OFFSET      0x024             /* CAN IF1 Command Mask               */
#define CAN_IF1MSK1_REG_OFFSET      0x028             /* CAN IF1 Mask 1                     */
#define CAN_IF1MSK2_REG_OFFSET      0x02C             /* CAN IF1 Mask 2                     */
#define CAN_IF1ARB1_REG_OFFSET      0x030             /* CAN IF1 Arbitration 1              */
#define CAN_IF1ARB2_REG_OFFSET      0x034             /* CAN IF1 Arbitration 2              */
#define CAN_IF1MCTL_REG_OFFSET      0x038             /* CAN IF1 Message Control            */
#define CAN_IF1DA1_REG_OFFSET       0x03C             /* CAN IF1 Data A1                    */
#define CAN_IF1DA2_REG_OFFSET       0x040             /* CAN IF1 Data A2                    */
#define CAN_IF1DB1_REG_OFFSET       0x044             /* CAN IF1 Data B1                    */
#define CAN_IF1DB2_REG_OFFSET       0x048             /* CAN IF1 Data B2                    */
#define CAN_IF2CRQ_REG_OFFSET       0x080             /* CAN IF2 Command Request            */
#define CAN_IF2CMSK_REG_OFFSET      0x084             /* CAN IF2 Command Mask               */
#define CAN_IF2MSK1_REG_OFFSET      0x088             /* CAN IF2 Mask 1                     */
#define CAN_IF2MSK2_REG_OFFSET      0x08C             /* CAN IF2 Mask 2                     */
#define CAN_IF2ARB1_REG_OFFSET      0x090             /* CAN IF2 Arbitration 1              */
#define CAN_IF2ARB2_REG_OFFSET      0x094             /* CAN IF2 Arbitration 2              */
#define CAN_IF2MCTL_REG_OFFSET      0x098             /* CAN IF2 Message Control            */
#define CAN_IF2DA1_REG_OFFSET       0x09C             /* CAN IF2 Data A1                    */
#define CAN_IF2DA2_REG_OFFSET       0x0A0             /* CAN IF2 Data A2                    */
#define CAN_IF2DB1_REG_OFFSET       0x0A4             /* CAN IF2 Data B1                    */
#define CAN_IF2DB2_REG_OFFSET       0x0A8             /* CAN IF2 Data B2                    */
#define CAN_TXRQ1_REG_OFFSET        0x100             /* CAN Transmission Request 1         */
#define CAN_TXRQ2_REG_OFFSET        0x104             /* CAN Transmission Request 2         */
#define CAN_NWDA1_REG_OFFSET        0x120             /* CAN New Data 1                     */
#define CAN_NWDA2_REG_OFFSET        0x124             /* CAN New Data 2                     */
#define CAN_MSG1INT_REG_OFFSET      0x140             /* CAN Message 1 Interrupt Pending    */
#define CAN_MSG2INT_REG_OFFSET      0x144             /* CAN Message 2 Interrupt Pending    */
#define CAN_MSG1VAL_REG_OFFSET      0x160             /* CAN Message 1 Valid                */
#define CAN_MSG2VAL_REG_OFFSET      0x164             /* CAN Message 2 Valid                */


/*******************************************************************************
 *                   System Control CAN Enable Clock Register                  *
 *******************************************************************************/
#define SYSCTL_RCGC0_REG  (*((volatile unsigned long*)0x400FE100))      /* Note: CAN Bits from bit 24 */


#endif /* DRIVERS_CAN_CAN_REG_H_ */
