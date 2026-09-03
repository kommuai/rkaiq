/*
 * Compact, typed calibration input for the KA2 ISP30 camera path.
 *
 * The view is an additive API. It deliberately contains only the calibration
 * fields used by the KA2 profiles; librkaiq owns and materializes its private
 * CamCalibDbProj_t representation during initialization.
 */
#ifndef RK_AIQ_USER_API2_KA2_CALIB_H
#define RK_AIQ_USER_API2_KA2_CALIB_H

#include <stddef.h>
#include <stdint.h>

#include "rk_aiq_comm.h"

RKAIQ_BEGIN_DECLARE

#define RK_AIQ_KA2_CALIB_VERSION 1U

typedef struct rk_aiq_ka2_calib_view_s {
    uint32_t version;

    uint8_t sensor_flip;
    uint8_t ccm_enable;
    uint8_t has_lsc;
    uint8_t reserved;

    RKAiqOPMode_t dcg_op_mode;
    float dcg_ratio;
    float lcg2hcg_gain_th;
    float hcg2lcg_gain_th;
    int32_t dcg_coeff[3];
    int32_t exp_update[3];

    uint8_t gamma_enable;
    uint16_t gamma_out_offset;
    const uint16_t *gamma_curve;
    uint32_t gamma_curve_len;

    const float *ccm_rgb2y;
    uint32_t ccm_rgb2y_len;
    float ccm_low_bound_pos_bit;
    const float *ccm_y_alpha_curve;
    uint32_t ccm_y_alpha_curve_len;
    const float *ccm_gain;
    const float *ccm_scale;
    uint32_t ccm_gain_scale_len;
    float ccm_wbgain_tolerance;
    float ccm_gain_tolerance;
    uint8_t ccm_damp_enable;
    uint8_t ccm_interp_enable;
    const char *ccm_default_illu;
    float ccm_weight_rb[2];
    float ccm_prob_limit;
    int32_t ccm_frame_no;

    const uint32_t *disable_algos;
    uint32_t disable_algos_len;

    const uint16_t *lsc_sector_x;
    const uint16_t *lsc_sector_y;
    uint32_t lsc_sector_len;
    const char *lsc_resolution;
    const char *lsc_illumination;
    const char *lsc_table_used;
    const char *lsc_table;
    float lsc_wb_gain[2];
    const float *lsc_gains;
    uint32_t lsc_gains_len;
    const float *lsc_vig;
    uint32_t lsc_vig_len;
    const uint16_t *lsc_red;
    const uint16_t *lsc_green_r;
    const uint16_t *lsc_green_b;
    const uint16_t *lsc_blue;
    uint32_t lsc_mesh_len;
} rk_aiq_ka2_calib_view_t;

XCamReturn rk_aiq_uapi2_sysctl_preInit_ka2_calib(
    const char *sns_ent_name,
    const rk_aiq_ka2_calib_view_t *calib);

RKAIQ_END_DECLARE

#endif
