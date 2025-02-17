/*
 * QEMU model of the INTLPD_CONFIG LPD Interconnect isolation, reset and
 * status registers
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
 * Copyright (c) 2023, Advanced Micro Devices, Inc.
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
#include "hw/qdev-properties.h"
#include "hw/misc/xlnx-versal-intlpd-config.h"

#ifndef XILINX_INTLPD_CONFIG_ERR_DEBUG
#define XILINX_INTLPD_CONFIG_ERR_DEBUG 0
#endif

REG32(IR_STATUS, 0x0)
    FIELD(IR_STATUS, IF_INTLPD_OCM2_AXI_T_MAINTIMEOUT, 31, 1)
    FIELD(IR_STATUS, IF_INTLPD_HSDP_APB_T_MAINTIMEOUT, 30, 1)
    FIELD(IR_STATUS, LPD_IPI_APB_T_MAINTIMEOUT, 23, 1)
    FIELD(IR_STATUS, IF_INTLPD_RPU1_AXI_T_MAINTIMEOUT, 22, 1)
    FIELD(IR_STATUS, IF_INTLPD_INTIOU_AXI_T_MAINTIMEOUT, 17, 1)
    FIELD(IR_STATUS, IF_PS_PMC_RPU_AXI0_T_MAINTIMEOUT, 16, 1)
    FIELD(IR_STATUS, IF_PS_PMC_PCIE_AXI0_T_MAINTIMEOUT, 15, 1)
    FIELD(IR_STATUS, IF_PS_PMC_AXI0_T_MAINTIMEOUT, 14, 1)
    FIELD(IR_STATUS, IF_PS_CPM_PCIE_AXI_T_MAINTIMEOUT, 13, 1)
    FIELD(IR_STATUS, IF_PS_CPM_CFG_AXI_T_MAINTIMEOUT, 12, 1)
    FIELD(IR_STATUS, IF_INTLPD_SYSMONSAT_APB_T_MAINTIMEOUT, 11, 1)
    FIELD(IR_STATUS, IF_INTLPD_RPU0_AXI_T_MAINTIMEOUT, 10, 1)
    FIELD(IR_STATUS, IF_INTLPD_OCM_AXI_T_MAINTIMEOUT, 9, 1)
    FIELD(IR_STATUS, IF_INTLPD_INTFPD_PCIE_AXI_T_MAINTIMEOUT, 8, 1)
    FIELD(IR_STATUS, IF_INTLPD_INTFPD_AXI_T_MAINTIMEOUT, 7, 1)
    FIELD(IR_STATUS, IF_INTLPD_CPMPCSR_APB_T_MAINTIMEOUT, 6, 1)
    FIELD(IR_STATUS, IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT, 5, 1)
    FIELD(IR_STATUS, LPD_SLCR_CRL_APB_T_MAINTIMEOUT, 4, 1)
    FIELD(IR_STATUS, LPD_OCM_RPU_APB_T_MAINTIMEOUT, 3, 1)
    FIELD(IR_STATUS, LPD_AFIFM_ADMA_APB_T_MAINTIMEOUT, 1, 1)
    FIELD(IR_STATUS, ADDR_DECODE_ERR, 0, 1)
REG32(IR_MASK, 0x4)
    FIELD(IR_MASK, IF_INTLPD_OCM2_AXI_T_MAINTIMEOUT, 31, 1)
    FIELD(IR_MASK, IF_INTLPD_HSDP_APB_T_MAINTIMEOUT, 30, 1)
    FIELD(IR_MASK, LPD_IPI_APB_T_MAINTIMEOUT, 23, 1)
    FIELD(IR_MASK, IF_INTLPD_RPU1_AXI_T_MAINTIMEOUT, 22, 1)
    FIELD(IR_MASK, IF_INTLPD_INTIOU_AXI_T_MAINTIMEOUT, 17, 1)
    FIELD(IR_MASK, IF_PS_PMC_RPU_AXI0_T_MAINTIMEOUT, 16, 1)
    FIELD(IR_MASK, IF_PS_PMC_PCIE_AXI0_T_MAINTIMEOUT, 15, 1)
    FIELD(IR_MASK, IF_PS_PMC_AXI0_T_MAINTIMEOUT, 14, 1)
    FIELD(IR_MASK, IF_PS_CPM_PCIE_AXI_T_MAINTIMEOUT, 13, 1)
    FIELD(IR_MASK, IF_PS_CPM_CFG_AXI_T_MAINTIMEOUT, 12, 1)
    FIELD(IR_MASK, IF_INTLPD_SYSMONSAT_APB_T_MAINTIMEOUT, 11, 1)
    FIELD(IR_MASK, IF_INTLPD_RPU0_AXI_T_MAINTIMEOUT, 10, 1)
    FIELD(IR_MASK, IF_INTLPD_OCM_AXI_T_MAINTIMEOUT, 9, 1)
    FIELD(IR_MASK, IF_INTLPD_INTFPD_PCIE_AXI_T_MAINTIMEOUT, 8, 1)
    FIELD(IR_MASK, IF_INTLPD_INTFPD_AXI_T_MAINTIMEOUT, 7, 1)
    FIELD(IR_MASK, IF_INTLPD_CPMPCSR_APB_T_MAINTIMEOUT, 6, 1)
    FIELD(IR_MASK, IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT, 5, 1)
    FIELD(IR_MASK, LPD_SLCR_CRL_APB_T_MAINTIMEOUT, 4, 1)
    FIELD(IR_MASK, LPD_OCM_RPU_APB_T_MAINTIMEOUT, 3, 1)
    FIELD(IR_MASK, LPD_AFIFM_ADMA_APB_T_MAINTIMEOUT, 1, 1)
    FIELD(IR_MASK, ADDR_DECODE_ERR, 0, 1)
REG32(IR_ENABLE, 0x8)
    FIELD(IR_ENABLE, IF_INTLPD_OCM2_AXI_T_MAINTIMEOUT, 31, 1)
    FIELD(IR_ENABLE, IF_INTLPD_HSDP_APB_T_MAINTIMEOUT, 30, 1)
    FIELD(IR_ENABLE, LPD_IPI_APB_T_MAINTIMEOUT, 23, 1)
    FIELD(IR_ENABLE, IF_INTLPD_RPU1_AXI_T_MAINTIMEOUT, 22, 1)
    FIELD(IR_ENABLE, IF_INTLPD_INTIOU_AXI_T_MAINTIMEOUT, 17, 1)
    FIELD(IR_ENABLE, IF_PS_PMC_RPU_AXI0_T_MAINTIMEOUT, 16, 1)
    FIELD(IR_ENABLE, IF_PS_PMC_PCIE_AXI0_T_MAINTIMEOUT, 15, 1)
    FIELD(IR_ENABLE, IF_PS_PMC_AXI0_T_MAINTIMEOUT, 14, 1)
    FIELD(IR_ENABLE, IF_PS_CPM_PCIE_AXI_T_MAINTIMEOUT, 13, 1)
    FIELD(IR_ENABLE, IF_PS_CPM_CFG_AXI_T_MAINTIMEOUT, 12, 1)
    FIELD(IR_ENABLE, IF_INTLPD_SYSMONSAT_APB_T_MAINTIMEOUT, 11, 1)
    FIELD(IR_ENABLE, IF_INTLPD_RPU_AXI_T_MAINTIMEOUT, 10, 1)
    FIELD(IR_ENABLE, IF_INTLPD_OCM_AXI_T_MAINTIMEOUT, 9, 1)
    FIELD(IR_ENABLE, IF_INTLPD_INTFPD_PCIE_AXI_T_MAINTIMEOUT, 8, 1)
    FIELD(IR_ENABLE, IF_INTLPD_INTFPD_AXI_T_MAINTIMEOUT, 7, 1)
    FIELD(IR_ENABLE, IF_INTLPD_CPMPCSR_APB_T_MAINTIMEOUT, 6, 1)
    FIELD(IR_ENABLE, IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT, 5, 1)
    FIELD(IR_ENABLE, LPD_SLCR_CRL_APB_T_MAINTIMEOUT, 4, 1)
    FIELD(IR_ENABLE, LPD_IPI_OCM_RPU_APB_T_MAINTIMEOUT, 3, 1)
    FIELD(IR_ENABLE, LPD_AFIFM_ADMA_APB_T_MAINTIMEOUT, 1, 1)
    FIELD(IR_ENABLE, ADDR_DECODE_ERR, 0, 1)
REG32(IR_DISABLE, 0xc)
    FIELD(IR_DISABLE, IF_INTLPD_OCM2_AXI_T_MAINTIMEOUT, 31, 1)
    FIELD(IR_DISABLE, IF_INTLPD_HSDP_APB_T_MAINTIMEOUT, 30, 1)
    FIELD(IR_DISABLE, LPD_IPI_APB_T_MAINTIMEOUT, 23, 1)
    FIELD(IR_DISABLE, IF_INTLPD_RPU1_AXI_T_MAINTIMEOUT, 22, 1)
    FIELD(IR_DISABLE, IF_INTLPD_INTIOU_AXI_T_MAINTIMEOUT, 17, 1)
    FIELD(IR_DISABLE, IF_PS_PMC_RPU_AXI0_T_MAINTIMEOUT, 16, 1)
    FIELD(IR_DISABLE, IF_PS_PMC_PCIE_AXI0_T_MAINTIMEOUT, 15, 1)
    FIELD(IR_DISABLE, IF_PS_PMC_AXI0_T_MAINTIMEOUT, 14, 1)
    FIELD(IR_DISABLE, IF_PS_CPM_PCIE_AXI_T_MAINTIMEOUT, 13, 1)
    FIELD(IR_DISABLE, IF_PS_CPM_CFG_AXI_T_MAINTIMEOUT, 12, 1)
    FIELD(IR_DISABLE, IF_INTLPD_SYSMONSAT_APB_T_MAINTIMEOUT, 11, 1)
    FIELD(IR_DISABLE, IF_INTLPD_RPU_AXI_T_MAINTIMEOUT, 10, 1)
    FIELD(IR_DISABLE, IF_INTLPD_OCM_AXI_T_MAINTIMEOUT, 9, 1)
    FIELD(IR_DISABLE, IF_INTLPD_INTFPD_PCIE_AXI_T_MAINTIMEOUT, 8, 1)
    FIELD(IR_DISABLE, IF_INTLPD_INTFPD_AXI_T_MAINTIMEOUT, 7, 1)
    FIELD(IR_DISABLE, IF_INTLPD_CPMPCSR_APB_T_MAINTIMEOUT, 6, 1)
    FIELD(IR_DISABLE, IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT, 5, 1)
    FIELD(IR_DISABLE, LPD_SLCR_CRL_APB_T_MAINTIMEOUT, 4, 1)
    FIELD(IR_DISABLE, LPD_IPI_OCM_RPU_APB_T_MAINTIMEOUT, 3, 1)
    FIELD(IR_DISABLE, LPD_AFIFM_ADMA_APB_T_MAINTIMEOUT, 1, 1)
    FIELD(IR_DISABLE, ADDR_DECODE_ERR, 0, 1)
REG32(ADMA, 0x14)
    FIELD(ADMA, ROUTING, 0, 1)
REG32(AFIFMLPD, 0x18)
    FIELD(AFIFMLPD, ROUTING, 0, 1)
REG32(RPU0, 0x1c)
    FIELD(RPU0, ROUTING, 0, 1)
REG32(RPU1, 0x20)
    FIELD(RPU1, ROUTING, 0, 1)
REG32(RPU0_QOS, 0x50)
    FIELD(RPU0_QOS, ARQOS, 4, 4)
    FIELD(RPU0_QOS, AWQOS, 0, 4)
REG32(RPU1_QOS, 0x54)
    FIELD(RPU1_QOS, ARQOS, 4, 4)
    FIELD(RPU1_QOS, AWQOS, 0, 4)
REG32(HSDP_DMA_QOS, 0x58)
    FIELD(HSDP_DMA_QOS, ARQOS, 4, 4)
    FIELD(HSDP_DMA_QOS, AWQOS, 0, 4)
REG32(IR_STATUS_PERR, 0x60)
    FIELD(IR_STATUS_PERR, RPU1_INTLPD_AXI, 24, 1)
    FIELD(IR_STATUS_PERR, RPU0_INTLPD_AXI, 23, 1)
    FIELD(IR_STATUS_PERR, INTLPD_XMPU_APB, 22, 1)
    FIELD(IR_STATUS_PERR, INTLPD_XPPU_APB, 21, 1)
    FIELD(IR_STATUS_PERR, INTLPD_SYSMONSAT_APB, 20, 1)
    FIELD(IR_STATUS_PERR, INTLPD_RPU_APB, 19, 1)
    FIELD(IR_STATUS_PERR, PS_OCM2_APB, 18, 1)
    FIELD(IR_STATUS_PERR, INTLPD_OCMCNTRL_APB, 17, 1)
    FIELD(IR_STATUS_PERR, INTLPD_LPDSLCRSECURE_APB, 16, 1)
    FIELD(IR_STATUS_PERR, INTLPD_LPDSLCR_APB, 15, 1)
    FIELD(IR_STATUS_PERR, INTLPD_IPI_APB, 14, 1)
    FIELD(IR_STATUS_PERR, INTLPD_HSDP_APB, 13, 1)
    FIELD(IR_STATUS_PERR, INTLPD_CRL_APB, 12, 1)
    FIELD(IR_STATUS_PERR, INTLPD_CPMPCSR_APB, 11, 1)
    FIELD(IR_STATUS_PERR, INTLPD_CONFIG_APB, 10, 1)
    FIELD(IR_STATUS_PERR, INTLPD_AURORA_APB, 9, 1)
    FIELD(IR_STATUS_PERR, INTLPD_AFIFMLPD_APB, 8, 1)
    FIELD(IR_STATUS_PERR, INTLPD_ADMA_APB, 7, 1)
    FIELD(IR_STATUS_PERR, HSDP_INTLPD_AXI, 6, 1)
    FIELD(IR_STATUS_PERR, INTLPD_RPU1_AXI, 5, 1)
    FIELD(IR_STATUS_PERR, INTLPD_RPU0_AXI, 4, 1)
    FIELD(IR_STATUS_PERR, INTLPD_OCM_AXI, 3, 1)
    FIELD(IR_STATUS_PERR, INTLPD_AFIFSLPD_AXI, 2, 1)
    FIELD(IR_STATUS_PERR, AFIFMLPD_INTLPD_AXI, 1, 1)
    FIELD(IR_STATUS_PERR, ADMA_INTLPD_AXI, 0, 1)
REG32(IR_MASK_PERR, 0x64)
    FIELD(IR_MASK_PERR, RPU1_INTLPD_AXI, 24, 1)
    FIELD(IR_MASK_PERR, RPU0_INTLPD_AXI, 23, 1)
    FIELD(IR_MASK_PERR, INTLPD_XMPU_APB, 22, 1)
    FIELD(IR_MASK_PERR, INTLPD_XPPU_APB, 21, 1)
    FIELD(IR_MASK_PERR, INTLPD_SYSMONSAT_APB, 20, 1)
    FIELD(IR_MASK_PERR, INTLPD_RPU_APB, 19, 1)
    FIELD(IR_MASK_PERR, PS_OCM2_APB, 18, 1)
    FIELD(IR_MASK_PERR, INTLPD_OCMCNTRL_APB, 17, 1)
    FIELD(IR_MASK_PERR, INTLPD_LPDSLCRSECURE_APB, 16, 1)
    FIELD(IR_MASK_PERR, INTLPD_LPDSLCR_APB, 15, 1)
    FIELD(IR_MASK_PERR, INTLPD_IPI_APB, 14, 1)
    FIELD(IR_MASK_PERR, INTLPD_HSDP_APB, 13, 1)
    FIELD(IR_MASK_PERR, INTLPD_CRL_APB, 12, 1)
    FIELD(IR_MASK_PERR, INTLPD_CPMPCSR_APB, 11, 1)
    FIELD(IR_MASK_PERR, INTLPD_CONFIG_APB, 10, 1)
    FIELD(IR_MASK_PERR, INTLPD_AURORA_APB, 9, 1)
    FIELD(IR_MASK_PERR, INTLPD_AFIFMLPD_APB, 8, 1)
    FIELD(IR_MASK_PERR, INTLPD_ADMA_APB, 7, 1)
    FIELD(IR_MASK_PERR, HSDP_INTLPD_AXI, 6, 1)
    FIELD(IR_MASK_PERR, INTLPD_RPU1_AXI, 5, 1)
    FIELD(IR_MASK_PERR, INTLPD_RPU0_AXI, 4, 1)
    FIELD(IR_MASK_PERR, INTLPD_OCM_AXI, 3, 1)
    FIELD(IR_MASK_PERR, INTLPD_AFIFSLPD_AXI, 2, 1)
    FIELD(IR_MASK_PERR, AFIFMLPD_INTLPD_AXI, 1, 1)
    FIELD(IR_MASK_PERR, ADMA_INTLPD_AXI, 0, 1)
REG32(IR_ENABLE_PERR, 0x68)
    FIELD(IR_ENABLE_PERR, RPU1_INTLPD_AXI, 24, 1)
    FIELD(IR_ENABLE_PERR, RPU0_INTLPD_AXI, 23, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_XMPU_APB, 22, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_XPPU_APB, 21, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_SYSMONSAT_APB, 20, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_RPU_APB, 19, 1)
    FIELD(IR_ENABLE_PERR, PS_OCM2_APB, 18, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_OCMCNTRL_APB, 17, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_LPDSLCRSECURE_APB, 16, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_LPDSLCR_APB, 15, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_IPI_APB, 14, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_HSDP_APB, 13, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_CRL_APB, 12, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_CPMPCSR_APB, 11, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_CONFIG_APB, 10, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_AURORA_APB, 9, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_AFIFMLPD_APB, 8, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_ADMA_APB, 7, 1)
    FIELD(IR_ENABLE_PERR, HSDP_INTLPD_AXI, 6, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_RPU1_AXI, 5, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_RPU0_AXI, 4, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_OCM_AXI, 3, 1)
    FIELD(IR_ENABLE_PERR, INTLPD_AFIFSLPD_AXI, 2, 1)
    FIELD(IR_ENABLE_PERR, AFIFMLPD_INTLPD_AXI, 1, 1)
    FIELD(IR_ENABLE_PERR, ADMA_INTLPD_AXI, 0, 1)
REG32(IR_DISABLE_PERR, 0x6c)
    FIELD(IR_DISABLE_PERR, RPU1_INTLPD_AXI, 24, 1)
    FIELD(IR_DISABLE_PERR, RPU0_INTLPD_AXI, 23, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_XMPU_APB, 22, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_XPPU_APB, 21, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_SYSMONSAT_APB, 20, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_RPU_APB, 19, 1)
    FIELD(IR_DISABLE_PERR, PS_OCM2_APB, 18, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_OCMCNTRL_APB, 17, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_LPDSLCRSECURE_APB, 16, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_LPDSLCR_APB, 15, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_IPI_APB, 14, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_HSDP_APB, 13, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_CRL_APB, 12, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_CPMPCSR_APB, 11, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_CONFIG_APB, 10, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_AURORA_APB, 9, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_AFIFMLPD_APB, 8, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_ADMA_APB, 7, 1)
    FIELD(IR_DISABLE_PERR, HSDP_INTLPD_AXI, 6, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_RPU1_AXI, 5, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_RPU0_AXI, 4, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_OCM_AXI, 3, 1)
    FIELD(IR_DISABLE_PERR, INTLPD_AFIFSLPD_AXI, 2, 1)
    FIELD(IR_DISABLE_PERR, AFIFMLPD_INTLPD_AXI, 1, 1)
    FIELD(IR_DISABLE_PERR, ADMA_INTLPD_AXI, 0, 1)
REG32(IR_STATUS_MISSION1, 0x80)
    FIELD(IR_STATUS_MISSION1, LPD_SLCR_CRL_APB, 4, 1)
    FIELD(IR_STATUS_MISSION1, LPD, 3, 1)
    FIELD(IR_STATUS_MISSION1, LPD_OCM_RPU_APB, 2, 1)
    FIELD(IR_STATUS_MISSION1, LPD_IPI_APB, 1, 1)
    FIELD(IR_STATUS_MISSION1, LPD_AFIFM_ADMA_APB, 0, 1)
REG32(IR_MASK_MISSION1, 0x84)
    FIELD(IR_MASK_MISSION1, LPD_SLCR_CRL_APB, 4, 1)
    FIELD(IR_MASK_MISSION1, LPD, 3, 1)
    FIELD(IR_MASK_MISSION1, LPD_OCM_RPU_APB, 2, 1)
    FIELD(IR_MASK_MISSION1, LPD_IPI_APB, 1, 1)
    FIELD(IR_MASK_MISSION1, LPD_AFIFM_ADMA_APB, 0, 1)
REG32(IR_ENABLE_MISSION1, 0x88)
    FIELD(IR_ENABLE_MISSION1, LPD_SLCR_CRL_APB, 4, 1)
    FIELD(IR_ENABLE_MISSION1, LPD, 3, 1)
    FIELD(IR_ENABLE_MISSION1, LPD_OCM_RPU_APB, 2, 1)
    FIELD(IR_ENABLE_MISSION1, LPD_IPI_APB, 1, 1)
    FIELD(IR_ENABLE_MISSION1, LPD_AFIFM_ADMA_APB, 0, 1)
REG32(IR_DISABLE_MISSION1, 0x8c)
    FIELD(IR_DISABLE_MISSION1, LPD_SLCR_CRL_APB, 4, 1)
    FIELD(IR_DISABLE_MISSION1, LPD, 3, 1)
    FIELD(IR_DISABLE_MISSION1, LPD_OCM_RPU_APB, 2, 1)
    FIELD(IR_DISABLE_MISSION1, LPD_IPI_APB, 1, 1)
    FIELD(IR_DISABLE_MISSION1, LPD_AFIFM_ADMA_APB, 0, 1)
REG32(IR_STATUS_MISSION2, 0xa0)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_INTIOU_AXI, 28, 1)
    FIELD(IR_STATUS_MISSION2, RPU1_LPD_AXI, 27, 1)
    FIELD(IR_STATUS_MISSION2, RPU0_LPD_AXI, 26, 1)
    FIELD(IR_STATUS_MISSION2, PSM_LPD_AXI, 25, 1)
    FIELD(IR_STATUS_MISSION2, PMC_PS_PCIE_AXI, 24, 1)
    FIELD(IR_STATUS_MISSION2, PMC_PS_AXI0, 23, 1)
    FIELD(IR_STATUS_MISSION2, LPD_HSDP_APB, 22, 1)
    FIELD(IR_STATUS_MISSION2, IOU_LPD_AXI, 21, 1)
    FIELD(IR_STATUS_MISSION2, IF_PS_PMC_RPU_AXI0, 20, 1)
    FIELD(IR_STATUS_MISSION2, IF_PS_PMC_PCIE_AXI0, 19, 1)
    FIELD(IR_STATUS_MISSION2, IF_PS_PMC_AXI0, 18, 1)
    FIELD(IR_STATUS_MISSION2, IF_PS_CPM_PCIE_AXI, 17, 1)
    FIELD(IR_STATUS_MISSION2, IF_PS_CPM_CFG_AXI, 16, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_SYSMONSAT_APB, 15, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_RPU1_AXI, 14, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_RPU0_AXI, 13, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_OCMEXT_AXI, 12, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_OCM_AXI, 11, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_INTFPD_PCIE_AXI, 10, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_INTFPD_AXI, 9, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_CPMPCSR_APB, 8, 1)
    FIELD(IR_STATUS_MISSION2, IF_INTLPD_AFIFSLPD_AXI, 7, 1)
    FIELD(IR_STATUS_MISSION2, HSDP_LPD_AXI, 6, 1)
    FIELD(IR_STATUS_MISSION2, FPD_LPD_PCIE_AXI, 5, 1)
    FIELD(IR_STATUS_MISSION2, FPD_LPD_OCM_AXI, 4, 1)
    FIELD(IR_STATUS_MISSION2, FPD_LPD_AXI, 3, 1)
    FIELD(IR_STATUS_MISSION2, CPM_PS_AXI0, 2, 1)
    FIELD(IR_STATUS_MISSION2, AFIFM_LPD_AXI, 1, 1)
    FIELD(IR_STATUS_MISSION2, ADMA_LPD_AXI, 0, 1)
REG32(IR_MASK_MISSION2, 0xa4)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_INTIOU_AXI, 28, 1)
    FIELD(IR_MASK_MISSION2, RPU1_LPD_AXI, 27, 1)
    FIELD(IR_MASK_MISSION2, RPU0_LPD_AXI, 26, 1)
    FIELD(IR_MASK_MISSION2, PSM_LPD_AXI, 25, 1)
    FIELD(IR_MASK_MISSION2, PMC_PS_PCIE_AXI, 24, 1)
    FIELD(IR_MASK_MISSION2, PMC_PS_AXI0, 23, 1)
    FIELD(IR_MASK_MISSION2, LPD_HSDP_APB, 22, 1)
    FIELD(IR_MASK_MISSION2, IOU_LPD_AXI, 21, 1)
    FIELD(IR_MASK_MISSION2, IF_PS_PMC_RPU_AXI0, 20, 1)
    FIELD(IR_MASK_MISSION2, IF_PS_PMC_PCIE_AXI0, 19, 1)
    FIELD(IR_MASK_MISSION2, IF_PS_PMC_AXI0, 18, 1)
    FIELD(IR_MASK_MISSION2, IF_PS_CPM_PCIE_AXI, 17, 1)
    FIELD(IR_MASK_MISSION2, IF_PS_CPM_CFG_AXI, 16, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_SYSMONSAT_APB, 15, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_RPU1_AXI, 14, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_RPU0_AXI, 13, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_OCMEXT_AXI, 12, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_OCM_AXI, 11, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_INTFPD_PCIE_AXI, 10, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_INTFPD_AXI, 9, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_CPMPCSR_APB, 8, 1)
    FIELD(IR_MASK_MISSION2, IF_INTLPD_AFIFSLPD_AXI, 7, 1)
    FIELD(IR_MASK_MISSION2, HSDP_LPD_AXI, 6, 1)
    FIELD(IR_MASK_MISSION2, FPD_LPD_PCIE_AXI, 5, 1)
    FIELD(IR_MASK_MISSION2, FPD_LPD_OCM_AXI, 4, 1)
    FIELD(IR_MASK_MISSION2, FPD_LPD_AXI, 3, 1)
    FIELD(IR_MASK_MISSION2, CPM_PS_AXI0, 2, 1)
    FIELD(IR_MASK_MISSION2, AFIFM_LPD_AXI, 1, 1)
    FIELD(IR_MASK_MISSION2, ADMA_LPD_AXI, 0, 1)
REG32(IR_ENABLE_MISSION2, 0xa8)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_INTIOU_AXI, 28, 1)
    FIELD(IR_ENABLE_MISSION2, RPU1_LPD_AXI, 27, 1)
    FIELD(IR_ENABLE_MISSION2, RPU0_LPD_AXI, 26, 1)
    FIELD(IR_ENABLE_MISSION2, PSM_LPD_AXI, 25, 1)
    FIELD(IR_ENABLE_MISSION2, PMC_PS_PCIE_AXI, 24, 1)
    FIELD(IR_ENABLE_MISSION2, PMC_PS_AXI0, 23, 1)
    FIELD(IR_ENABLE_MISSION2, LPD_HSDP_APB, 22, 1)
    FIELD(IR_ENABLE_MISSION2, IOU_LPD_AXI, 21, 1)
    FIELD(IR_ENABLE_MISSION2, IF_PS_PMC_RPU_AXI0, 20, 1)
    FIELD(IR_ENABLE_MISSION2, IF_PS_PMC_PCIE_AXI0, 19, 1)
    FIELD(IR_ENABLE_MISSION2, IF_PS_PMC_AXI0, 18, 1)
    FIELD(IR_ENABLE_MISSION2, IF_PS_CPM_PCIE_AXI, 17, 1)
    FIELD(IR_ENABLE_MISSION2, IF_PS_CPM_CFG_AXI, 16, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_SYSMONSAT_APB, 15, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_RPU1_AXI, 14, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_RPU0_AXI, 13, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_OCMEXT_AXI, 12, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_OCM_AXI, 11, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_INTFPD_PCIE_AXI, 10, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_INTFPD_AXI, 9, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_CPMPCSR_APB, 8, 1)
    FIELD(IR_ENABLE_MISSION2, IF_INTLPD_AFIFSLPD_AXI, 7, 1)
    FIELD(IR_ENABLE_MISSION2, HSDP_LPD_AXI, 6, 1)
    FIELD(IR_ENABLE_MISSION2, FPD_LPD_PCIE_AXI, 5, 1)
    FIELD(IR_ENABLE_MISSION2, FPD_LPD_OCM_AXI, 4, 1)
    FIELD(IR_ENABLE_MISSION2, FPD_LPD_AXI, 3, 1)
    FIELD(IR_ENABLE_MISSION2, CPM_PS_AXI0, 2, 1)
    FIELD(IR_ENABLE_MISSION2, AFIFM_LPD_AXI, 1, 1)
    FIELD(IR_ENABLE_MISSION2, ADMA_LPD_AXI, 0, 1)
REG32(IR_DISABLE_MISSION2, 0xac)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_INTIOU_AXI, 28, 1)
    FIELD(IR_DISABLE_MISSION2, RPU1_LPD_AXI, 27, 1)
    FIELD(IR_DISABLE_MISSION2, RPU0_LPD_AXI, 26, 1)
    FIELD(IR_DISABLE_MISSION2, PSM_LPD_AXI, 25, 1)
    FIELD(IR_DISABLE_MISSION2, PMC_PS_PCIE_AXI, 24, 1)
    FIELD(IR_DISABLE_MISSION2, PMC_PS_AXI0, 23, 1)
    FIELD(IR_DISABLE_MISSION2, LPD_HSDP_APB, 22, 1)
    FIELD(IR_DISABLE_MISSION2, IOU_LPD_AXI, 21, 1)
    FIELD(IR_DISABLE_MISSION2, IF_PS_PMC_RPU_AXI0, 20, 1)
    FIELD(IR_DISABLE_MISSION2, IF_PS_PMC_PCIE_AXI0, 19, 1)
    FIELD(IR_DISABLE_MISSION2, IF_PS_PMC_AXI0, 18, 1)
    FIELD(IR_DISABLE_MISSION2, IF_PS_CPM_PCIE_AXI, 17, 1)
    FIELD(IR_DISABLE_MISSION2, IF_PS_CPM_CFG_AXI, 16, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_SYSMONSAT_APB, 15, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_RPU1_AXI, 14, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_RPU0_AXI, 13, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_OCMEXT_AXI, 12, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_OCM_AXI, 11, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_INTFPD_PCIE_AXI, 10, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_INTFPD_AXI, 9, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_CPMPCSR_APB, 8, 1)
    FIELD(IR_DISABLE_MISSION2, IF_INTLPD_AFIFSLPD_AXI, 7, 1)
    FIELD(IR_DISABLE_MISSION2, HSDP_LPD_AXI, 6, 1)
    FIELD(IR_DISABLE_MISSION2, FPD_LPD_PCIE_AXI, 5, 1)
    FIELD(IR_DISABLE_MISSION2, FPD_LPD_OCM_AXI, 4, 1)
    FIELD(IR_DISABLE_MISSION2, FPD_LPD_AXI, 3, 1)
    FIELD(IR_DISABLE_MISSION2, CPM_PS_AXI0, 2, 1)
    FIELD(IR_DISABLE_MISSION2, AFIFM_LPD_AXI, 1, 1)
    FIELD(IR_DISABLE_MISSION2, ADMA_LPD_AXI, 0, 1)
/*
REG32(LPD_AFIFM_ADMA_APB, 0x10000)
    FIELD(LPD_AFIFM_ADMA_APB, RAW_RST_N, 4, 1)
    FIELD(LPD_AFIFM_ADMA_APB, POWER_IDLEREQ, 3, 1)
    FIELD(LPD_AFIFM_ADMA_APB, POWER_IDLEACK, 2, 1)
    FIELD(LPD_AFIFM_ADMA_APB, POWER_IDLE, 1, 1)
    FIELD(LPD_AFIFM_ADMA_APB, MAINEXTEN, 0, 1)
REG32(LPD_OCM_RPU_APB, 0x20000)
    FIELD(LPD_OCM_RPU_APB, RAW_RST_N, 4, 1)
    FIELD(LPD_OCM_RPU_APB, POWER_IDLEREQ, 3, 1)
    FIELD(LPD_OCM_RPU_APB, POWER_IDLEACK, 2, 1)
    FIELD(LPD_OCM_RPU_APB, POWER_IDLE, 1, 1)
    FIELD(LPD_OCM_RPU_APB, MAINEXTEN, 0, 1)
REG32(LPD_SLCR_CRL_APB, 0x30000)
    FIELD(LPD_SLCR_CRL_APB, RAW_RST_N, 4, 1)
    FIELD(LPD_SLCR_CRL_APB, POWER_IDLEREQ, 3, 1)
    FIELD(LPD_SLCR_CRL_APB, POWER_IDLEACK, 2, 1)
    FIELD(LPD_SLCR_CRL_APB, POWER_IDLE, 1, 1)
    FIELD(LPD_SLCR_CRL_APB, MAINEXTEN, 0, 1)
REG32(INTLPD_AFIFSLPD_AXI, 0x40000)
    FIELD(INTLPD_AFIFSLPD_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_AFIFSLPD_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_AFIFSLPD_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_AFIFSLPD_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_AFIFSLPD_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_CPMPCSR_APB, 0x50000)
    FIELD(INTLPD_CPMPCSR_APB, RAW_RST_N, 4, 1)
    FIELD(INTLPD_CPMPCSR_APB, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_CPMPCSR_APB, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_CPMPCSR_APB, POWER_IDLE, 1, 1)
    FIELD(INTLPD_CPMPCSR_APB, MAINEXTEN, 0, 1)
REG32(INTLPD_INTFPD_AXI, 0x60000)
    FIELD(INTLPD_INTFPD_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_INTFPD_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_INTFPD_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_INTFPD_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_INTFPD_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_INTFPD_PCIE_AXI, 0x70000)
    FIELD(INTLPD_INTFPD_PCIE_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_INTFPD_PCIE_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_INTFPD_PCIE_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_INTFPD_PCIE_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_INTFPD_PCIE_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_OCM_AXI, 0x80000)
    FIELD(INTLPD_OCM_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_OCM_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_OCM_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_OCM_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_OCM_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_RPU0_AXI, 0x90000)
    FIELD(INTLPD_RPU0_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_RPU0_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_RPU0_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_RPU0_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_RPU0_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_RPU1_AXI, 0xa0000)
    FIELD(INTLPD_RPU1_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_RPU1_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_RPU1_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_RPU1_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_RPU1_AXI, MAINEXTEN, 0, 1)
REG32(INTLPD_SYSMONSAT_APB, 0xb0000)
    FIELD(INTLPD_SYSMONSAT_APB, RAW_RST_N, 4, 1)
    FIELD(INTLPD_SYSMONSAT_APB, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_SYSMONSAT_APB, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_SYSMONSAT_APB, POWER_IDLE, 1, 1)
    FIELD(INTLPD_SYSMONSAT_APB, MAINEXTEN, 0, 1)
REG32(PS_CPM_CFG_AXI, 0xc0000)
    FIELD(PS_CPM_CFG_AXI, RAW_RST_N, 4, 1)
    FIELD(PS_CPM_CFG_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(PS_CPM_CFG_AXI, POWER_IDLEACK, 2, 1)
    FIELD(PS_CPM_CFG_AXI, POWER_IDLE, 1, 1)
    FIELD(PS_CPM_CFG_AXI, MAINEXTEN, 0, 1)
REG32(PS_CPM_PCIE_AXI, 0xd0000)
    FIELD(PS_CPM_PCIE_AXI, RAW_RST_N, 4, 1)
    FIELD(PS_CPM_PCIE_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(PS_CPM_PCIE_AXI, POWER_IDLEACK, 2, 1)
    FIELD(PS_CPM_PCIE_AXI, POWER_IDLE, 1, 1)
    FIELD(PS_CPM_PCIE_AXI, MAINEXTEN, 0, 1)
REG32(PS_PMC_AXI0, 0xe0000)
    FIELD(PS_PMC_AXI0, RAW_RST_N, 4, 1)
    FIELD(PS_PMC_AXI0, POWER_IDLEREQ, 3, 1)
    FIELD(PS_PMC_AXI0, POWER_IDLEACK, 2, 1)
    FIELD(PS_PMC_AXI0, POWER_IDLE, 1, 1)
    FIELD(PS_PMC_AXI0, MAINEXTEN, 0, 1)
REG32(PS_PMC_PCIE_AXI0, 0xf0000)
    FIELD(PS_PMC_PCIE_AXI0, RAW_RST_N, 4, 1)
    FIELD(PS_PMC_PCIE_AXI0, POWER_IDLEREQ, 3, 1)
    FIELD(PS_PMC_PCIE_AXI0, POWER_IDLEACK, 2, 1)
    FIELD(PS_PMC_PCIE_AXI0, POWER_IDLE, 1, 1)
    FIELD(PS_PMC_PCIE_AXI0, MAINEXTEN, 0, 1)
REG32(PS_PMC_RPU_AXI0, 0x100000)
    FIELD(PS_PMC_RPU_AXI0, RAW_RST_N, 4, 1)
    FIELD(PS_PMC_RPU_AXI0, POWER_IDLEREQ, 3, 1)
    FIELD(PS_PMC_RPU_AXI0, POWER_IDLEACK, 2, 1)
    FIELD(PS_PMC_RPU_AXI0, POWER_IDLE, 1, 1)
    FIELD(PS_PMC_RPU_AXI0, MAINEXTEN, 0, 1)
REG32(LPD_IPI_APB, 0x110000)
    FIELD(LPD_IPI_APB, RAW_RST_N, 4, 1)
    FIELD(LPD_IPI_APB, POWER_IDLEREQ, 3, 1)
    FIELD(LPD_IPI_APB, POWER_IDLEACK, 2, 1)
    FIELD(LPD_IPI_APB, POWER_IDLE, 1, 1)
    FIELD(LPD_IPI_APB, MAINEXTEN, 0, 1)
REG32(LPD_HSDP, 0x1e0000)
    FIELD(LPD_HSDP, APB_RAW_RST_N, 4, 1)
    FIELD(LPD_HSDP, APB_POWER_IDLEREQ, 3, 1)
    FIELD(LPD_HSDP, APB_POWER_IDLEACK, 2, 1)
    FIELD(LPD_HSDP, APB_POWER_IDLE, 1, 1)
    FIELD(LPD_HSDP, APB_MAINEXTEN, 0, 1)
REG32(INTLPD_OCM2_AXI, 0x1f0000)
    FIELD(INTLPD_OCM2_AXI, RAW_RST_N, 4, 1)
    FIELD(INTLPD_OCM2_AXI, POWER_IDLEREQ, 3, 1)
    FIELD(INTLPD_OCM2_AXI, POWER_IDLEACK, 2, 1)
    FIELD(INTLPD_OCM2_AXI, POWER_IDLE, 1, 1)
    FIELD(INTLPD_OCM2_AXI, MAINEXTEN, 0, 1)
*/

