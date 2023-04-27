/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <iostream>

TEST(PilatesTest, copy_style_same) {
  const PilatesNodeRef node0 = PilatesNodeNew();
  const PilatesNodeRef node1 = PilatesNodeNew();
  ASSERT_FALSE(node0->isDirty());

  PilatesNodeCopyStyle(node0, node1);
  ASSERT_FALSE(node0->isDirty());

  PilatesNodeFree(node0);
  PilatesNodeFree(node1);
}

TEST(PilatesTest, copy_style_modified) {
  const PilatesNodeRef node0 = PilatesNodeNew();
  ASSERT_FALSE(node0->isDirty());
  ASSERT_EQ(PilatesFlexDirectionColumn, PilatesNodeStyleGetFlexDirection(node0));
  ASSERT_FALSE(PilatesNodeStyleGetMaxHeight(node0).unit != PilatesUnitUndefined);

  const PilatesNodeRef node1 = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(node1, PilatesFlexDirectionRow);
  PilatesNodeStyleSetMaxHeight(node1, 10);

  PilatesNodeCopyStyle(node0, node1);
  ASSERT_TRUE(node0->isDirty());
  ASSERT_EQ(PilatesFlexDirectionRow, PilatesNodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, PilatesNodeStyleGetMaxHeight(node0).value);

  PilatesNodeFree(node0);
  PilatesNodeFree(node1);
}

TEST(PilatesTest, copy_style_modified_same) {
  const PilatesNodeRef node0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(node0, PilatesFlexDirectionRow);
  PilatesNodeStyleSetMaxHeight(node0, 10);
  PilatesNodeCalculateLayout(node0, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FALSE(node0->isDirty());

  const PilatesNodeRef node1 = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(node1, PilatesFlexDirectionRow);
  PilatesNodeStyleSetMaxHeight(node1, 10);

  PilatesNodeCopyStyle(node0, node1);
  ASSERT_FALSE(node0->isDirty());

  PilatesNodeFree(node0);
  PilatesNodeFree(node1);
}
