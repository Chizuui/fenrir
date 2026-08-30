# Timeline (append-only)

## 2026-08-30T20:06:55.2444896+07:00 | lead | init
- action: case-init
- command_or_ref: skills/scripts/case-init.ps1
- result_summary: case directory created; scope pending auth
- artifacts: [scope.md, workitems.md]
- evidence_ids: []
- next: fill scope auth + in_scope; set ready_for_act

## 2026-08-30T20:10:00+07:00 | lead | triage
- action: read-only LK triage
- command_or_ref: PowerShell byte/header/hash inspection; repository source review
- result_summary: D:\\13c_Utils\\fenrir\\lk.img exists, size 1658768 bytes, SHA256 6A629F8E1BF8F605AB64E50E8AF30346003590DC3CC111DEB339DFB2CCA68351; header begins with MediaTek LK magic 0x58881688 and name `lk`; stock package identifies codename `gale` and platform family MT6768
- comparison: stock `images\\lk.img` is a different build (1663104 bytes, SHA256 6515DBC710B88EFC25F124656EB753F7CAB6E5B736BEEE67CE02637445117C89), so addresses must be recovered from the exact Fenrir input rather than copied from stock blindly

## 2026-08-30T20:28:00+07:00 | firmware-triage | architecture correction
- action: offline instruction-signature scan
- command_or_ref: PowerShell byte-pattern scan against D:\\13c_Utils\\fenrir\\lk.img
- result_summary: no AArch64 prologue/return signatures were found; ARM32 prologues occur at file offsets 0x2460C and 0x24668. The raw image begins with the little-endian ARM branch encoding 0xEA000007, targeting offset 0x24. The target must be analyzed as ARM32 little-endian, not AArch64.
- impact: existing Fenrir payload source is AArch64-only; full payload support requires an ARMv7 port. Patch-only device support remains a separate feasible track pending function analysis.
- evidence_ids: [E-001]
- next: define ARM32 code/function at offsets 0x0 and 0x24 in IDA; use strings/cross-references to recover security policy routines
- artifacts: [D:\\13c_Utils\\fenrir\\lk.img, D:\\13c_Utils\\Stock_Rom\\gale_id_global_images_V14.0.5.0.TGPIDXM_13.0\\images\\lk.img]
- evidence_ids: [E-001]
- next: analyze LK in IDA, recover stage/pivot addresses and device-specific patch patterns

## 2026-08-30T20:45:00+07:00 | ida-static-analysis | patch-only support
- action: recover and validate image-authentication policy function
- command_or_ref: IDA MCP direct API; liblk validation through injector.py
- result_summary: ARM Thumb function at partition offset 0x17A24 reads the secure-boot policy table. Signature `70 B5 82 B0 27 4D` is unique in the `lk` partition; patch `00 20 70 47 00 BF` returns policy value 0. The injector applied exactly one patch to a validation copy.
- artifacts: [injector/devices.py, work/redmi13c-lk/gale-validation.bin]
- evidence_ids: [E-002]
- next: device-level boot validation on a recoverable test setup; ARMv7 payload port remains separate work

## 2026-08-30T21:10:00+07:00 | ida-static-analysis | lock-state spoof
- action: recover and validate MI seccfg lock-state getter
- command_or_ref: IDA MCP direct API; liblk validation through injector.py
- result_summary: Thumb function `sub_3C67C` at partition offset `0x3C67C` logs `get_lock_state`, calls the seccfg readers, and writes the result through its pointer parameter. Its callers treat state `3` as unlocked and state `4` as locked/default. The unique 10-byte signature was replaced with a Thumb stub that writes `4`, returns success, and preserves the ABI.
- artifacts: [injector/devices.py, work/redmi13c-lk/gale-lock-validation.bin]
- evidence_ids: [E-003]
- next: find a Gale fastboot command-gate branch before considering a `bypass_security_control` patch

## 2026-08-30T21:40:00+07:00 | ida-static-analysis | Android-only AVB spoof
- action: replace global seccfg spoof with AVB cmdline serialization patches
- command_or_ref: IDA MCP direct API; liblk validation through injector.py
- result_summary: `sub_62260` serializes `androidboot.vbmeta.device_state`; its `unlocked` branch was suppressed at offset `0x62300`. `sub_54758` serializes `androidboot.verifiedbootstate`; it now uses its existing green case at offset `0x54758`. Both signatures were unique and applied once to a validation copy. The global seccfg lock getter is no longer patched.
- artifacts: [injector/devices.py, payload/devices/gale.h, work/redmi13c-lk/gale-android-spoof-validation.bin]
- evidence_ids: [E-003]
- next: port the payload runtime/toolchain to ARMv7/Thumb before assigning executable stage addresses
