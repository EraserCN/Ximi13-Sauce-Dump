// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_EVDEV_TOUCH_FILTER_NEURAL_STYLUS_PALM_DETECTION_FILTER_MODEL_H_
#define UI_EVENTS_OZONE_EVDEV_TOUCH_FILTER_NEURAL_STYLUS_PALM_DETECTION_FILTER_MODEL_H_

#if defined(__ANDROID__)
#include "chrome_to_android_compatibility.h"
#endif

#include <cstdint>
#include <vector>

#include "base/component_export.h"
#include "base/time/time.h"

namespace ui {

struct COMPONENT_EXPORT(EVDEV) NeuralStylusPalmDetectionFilterModelConfig {
  // Explicit constructor to make chromium style happy.
  NeuralStylusPalmDetectionFilterModelConfig();
  NeuralStylusPalmDetectionFilterModelConfig(
      const NeuralStylusPalmDetectionFilterModelConfig& other);
  ~NeuralStylusPalmDetectionFilterModelConfig();
  // Number of nearest neighbors to use in vector construction.
  uint32_t nearest_neighbor_count = 0;

  // Number of biggest nearby neighbors to use in vector construction.
  uint32_t biggest_near_neighbor_count = 0;

  // Maximum distance of neighbor centroid, in millimeters.
  float max_neighbor_distance_in_mm = 0.0f;

  base::TimeDelta max_dead_neighbor_time;

  // Minimum count of samples in a stroke for neural comparison.
  uint32_t min_sample_count = 0;

  // Maximum sample count.
  uint32_t max_sample_count = 0;

  uint32_t max_sequence_start_count_for_inference = 0;

  bool include_sequence_count_in_strokes = false;

  // If this number is positive, short strokes with a touch major greater than
  // or equal to this should be marked as a palm. If 0 or less, has no effect.
  float heuristic_palm_touch_limit = 0.0f;

  // If this number is positive, short strokes with any touch having an area
  // greater than or equal to this should be marked as a palm. If <= 0, has no
  // effect
  float heuristic_palm_area_limit = 0.0f;

  // If true, runs the heuristic palm check on short strokes, and enables delay
  // on them if the heuristic would have marked the touch as a palm at that
  // point.
  bool heuristic_delay_start_if_palm = false;

  // Maximum blank time within a session, in milliseconds.
  // Two tracking_ids are considered in one session if they overlap with each
  // other or the gap between them is less than max_blank_time.
  base::TimeDelta max_blank_time;

  // If true, uses tracking_id count within a session as a feature.
  bool use_tracking_id_count = false;

  // If true, uses current active tracking_id count as a feature.
  bool use_active_tracking_id_count = false;

  // If empty, the radius by the device is left as is.
  // If non empty, the radius reported by device is re-sized in features by the
  // polynomial defined in this vector. E.g. if this vector is {0.5, 1.3,
  // -0.2, 1.0} Each radius r is replaced by
  //
  // R = 0.5 * r^3 + 1.3 * r^2 - 0.2 * r + 1
  std::vector<float> radius_polynomial_resize;
};

// An abstract model utilized by NueralStylusPalmDetectionFilter.
class COMPONENT_EXPORT(EVDEV) NeuralStylusPalmDetectionFilterModel {
 public:
  virtual ~NeuralStylusPalmDetectionFilterModel() {}

  // Actually execute inference on floating point input. If the length of
  // features is not correct, return Nan. The return value is assumed to be the
  // input of a sigmoid. i.e. any value greater than 0 implies a positive
  // result.
  virtual float Inference(const std::vector<float>& features) const = 0;

  virtual const NeuralStylusPalmDetectionFilterModelConfig& config() const = 0;
};

}  // namespace ui

#endif  // UI_EVENTS_OZONE_EVDEV_TOUCH_FILTER_NEURAL_STYLUS_PALM_DETECTION_FILTER_MODEL_H_