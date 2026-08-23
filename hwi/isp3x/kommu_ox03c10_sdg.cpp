/*
 * Spectra IFE linearization inverse (OX03C10 PWL12) → rkisp SDG knots.
 * Tables match commaai/openpilot ox03c10 IFE linearization (rk_tone_tables.h).
 */
#include "kommu_ox03c10_sdg.h"

#include <algorithm>
#include <cmath>
#include <cstdint>

namespace RkCam {

namespace {

constexpr int kDegammaKnots = 17;

constexpr int clamp_int(int v, int lo, int hi) {
  return v < lo ? lo : (v > hi ? hi : v);
}

constexpr int kDegammaX[kDegammaKnots] = {
    0, 256, 512, 768, 1024, 1280, 1536, 1792, 2048,
    2304, 2560, 2816, 3072, 3328, 3584, 3840, 4096,
};

constexpr int kOx03c10DegammaY[kDegammaKnots] = {
    0, 16, 32, 64, 128, 192, 257, 514, 1028, 2053,
    4095, 4095, 4095, 4095, 4095, 4095, 4095,
};

void pack_degamma_x(const float* x_axis, int* dx_out) {
  constexpr int kNorm = 4;
  for (int i = 0; i < kDegammaKnots - 1; i++) {
    int delta = (int)(x_axis[i + 1] - x_axis[i] + 0.5f);
    delta = std::max(delta, 1);
    int v = (int)(std::log((double)delta) / std::log(2.0) - (double)kNorm);
    dx_out[i] = clamp_int(v, 0, 7);
  }
}

void apply_sdg_cfg(struct isp2x_sdg_cfg* sdg) {
  float x_axis[kDegammaKnots];
  for (int i = 0; i < kDegammaKnots; i++) x_axis[i] = (float)kDegammaX[i];
  int dx[16] = {};
  pack_degamma_x(x_axis, dx);
  int d0 = 0, d1 = 0;
  for (int i = 0; i < 8; i++) {
    d0 |= (dx[i] << (4 * i));
    d1 |= (dx[i + 8] << (4 * i));
  }
  sdg->xa_pnts.gamma_dx0 = (uint32_t)d0;
  sdg->xa_pnts.gamma_dx1 = (uint32_t)d1;
  for (int i = 0; i < kDegammaKnots; i++) {
    int y = clamp_int(kOx03c10DegammaY[i], 0, 4095);
    sdg->curve_r.gamma_y[i] = (uint16_t)y;
    sdg->curve_g.gamma_y[i] = (uint16_t)y;
    sdg->curve_b.gamma_y[i] = (uint16_t)y;
  }
}

}  // namespace

void kommuApplyOx03c10Sdg(struct isp3x_isp_params_cfg& isp_cfg) {
  isp_cfg.module_en_update |= ISP3X_MODULE_SDG;
  isp_cfg.module_ens |= ISP3X_MODULE_SDG;
  isp_cfg.module_cfg_update |= ISP3X_MODULE_SDG;
  apply_sdg_cfg(&isp_cfg.others.sdg_cfg);
}

}  // namespace RkCam
