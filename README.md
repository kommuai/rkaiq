# rkaiq (KA2 / RK3588 ISP30)

Fork of Rockchip camera engine **rkaiq** used to build the KA2 `librkaiq.so` with **sensor degamma (SDG / DEGAMMA_V1)** enabled for ISP3.0.

## Upstream

- Base: [JeffyCN/mirrors](https://github.com/JeffyCN/mirrors) tag `rkaiq-2024_04_08` (commit `bd19d1ee`)
- Stock KA2 package `camera-engine-rkaiq-rk3588` 6.0×6.1 ships `RKAIQ_HAVE_DEGAMMA_V1=0`; this tree enables it for ISP30.

## KA2 patches (vs upstream)

1. `cmake/BuildOptions.cmake` — `RKAIQ_HAVE_DEGAMMA=TRUE` and `RKAIQ_HAVE_DEGAMMA_V1=TRUE` for ISP30
2. `hwi/isp3x/kommu_ox03c10_sdg.cpp` — Spectra OX03C10 degamma → SDG in `convert3aResultsToIspCfg` (replaces openpilot `librk_sdg_hook.so`)
3. `ipc_server/MessageParser.cpp` — `#include <cstdio>` (cross-build fix)
4. `cmake/toolchains/gcc-system-aarch64.cmake` — host cross-compile toolchain file

## Build (host → aarch64)

Prereqs: `gcc-aarch64-linux-gnu`, `g++-aarch64-linux-gnu`, `cmake`, `ninja-build`

```bash
./scripts/build_ka2.sh
```

Output: `build/out/all_lib/MinSizeRel/librkaiq.so`

Verified MD5 on KA2 device (2026-08-21): `44bfef03dac8c565f9f2e68a153f24aa`

## Install on KA2

```bash
sudo cp -a build/out/all_lib/MinSizeRel/librkaiq.so /usr/lib/librkaiq.so
```

Stock backup on device: `/usr/lib/librkaiq.so.stock-6.0x6.1.bak`

Restore stock:

```bash
sudo cp -a /usr/lib/librkaiq.so.stock-6.0x6.1.bak /usr/lib/librkaiq.so
```