G_STATIC_ASSERT(INTLPD_CONFIG_R_MAX == (R_IR_DISABLE_MISSION2 + 1));

static void ir_mission1_update_irq(INTLPD_CONFIG *s)
{
    bool pending = s->regs[R_IR_STATUS_MISSION1] & ~s->regs[R_IR_MASK_MISSION1];
    qemu_set_irq(s->irq_ir_mission1, pending);
}

static void ir_status_mission1_postw(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    ir_mission1_update_irq(s);
}

static uint64_t ir_enable_mission1_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_MISSION1] &= ~val;
    ir_mission1_update_irq(s);
    return 0;
}

static uint64_t ir_disable_mission1_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_MISSION1] |= val;
    ir_mission1_update_irq(s);
    return 0;
}

static void ir_mission2_update_irq(INTLPD_CONFIG *s)
{
    bool pending = s->regs[R_IR_STATUS_MISSION2] & ~s->regs[R_IR_MASK_MISSION2];
    qemu_set_irq(s->irq_ir_mission2, pending);
}

static void ir_status_mission2_postw(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    ir_mission2_update_irq(s);
}

static uint64_t ir_enable_mission2_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_MISSION2] &= ~val;
    ir_mission2_update_irq(s);
    return 0;
}

static uint64_t ir_disable_mission2_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_MISSION2] |= val;
    ir_mission2_update_irq(s);
    return 0;
}

