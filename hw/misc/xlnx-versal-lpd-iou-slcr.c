/*
 * QEMU model of the LPD_IOU_SLCR Global system level control registers for the iou
 *
 * Copyright (c) 2024 Wind River Systems, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Copyright (c) 2020 Xilinx Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include "hw/sysbus.h"
#include "hw/register.h"
#include "qemu/bitops.h"
#include "qemu/log.h"
#include "migration/vmstate.h"
#include "hw/irq.h"
#include "hw/misc/xlnx-versal-lpd-iou-slcr.h"

#ifndef XILINX_LPD_IOU_SLCR_ERR_DEBUG
#define XILINX_LPD_IOU_SLCR_ERR_DEBUG 0
#endif

REG32(MIO_PIN_0, 0x0)
    FIELD(MIO_PIN_0, L3_SEL, 7, 3)
    FIELD(MIO_PIN_0, L2_SEL, 5, 2)
    FIELD(MIO_PIN_0, L1_SEL, 3, 2)
    FIELD(MIO_PIN_0, L0_SEL, 1, 2)
REG32(MIO_PIN_1, 0x4)
    FIELD(MIO_PIN_1, L3_SEL, 7, 3)
    FIELD(MIO_PIN_1, L2_SEL, 5, 2)
    FIELD(MIO_PIN_1, L1_SEL, 3, 2)
    FIELD(MIO_PIN_1, L0_SEL, 1, 2)
REG32(MIO_PIN_2, 0x8)
    FIELD(MIO_PIN_2, L3_SEL, 7, 3)
    FIELD(MIO_PIN_2, L2_SEL, 5, 2)
    FIELD(MIO_PIN_2, L1_SEL, 3, 2)
    FIELD(MIO_PIN_2, L0_SEL, 1, 2)
REG32(MIO_PIN_3, 0xc)
    FIELD(MIO_PIN_3, L3_SEL, 7, 3)
    FIELD(MIO_PIN_3, L2_SEL, 5, 2)
    FIELD(MIO_PIN_3, L1_SEL, 3, 2)
    FIELD(MIO_PIN_3, L0_SEL, 1, 2)
REG32(MIO_PIN_4, 0x10)
    FIELD(MIO_PIN_4, L3_SEL, 7, 3)
    FIELD(MIO_PIN_4, L2_SEL, 5, 2)
    FIELD(MIO_PIN_4, L1_SEL, 3, 2)
    FIELD(MIO_PIN_4, L0_SEL, 1, 2)
REG32(MIO_PIN_5, 0x14)
    FIELD(MIO_PIN_5, L3_SEL, 7, 3)
    FIELD(MIO_PIN_5, L2_SEL, 5, 2)
    FIELD(MIO_PIN_5, L1_SEL, 3, 2)
    FIELD(MIO_PIN_5, L0_SEL, 1, 2)
REG32(MIO_PIN_6, 0x18)
    FIELD(MIO_PIN_6, L3_SEL, 7, 3)
    FIELD(MIO_PIN_6, L2_SEL, 5, 2)
    FIELD(MIO_PIN_6, L1_SEL, 3, 2)
    FIELD(MIO_PIN_6, L0_SEL, 1, 2)
REG32(MIO_PIN_7, 0x1c)
    FIELD(MIO_PIN_7, L3_SEL, 7, 3)
    FIELD(MIO_PIN_7, L2_SEL, 5, 2)
    FIELD(MIO_PIN_7, L1_SEL, 3, 2)
    FIELD(MIO_PIN_7, L0_SEL, 1, 2)
REG32(MIO_PIN_8, 0x20)
    FIELD(MIO_PIN_8, L3_SEL, 7, 3)
    FIELD(MIO_PIN_8, L2_SEL, 5, 2)
    FIELD(MIO_PIN_8, L1_SEL, 3, 2)
    FIELD(MIO_PIN_8, L0_SEL, 1, 2)
REG32(MIO_PIN_9, 0x24)
    FIELD(MIO_PIN_9, L3_SEL, 7, 3)
    FIELD(MIO_PIN_9, L2_SEL, 5, 2)
    FIELD(MIO_PIN_9, L1_SEL, 3, 2)
    FIELD(MIO_PIN_9, L0_SEL, 1, 2)
REG32(MIO_PIN_10, 0x28)
    FIELD(MIO_PIN_10, L3_SEL, 7, 3)
    FIELD(MIO_PIN_10, L2_SEL, 5, 2)
    FIELD(MIO_PIN_10, L1_SEL, 3, 2)
    FIELD(MIO_PIN_10, L0_SEL, 1, 2)
REG32(MIO_PIN_11, 0x2c)
    FIELD(MIO_PIN_11, L3_SEL, 7, 3)
    FIELD(MIO_PIN_11, L2_SEL, 5, 2)
    FIELD(MIO_PIN_11, L1_SEL, 3, 2)
    FIELD(MIO_PIN_11, L0_SEL, 1, 2)
REG32(MIO_PIN_12, 0x30)
    FIELD(MIO_PIN_12, L3_SEL, 7, 3)
    FIELD(MIO_PIN_12, L2_SEL, 5, 2)
    FIELD(MIO_PIN_12, L1_SEL, 3, 2)
    FIELD(MIO_PIN_12, L0_SEL, 1, 2)
REG32(MIO_PIN_13, 0x34)
    FIELD(MIO_PIN_13, L3_SEL, 7, 3)
    FIELD(MIO_PIN_13, L2_SEL, 5, 2)
    FIELD(MIO_PIN_13, L1_SEL, 3, 2)
    FIELD(MIO_PIN_13, L0_SEL, 1, 2)
REG32(MIO_PIN_14, 0x38)
    FIELD(MIO_PIN_14, L3_SEL, 7, 3)
    FIELD(MIO_PIN_14, L2_SEL, 5, 2)
    FIELD(MIO_PIN_14, L1_SEL, 3, 2)
    FIELD(MIO_PIN_14, L0_SEL, 1, 2)
REG32(MIO_PIN_15, 0x3c)
    FIELD(MIO_PIN_15, L3_SEL, 7, 3)
    FIELD(MIO_PIN_15, L2_SEL, 5, 2)
    FIELD(MIO_PIN_15, L1_SEL, 3, 2)
    FIELD(MIO_PIN_15, L0_SEL, 1, 2)
REG32(MIO_PIN_16, 0x40)
    FIELD(MIO_PIN_16, L3_SEL, 7, 3)
    FIELD(MIO_PIN_16, L2_SEL, 5, 2)
    FIELD(MIO_PIN_16, L1_SEL, 3, 2)
    FIELD(MIO_PIN_16, L0_SEL, 1, 2)
REG32(MIO_PIN_17, 0x44)
    FIELD(MIO_PIN_17, L3_SEL, 7, 3)
    FIELD(MIO_PIN_17, L2_SEL, 5, 2)
    FIELD(MIO_PIN_17, L1_SEL, 3, 2)
    FIELD(MIO_PIN_17, L0_SEL, 1, 2)
REG32(MIO_PIN_18, 0x48)
    FIELD(MIO_PIN_18, L3_SEL, 7, 3)
    FIELD(MIO_PIN_18, L2_SEL, 5, 2)
    FIELD(MIO_PIN_18, L1_SEL, 3, 2)
    FIELD(MIO_PIN_18, L0_SEL, 1, 2)
REG32(MIO_PIN_19, 0x4c)
    FIELD(MIO_PIN_19, L3_SEL, 7, 3)
    FIELD(MIO_PIN_19, L2_SEL, 5, 2)
    FIELD(MIO_PIN_19, L1_SEL, 3, 2)
    FIELD(MIO_PIN_19, L0_SEL, 1, 2)
REG32(MIO_PIN_20, 0x50)
    FIELD(MIO_PIN_20, L3_SEL, 7, 3)
    FIELD(MIO_PIN_20, L2_SEL, 5, 2)
    FIELD(MIO_PIN_20, L1_SEL, 3, 2)
    FIELD(MIO_PIN_20, L0_SEL, 1, 2)
REG32(MIO_PIN_21, 0x54)
    FIELD(MIO_PIN_21, L3_SEL, 7, 3)
    FIELD(MIO_PIN_21, L2_SEL, 5, 2)
    FIELD(MIO_PIN_21, L1_SEL, 3, 2)
    FIELD(MIO_PIN_21, L0_SEL, 1, 2)
REG32(MIO_PIN_22, 0x58)
    FIELD(MIO_PIN_22, L3_SEL, 7, 3)
    FIELD(MIO_PIN_22, L2_SEL, 5, 2)
    FIELD(MIO_PIN_22, L1_SEL, 3, 2)
    FIELD(MIO_PIN_22, L0_SEL, 1, 2)
REG32(MIO_PIN_23, 0x5c)
    FIELD(MIO_PIN_23, L3_SEL, 7, 3)
    FIELD(MIO_PIN_23, L2_SEL, 5, 2)
    FIELD(MIO_PIN_23, L1_SEL, 3, 2)
    FIELD(MIO_PIN_23, L0_SEL, 1, 2)
REG32(MIO_PIN_24, 0x60)
    FIELD(MIO_PIN_24, L3_SEL, 7, 3)
    FIELD(MIO_PIN_24, L2_SEL, 5, 2)
    FIELD(MIO_PIN_24, L1_SEL, 3, 2)
    FIELD(MIO_PIN_24, L0_SEL, 1, 2)
REG32(MIO_PIN_25, 0x64)
    FIELD(MIO_PIN_25, L3_SEL, 7, 3)
    FIELD(MIO_PIN_25, L2_SEL, 5, 2)
    FIELD(MIO_PIN_25, L1_SEL, 3, 2)
    FIELD(MIO_PIN_25, L0_SEL, 1, 2)
REG32(BNK2_EN_RX_SCHMITT_HYST, 0x10c)
    FIELD(BNK2_EN_RX_SCHMITT_HYST, BNK2_EN_RX_SCHMITT_HYST, 0, 26)
REG32(BNK2_EN_WK_PD, 0x110)
    FIELD(BNK2_EN_WK_PD, BNK2_EN_WK_PD, 0, 26)
REG32(BNK2_EN_WK_PU, 0x114)
    FIELD(BNK2_EN_WK_PU, BNK2_EN_WK_PU, 0, 26)
REG32(BNK2_SEL_DRV0, 0x118)
REG32(BNK2_SEL_DRV1, 0x11c)
    FIELD(BNK2_SEL_DRV1, BNK2_SEL_DRV, 0, 20)
REG32(BNK2_SEL_SLEW, 0x120)
    FIELD(BNK2_SEL_SLEW, BNK2_SEL_SLEW, 0, 26)
REG32(BNK2_VMODE, 0x15c)
    FIELD(BNK2_VMODE, BNK2_VMODE, 0, 1)
REG32(BNK2_SEL_AUX_IO_RX, 0x160)
    FIELD(BNK2_SEL_AUX_IO_RX, BNK2_SEL_AUX_IO_RX, 0, 26)
REG32(MIO_LOOPBACK, 0x200)
    FIELD(MIO_LOOPBACK, I2C0_LOOP_I2C1, 3, 1)
    FIELD(MIO_LOOPBACK, CAN0_LOOP_CAN1, 2, 1)
    FIELD(MIO_LOOPBACK, UA0_LOOP_UA1, 1, 1)
    FIELD(MIO_LOOPBACK, SPI0_LOOP_SPI1, 0, 1)
REG32(MIO_MST_TRI0, 0x204)
    FIELD(MIO_MST_TRI0, PIN_25_TRI, 25, 1)
    FIELD(MIO_MST_TRI0, PIN_24_TRI, 24, 1)
    FIELD(MIO_MST_TRI0, PIN_23_TRI, 23, 1)
    FIELD(MIO_MST_TRI0, PIN_22_TRI, 22, 1)
    FIELD(MIO_MST_TRI0, PIN_21_TRI, 21, 1)
    FIELD(MIO_MST_TRI0, PIN_20_TRI, 20, 1)
    FIELD(MIO_MST_TRI0, PIN_19_TRI, 19, 1)
    FIELD(MIO_MST_TRI0, PIN_18_TRI, 18, 1)
    FIELD(MIO_MST_TRI0, PIN_17_TRI, 17, 1)
    FIELD(MIO_MST_TRI0, PIN_16_TRI, 16, 1)
    FIELD(MIO_MST_TRI0, PIN_15_TRI, 15, 1)
    FIELD(MIO_MST_TRI0, PIN_14_TRI, 14, 1)
    FIELD(MIO_MST_TRI0, PIN_13_TRI, 13, 1)
    FIELD(MIO_MST_TRI0, PIN_12_TRI, 12, 1)
    FIELD(MIO_MST_TRI0, PIN_11_TRI, 11, 1)
    FIELD(MIO_MST_TRI0, PIN_10_TRI, 10, 1)
    FIELD(MIO_MST_TRI0, PIN_09_TRI, 9, 1)
    FIELD(MIO_MST_TRI0, PIN_08_TRI, 8, 1)
    FIELD(MIO_MST_TRI0, PIN_07_TRI, 7, 1)
    FIELD(MIO_MST_TRI0, PIN_06_TRI, 6, 1)
    FIELD(MIO_MST_TRI0, PIN_05_TRI, 5, 1)
    FIELD(MIO_MST_TRI0, PIN_04_TRI, 4, 1)
    FIELD(MIO_MST_TRI0, PIN_03_TRI, 3, 1)
    FIELD(MIO_MST_TRI0, PIN_02_TRI, 2, 1)
    FIELD(MIO_MST_TRI0, PIN_01_TRI, 1, 1)
    FIELD(MIO_MST_TRI0, PIN_00_TRI, 0, 1)
REG32(WDT_CLK_SEL, 0x300)
    FIELD(WDT_CLK_SEL, SELECT, 0, 1)
REG32(GEM_CLK_CTRL, 0x320)
    FIELD(GEM_CLK_CTRL, TSU_CLK_LB_SEL, 22, 1)
    FIELD(GEM_CLK_CTRL, TSU_CLK_SEL, 20, 2)
    FIELD(GEM_CLK_CTRL, GEM1_FIFO_CLK_SEL, 7, 1)
    FIELD(GEM_CLK_CTRL, GEM1_REF_SRC_SEL, 6, 1)
    FIELD(GEM_CLK_CTRL, GEM1_RX_SRC_SEL, 5, 1)
    FIELD(GEM_CLK_CTRL, GEM0_FIFO_CLK_SEL, 2, 1)
    FIELD(GEM_CLK_CTRL, GEM0_REF_SRC_SEL, 1, 1)
    FIELD(GEM_CLK_CTRL, GEM0_RX_SRC_SEL, 0, 1)
REG32(GEM0_IOU_COHERENT_CTRL, 0x324)
    FIELD(GEM0_IOU_COHERENT_CTRL, GEM0_AXI_COH, 0, 4)
REG32(GEM0_IOU_INTERCONNECT_ROUTE, 0x328)
    FIELD(GEM0_IOU_INTERCONNECT_ROUTE, GEM0, 0, 1)
REG32(GEM0_IOU_INTERCONNECT_QOS, 0x32c)
    FIELD(GEM0_IOU_INTERCONNECT_QOS, GEM0_QOS, 0, 4)
REG32(GEM1_IOU_COHERENT_CTRL, 0x344)
    FIELD(GEM1_IOU_COHERENT_CTRL, GEM1_AXI_COH, 0, 4)
REG32(GEM1_IOU_INTERCONNECT_ROUTE, 0x348)
    FIELD(GEM1_IOU_INTERCONNECT_ROUTE, GEM1, 0, 1)
REG32(GEM1_IOU_INTERCONNECT_QOS, 0x34c)
    FIELD(GEM1_IOU_INTERCONNECT_QOS, GEM1_QOS, 0, 4)
REG32(IOU_TTC_APB_CLK, 0x360)
    FIELD(IOU_TTC_APB_CLK, TTC3_SEL, 6, 2)
    FIELD(IOU_TTC_APB_CLK, TTC2_SEL, 4, 2)
    FIELD(IOU_TTC_APB_CLK, TTC1_SEL, 2, 2)
    FIELD(IOU_TTC_APB_CLK, TTC0_SEL, 0, 2)
REG32(LPD_MIO_SEL, 0x410)
    FIELD(LPD_MIO_SEL, WWDT1_SEL, 17, 1)
    FIELD(LPD_MIO_SEL, WWDT0_SEL, 16, 1)
    FIELD(LPD_MIO_SEL, I2C1_SEL, 15, 1)
    FIELD(LPD_MIO_SEL, I2C0_SEL, 14, 1)
    FIELD(LPD_MIO_SEL, CAN1_SEL, 13, 1)
    FIELD(LPD_MIO_SEL, CAN0_SEL, 12, 1)
    FIELD(LPD_MIO_SEL, UART1_SEL, 11, 1)
    FIELD(LPD_MIO_SEL, UART0_SEL, 10, 1)
    FIELD(LPD_MIO_SEL, TTC3_SEL, 9, 1)
    FIELD(LPD_MIO_SEL, TTC2_SEL, 8, 1)
    FIELD(LPD_MIO_SEL, TTC1_SEL, 7, 1)
    FIELD(LPD_MIO_SEL, TTC0_SEL, 6, 1)
    FIELD(LPD_MIO_SEL, SPI1_SEL, 5, 1)
    FIELD(LPD_MIO_SEL, SPI0_SEL, 4, 1)
    FIELD(LPD_MIO_SEL, GEM1_MDIO_SEL, 3, 1)
    FIELD(LPD_MIO_SEL, GEM1RGMII_SEL, 2, 1)
    FIELD(LPD_MIO_SEL, GEM0_MDIO_SEL, 1, 1)
    FIELD(LPD_MIO_SEL, GEM0RGMII_SEL, 0, 1)
REG32(USB_IOU_INTERCONNECT_ROUTE, 0x428)
    FIELD(USB_IOU_INTERCONNECT_ROUTE, USB, 0, 1)
REG32(USB_IOU_INTERCONNECT_QOS, 0x42c)
    FIELD(USB_IOU_INTERCONNECT_QOS, USB_QOS, 0, 4)
REG32(SMID_FOR_USB, 0x430)
    FIELD(SMID_FOR_USB, SMID_CONFIG_USB, 0, 1)
REG32(CTRL, 0x600)
    FIELD(CTRL, SLVERR_ENABLE, 0, 1)
REG32(ISR, 0x700)
    FIELD(ISR, ADDR_DECODE_ERR, 0, 1)
REG32(IMR, 0x704)
    FIELD(IMR, ADDR_DECODE_ERR, 0, 1)
REG32(IER, 0x708)
    FIELD(IER, ADDR_DECODE_ERR, 0, 1)
REG32(IDR, 0x70c)
    FIELD(IDR, ADDR_DECODE_ERR, 0, 1)
REG32(ITR, 0x710)
    FIELD(ITR, ADDR_DECODE_ERR, 0, 1)
REG32(PARITY_ISR, 0x714)
    FIELD(PARITY_ISR, PERR_WWDT0_APB, 24, 1)
    FIELD(PARITY_ISR, PERR_USB_XS, 23, 1)
    FIELD(PARITY_ISR, PERR_USB_XM_IOU, 22, 1)
    FIELD(PARITY_ISR, PERR_USB_APB, 21, 1)
    FIELD(PARITY_ISR, PERR_UART1_APB, 20, 1)
    FIELD(PARITY_ISR, PERR_UART0_APB, 19, 1)
    FIELD(PARITY_ISR, PERR_TTC3_APB, 18, 1)
    FIELD(PARITY_ISR, PERR_TTC2_APB, 17, 1)
    FIELD(PARITY_ISR, PERR_TTC1_APB, 16, 1)
    FIELD(PARITY_ISR, PERR_TTC0_APB, 15, 1)
    FIELD(PARITY_ISR, PERR_SPI1_APB, 14, 1)
    FIELD(PARITY_ISR, PERR_IOU_SPI0_APB, 13, 1)
    FIELD(PARITY_ISR, PERR_SCNTR2_APB, 12, 1)
    FIELD(PARITY_ISR, PERR_SCNTR1_APB, 11, 1)
    FIELD(PARITY_ISR, PERR_IOUSLCR_SECURE_APB, 10, 1)
    FIELD(PARITY_ISR, PERR_IOUSLCR_APB, 9, 1)
    FIELD(PARITY_ISR, PERR_IOU_GEM1_APB, 8, 1)
    FIELD(PARITY_ISR, PERR_IOU_GEM0_APB, 7, 1)
    FIELD(PARITY_ISR, PERR_I2C1_APB, 6, 1)
    FIELD(PARITY_ISR, PERR_I2C0_APB, 5, 1)
    FIELD(PARITY_ISR, PERR_GPIO_APB, 4, 1)
    FIELD(PARITY_ISR, PERR_GEM1_IOU, 3, 1)
    FIELD(PARITY_ISR, PERR_GEM0_IOU, 2, 1)
    FIELD(PARITY_ISR, PERR_CAN1_APB, 1, 1)
    FIELD(PARITY_ISR, PERR_CAN0_APB, 0, 1)
REG32(PARITY_IMR, 0x718)
    FIELD(PARITY_IMR, PERR_WWDT0_APB, 24, 1)
    FIELD(PARITY_IMR, PERR_USB_XS, 23, 1)
    FIELD(PARITY_IMR, PERR_USB_XM_IOU, 22, 1)
    FIELD(PARITY_IMR, PERR_USB_APB, 21, 1)
    FIELD(PARITY_IMR, PERR_UART1_APB, 20, 1)
    FIELD(PARITY_IMR, PERR_UART0_APB, 19, 1)
    FIELD(PARITY_IMR, PERR_TTC3_APB, 18, 1)
    FIELD(PARITY_IMR, PERR_TTC2_APB, 17, 1)
    FIELD(PARITY_IMR, PERR_TTC1_APB, 16, 1)
    FIELD(PARITY_IMR, PERR_TTC0_APB, 15, 1)
    FIELD(PARITY_IMR, PERR_SPI1_APB, 14, 1)
    FIELD(PARITY_IMR, PERR_IOU_SPI0_APB, 13, 1)
    FIELD(PARITY_IMR, PERR_SCNTR2_APB, 12, 1)
    FIELD(PARITY_IMR, PERR_SCNTR1_APB, 11, 1)
    FIELD(PARITY_IMR, PERR_IOUSLCR_SECURE_APB, 10, 1)
    FIELD(PARITY_IMR, PERR_IOUSLCR_APB, 9, 1)
    FIELD(PARITY_IMR, PERR_IOU_GEM1_APB, 8, 1)
    FIELD(PARITY_IMR, PERR_IOU_GEM0_APB, 7, 1)
    FIELD(PARITY_IMR, PERR_I2C1_APB, 6, 1)
    FIELD(PARITY_IMR, PERR_I2C0_APB, 5, 1)
    FIELD(PARITY_IMR, PERR_GPIO_APB, 4, 1)
    FIELD(PARITY_IMR, PERR_GEM1_IOU, 3, 1)
    FIELD(PARITY_IMR, PERR_GEM0_IOU, 2, 1)
    FIELD(PARITY_IMR, PERR_CAN1_APB, 1, 1)
    FIELD(PARITY_IMR, PERR_CAN0_APB, 0, 1)
REG32(PARITY_IER, 0x71c)
    FIELD(PARITY_IER, PERR_WWDT0_APB, 24, 1)
    FIELD(PARITY_IER, PERR_USB_XS, 23, 1)
    FIELD(PARITY_IER, PERR_USB_XM_IOU, 22, 1)
    FIELD(PARITY_IER, PERR_USB_APB, 21, 1)
    FIELD(PARITY_IER, PERR_UART1_APB, 20, 1)
    FIELD(PARITY_IER, PERR_UART0_APB, 19, 1)
    FIELD(PARITY_IER, PERR_TTC3_APB, 18, 1)
    FIELD(PARITY_IER, PERR_TTC2_APB, 17, 1)
    FIELD(PARITY_IER, PERR_TTC1_APB, 16, 1)
    FIELD(PARITY_IER, PERR_TTC0_APB, 15, 1)
    FIELD(PARITY_IER, PERR_SPI1_APB, 14, 1)
    FIELD(PARITY_IER, PERR_IOU_SPI0_APB, 13, 1)
    FIELD(PARITY_IER, PERR_SCNTR2_APB, 12, 1)
    FIELD(PARITY_IER, PERR_SCNTR1_APB, 11, 1)
    FIELD(PARITY_IER, PERR_IOUSLCR_SECURE_APB, 10, 1)
    FIELD(PARITY_IER, PERR_IOUSLCR_APB, 9, 1)
    FIELD(PARITY_IER, PERR_IOU_GEM1_APB, 8, 1)
    FIELD(PARITY_IER, PERR_IOU_GEM0_APB, 7, 1)
    FIELD(PARITY_IER, PERR_I2C1_APB, 6, 1)
    FIELD(PARITY_IER, PERR_I2C0_APB, 5, 1)
    FIELD(PARITY_IER, PERR_GPIO_APB, 4, 1)
    FIELD(PARITY_IER, PERR_GEM1_IOU, 3, 1)
    FIELD(PARITY_IER, PERR_GEM0_IOU, 2, 1)
    FIELD(PARITY_IER, PERR_CAN1_APB, 1, 1)
    FIELD(PARITY_IER, PERR_CAN0_APB, 0, 1)
REG32(PARITY_IDR, 0x720)
    FIELD(PARITY_IDR, PERR_WWDT0_APB, 24, 1)
    FIELD(PARITY_IDR, PERR_USB_XS, 23, 1)
    FIELD(PARITY_IDR, PERR_USB_XM_IOU, 22, 1)
    FIELD(PARITY_IDR, PERR_USB_APB, 21, 1)
    FIELD(PARITY_IDR, PERR_UART1_APB, 20, 1)
    FIELD(PARITY_IDR, PERR_UART0_APB, 19, 1)
    FIELD(PARITY_IDR, PERR_TTC3_APB, 18, 1)
    FIELD(PARITY_IDR, PERR_TTC2_APB, 17, 1)
    FIELD(PARITY_IDR, PERR_TTC1_APB, 16, 1)
    FIELD(PARITY_IDR, PERR_TTC0_APB, 15, 1)
    FIELD(PARITY_IDR, PERR_SPI1_APB, 14, 1)
    FIELD(PARITY_IDR, PERR_IOU_SPI0_APB, 13, 1)
    FIELD(PARITY_IDR, PERR_SCNTR2_APB, 12, 1)
    FIELD(PARITY_IDR, PERR_SCNTR1_APB, 11, 1)
    FIELD(PARITY_IDR, PERR_IOUSLCR_SECURE_APB, 10, 1)
    FIELD(PARITY_IDR, PERR_IOUSLCR_APB, 9, 1)
    FIELD(PARITY_IDR, PERR_IOU_GEM1_APB, 8, 1)
    FIELD(PARITY_IDR, PERR_IOU_GEM0_APB, 7, 1)
    FIELD(PARITY_IDR, PERR_I2C1_APB, 6, 1)
    FIELD(PARITY_IDR, PERR_I2C0_APB, 5, 1)
    FIELD(PARITY_IDR, PERR_GPIO_APB, 4, 1)
    FIELD(PARITY_IDR, PERR_GEM1_IOU, 3, 1)
    FIELD(PARITY_IDR, PERR_GEM0_IOU, 2, 1)
    FIELD(PARITY_IDR, PERR_CAN1_APB, 1, 1)
    FIELD(PARITY_IDR, PERR_CAN0_APB, 0, 1)
REG32(PARITY_ITR, 0x724)
    FIELD(PARITY_ITR, PERR_WWDT0_APB, 24, 1)
    FIELD(PARITY_ITR, PERR_USB_XS, 23, 1)
    FIELD(PARITY_ITR, PERR_USB_XM_IOU, 22, 1)
    FIELD(PARITY_ITR, PERR_USB_APB, 21, 1)
    FIELD(PARITY_ITR, PERR_UART1_APB, 20, 1)
    FIELD(PARITY_ITR, PERR_UART0_APB, 19, 1)
    FIELD(PARITY_ITR, PERR_TTC3_APB, 18, 1)
    FIELD(PARITY_ITR, PERR_TTC2_APB, 17, 1)
    FIELD(PARITY_ITR, PERR_TTC1_APB, 16, 1)
    FIELD(PARITY_ITR, PERR_TTC0_APB, 15, 1)
    FIELD(PARITY_ITR, PERR_SPI1_APB, 14, 1)
    FIELD(PARITY_ITR, PERR_IOU_SPI0_APB, 13, 1)
    FIELD(PARITY_ITR, PERR_SCNTR2_APB, 12, 1)
    FIELD(PARITY_ITR, PERR_SCNTR1_APB, 11, 1)
    FIELD(PARITY_ITR, PERR_IOUSLCR_SECURE_APB, 10, 1)
    FIELD(PARITY_ITR, PERR_IOUSLCR_APB, 9, 1)
    FIELD(PARITY_ITR, PERR_IOU_GEM1_APB, 8, 1)
    FIELD(PARITY_ITR, PERR_IOU_GEM0_APB, 7, 1)
    FIELD(PARITY_ITR, PERR_I2C1_APB, 6, 1)
    FIELD(PARITY_ITR, PERR_I2C0_APB, 5, 1)
    FIELD(PARITY_ITR, PERR_GPIO_APB, 4, 1)
    FIELD(PARITY_ITR, PERR_GEM1_IOU, 3, 1)
    FIELD(PARITY_ITR, PERR_GEM0_IOU, 2, 1)
    FIELD(PARITY_ITR, PERR_CAN1_APB, 1, 1)
    FIELD(PARITY_ITR, PERR_CAN0_APB, 0, 1)
REG32(WPROT0, 0x728)
    FIELD(WPROT0, ACTIVE, 0, 1)

G_STATIC_ASSERT(LPD_IOU_SLCR_R_MAX == R_WPROT0 + 1);

static void parity_imr_update_irq(LPD_IOU_SLCR *s)
{
    bool pending = s->regs[R_PARITY_ISR] & ~s->regs[R_PARITY_IMR];
    qemu_set_irq(s->irq_parity_imr, pending);
}

static void parity_isr_postw(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    parity_imr_update_irq(s);
}

static uint64_t parity_ier_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_PARITY_IMR] &= ~val;
    parity_imr_update_irq(s);
    return 0;
}

static uint64_t parity_idr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_PARITY_IMR] |= val;
    parity_imr_update_irq(s);
    return 0;
}

static uint64_t parity_itr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_PARITY_ISR] |= val;
    parity_imr_update_irq(s);
    return 0;
}

static void imr_update_irq(LPD_IOU_SLCR *s)
{
    bool pending = s->regs[R_ISR] & ~s->regs[R_IMR];
    qemu_set_irq(s->irq_imr, pending);
}

static void isr_postw(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    imr_update_irq(s);
}

static uint64_t ier_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] &= ~val;
    imr_update_irq(s);
    return 0;
}

static uint64_t idr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] |= val;
    imr_update_irq(s);
    return 0;
}

static uint64_t itr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_ISR] |= val;
    imr_update_irq(s);
    return 0;
}

static const RegisterAccessInfo lpd_iou_slcr_regs_info[] = {
    {   .name = "MIO_PIN_0",  .addr = A_MIO_PIN_0,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_1",  .addr = A_MIO_PIN_1,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_2",  .addr = A_MIO_PIN_2,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_3",  .addr = A_MIO_PIN_3,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_4",  .addr = A_MIO_PIN_4,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_5",  .addr = A_MIO_PIN_5,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_6",  .addr = A_MIO_PIN_6,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_7",  .addr = A_MIO_PIN_7,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_8",  .addr = A_MIO_PIN_8,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_9",  .addr = A_MIO_PIN_9,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_10",  .addr = A_MIO_PIN_10,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_11",  .addr = A_MIO_PIN_11,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_12",  .addr = A_MIO_PIN_12,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_13",  .addr = A_MIO_PIN_13,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_14",  .addr = A_MIO_PIN_14,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_15",  .addr = A_MIO_PIN_15,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_16",  .addr = A_MIO_PIN_16,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_17",  .addr = A_MIO_PIN_17,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_18",  .addr = A_MIO_PIN_18,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_19",  .addr = A_MIO_PIN_19,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_20",  .addr = A_MIO_PIN_20,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_21",  .addr = A_MIO_PIN_21,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_22",  .addr = A_MIO_PIN_22,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_23",  .addr = A_MIO_PIN_23,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_24",  .addr = A_MIO_PIN_24,
        .rsvd = 0xfffffc01,
    },{ .name = "MIO_PIN_25",  .addr = A_MIO_PIN_25,
        .rsvd = 0xfffffc01,
    },{ .name = "BNK2_EN_RX_SCHMITT_HYST",  .addr = A_BNK2_EN_RX_SCHMITT_HYST,
        .rsvd = 0xfc000000,
    },{ .name = "BNK2_EN_WK_PD",  .addr = A_BNK2_EN_WK_PD,
        .rsvd = 0xfc000000,
    },{ .name = "BNK2_EN_WK_PU",  .addr = A_BNK2_EN_WK_PU,
        .reset = 0x3ffffff,
        .rsvd = 0xfc000000,
    },{ .name = "BNK2_SEL_DRV0",  .addr = A_BNK2_SEL_DRV0,
        .reset = 0xaaaaaaaa,
    },{ .name = "BNK2_SEL_DRV1",  .addr = A_BNK2_SEL_DRV1,
        .reset = 0xaaaaa,
        .rsvd = 0xfff00000,
    },{ .name = "BNK2_SEL_SLEW",  .addr = A_BNK2_SEL_SLEW,
        .rsvd = 0xfc000000,
    },{ .name = "BNK2_VMODE",  .addr = A_BNK2_VMODE,
        .reset = 0x1,
        .rsvd = 0xfffffffe,
        .ro = 0x1,
    },{ .name = "BNK2_SEL_AUX_IO_RX",  .addr = A_BNK2_SEL_AUX_IO_RX,
        .rsvd = 0xfc000000,
    },{ .name = "MIO_LOOPBACK",  .addr = A_MIO_LOOPBACK,
        .rsvd = 0xfffffff0,
    },{ .name = "MIO_MST_TRI0",  .addr = A_MIO_MST_TRI0,
        .reset = 0x3ffffff,
        .rsvd = 0xfc000000,
    },{ .name = "WDT_CLK_SEL",  .addr = A_WDT_CLK_SEL,
        .rsvd = 0xfffffffe,
    },{ .name = "GEM_CLK_CTRL",  .addr = A_GEM_CLK_CTRL,
        .rsvd = 0xff8fff18,
    },{ .name = "GEM0_IOU_COHERENT_CTRL",  .addr = A_GEM0_IOU_COHERENT_CTRL,
        .rsvd = 0xfffffff0,
    },{ .name = "GEM0_IOU_INTERCONNECT_ROUTE",
        .addr = A_GEM0_IOU_INTERCONNECT_ROUTE,
        .rsvd = 0xfffffffe,
    },{ .name = "GEM0_IOU_INTERCONNECT_QOS",
        .addr = A_GEM0_IOU_INTERCONNECT_QOS,
        .rsvd = 0xfffffff0,
    },{ .name = "GEM1_IOU_COHERENT_CTRL",  .addr = A_GEM1_IOU_COHERENT_CTRL,
        .rsvd = 0xfffffff0,
    },{ .name = "GEM1_IOU_INTERCONNECT_ROUTE",
        .addr = A_GEM1_IOU_INTERCONNECT_ROUTE,
        .rsvd = 0xfffffffe,
    },{ .name = "GEM1_IOU_INTERCONNECT_QOS",
        .addr = A_GEM1_IOU_INTERCONNECT_QOS,
        .rsvd = 0xfffffff0,
    },{ .name = "IOU_TTC_APB_CLK",  .addr = A_IOU_TTC_APB_CLK,
        .rsvd = 0xffffff00,
    },{ .name = "LPD_MIO_SEL",  .addr = A_LPD_MIO_SEL,
        .reset = 0x3ffff,
        .rsvd = 0xfffc0000,
    },{ .name = "USB_IOU_INTERCONNECT_ROUTE",
        .addr = A_USB_IOU_INTERCONNECT_ROUTE,
        .rsvd = 0xfffffffe,
    },{ .name = "USB_IOU_INTERCONNECT_QOS",  .addr = A_USB_IOU_INTERCONNECT_QOS,
        .rsvd = 0xfffffff0,
    },{ .name = "SMID_FOR_USB",  .addr = A_SMID_FOR_USB,
        .rsvd = 0xfffffffe,
    },{ .name = "CTRL",  .addr = A_CTRL,
    },{ .name = "ISR",  .addr = A_ISR,
        .w1c = 0x1,
        .post_write = isr_postw,
    },{ .name = "IMR",  .addr = A_IMR,
        .reset = 0x1,
        .ro = 0x1,
    },{ .name = "IER",  .addr = A_IER,
        .pre_write = ier_prew,
    },{ .name = "IDR",  .addr = A_IDR,
        .pre_write = idr_prew,
    },{ .name = "ITR",  .addr = A_ITR,
        .pre_write = itr_prew,
    },{ .name = "PARITY_ISR",  .addr = A_PARITY_ISR,
        .w1c = 0x1ffffff,
        .post_write = parity_isr_postw,
    },{ .name = "PARITY_IMR",  .addr = A_PARITY_IMR,
        .reset = 0x1ffffff,
        .ro = 0x1ffffff,
    },{ .name = "PARITY_IER",  .addr = A_PARITY_IER,
        .pre_write = parity_ier_prew,
    },{ .name = "PARITY_IDR",  .addr = A_PARITY_IDR,
        .pre_write = parity_idr_prew,
    },{ .name = "PARITY_ITR",  .addr = A_PARITY_ITR,
        .pre_write = parity_itr_prew,
    },{ .name = "WPROT0",  .addr = A_WPROT0,
        .reset = 0x1,
    }
};

static void lpd_iou_slcr_reset(DeviceState *dev)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    parity_imr_update_irq(s);
    imr_update_irq(s);
}

static const MemoryRegionOps lpd_iou_slcr_ops = {
    .read = register_read_memory,
    .write = register_write_memory,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void lpd_iou_slcr_realize(DeviceState *dev, Error **errp)
{
    /* Delete this if you don't need it */
}

