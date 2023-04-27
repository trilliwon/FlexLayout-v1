/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @Generated by gentest/gentest.rb from gentest/fixtures/PilatesAlignSelfTest.html

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, align_self_center) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignCenter);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(45, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(45, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, align_self_flex_end) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignFlexEnd);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, align_self_flex_start) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, align_self_flex_end_override_flex_start) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignFlexEnd);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, align_self_baseline) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child0, PilatesAlignBaseline);
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignSelf(root_child1, PilatesAlignBaseline);
  PilatesNodeStyleSetWidth(root_child1, 50);
  PilatesNodeStyleSetHeight(root_child1, 20);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child1_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1_child0, 50);
  PilatesNodeStyleSetHeight(root_child1_child0, 10);
  PilatesNodeInsertChild(root_child1, root_child1_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(40, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(40, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}