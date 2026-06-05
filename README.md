# Galaxy Tab S6 Lite 2022 Kernel

> [!NOTE]
> Feel free to FORK or create PR.

> [!NOTE]
> Make sure you have build tools/packages installed, else it won't compile properly.

## Looking for linux readme?
- [Click here](https://github.com/AlfCraft07/valeryn_samsung_sm7125_P613/blob/main/README)

### Features [To be added/Implemented] 
    [✅️ = Done | ❌️ = Not done yet]
- Bootable with OneUI7/8 ❌️
- Upstreamed to 4.14.356 ✅️
- KernelSU ❌️
- Maybe more in future

### Progress (Disclaimer: Kernel is most likely not the issue here)
- LineageOS boot ✅️
- Stock boot ✅
- TrebleDroid GSI boot ✅
- LineageOS GSI boot ❌ (hangs on splash screen)
- PixelOS GSI boot ✅
- One UI 6 GSI boot ❌ (hangs on boot animation)
- One UI 7/8 GSI boot ❌️ (restarts after 12-14 secs)

### About this Repository:
- This kernel was compiled in late May 2026 from the kernel source used in the One UI 8 port for the Galaxy A52 4G (SM-A525F), using a defconfig containing entries for P613 drivers. Thus, theoretically, this kernel should boot One UI 8 on the tablet, but a proper port has not yet been done.
