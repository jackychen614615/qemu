/*
 * QEMU model of the LPD_SLCR Global system level control registers for the low
 * power domain
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
#include "migration/vmstate.h"
#include "hw/irq.h"
#include "qemu/log.h"
#include "hw/misc/xlnx-versal-lpd-slcr.h"

/* Skeleton model */

#ifndef XILINX_LPD_SLCR_ERR_DEBUG
#define XILINX_LPD_SLCR_ERR_DEBUG 0
#endif

REG32(WPROT0, 0x0)
    FIELD(WPROT0, ACTIVE, 0, 1)
REG32(CTRL, 0x4)
    FIELD(CTRL, SLVERR_ENABLE, 0, 1)
REG32(ISR, 0x8)
    FIELD(ISR, ADDR_DECODE_ERR, 0, 1)
REG32(IMR, 0xc)
    FIELD(IMR, ADDR_DECODE_ERR, 0, 1)
REG32(IER, 0x10)
    FIELD(IER, ADDR_DECODE_ERR, 0, 1)
REG32(IDR, 0x14)
    FIELD(IDR, ADDR_DECODE_ERR, 0, 1)
REG32(ITR, 0x18)
    FIELD(ITR, ADDR_DECODE_ERR, 0, 1)
REG32(ECO, 0x1c)
REG32(PERSISTENT0, 0x20)
REG32(PERSISTENT1, 0x24)
REG32(PERSISTENT2, 0x28)
REG32(PERSISTENT3, 0x2c)
REG32(PERSISTENT4, 0x30)
REG32(PERSISTENT5, 0x34)
REG32(PERSISTENT6, 0x38)
REG32(PERSISTENT7, 0x3c)
REG32(PERSISTENT8, 0x40)
REG32(PERSISTENT9, 0x44)
REG32(PERSISTENT10, 0x48)
REG32(PERSISTENT11, 0x4c)
REG32(PERSISTENT12, 0x50)
REG32(PERSISTENT13, 0x54)
REG32(PERSISTENT14, 0x58)
REG32(PERSISTENT15, 0x5c)
REG32(SAFETY_CHK0, 0x60)
REG32(SAFETY_CHK1, 0x64)
REG32(SAFETY_CHK2, 0x68)
REG32(SAFETY_CHK3, 0x6c)
REG32(SMID_CONFIG_ADMA0, 0x74)
    FIELD(SMID_CONFIG_ADMA0, CH7, 7, 1)
    FIELD(SMID_CONFIG_ADMA0, CH6, 6, 1)
    FIELD(SMID_CONFIG_ADMA0, CH5, 5, 1)
    FIELD(SMID_CONFIG_ADMA0, CH4, 4, 1)
    FIELD(SMID_CONFIG_ADMA0, CH3, 3, 1)
    FIELD(SMID_CONFIG_ADMA0, CH2, 2, 1)
    FIELD(SMID_CONFIG_ADMA0, CH1, 1, 1)
    FIELD(SMID_CONFIG_ADMA0, CH0, 0, 1)
REG32(SMID_CONFIG_ADMA1, 0x78)
    FIELD(SMID_CONFIG_ADMA1, CH7, 7, 1)
    FIELD(SMID_CONFIG_ADMA1, CH6, 6, 1)
    FIELD(SMID_CONFIG_ADMA1, CH5, 5, 1)
    FIELD(SMID_CONFIG_ADMA1, CH4, 4, 1)
    FIELD(SMID_CONFIG_ADMA1, CH3, 3, 1)
    FIELD(SMID_CONFIG_ADMA1, CH2, 2, 1)
    FIELD(SMID_CONFIG_ADMA1, CH1, 1, 1)
    FIELD(SMID_CONFIG_ADMA1, CH0, 0, 1)
REG32(SMID_CONFIG_RPU0, 0x7c)
    FIELD(SMID_CONFIG_RPU0, CH3, 6, 2)
    FIELD(SMID_CONFIG_RPU0, CH2, 4, 2)
    FIELD(SMID_CONFIG_RPU0, CH1, 2, 2)
    FIELD(SMID_CONFIG_RPU0, CH0, 0, 2)
REG32(SMID_CONFIG_RPU1, 0x80)
    FIELD(SMID_CONFIG_RPU1, CH3, 6, 2)
    FIELD(SMID_CONFIG_RPU1, CH2, 4, 2)
    FIELD(SMID_CONFIG_RPU1, CH1, 2, 2)
    FIELD(SMID_CONFIG_RPU1, CH0, 0, 2)
REG32(HSDP_CONFIG, 0x88)
    FIELD(HSDP_CONFIG, LINK_REACH, 3, 1)
    FIELD(HSDP_CONFIG, AURORA_XPIPE_SEL, 2, 1)
    FIELD(HSDP_CONFIG, SEL_AUR_PCIE, 1, 1)
    FIELD(HSDP_CONFIG, SEL_AUR_PL, 0, 1)
REG32(OCM2_CONFIG, 0x8c)
    FIELD(OCM2_CONFIG, PRESENT, 0, 1)