static void ir_update_irq(INTLPD_CONFIG *s)
{
    bool pending = s->regs[R_IR_STATUS] & ~s->regs[R_IR_MASK];
    qemu_set_irq(s->irq_ir, pending);
}

static void ir_status_postw(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    bool afifs_timeout = ARRAY_FIELD_EX32(s->regs, IR_STATUS,
                         IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT);

    if (!afifs_timeout && s->AFIFSSerbs) {
        xlnx_serbs_if_timeout_set(s->AFIFSSerbs, AFIFS_SERBS_ID, false);
    }
    ir_update_irq(s);
}

static uint64_t ir_enable_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK] &= ~val;
    ir_update_irq(s);
    return 0;
}

static uint64_t ir_disable_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK] |= val;
    ir_update_irq(s);
    return 0;
}

static void ir_perr_update_irq(INTLPD_CONFIG *s)
{
    bool pending = s->regs[R_IR_STATUS_PERR] & ~s->regs[R_IR_MASK_PERR];
    qemu_set_irq(s->irq_ir_perr, pending);
}

static void ir_status_perr_postw(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    ir_perr_update_irq(s);
}

static uint64_t ir_enable_perr_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_PERR] &= ~val;
    ir_perr_update_irq(s);
    return 0;
}

static uint64_t ir_disable_perr_prew(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IR_MASK_PERR] |= val;
    ir_perr_update_irq(s);
    return 0;
}

