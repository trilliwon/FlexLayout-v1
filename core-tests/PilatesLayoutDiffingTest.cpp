/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, assert_layout_trees_are_same) {
  PilatesConfig* config = PilatesConfigNew();
  PilatesConfigSetUseLegacyStretchBehaviour(config, true);
  const PilatesNodeRef root1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root1, 500);
  PilatesNodeStyleSetHeight(root1, 500);

  const PilatesNodeRef root1_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignItems(root1_child0, PilatesAlignFlexStart);
  PilatesNodeInsertChild(root1, root1_child0, 0);

  const PilatesNodeRef root1_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root1_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root1_child0_child0, 1);
  PilatesNodeInsertChild(root1_child0, root1_child0_child0, 0);

  const PilatesNodeRef root1_child0_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root1_child0_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root1_child0_child0_child0, 1);
  PilatesNodeInsertChild(root1_child0_child0, root1_child0_child0_child0, 0);

  const int32_t cal1_configInstanceCount = PilatesConfigGetInstanceCount();
  const int32_t cal1_nodeInstanceCount = PilatesNodeGetInstanceCount();

  PilatesNodeCalculateLayout(root1, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(PilatesConfigGetInstanceCount(), cal1_configInstanceCount);
  ASSERT_EQ(PilatesNodeGetInstanceCount(), cal1_nodeInstanceCount);

  const PilatesNodeRef root2 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root2, 500);
  PilatesNodeStyleSetHeight(root2, 500);

  const PilatesNodeRef root2_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignItems(root2_child0, PilatesAlignFlexStart);
  PilatesNodeInsertChild(root2, root2_child0, 0);

  const PilatesNodeRef root2_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root2_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root2_child0_child0, 1);
  PilatesNodeInsertChild(root2_child0, root2_child0_child0, 0);

  const PilatesNodeRef root2_child0_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root2_child0_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root2_child0_child0_child0, 1);
  PilatesNodeInsertChild(root2_child0_child0, root2_child0_child0_child0, 0);

  const int32_t cal2_configInstanceCount = PilatesConfigGetInstanceCount();
  const int32_t cal2_nodeInstanceCount = PilatesNodeGetInstanceCount();

  PilatesNodeCalculateLayout(root2, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(PilatesConfigGetInstanceCount(), cal2_configInstanceCount);
  ASSERT_EQ(PilatesNodeGetInstanceCount(), cal2_nodeInstanceCount);

  ASSERT_TRUE(PilatesNodeLayoutGetDidUseLegacyFlag(root1));
  ASSERT_TRUE(PilatesNodeLayoutGetDidUseLegacyFlag(root2));
  ASSERT_TRUE(root1->isLayoutTreeEqualToNode(*root2));

  PilatesNodeStyleSetAlignItems(root2, PilatesAlignFlexEnd);

  const int32_t cal3_configInstanceCount = PilatesConfigGetInstanceCount();
  const int32_t cal3_nodeInstanceCount = PilatesNodeGetInstanceCount();

  PilatesNodeCalculateLayout(root2, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(PilatesConfigGetInstanceCount(), cal3_configInstanceCount);
  ASSERT_EQ(PilatesNodeGetInstanceCount(), cal3_nodeInstanceCount);

  ASSERT_FALSE(root1->isLayoutTreeEqualToNode(*root2));

  PilatesNodeFreeRecursive(root1);
  PilatesNodeFreeRecursive(root2);

  PilatesConfigFree(config);
}