REG32(BISR_CACHE_CTRL_0, 0x100)
    FIELD(BISR_CACHE_CTRL_0, CLR, 4, 1)
    FIELD(BISR_CACHE_CTRL_0, TRIGGER, 0, 1)
REG32(BISR_CACHE_CTRL_1, 0x104)
    FIELD(BISR_CACHE_CTRL_1, PGEN_1, 1, 1)
    FIELD(BISR_CACHE_CTRL_1, PGEN_0, 0, 1)
REG32(BISR_CACHE_STATUS, 0x108)
    FIELD(BISR_CACHE_STATUS, PASS_GLOBAL, 31, 1)
    FIELD(BISR_CACHE_STATUS, DONE_GLOBAL, 30, 1)
    FIELD(BISR_CACHE_STATUS, PASS_1, 3, 1)
    FIELD(BISR_CACHE_STATUS, DONE_1, 2, 1)
    FIELD(BISR_CACHE_STATUS, PASS_0, 1, 1)
    FIELD(BISR_CACHE_STATUS, DONE_0, 0, 1)
REG32(BISR_CACHE_DATA_0, 0x10c)
REG32(BISR_CACHE_DATA_1, 0x110)
REG32(BISR_CACHE_DATA_2, 0x114)
REG32(BISR_CACHE_DATA_3, 0x118)
REG32(BISR_CACHE_DATA_4, 0x11c)
REG32(BISR_CACHE_DATA_5, 0x120)
REG32(BISR_CACHE_DATA_6, 0x124)
REG32(BISR_CACHE_DATA_7, 0x128)
REG32(BISR_TEST_DATA_0, 0x12c)
REG32(BISR_TEST_DATA_1, 0x130)
REG32(BISR_TEST_DATA_2, 0x134)
REG32(BISR_TEST_DATA_3, 0x138)
REG32(BISR_TEST_DATA_4, 0x13c)
REG32(BISR_TEST_DATA_5, 0x140)
REG32(BISR_TEST_DATA_6, 0x144)
REG32(BISR_TEST_DATA_7, 0x148)

G_STATIC_ASSERT(LPD_SLCR_R_MAX == (R_BISR_TEST_DATA_7 + 1));

static void imr_update_irq(LPD_SLCR *s)
{
    bool pending = s->regs[R_ISR] & ~s->regs[R_IMR];
    qemu_set_irq(s->irq_imr, pending);
}

static void isr_postw(RegisterInfo *reg, uint64_t val64)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(reg->opaque);
    imr_update_irq(s);
}

static uint64_t ier_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] &= ~val;
    imr_update_irq(s);
    return 0;
}

static uint64_t idr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_IMR] |= val;
    imr_update_irq(s);
    return 0;
}

static uint64_t itr_prew(RegisterInfo *reg, uint64_t val64)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(reg->opaque);
    uint32_t val = val64;

    s->regs[R_ISR] |= val;
    imr_update_irq(s);
    return 0;
}

