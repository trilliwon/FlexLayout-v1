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
  return PilatesSize{
      .width = widthMode == PilatesMeasureModeExactly ? width : 50,
      .height = heightMode == PilatesMeasureModeExactly ? height : 50,
  };
}

TEST(PilatesTest, aspect_ratio_cross_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_main_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_both_dimensions_defined_row) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 100);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_both_dimensions_defined_column) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 100);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_align_stretch) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_flex_grow) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_flex_shrink) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 150);
  PilatesNodeStyleSetFlexShrink(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_flex_shrink_2) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeightPercent(root_child0, 100);
  PilatesNodeStyleSetFlexShrink(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetHeightPercent(root_child1, 100);
  PilatesNodeStyleSetFlexShrink(root_child1, 1);
  PilatesNodeStyleSetAspectRatio(root_child1, 1);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(50, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_basis) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexBasis(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_absolute_layout_width_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPositionType(root_child0, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeLeft, 0);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeTop, 0);
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_absolute_layout_height_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPositionType(root_child0, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeLeft, 0);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeTop, 0);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_with_max_cross_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetMaxWidth(root_child0, 40);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_with_max_main_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetMaxHeight(root_child0, 40);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_with_min_cross_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 30);
  PilatesNodeStyleSetMinWidth(root_child0, 40);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(30, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_with_min_main_defined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 30);
  PilatesNodeStyleSetMinHeight(root_child0, 40);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_double_cross) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 2);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_half_cross) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 100);
  PilatesNodeStyleSetAspectRatio(root_child0, 0.5);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_double_main) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 0.5);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_half_main) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 100);
  PilatesNodeStyleSetAspectRatio(root_child0, 2);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_with_measure_func) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setMeasureFunc(_measure);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_width_height_flex_grow_row) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 200);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_width_height_flex_grow_column) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 200);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_height_as_flex_basis) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 200);
  PilatesNodeStyleSetHeight(root, 200);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child1, 100);
  PilatesNodeStyleSetFlexGrow(root_child1, 1);
  PilatesNodeStyleSetAspectRatio(root_child1, 1);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(75, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_width_as_flex_basis) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 200);
  PilatesNodeStyleSetHeight(root, 200);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child1, 100);
  PilatesNodeStyleSetFlexGrow(root_child1, 1);
  PilatesNodeStyleSetAspectRatio(root_child1, 1);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(75, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_overrides_flex_grow_row) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 0.5);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(200, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_overrides_flex_grow_column) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetAspectRatio(root_child0, 2);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(200, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_left_right_absolute) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPositionType(root_child0, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeLeft, 10);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeRight, 10);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_top_bottom_absolute) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetPositionType(root_child0, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeLeft, 10);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetPosition(root_child0, PilatesEdgeBottom, 10);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_width_overrides_align_stretch_row) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_height_overrides_align_stretch_column) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_allow_child_overflow_parent_size) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 4);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(200, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_defined_main_with_margin) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignCenter);
  PilatesNodeStyleSetJustifyContent(root, PilatesJustifyCenter);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeRight, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_defined_cross_with_margin) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignCenter);
  PilatesNodeStyleSetJustifyContent(root, PilatesJustifyCenter);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeRight, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_defined_cross_with_main_margin) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignCenter);
  PilatesNodeStyleSetJustifyContent(root, PilatesJustifyCenter);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetAspectRatio(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeBottom, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_should_prefer_explicit_height) {
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetUseWebDefaults(config, true);

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root_child0, PilatesFlexDirectionColumn);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root_child0_child0, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetHeight(root_child0_child0, 100);
  PilatesNodeStyleSetAspectRatio(root_child0_child0, 2);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  PilatesNodeCalculateLayout(root, 100, 200, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(200, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(200, PilatesNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_should_prefer_explicit_width) {
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetUseWebDefaults(config, true);

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root_child0, PilatesFlexDirectionRow);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root_child0_child0, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root_child0_child0, 100);
  PilatesNodeStyleSetAspectRatio(root_child0_child0, 0.5);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_EQ(200, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(200, PilatesNodeLayoutGetHeight(root_child0_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, aspect_ratio_should_prefer_flexed_dimension) {
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetUseWebDefaults(config, true);

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root_child0, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetAspectRatio(root_child0, 2);
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAspectRatio(root_child0_child0, 4);
  PilatesNodeStyleSetFlexGrow(root_child0_child0, 1);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(200, PilatesNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(50, PilatesNodeLayoutGetHeight(root_child0_child0));

  PilatesNodeFreeRecursive(root);
}
