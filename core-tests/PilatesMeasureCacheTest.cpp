/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

static PilatesSize _measureMax(PilatesNodeRef node,
                          float width,
                          PilatesMeasureMode widthMode,
                          float height,
                          PilatesMeasureMode heightMode) {
  int* measureCount = (int*)node->getContext();
  (*measureCount)++;

  return PilatesSize{
      .width = widthMode == PilatesMeasureModeUndefined ? 10 : width,
      .height = heightMode == PilatesMeasureModeUndefined ? 10 : height,
  };
}

static PilatesSize _measureMin(PilatesNodeRef node,
                          float width,
                          PilatesMeasureMode widthMode,
                          float height,
                          PilatesMeasureMode heightMode) {
  int* measureCount = (int*)node->getContext();
  *measureCount = *measureCount + 1;
  return PilatesSize{
      .width =
          widthMode == PilatesMeasureModeUndefined || (widthMode == PilatesMeasureModeAtMost && width > 10)
              ? 10
              : width,
      .height =
          heightMode == PilatesMeasureModeUndefined || (heightMode == PilatesMeasureModeAtMost && height > 10)
              ? 10
              : height,
  };
}

static PilatesSize _measure_84_49(PilatesNodeRef node,
                             float width,
                             PilatesMeasureMode widthMode,
                             float height,
                             PilatesMeasureMode heightMode) {
  int* measureCount = (int*)node->getContext();
  if (measureCount) {
    (*measureCount)++;
  }

  return PilatesSize{
      .width = 84.f, .height = 49.f,
  };
}

TEST(PilatesTest, measure_once_single_flexible_child) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  int measureCount = 0;
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measureMax);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, remeasure_with_same_exact_width_larger_than_needed_height) {
  const PilatesNodeRef root = PilatesNodeNew();

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  int measureCount = 0;
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measureMin);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);
  PilatesNodeCalculateLayout(root, 100, 50, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, remeasure_with_same_atmost_width_larger_than_needed_height) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  int measureCount = 0;
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measureMin);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);
  PilatesNodeCalculateLayout(root, 100, 50, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, remeasure_with_computed_width_larger_than_needed_height) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  int measureCount = 0;
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measureMin);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignStretch);
  PilatesNodeCalculateLayout(root, 10, 50, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, remeasure_with_atmost_computed_width_undefined_height) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  int measureCount = 0;
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measureMin);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 100, PilatesUndefined, PilatesDirectionLTR);
  PilatesNodeCalculateLayout(root, 10, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, remeasure_with_already_measured_value_smaller_but_still_float_equal) {
  int measureCount = 0;

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 288.f);
  PilatesNodeStyleSetHeight(root, 288.f);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPadding(root_child0, PilatesEdgeAll, 2.88f);
  PilatesNodeStyleSetFlexDirection(root_child0, PilatesFlexDirectionRow);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child0_child0 = PilatesNodeNew();
  root_child0_child0->setContext(&measureCount);
  root_child0_child0->setMeasureFunc(_measure_84_49);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  PilatesNodeFreeRecursive(root);

  ASSERT_EQ(1, measureCount);
}
