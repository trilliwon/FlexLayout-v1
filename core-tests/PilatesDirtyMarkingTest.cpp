/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>

TEST(PilatesTest, dirty_propagation) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child1, 50);
  PilatesNodeStyleSetHeight(root_child1, 20);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  PilatesNodeStyleSetWidth(root_child0, 20);

  EXPECT_TRUE(root_child0->isDirty());
  EXPECT_FALSE(root_child1->isDirty());
  EXPECT_TRUE(root->isDirty());

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  EXPECT_FALSE(root_child0->isDirty());
  EXPECT_FALSE(root_child1->isDirty());
  EXPECT_FALSE(root->isDirty());

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dirty_propagation_only_if_prop_changed) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 20);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child1, 50);
  PilatesNodeStyleSetHeight(root_child1, 20);
  PilatesNodeInsertChild(root, root_child1, 1);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  PilatesNodeStyleSetWidth(root_child0, 50);

  EXPECT_FALSE(root_child0->isDirty());
  EXPECT_FALSE(root_child1->isDirty());
  EXPECT_FALSE(root->isDirty());

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dirty_mark_all_children_as_dirty_when_display_changes) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(child0, 1);
  const PilatesNodeRef child1 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(child1, 1);

  const PilatesNodeRef child1_child0 = PilatesNodeNew();
  const PilatesNodeRef child1_child0_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(child1_child0_child0, 8);
  PilatesNodeStyleSetHeight(child1_child0_child0, 16);

  PilatesNodeInsertChild(child1_child0, child1_child0_child0, 0);

  PilatesNodeInsertChild(child1, child1_child0, 0);
  PilatesNodeInsertChild(root, child0, 0);
  PilatesNodeInsertChild(root, child1, 0);

  PilatesNodeStyleSetDisplay(child0, PilatesDisplayFlex);
  PilatesNodeStyleSetDisplay(child1, PilatesDisplayNone);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(child1_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(child1_child0_child0));

  PilatesNodeStyleSetDisplay(child0, PilatesDisplayNone);
  PilatesNodeStyleSetDisplay(child1, PilatesDisplayFlex);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(8, PilatesNodeLayoutGetWidth(child1_child0_child0));
  ASSERT_FLOAT_EQ(16, PilatesNodeLayoutGetHeight(child1_child0_child0));

  PilatesNodeStyleSetDisplay(child0, PilatesDisplayFlex);
  PilatesNodeStyleSetDisplay(child1, PilatesDisplayNone);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(child1_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(child1_child0_child0));

  PilatesNodeStyleSetDisplay(child0, PilatesDisplayNone);
  PilatesNodeStyleSetDisplay(child1, PilatesDisplayFlex);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(8, PilatesNodeLayoutGetWidth(child1_child0_child0));
  ASSERT_FLOAT_EQ(16, PilatesNodeLayoutGetHeight(child1_child0_child0));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dirty_node_only_if_children_are_actually_removed) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);

  const PilatesNodeRef child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(child0, 50);
  PilatesNodeStyleSetHeight(child0, 25);
  PilatesNodeInsertChild(root, child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  const PilatesNodeRef child1 = PilatesNodeNew();
  PilatesNodeRemoveChild(root, child1);
  EXPECT_FALSE(root->isDirty());
  PilatesNodeFree(child1);

  PilatesNodeRemoveChild(root, child0);
  EXPECT_TRUE(root->isDirty());
  PilatesNodeFree(child0);

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, dirty_node_only_if_undefined_values_gets_set_to_undefined) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 50);
  PilatesNodeStyleSetHeight(root, 50);
  PilatesNodeStyleSetMinWidth(root, PilatesUndefined);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  EXPECT_FALSE(root->isDirty());

  PilatesNodeStyleSetMinWidth(root, PilatesUndefined);

  EXPECT_FALSE(root->isDirty());

  PilatesNodeFreeRecursive(root);
}
