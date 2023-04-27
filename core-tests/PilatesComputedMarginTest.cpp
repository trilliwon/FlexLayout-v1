/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, computed_layout_margin) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);
  PilatesNodeStyleSetMarginPercent(root, PilatesEdgeStart, 10);

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetMargin(root, PilatesEdgeLeft));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeRight));

  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionRTL);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeLeft));
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetMargin(root, PilatesEdgeRight));

  PilatesNodeFreeRecursive(root);
}
