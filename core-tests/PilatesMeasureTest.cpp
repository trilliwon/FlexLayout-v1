/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

static PilatesSize _measure(PilatesNodeRef node,
                       float width,
                       PilatesMeasureMode widthMode,
                       float height,
                       PilatesMeasureMode heightMode) {
  int* measureCount = (int*)node->getContext();
  if (measureCount) {
    (*measureCount)++;
  }

  return PilatesSize{
      .width = 10, .height = 10,
  };
}

static PilatesSize _simulate_wrapping_text(PilatesNodeRef node,
                                      float width,
                                      PilatesMeasureMode widthMode,
                                      float height,
                                      PilatesMeasureMode heightMode) {
  if (widthMode == PilatesMeasureModeUndefined || width >= 68) {
    return PilatesSize{.width = 68, .height = 16};
  }

  return PilatesSize{
      .width = 50, .height = 32,
  };
}

static PilatesSize _measure_assert_negative(PilatesNodeRef node,
                                       float width,
                                       PilatesMeasureMode widthMode,
                                       float height,
                                       PilatesMeasureMode heightMode) {
  EXPECT_GE(width, 0);
  EXPECT_GE(height, 0);

  return PilatesSize{
    .width = 0, .height = 0,
  };
}

TEST(PilatesTest, dont_measure_single_grow_shrink_child) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetFlexShrink(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, measure_absolute_child_with_no_constraints) {
  const PilatesNodeRef root = PilatesNodeNew();

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeInsertChild(root, root_child0, 0);

  int measureCount = 0;

  const PilatesNodeRef root_child0_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPositionType(root_child0_child0, PilatesPositionTypeAbsolute);
  root_child0_child0->setContext(&measureCount);
  root_child0_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, measureCount);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dont_measure_when_min_equals_max) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetMinWidth(root_child0, 10);
  PilatesNodeStyleSetMaxWidth(root_child0, 10);
  PilatesNodeStyleSetMinHeight(root_child0, 10);
  PilatesNodeStyleSetMaxHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dont_measure_when_min_equals_max_percentages) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetMinWidthPercent(root_child0, 10);
  PilatesNodeStyleSetMaxWidthPercent(root_child0, 10);
  PilatesNodeStyleSetMinHeightPercent(root_child0, 10);
  PilatesNodeStyleSetMaxHeightPercent(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}


TEST(PilatesTest, measure_nodes_with_margin_auto_and_stretch) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 500);
  PilatesNodeStyleSetHeight(root, 500);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetMarginAuto(root_child0, PilatesEdgeLeft);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  EXPECT_EQ(490, PilatesNodeLayoutGetLeft(root_child0));
  EXPECT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  EXPECT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  EXPECT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dont_measure_when_min_equals_max_mixed_width_percent) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetMinWidthPercent(root_child0, 10);
  PilatesNodeStyleSetMaxWidthPercent(root_child0, 10);
  PilatesNodeStyleSetMinHeight(root_child0, 10);
  PilatesNodeStyleSetMaxHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dont_measure_when_min_equals_max_mixed_height_percent) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetMinWidth(root_child0, 10);
  PilatesNodeStyleSetMaxWidth(root_child0, 10);
  PilatesNodeStyleSetMinHeightPercent(root_child0, 10);
  PilatesNodeStyleSetMaxHeightPercent(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, measure_enough_size_should_be_in_single_line) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignFlexStart);
  root_child0->setMeasureFunc(_simulate_wrapping_text);

  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(68, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(16, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, measure_not_enough_size_should_wrap) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 55);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignFlexStart);
  //  PilatesNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, measure_zero_space_should_grow) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root, 200);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetFlexGrow(root, 0);

  int measureCount = 0;

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root_child0, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetPadding(root_child0, PilatesEdgeAll, 100);
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);

  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 282, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(282, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, measure_flex_direction_row_and_padding) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetPadding(root, PilatesEdgeLeft, 25);
  PilatesNodeStyleSetPadding(root, PilatesEdgeTop, 25);
  PilatesNodeStyleSetPadding(root, PilatesEdgeRight, 25);
  PilatesNodeStyleSetPadding(root, PilatesEdgeBottom, 25);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  //  PilatesNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(75, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_flex_direction_column_and_padding) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetPadding(root, PilatesEdgeAll, 25);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  //  PilatesNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(57, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_flex_direction_row_no_padding) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  //  PilatesNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_flex_direction_row_no_padding_align_items_flexstart) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_with_fixed_size) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetPadding(root, PilatesEdgeAll, 25);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(35, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_with_flex_shrink) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetPadding(root, PilatesEdgeAll, 25);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeStyleSetFlexShrink(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(25, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, measure_no_padding) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetMargin(root, PilatesEdgeTop, 20);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  PilatesNodeStyleSetFlexShrink(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 5);
  PilatesNodeStyleSetHeight(root_child1, 5);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(32, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

#if GTEST_HAS_DEATH_TEST
TEST(PilatesDeathTest, cannot_add_child_to_node_with_measure_func) {
  const PilatesNodeRef root = PilatesNodeNew();
  root->setMeasureFunc(_measure);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  ASSERT_DEATH(PilatesNodeInsertChild(root, root_child0, 0), "Cannot add child.*");
  PilatesNodeFree(root_child0);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesDeathTest, cannot_add_nonnull_measure_func_to_non_leaf_node) {
  const PilatesNodeRef root = PilatesNodeNew();
  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeInsertChild(root, root_child0, 0);
  ASSERT_DEATH(root->setMeasureFunc(_measure), "Cannot set measure function.*");
  PilatesNodeFreeRecursive(root);
}

#endif

TEST(PilatesTest, can_nullify_measure_func_on_any_node) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeInsertChild(root, PilatesNodeNew(), 0);
  root->setMeasureFunc(nullptr);
  ASSERT_TRUE(root->getMeasure() == NULL);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, cant_call_negative_measure) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 10);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measure_assert_negative);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeTop, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  PilatesNodeFreeRecursive(root);
  PilatesConfigFree(config);
}

TEST(PilatesTest, cant_call_negative_measure_horizontal) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 10);
  PilatesNodeStyleSetHeight(root, 20);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measure_assert_negative);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeStart, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  PilatesNodeFreeRecursive(root);
  PilatesConfigFree(config);
}

static PilatesSize _measure_90_10(PilatesNodeRef node,
  float width,
  PilatesMeasureMode widthMode,
  float height,
  PilatesMeasureMode heightMode) {

  return PilatesSize{
    .width = 90, .height = 10,
  };
}

TEST(PilatesTest, percent_with_text_node) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetJustifyContent(root, PilatesJustifySpaceBetween);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignCenter);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 80);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  root_child1->setMeasureFunc(_measure_90_10);
  PilatesNodeStyleSetMaxWidthPercent(root_child1, 50);
  PilatesNodeStyleSetPaddingPercent(root_child1, PilatesEdgeTop, 50);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(80, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(40, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(15, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}