/*
static void intlpd_afifslpd_axi_postw(RegisterInfo *reg, uint64_t val64)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(reg->opaque);

    if (s->AFIFSSerbs) {
        xlnx_serbs_if_timer_config(s->AFIFSSerbs, AFIFS_SERBS_ID, s->tov,
              ARRAY_FIELD_EX32(s->regs, INTLPD_AFIFSLPD_AXI, MAINEXTEN));
    }
}
*/

static const RegisterAccessInfo intlpd_config_regs_info[] = {
    {   .name = "IR_STATUS",  .addr = A_IR_STATUS,
        .rsvd = 0x3f3c0004,
        .w1c = 0xffffffff,
        .post_write = ir_status_postw,
    },{ .name = "IR_MASK",  .addr = A_IR_MASK,
        .reset = 0xc0c3fffb,
        .rsvd = 0x3f3c0004,
        .ro = 0xffffffff,
    },{ .name = "IR_ENABLE",  .addr = A_IR_ENABLE,
        .rsvd = 0x3f3c0004,
        .pre_write = ir_enable_prew,
    },{ .name = "IR_DISABLE",  .addr = A_IR_DISABLE,
        .rsvd = 0x3f3c0004,
        .pre_write = ir_disable_prew,
    },{ .name = "ADMA",  .addr = A_ADMA,
        .rsvd = 0xfffffffe,
    },{ .name = "AFIFMLPD",  .addr = A_AFIFMLPD,
        .rsvd = 0xfffffffe,
    },{ .name = "RPU0",  .addr = A_RPU0,
        .rsvd = 0xfffffffe,
    },{ .name = "RPU1",  .addr = A_RPU1,
        .rsvd = 0xfffffffe,
    },{ .name = "RPU0_QOS",  .addr = A_RPU0_QOS,
        .rsvd = 0xffffff00,
    },{ .name = "RPU1_QOS",  .addr = A_RPU1_QOS,
        .rsvd = 0xffffff00,
    },{ .name = "HSDP_DMA_QOS",  .addr = A_HSDP_DMA_QOS,
        .rsvd = 0xffffff00,
    },{ .name = "IR_STATUS_PERR",  .addr = A_IR_STATUS_PERR,
        .rsvd = 0xfe000000,
        .ro = 0xfe000000,
        .w1c = 0x1ffffff,
        .post_write = ir_status_perr_postw,
    },{ .name = "IR_MASK_PERR",  .addr = A_IR_MASK_PERR,
        .reset = 0x1ffffff,
        .rsvd = 0xfe000000,
        .ro = 0xffffffff,
    },{ .name = "IR_ENABLE_PERR",  .addr = A_IR_ENABLE_PERR,
        .rsvd = 0xfe000000,
        .pre_write = ir_enable_perr_prew,
    },{ .name = "IR_DISABLE_PERR",  .addr = A_IR_DISABLE_PERR,
        .rsvd = 0xfe000000,
        .pre_write = ir_disable_perr_prew,
    },{ .name = "IR_STATUS_MISSION1",  .addr = A_IR_STATUS_MISSION1,
        .rsvd = 0xffffffe0,
        .w1c = 0xffffffff,
        .post_write = ir_status_mission1_postw,
    },{ .name = "IR_MASK_MISSION1",  .addr = A_IR_MASK_MISSION1,
        .reset = 0x1f,
        .rsvd = 0xffffffe0,
        .ro = 0xffffffff,
    },{ .name = "IR_ENABLE_MISSION1",  .addr = A_IR_ENABLE_MISSION1,
        .rsvd = 0xffffffe0,
        .pre_write = ir_enable_mission1_prew,
    },{ .name = "IR_DISABLE_MISSION1",  .addr = A_IR_DISABLE_MISSION1,
        .rsvd = 0xffffffe0,
        .pre_write = ir_disable_mission1_prew,
    },{ .name = "IR_STATUS_MISSION2",  .addr = A_IR_STATUS_MISSION2,
        .rsvd = 0xe0000000,
        .ro = 0xe0000000,
        .w1c = 0x1fffffff,
        .post_write = ir_status_mission2_postw,
    },{ .name = "IR_MASK_MISSION2",  .addr = A_IR_MASK_MISSION2,
        .reset = 0x1fffffff,
        .rsvd = 0xe0000000,
        .ro = 0xffffffff,
    },{ .name = "IR_ENABLE_MISSION2",  .addr = A_IR_ENABLE_MISSION2,
        .rsvd = 0xe0000000,
        .pre_write = ir_enable_mission2_prew,
    },{ .name = "IR_DISABLE_MISSION2",  .addr = A_IR_DISABLE_MISSION2,
        .rsvd = 0xe0000000,
        .pre_write = ir_disable_mission2_prew,
/*
    },{ .name = "LPD_AFIFM_ADMA_APB",  .addr = A_LPD_AFIFM_ADMA_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "LPD_OCM_RPU_APB",  .addr = A_LPD_OCM_RPU_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "LPD_SLCR_CRL_APB",  .addr = A_LPD_SLCR_CRL_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_AFIFSLPD_AXI",  .addr = A_INTLPD_AFIFSLPD_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
        .post_write = intlpd_afifslpd_axi_postw,
    },{ .name = "INTLPD_CPMPCSR_APB",  .addr = A_INTLPD_CPMPCSR_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_INTFPD_AXI",  .addr = A_INTLPD_INTFPD_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_INTFPD_PCIE_AXI",  .addr = A_INTLPD_INTFPD_PCIE_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_OCM_AXI",  .addr = A_INTLPD_OCM_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_RPU0_AXI",  .addr = A_INTLPD_RPU0_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_RPU1_AXI",  .addr = A_INTLPD_RPU1_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "INTLPD_SYSMONSAT_APB",  .addr = A_INTLPD_SYSMONSAT_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "PS_CPM_CFG_AXI",  .addr = A_PS_CPM_CFG_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "PS_CPM_PCIE_AXI",  .addr = A_PS_CPM_PCIE_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "PS_PMC_AXI0",  .addr = A_PS_PMC_AXI0,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "PS_PMC_PCIE_AXI0",  .addr = A_PS_PMC_PCIE_AXI0,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "PS_PMC_RPU_AXI0",  .addr = A_PS_PMC_RPU_AXI0,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "LPD_IPI_APB",  .addr = A_LPD_IPI_APB,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
    },{ .name = "LPD_HSDP",  .addr = A_LPD_HSDP,
        .reset = 0xb0016,
        .rsvd = 0xfff0ffe0,
        .ro = 0x30006,
    },{ .name = "INTLPD_OCM2_AXI",  .addr = A_INTLPD_OCM2_AXI,
        .reset = 0x16,
        .rsvd = 0xffffffe0,
        .ro = 0x6,
*/
    }
};

