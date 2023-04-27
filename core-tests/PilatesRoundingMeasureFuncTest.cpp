/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

static PilatesSize _measureFloor(PilatesNodeRef node,
                            float width,
                            PilatesMeasureMode widthMode,
                            float height,
                            PilatesMeasureMode heightMode) {
  return PilatesSize{
      width = 10.2f, height = 10.2f,
  };
}

static PilatesSize _measureCeil(PilatesNodeRef node,
                           float width,
                           PilatesMeasureMode widthMode,
                           float height,
                           PilatesMeasureMode heightMode) {
  return PilatesSize{
      width = 10.5f, height = 10.5f,
  };
}

static PilatesSize _measureFractial(PilatesNodeRef node,
  float width,
  PilatesMeasureMode widthMode,
  float height,
  PilatesMeasureMode heightMode) {
  return PilatesSize{
    width = 0.5f, height = 0.5f,
  };
}

TEST(PilatesTest, rounding_feature_with_custom_measure_func_floor) {
  const PilatesConfigRef config = PilatesConfigNew();
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measureFloor);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesConfigSetPointScaleFactor(config, 0.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(10.2, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.2, PilatesNodeLayoutGetHeight(root_child0));

  PilatesConfigSetPointScaleFactor(config, 1.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(11, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, PilatesNodeLayoutGetHeight(root_child0));

  PilatesConfigSetPointScaleFactor(config, 2.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(10.5, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.5, PilatesNodeLayoutGetHeight(root_child0));

  PilatesConfigSetPointScaleFactor(config, 4.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(10.25, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.25, PilatesNodeLayoutGetHeight(root_child0));

  PilatesConfigSetPointScaleFactor(config, 1.0f / 3.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(12.0, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(12.0, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, rounding_feature_with_custom_measure_func_ceil) {
  const PilatesConfigRef config = PilatesConfigNew();
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measureCeil);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesConfigSetPointScaleFactor(config, 1.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(11, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, rounding_feature_with_custom_measure_and_fractial_matching_scale) {
  const PilatesConfigRef config = PilatesConfigNew();
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeLeft, 73.625);
  root_child0->setMeasureFunc(_measureFractial);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesConfigSetPointScaleFactor(config, 2.0f);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0.5, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0.5, PilatesNodeLayoutGetHeight(root_child0));
  ASSERT_FLOAT_EQ(73.5, PilatesNodeLayoutGetLeft(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}
