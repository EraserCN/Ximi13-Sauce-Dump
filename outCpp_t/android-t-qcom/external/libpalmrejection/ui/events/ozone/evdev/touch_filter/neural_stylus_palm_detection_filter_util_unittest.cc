// Copyright 2019 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/events/ozone/evdev/touch_filter/neural_stylus_palm_detection_filter_util.h"

#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

#include "testing/gtest/include/gtest/gtest.h"
#if defined(__ANDROID__)
#include <linux/input-event-codes.h>
#include "chrome_to_android_compatibility_test_support.h"
#else
#include "ui/events/ozone/evdev/event_device_test_util.h"
#endif
#include "ui/events/ozone/evdev/touch_evdev_types.h"
#include "ui/events/ozone/evdev/touch_filter/palm_detection_filter.h"
#include "ui/events/ozone/evdev/touch_filter/shared_palm_detection_filter_state.h"

namespace ui {

#if defined(__ANDROID__)
/**
 * The tests that require an actual device (something that responds to ioctls)
 * have been removed. The rest of the tests were simplified by modifying the
 * 'CreatePalmFilterDeviceInfo' method.
 */
enum DeviceType {
  kNocturneTouchScreen,
  kLinkTouchscreen,
  kKohakuTouchscreen,
};

static PalmFilterDeviceInfo CreatePalmFilterDeviceInfo(DeviceType deviceType) {
  // Default value for resolution is 1 if it's not specified (or set to 0). See
  // https://source.chromium.org/chromium/chromium/src/+/main:ui/events/ozone/evdev/touch_filter/
  // neural_stylus_palm_detection_filter_util.cc;l=11;drc=7f74e1d22e2d0b91856ea6b3619098cd05ef6158

  switch (deviceType) {
    case kNocturneTouchScreen:
      return PalmFilterDeviceInfo{
          .max_x = 10404,
          .max_y = 6936,
          .x_res = 40,
          .y_res = 40,
          .major_radius_res = 1,
          .minor_radius_res = 1,
          .minor_radius_supported = true,
      };
    case kLinkTouchscreen:
      return PalmFilterDeviceInfo{
          .max_x = 2559,
          .max_y = 1699,
          .x_res = 20,
          .y_res = 20,
          .major_radius_res = 1,
          .minor_radius_res = 1,
          .minor_radius_supported = false,
      };
    case kKohakuTouchscreen:
      return PalmFilterDeviceInfo{
          .max_x = 2559,
          .max_y = 1699,
          .x_res = 1,
          .y_res = 1,
          .major_radius_res = 1,
          .minor_radius_res = 1,
          .minor_radius_supported = false,
      };
  }
}

class EventDeviceInfo {
 public:
  float GetAbsResolution(int /*axis*/) { return 20; }
};

bool CapabilitiesToDeviceInfo(DeviceType, EventDeviceInfo*) {
  return true;
}
#endif

class NeuralStylusPalmDetectionFilterUtilTest : public testing::Test {
 public:
  NeuralStylusPalmDetectionFilterUtilTest() = default;

  NeuralStylusPalmDetectionFilterUtilTest(
      const NeuralStylusPalmDetectionFilterUtilTest&) = delete;
  NeuralStylusPalmDetectionFilterUtilTest& operator=(
      const NeuralStylusPalmDetectionFilterUtilTest&) = delete;

  void SetUp() override {
    EXPECT_TRUE(
        CapabilitiesToDeviceInfo(kNocturneTouchScreen, &nocturne_touchscreen_));
    touch_.major = 25;
    touch_.minor = 24;
    touch_.pressure = 23;
    touch_.tracking_id = 22;
    touch_.x = 21;
    touch_.y = 20;
  }