static void intlpd_config_reset_enter(Object *obj, ResetType type)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(obj);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }
}

static void intlpd_config_reset_hold(Object *obj, ResetType type)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(obj);

    ir_mission1_update_irq(s);
    ir_mission2_update_irq(s);
    ir_update_irq(s);
    ir_perr_update_irq(s);
}

static void intlpd_afifs_timeout_notify(xlnx_serbs_if *sif, int id, bool level)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(sif);

    switch (id) {
    case AFIFS_SERBS_ID:
        ARRAY_FIELD_DP32(s->regs, IR_STATUS,
                     IF_INTLPD_AFIFSLPD_AXI_T_MAINTIMEOUT, level);
        break;
    default:
         g_assert_not_reached();
    };
    ir_update_irq(s);
}

static const MemoryRegionOps intlpd_config_ops = {
    .read = register_read_memory,
    .write = register_write_memory,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void intlpd_config_realize(DeviceState *dev, Error **errp)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(dev);

    if (s->AFIFSSerbs) {
        xlnx_serbs_if_timer_config(s->AFIFSSerbs, AFIFS_SERBS_ID, s->tov,
                                   false);
    }
}

static void intlpd_config_init(Object *obj)
{
    INTLPD_CONFIG *s = XILINX_INTLPD_CONFIG(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    RegisterInfoArray *reg_array;

    memory_region_init(&s->iomem, obj, TYPE_XILINX_INTLPD_CONFIG,
                       INTLPD_CONFIG_R_MAX * 4);
    reg_array =
        register_init_block32(DEVICE(obj), intlpd_config_regs_info,
                              ARRAY_SIZE(intlpd_config_regs_info),
                              s->regs_info, s->regs,
                              &intlpd_config_ops,
                              XILINX_INTLPD_CONFIG_ERR_DEBUG,
                              INTLPD_CONFIG_R_MAX * 4);
    memory_region_add_subregion(&s->iomem,
                                0x0,
                                &reg_array->mem);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_ir);
    sysbus_init_irq(sbd, &s->irq_ir_mission1);
    sysbus_init_irq(sbd, &s->irq_ir_mission2);
    sysbus_init_irq(sbd, &s->irq_ir_perr);
    object_property_add_link(obj, "afifs-serbs", TYPE_XLNX_SERBS_IF,
                             (Object **)&s->AFIFSSerbs,
                             qdev_prop_allow_set_link_before_realize,
                             OBJ_PROP_LINK_STRONG);
}

