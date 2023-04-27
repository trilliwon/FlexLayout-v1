/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, reset_layout_when_child_removed) {
  const PilatesNodeRef root = PilatesNodeNew();

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 100);
  PilatesNodeStyleSetHeight(root_child0, 100);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeRemoveChild(root, root_child0);

  ASSERT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeLayoutGetWidth(root_child0)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeLayoutGetHeight(root_child0)));

  PilatesNodeFreeRecursive(root);
}
