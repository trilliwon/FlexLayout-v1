/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

static float _baseline(PilatesNodeRef node, const float width, const float height) {
  float* baseline = (float*)node->getContext();
  return *baseline;
}

TEST(PilatesTest, align_baseline_customer_func) {
  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignBaseline);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child0, 50);
  PilatesNodeStyleSetHeight(root_child0, 50);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child1 = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root_child1, 50);
  PilatesNodeStyleSetHeight(root_child1, 20);
  PilatesNodeInsertChild(root, root_child1, 1);

  float baselineValue = 10;
  const PilatesNodeRef root_child1_child0 = PilatesNodeNew();
  root_child1_child0->setContext(&baselineValue);
  PilatesNodeStyleSetWidth(root_child1_child0, 50);
  root_child1_child0->setBaseLineFunc(_baseline);
  PilatesNodeStyleSetHeight(root_child1_child0, 20);
  PilatesNodeInsertChild(root_child1, root_child1_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(40, PilatesNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child1_child0));
  ASSERT_FLOAT_EQ(50, PilatesNodeLayoutGetWidth(root_child1_child0));
  ASSERT_FLOAT_EQ(20, PilatesNodeLayoutGetHeight(root_child1_child0));
}
