/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

// This test isn't correct from the Flexbox standard standpoint,
// because percentages are calculated with parent constraints.
// However, we need to make sure we fail gracefully in this case, not returning NaN
TEST(PilatesTest, percent_absolute_position_infinite_height) {
  const PilatesConfigRef config = PilatesConfigNew();

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 300);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root_child0, 300);
  PilatesNodeStyleSetHeight(root_child0, 300);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetPositionType(root_child1, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetPositionPercent(root_child1, PilatesEdgeLeft, 20);
  PilatesNodeStyleSetPositionPercent(root_child1, PilatesEdgeTop, 20);
  PilatesNodeStyleSetWidthPercent(root_child1, 20);
  PilatesNodeStyleSetHeightPercent(root_child1, 20);
  PilatesNodeInsertChild(root, root_child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(300, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(300, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(300, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(300, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(60, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(60, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(root_child1));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}
