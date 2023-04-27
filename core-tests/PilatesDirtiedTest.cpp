/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>

static void _dirtied(PilatesNodeRef node) {
  int* dirtiedCount = (int*)node->getContext();
  (*dirtiedCount)++;
}

TEST(PilatesTest, dirtied) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  int dirtiedCount = 0;
  root->setContext(&dirtiedCount);
  root->setDirtiedFunc(_dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called in case of explicit dirtying.
  root->setDirty(true);
  ASSERT_EQ(1, dirtiedCount);

  // `_dirtied` MUST be called ONCE.
  root->setDirty(true);
  ASSERT_EQ(1, dirtiedCount);
}

TEST(PilatesTest, dirtied_propagation) {
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

  int dirtiedCount = 0;
  root->setContext(&dirtiedCount);
  root->setDirtiedFunc(_dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called for the first time.
  root_child0->markDirtyAndPropogate();
  ASSERT_EQ(1, dirtiedCount);

  // `_dirtied` must NOT be called for the second time.
  root_child0->markDirtyAndPropogate();
  ASSERT_EQ(1, dirtiedCount);
}

TEST(PilatesTest, dirtied_hierarchy) {
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

  int dirtiedCount = 0;
  root_child0->setContext(&dirtiedCount);
  root_child0->setDirtiedFunc(_dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` must NOT be called for descendants.
  root->markDirtyAndPropogate();
  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` must NOT be called for the sibling node.
  root_child1->markDirtyAndPropogate();
  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called in case of explicit dirtying.
  root_child0->markDirtyAndPropogate();
  ASSERT_EQ(1, dirtiedCount);
}