static const RegisterAccessInfo lpd_slcr_regs_info[] = {
    {   .name = "WPROT0",  .addr = A_WPROT0,
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
    },{ .name = "ECO",  .addr = A_ECO,
    },{ .name = "PERSISTENT0",  .addr = A_PERSISTENT0,
    },{ .name = "PERSISTENT1",  .addr = A_PERSISTENT1,
    },{ .name = "PERSISTENT2",  .addr = A_PERSISTENT2,
    },{ .name = "PERSISTENT3",  .addr = A_PERSISTENT3,
    },{ .name = "PERSISTENT4",  .addr = A_PERSISTENT4,
    },{ .name = "PERSISTENT5",  .addr = A_PERSISTENT5,
    },{ .name = "PERSISTENT6",  .addr = A_PERSISTENT6,
    },{ .name = "PERSISTENT7",  .addr = A_PERSISTENT7,
    },{ .name = "PERSISTENT8",  .addr = A_PERSISTENT8,
    },{ .name = "PERSISTENT9",  .addr = A_PERSISTENT9,
    },{ .name = "PERSISTENT10",  .addr = A_PERSISTENT10,
    },{ .name = "PERSISTENT11",  .addr = A_PERSISTENT11,
    },{ .name = "PERSISTENT12",  .addr = A_PERSISTENT12,
    },{ .name = "PERSISTENT13",  .addr = A_PERSISTENT13,
    },{ .name = "PERSISTENT14",  .addr = A_PERSISTENT14,
    },{ .name = "PERSISTENT15",  .addr = A_PERSISTENT15,
    },{ .name = "SAFETY_CHK0",  .addr = A_SAFETY_CHK0,
    },{ .name = "SAFETY_CHK1",  .addr = A_SAFETY_CHK1,
    },{ .name = "SAFETY_CHK2",  .addr = A_SAFETY_CHK2,
    },{ .name = "SAFETY_CHK3",  .addr = A_SAFETY_CHK3,
    },{ .name = "SMID_CONFIG_ADMA0",  .addr = A_SMID_CONFIG_ADMA0,
    },{ .name = "SMID_CONFIG_ADMA1",  .addr = A_SMID_CONFIG_ADMA1,
        .rsvd = 0xffffff00,
    },{ .name = "SMID_CONFIG_RPU0",  .addr = A_SMID_CONFIG_RPU0,
        .rsvd = 0xffffff00,
    },{ .name = "SMID_CONFIG_RPU1",  .addr = A_SMID_CONFIG_RPU1,
        .rsvd = 0xffffff00,
    },{ .name = "HSDP_CONFIG",  .addr = A_HSDP_CONFIG,
        .rsvd = 0xfffffff0,
    },{ .name = "OCM2_CONFIG",  .addr = A_OCM2_CONFIG,
        .rsvd = 0xfffffffe,
        .ro = 0x1,
    },{ .name = "BISR_CACHE_CTRL_0",  .addr = A_BISR_CACHE_CTRL_0,
        .rsvd = 0xe,
    },{ .name = "BISR_CACHE_CTRL_1",  .addr = A_BISR_CACHE_CTRL_1,
    },{ .name = "BISR_CACHE_STATUS",  .addr = A_BISR_CACHE_STATUS,
        .ro = 0xc000000f,
    },{ .name = "BISR_CACHE_DATA_0",  .addr = A_BISR_CACHE_DATA_0,
    },{ .name = "BISR_CACHE_DATA_1",  .addr = A_BISR_CACHE_DATA_1,
    },{ .name = "BISR_CACHE_DATA_2",  .addr = A_BISR_CACHE_DATA_2,
    },{ .name = "BISR_CACHE_DATA_3",  .addr = A_BISR_CACHE_DATA_3,
    },{ .name = "BISR_CACHE_DATA_4",  .addr = A_BISR_CACHE_DATA_4,
    },{ .name = "BISR_CACHE_DATA_5",  .addr = A_BISR_CACHE_DATA_5,
    },{ .name = "BISR_CACHE_DATA_6",  .addr = A_BISR_CACHE_DATA_6,
    },{ .name = "BISR_CACHE_DATA_7",  .addr = A_BISR_CACHE_DATA_7,
    },{ .name = "BISR_TEST_DATA_0",  .addr = A_BISR_TEST_DATA_0,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_1",  .addr = A_BISR_TEST_DATA_1,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_2",  .addr = A_BISR_TEST_DATA_2,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_3",  .addr = A_BISR_TEST_DATA_3,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_4",  .addr = A_BISR_TEST_DATA_4,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_5",  .addr = A_BISR_TEST_DATA_5,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_6",  .addr = A_BISR_TEST_DATA_6,
        .ro = 0xffffffff,
    },{ .name = "BISR_TEST_DATA_7",  .addr = A_BISR_TEST_DATA_7,
        .ro = 0xffffffff,
    }
};

static void lpd_slcr_reset(DeviceState *dev)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(dev);
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(s->regs_info); ++i) {
        register_reset(&s->regs_info[i]);
    }

    imr_update_irq(s);
}

static const MemoryRegionOps lpd_slcr_ops = {
    .read = register_read_memory,
    .write = register_write_memory,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = {
        .min_access_size = 4,
        .max_access_size = 4,
    },
};

static void lpd_slcr_init(Object *obj)
{
    LPD_SLCR *s = XILINX_LPD_SLCR(obj);
    SysBusDevice *sbd = SYS_BUS_DEVICE(obj);
    RegisterInfoArray *reg_array;

    memory_region_init(&s->iomem, obj, TYPE_XILINX_LPD_SLCR,
                       LPD_SLCR_R_MAX * 4);
    reg_array =
        register_init_block32(DEVICE(obj), lpd_slcr_regs_info,
                              ARRAY_SIZE(lpd_slcr_regs_info),
                              s->regs_info, s->regs,
                              &lpd_slcr_ops,
                              XILINX_LPD_SLCR_ERR_DEBUG,
                              LPD_SLCR_R_MAX * 4);
    memory_region_add_subregion(&s->iomem,
                                0x0,
                                &reg_array->mem);
    sysbus_init_mmio(sbd, &s->iomem);
    sysbus_init_irq(sbd, &s->irq_imr);
}

static const VMStateDescription vmstate_lpd_slcr = {
    .name = TYPE_XILINX_LPD_SLCR,
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32_ARRAY(regs, LPD_SLCR, LPD_SLCR_R_MAX),
        VMSTATE_END_OF_LIST(),
    }
};

static void lpd_slcr_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    dc->reset = lpd_slcr_reset;
    dc->vmsd = &vmstate_lpd_slcr;
}

static const TypeInfo lpd_slcr_info = {
    .name          = TYPE_XILINX_LPD_SLCR,
    .parent        = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(LPD_SLCR),
    .class_init    = lpd_slcr_class_init,
    .instance_init = lpd_slcr_init,
};

static void lpd_slcr_register_types(void)
{
    type_register_static(&lpd_slcr_info);
}

type_init(lpd_slcr_register_types)
