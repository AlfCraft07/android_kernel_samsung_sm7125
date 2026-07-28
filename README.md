# Legion-atoll Kernel

> [!NOTE]
> I'm not the original author of this nor did I make the BPF backports. This kernel's maintainer was [Simon1511](https://github.com/Simon1511) previously, and later [frostg-012](https://github.com/frostg-012) under the name Valeryn, I just added defconfig entries in order to make it compatible with the Tab S6 Lite 2022. Workflows were taken from [the LineageOS KernelSU Next kernel](https://github.com/IamKavy47/gta4xlve_kernel_ksun) by [IamKavy47](https://github.com/IamKavy47)

> [!NOTE]
> Feel free to FORK or create PR.

> [!NOTE]
> Make sure you have build tools/packages installed, else it won't compile properly.

## Looking for linux readme?
- [Click here](https://github.com/AlfCraft07/android_kernel_samsung_sm7125/blob/oneui/android16/README)

### Features [To be added/Implemented] 
    [✅️ = Done | ❌️ = Not done yet]
- Bootable with OneUI7 ✅
- Bootable with OneUI8+ ✅
- Upstreamed to 4.14.357 ✅️
- KernelSU Next ❌️
- Maybe more in future

### Progress (Disclaimer: Kernel is most likely not the issue here)
    [✅️ = Boots | ❌️ = Doesn't boot]
- LineageOS boot ✅️
- Stock boot ✅
- TrebleDroid GSI boot ✅
- LineageOS GSI boot ❌ (hangs on splash screen)
- PixelOS GSI boot ✅
- One UI 6 GSI boot ❌ (hangs on boot animation)
- One UI 7 GSI boot ✅, but currently has userspace crashes when connected to WiFi
- One UI 8 GSI boot ❌️ (restarts after 12-14 secs)
- One UI 8 port boot ✅️, minor issues
- One UI 8.5 ROM port boot ✅, but negative amount of internal storage is shown and setup won't load on either QSSI or ESSI bases.

### Known issues
- a52q: none so far
- a72q: none so far
- gta4xlvewifi: none so far
- gta4xlve: none so far

### About this Repository:
- This kernel was compiled in late May 2026 from the kernel source used in the One UI 8 port for the Galaxy A52 4G (SM-A525F), using a defconfig containing entries for P613 drivers. It has also recently been proven capable of booting OneUI 8 with minor bugs, and 8.5 albeit with critical issues most likely related to the ROM itself.
