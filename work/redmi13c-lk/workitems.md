# Work Items

| ID | title | role | targets | surface | status | evidence | notes |
|----|-------|------|---------|---------|--------|----------|-------|
| WI-001 | Establish scope and auth | lead | case | process | completed | | Scope set to D:\\13c_Utils\\fenrir\\lk.img; local-only; gate passed |
| WI-002 | Triage Redmi 13C LK image | firmware-triage | lk.img | static | completed | E-001 | MTK LK container identified; target codename inferred as gale |
| WI-003 | Recover ARM32 policy patch signature | ida-static-analysis | lk.img | static | completed | E-001, E-002 | `sec_get_vfy_policy` Thumb policy routine verified and injector validation passed |
| WI-005 | Recover lock-state spoof patch | ida-static-analysis | lk.img | static | completed | E-003 | `sub_3C67C` verified as MI `get_lock_state`; injector validation passed |
| WI-006 | Recover fastboot security-control bypass | ida-static-analysis | lk.img | static | pending | | Gale implementation has not yet been tied to a verified command-gate branch |
| WI-004 | Port stage payload to ARMv7/Thumb | payload-development | payload/ | implementation | pending | | Needed for payload stages; Gale currently supports patch-only injection |

## Coverage
- [ ] Recon/analysis complete for in_scope assets
- [ ] Critical/High candidates triaged (or N/A for pure RE)
- [ ] Validated findings have Evidence (E-*)
- [ ] Path documented (attack/call/solve)
- [ ] Timeline continuous across major phases
- [ ] Report via docs-generator
- [ ] field-journal anonymized

## Refs
- skills/ops/timeline-workitem.md
- skills/ops/evidence-finding-path.md
