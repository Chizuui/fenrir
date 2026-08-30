#pragma once

/*
 * Redmi 13C (gale) / MediaTek MT6768 Little Kernel
 *
 * This LK is 32-bit ARM with Thumb code.  It is intentionally excluded from
 * the current payload build because that build emits AArch64 instructions.
 * The constants below are offsets in the exact analysed LK image:
 * SHA256 6A629F8E1BF8F605AB64E50E8AF30346003590DC3CC111DEB339DFB2CCA68351
 *
 * An ARMv7/Thumb payload port must supply a verified runtime load base and
 * stage placement addresses before these can become callable payload macros.
 */

#define DEVICE_NAME "Gale"
#define GALE_LK_ARCH_ARM32_THUMB 1

#define GALE_PLATFORM_INIT_OFFSET             0x000039DAU
#define GALE_PRINTF_OFFSET                    0x00040CE4U
#define GALE_SECCFG_GET_LOCK_STATE_OFFSET     0x0003C67CU
#define GALE_AVB_CMDLINE_BUILDER_OFFSET       0x00062260U
#define GALE_VB_STATE_BUILDER_OFFSET          0x00054758U
