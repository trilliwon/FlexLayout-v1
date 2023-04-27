/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, zero_out_layout) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 200);
  PilatesNodeStyleSetHeight(root, 200);

  const PilatesNodeRef child = PilatesNodeNew();
  PilatesNodeInsertChild(root, child, 0);
  PilatesNodeStyleSetWidth(child, 100);
  PilatesNodeStyleSetHeight(child, 100);
  PilatesNodeStyleSetMargin(child, PilatesEdgeTop, 10);
  PilatesNodeStyleSetPadding(child, PilatesEdgeTop, 10);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetMargin(child, PilatesEdgeTop));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetPadding(child, PilatesEdgeTop));

  PilatesNodeStyleSetDisplay(child, PilatesDisplayNone);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(child, PilatesEdgeTop));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetPadding(child, PilatesEdgeTop));

  PilatesNodeFreeRecursive(root);
}