 protected:
  InProgressTouchEvdev touch_;
  EventDeviceInfo nocturne_touchscreen_;
  NeuralStylusPalmDetectionFilterModelConfig model_config_;
};

#if !defined(__ANDROID__)
TEST_F(NeuralStylusPalmDetectionFilterUtilTest, DistilledNocturneTest) {
  const PalmFilterDeviceInfo nocturne_distilled =
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
  EXPECT_FLOAT_EQ(nocturne_distilled.max_x,
                  nocturne_touchscreen_.GetAbsMaximum(ABS_MT_POSITION_X));
  EXPECT_FLOAT_EQ(nocturne_distilled.max_y,
                  nocturne_touchscreen_.GetAbsMaximum(ABS_MT_POSITION_Y));
  EXPECT_FLOAT_EQ(nocturne_distilled.x_res,
                  nocturne_touchscreen_.GetAbsResolution(ABS_MT_POSITION_X));
  EXPECT_FLOAT_EQ(nocturne_distilled.y_res,
                  nocturne_touchscreen_.GetAbsResolution(ABS_MT_POSITION_Y));
  EXPECT_FLOAT_EQ(nocturne_distilled.major_radius_res,
                  nocturne_touchscreen_.GetAbsResolution(ABS_MT_TOUCH_MAJOR));
  EXPECT_TRUE(nocturne_distilled.minor_radius_supported);
  EXPECT_FLOAT_EQ(nocturne_distilled.minor_radius_res,
                  nocturne_touchscreen_.GetAbsResolution(ABS_MT_TOUCH_MINOR));
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, NoMinorResTest) {
  // Nocturne has minor resolution: but lets pretend it didnt. we should recover
  // "1" as the resolution.
  auto abs_info = nocturne_touchscreen_.GetAbsInfoByCode(ABS_MT_TOUCH_MINOR);
  abs_info.resolution = 0;
  nocturne_touchscreen_.SetAbsInfo(ABS_MT_TOUCH_MINOR, abs_info);
  const PalmFilterDeviceInfo nocturne_distilled =
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
  EXPECT_EQ(1, nocturne_distilled.minor_radius_res);
  EXPECT_EQ(1, nocturne_distilled.major_radius_res);
}
#endif

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, DistillerKohakuTest) {
  EventDeviceInfo kohaku_touchscreen;
  ASSERT_TRUE(
      CapabilitiesToDeviceInfo(kKohakuTouchscreen, &kohaku_touchscreen));
  const PalmFilterDeviceInfo kohaku_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(kohaku_touchscreen);
#else
      CreatePalmFilterDeviceInfo(kKohakuTouchscreen);
#endif
  EXPECT_FALSE(kohaku_distilled.minor_radius_supported);
  EXPECT_EQ(1, kohaku_distilled.x_res);
  EXPECT_EQ(1, kohaku_distilled.y_res);
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, DistilledLinkTest) {
  EventDeviceInfo link_touchscreen;
  ASSERT_TRUE(CapabilitiesToDeviceInfo(kLinkTouchscreen, &link_touchscreen));
  const PalmFilterDeviceInfo link_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(link_touchscreen);
#else
      CreatePalmFilterDeviceInfo(kLinkTouchscreen);
#endif
  EXPECT_FALSE(link_distilled.minor_radius_supported);
  EXPECT_FLOAT_EQ(1.f, link_distilled.major_radius_res);
  EXPECT_FLOAT_EQ(link_distilled.major_radius_res,
                  link_distilled.minor_radius_res);
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, PalmFilterSampleTest) {
  base::TimeTicks time = base::TimeTicks() + base::Seconds(30);
  const PalmFilterDeviceInfo nocturne_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
#else
      CreatePalmFilterDeviceInfo(kNocturneTouchScreen);
#endif
  const PalmFilterSample sample =
      CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
  EXPECT_EQ(time, sample.time);
  EXPECT_EQ(25, sample.major_radius);
  EXPECT_EQ(24, sample.minor_radius);
  EXPECT_EQ(23, sample.pressure);
  EXPECT_EQ(22, sample.tracking_id);
  EXPECT_EQ(gfx::PointF(21 / 40.f, 20 / 40.f), sample.point);
  EXPECT_EQ(0.5, sample.edge);
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, LinkTouchscreenSampleTest) {
  EventDeviceInfo link_touchscreen;
  base::TimeTicks time = base::TimeTicks() + base::Seconds(30);
  ASSERT_TRUE(CapabilitiesToDeviceInfo(kLinkTouchscreen, &link_touchscreen));
  const PalmFilterDeviceInfo link_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(link_touchscreen);
#else
      CreatePalmFilterDeviceInfo(kLinkTouchscreen);
#endif
  touch_.minor = 0;  // no minor from link.
  // use 40 as a base since model is trained on that kind of device.
  model_config_.radius_polynomial_resize = {
      link_touchscreen.GetAbsResolution(ABS_MT_POSITION_X) / 40.0f, 0.0};
  const PalmFilterSample sample =
      CreatePalmFilterSample(touch_, time, model_config_, link_distilled);
  EXPECT_FLOAT_EQ(12.5, sample.major_radius);
  EXPECT_FLOAT_EQ(12.5, sample.minor_radius);
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, PalmFilterStrokeTest) {
  PalmFilterStroke stroke(3);  // maxsize: 3.
  EXPECT_EQ(0, stroke.tracking_id());
  // With no points, center is 0.
  EXPECT_EQ(gfx::PointF(0., 0.), stroke.GetCentroid());

  base::TimeTicks time = base::TimeTicks() + base::Seconds(30);
  const PalmFilterDeviceInfo nocturne_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
#else
      CreatePalmFilterDeviceInfo(kNocturneTouchScreen);
#endif
  // Deliberately long test to ensure floating point continued accuracy.
  for (int i = 0; i < 500000; ++i) {
    touch_.x = 15 + i;
    PalmFilterSample sample =
        CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
    stroke.AddSample(std::move(sample));
    EXPECT_EQ(touch_.tracking_id, stroke.tracking_id());
    if (i < 3) {
      if (i == 0) {
        EXPECT_FLOAT_EQ(gfx::PointF(15 / 40.f, 0.5).x(),
                        stroke.GetCentroid().x());
      } else if (i == 1) {
        EXPECT_FLOAT_EQ(gfx::PointF((30 + 1) / (2 * 40.f), 0.5).x(),
                        stroke.GetCentroid().x());
      } else if (i == 2) {
        EXPECT_FLOAT_EQ(gfx::PointF((45 + 1 + 2) / (3 * 40.f), 0.5).x(),
                        stroke.GetCentroid().x());
      }
      continue;
    }
    float expected_x = (45 + 3 * i - 3) / (3 * 40.f);
    gfx::PointF expected_centroid = gfx::PointF(expected_x, 0.5);
    ASSERT_FLOAT_EQ(expected_centroid.x(), stroke.GetCentroid().x())
        << "failed at i " << i;
  }
  stroke.SetTrackingId(55);
  EXPECT_EQ(55, stroke.tracking_id());
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest,
       PalmFilterStrokeBiggestSizeTest) {
  PalmFilterStroke stroke(3);
  PalmFilterStroke no_minor_stroke(3);  // maxsize: 3.
  EXPECT_EQ(0, stroke.BiggestSize());

  base::TimeTicks time = base::TimeTicks() + base::Seconds(30);
  const PalmFilterDeviceInfo nocturne_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
#else
      CreatePalmFilterDeviceInfo(kNocturneTouchScreen);
#endif
  for (int i = 0; i < 500; ++i) {
    touch_.major = 2 + i;
    touch_.minor = 1 + i;
    PalmFilterSample sample =
        CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
    EXPECT_EQ(static_cast<uint64_t>(i), stroke.samples_seen());
    stroke.AddSample(sample);
    EXPECT_FLOAT_EQ((1 + i) * (2 + i), stroke.BiggestSize());

    PalmFilterSample second_sample =
        CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
    second_sample.minor_radius = 0;
    no_minor_stroke.AddSample(std::move(second_sample));
    EXPECT_FLOAT_EQ((2 + i) * (2 + i), no_minor_stroke.BiggestSize());
    EXPECT_EQ(std::min(3ul, 1ul + i), stroke.samples().size());
  }
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, StrokeGetMaxMajorTest) {
  PalmFilterStroke stroke(3);
  EXPECT_FLOAT_EQ(0, stroke.MaxMajorRadius());
  base::TimeTicks time = base::TimeTicks::UnixEpoch() + base::Seconds(30);
  const PalmFilterDeviceInfo nocturne_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
#else
      CreatePalmFilterDeviceInfo(kNocturneTouchScreen);
#endif
  for (int i = 1; i < 50; ++i) {
    touch_.major = i;
    touch_.minor = i - 1;
    PalmFilterSample sample =
        CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
    time += base::Milliseconds(8);
    EXPECT_EQ(static_cast<uint64_t>(i - 1), stroke.samples_seen());
    stroke.AddSample(sample);
    EXPECT_FLOAT_EQ(i, stroke.MaxMajorRadius());
  }
}