static void lpd_iou_slcr_init(Object *obj)
{
    LPD_IOU_SLCR *s = XILINX_LPD_IOU_SLCR(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    RegisterInfoArray *reg_array;

    memory_region_init(&s->iomem, obj, TYPE_XILINX_LPD_IOU_SLCR, LPD_IOU_SLCR_R_MAX * 4);
    reg_array =
        register_init_block32(DEVICE(obj), lpd_iou_slcr_regs_info,
                              ARRAY_SIZE(lpd_iou_slcr_regs_info),
                              s->regs_info, s->regs,
                              &lpd_iou_slcr_ops,
                              XILINX_LPD_IOU_SLCR_ERR_DEBUG,
                              LPD_IOU_SLCR_R_MAX * 4);
    memory_region_add_subregion(&s->iomem,
                                0x0,
                                &reg_array->mem);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_parity_imr);
    sysbus_init_irq(sbd, &s->irq_imr);
}

static const VMStateDescription vmstate_lpd_iou_slcr = {
    .name = TYPE_XILINX_LPD_IOU_SLCR,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, LPD_IOU_SLCR, LPD_IOU_SLCR_R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static void lpd_iou_slcr_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = lpd_iou_slcr_reset;
    dc->realize = lpd_iou_slcr_realize;
    dc->vmsd = &vmstate_lpd_iou_slcr;
}

static const TypeInfo lpd_iou_slcr_info = {
    .name          = TYPE_XILINX_LPD_IOU_SLCR,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(LPD_IOU_SLCR),
    .class_init    = lpd_iou_slcr_class_init,
    .instance_init = lpd_iou_slcr_init,
};

static void lpd_iou_slcr_register_types(void)
{
    type_register_static(&lpd_iou_slcr_info);
}

type_init(lpd_iou_slcr_register_types)
