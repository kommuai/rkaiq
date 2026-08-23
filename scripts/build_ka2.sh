#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD="${BUILD_DIR:-$ROOT/build}"
OUT="$BUILD/out"
TOOLCHAIN="$ROOT/cmake/toolchains/gcc-system-aarch64.cmake"

mkdir -p "$OUT"
cmake -S "$ROOT" -B "$OUT" -G Ninja \
  -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" \
  -DARCH=aarch64 \
  -DRKAIQ_TARGET_SOC=rk3588 \
  -DISP_HW_VERSION=-DISP_HW_V30 \
  -DRKAIQ_BUILD_BINARY_IQ=OFF \
  -DCMAKE_BUILD_TYPE=MinSizeRel \
  -DCMAKE_INSTALL_PREFIX="$BUILD/install"

cmake --build "$OUT" -j"$(nproc)"
echo "Built: $OUT/all_lib/MinSizeRel/librkaiq.so"
md5sum "$OUT/all_lib/MinSizeRel/librkaiq.so"