TEST_F(NeuralStylusPalmDetectionFilterUtilTest, SampleRadiusConversion) {
  // A single number: a _constant_.
  model_config_.radius_polynomial_resize = {71.3};
  base::TimeTicks time = base::TimeTicks::UnixEpoch() + base::Seconds(30);
  const PalmFilterDeviceInfo nocturne_distilled =
#if !defined(__ANDROID__)
      CreatePalmFilterDeviceInfo(nocturne_touchscreen_);
#else
      CreatePalmFilterDeviceInfo(kNocturneTouchScreen);
#endif
  PalmFilterSample sample =
      CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
  EXPECT_FLOAT_EQ(71.3, sample.major_radius);
  EXPECT_FLOAT_EQ(71.3, sample.minor_radius);

  // 0.1*r^2 + 0.4*r - 5.0
  model_config_.radius_polynomial_resize = {0.1, 0.4, -5.0};
  sample =
      CreatePalmFilterSample(touch_, time, model_config_, nocturne_distilled);
  EXPECT_FLOAT_EQ(0.1 * 25 * 25 + 0.4 * 25 - 5.0, sample.major_radius);
  EXPECT_FLOAT_EQ(0.1 * 24 * 24 + 0.4 * 24 - 5.0, sample.minor_radius);
}

}  // namespace ui