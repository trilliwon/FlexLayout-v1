/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// @Generated by gentest/gentest.rb from gentest/fixtures/PilatesFlexDirectionTest.html

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, flex_direction_column_no_height) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(30, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(30, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, flex_direction_row_no_width) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(30, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(30, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, flex_direction_column) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, flex_direction_row) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(80, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(70, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, flex_direction_column_reverse) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumnReverse);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(80, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(70, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(80, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(70, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, flex_direction_row_reverse) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRowReverse);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child1, 10);
  PilatesNodeInsertChild(root, root_child1, 1);

  const PilatesNodeRef root_child2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child2, 10);
  PilatesNodeInsertChild(root, root_child2, 2);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(80, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(70, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child2));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}