static const VMStateDescription vmstate_intlpd_config = {
    .name = TYPE_XILINX_INTLPD_CONFIG,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, INTLPD_CONFIG, INTLPD_CONFIG_R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static Property intlpd_properties[] = {
    DEFINE_PROP_INT32("timeout", INTLPD_CONFIG, tov, 0),
    DEFINE_PROP_END_OF_LIST()
};

static void intlpd_config_class_init(ObjectClass *klass, void *data)
{
    ResettableClass *rc = RESETTABLE_CLASS(klass);
    DeviceClass *dc = DEVICE_CLASS(klass);
    xlnx_serbs_if_class *sc = XLNX_SERBS_IF_CLASS(klass);

    dc->realize = intlpd_config_realize;
    dc->vmsd = &vmstate_intlpd_config;
    rc->phases.enter = intlpd_config_reset_enter;
    rc->phases.hold = intlpd_config_reset_hold;
    device_class_set_props(dc, intlpd_properties);
    sc->timeout_set = intlpd_afifs_timeout_notify;
}

static const TypeInfo intlpd_config_info = {
    .name          = TYPE_XILINX_INTLPD_CONFIG,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(INTLPD_CONFIG),
    .class_init    = intlpd_config_class_init,
    .instance_init = intlpd_config_init,
    .interfaces    = (InterfaceInfo[]) {
        { TYPE_XLNX_SERBS_IF },
        { },
    },
};

static void intlpd_config_register_types(void)
{
    type_register_static(&intlpd_config_info);
}

type_init(intlpd_config_register_types)
