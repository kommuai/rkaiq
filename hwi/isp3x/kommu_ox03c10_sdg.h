/*
 * KA2 / OX03C10: force Spectra IFE linearization inverse into ISP30 SDG.
 * Replaces openpilot librk_sdg_hook.so binary patch of convert3aResultsToIspCfg.
 */
#ifndef _KOMMU_OX03C10_SDG_H_
#define _KOMMU_OX03C10_SDG_H_

#include "rkisp3-config.h"

namespace RkCam {

void kommuApplyOx03c10Sdg(struct isp3x_isp_params_cfg& isp_cfg);

}  // namespace RkCam

#endif
