/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, start_overrides) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeStart, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 20);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeRight, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetRight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetRight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, end_overrides) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeEnd, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 20);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeRight, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetRight(root_child0));

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionRTL);
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetRight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, horizontal_overridden) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeHorizontal, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetRight(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, vertical_overridden) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeVertical, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeTop, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetBottom(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, horizontal_overrides_all) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeHorizontal, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeAll, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetBottom(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, vertical_overrides_all) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeVertical, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeAll, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetBottom(root_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, all_overridden) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeLeft, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeRight, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeBottom, 10);
  PilatesNodeStyleSetMargin(root_child0, PilatesEdgeAll, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetBottom(root_child0));

  PilatesNodeFreeRecursive(root);
}
