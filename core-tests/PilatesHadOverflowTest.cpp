// Copyright 2004-present Facebook. All Rights Reserved.

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

using namespace ::testing;

class PilatesTest_HadOverflowTests : public Test {
protected:
  PilatesTest_HadOverflowTests() {
    config = PilatesConfigNew();
    root = PilatesNodeNewWithConfig(config);
    PilatesNodeStyleSetWidth(root, 200);
    PilatesNodeStyleSetHeight(root, 100);
    PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionColumn);
    PilatesNodeStyleSetFlexWrap(root, PilatesWrapNoWrap);
  }

  ~PilatesTest_HadOverflowTests() {
    PilatesNodeFreeRecursive(root);
    PilatesConfigFree(config);
  }

  PilatesNodeRef root;
  PilatesConfigRef config;
};

TEST_F(PilatesTest_HadOverflowTests, children_overflow_no_wrap_and_no_flex_children) {
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child0, 80);
  PilatesNodeStyleSetHeight(child0, 40);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeBottom, 15);
  PilatesNodeInsertChild(root, child0, 0);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1, 80);
  PilatesNodeStyleSetHeight(child1, 40);
  PilatesNodeStyleSetMargin(child1, PilatesEdgeBottom, 5);
  PilatesNodeInsertChild(root, child1, 1);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_TRUE(PilatesNodeLayoutGetHadOverflow(root));
}

TEST_F(PilatesTest_HadOverflowTests, spacing_overflow_no_wrap_and_no_flex_children) {
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child0, 80);
  PilatesNodeStyleSetHeight(child0, 40);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeBottom, 10);
  PilatesNodeInsertChild(root, child0, 0);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1, 80);
  PilatesNodeStyleSetHeight(child1, 40);
  PilatesNodeStyleSetMargin(child1, PilatesEdgeBottom, 5);
  PilatesNodeInsertChild(root, child1, 1);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_TRUE(PilatesNodeLayoutGetHadOverflow(root));
}

TEST_F(PilatesTest_HadOverflowTests, no_overflow_no_wrap_and_flex_children) {
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child0, 80);
  PilatesNodeStyleSetHeight(child0, 40);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeBottom, 10);
  PilatesNodeInsertChild(root, child0, 0);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1, 80);
  PilatesNodeStyleSetHeight(child1, 40);
  PilatesNodeStyleSetMargin(child1, PilatesEdgeBottom, 5);
  PilatesNodeStyleSetFlexShrink(child1, 1);
  PilatesNodeInsertChild(root, child1, 1);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_FALSE(PilatesNodeLayoutGetHadOverflow(root));
}

TEST_F(PilatesTest_HadOverflowTests, hadOverflow_gets_reset_if_not_logger_valid) {
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child0, 80);
  PilatesNodeStyleSetHeight(child0, 40);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeBottom, 10);
  PilatesNodeInsertChild(root, child0, 0);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1, 80);
  PilatesNodeStyleSetHeight(child1, 40);
  PilatesNodeStyleSetMargin(child1, PilatesEdgeBottom, 5);
  PilatesNodeInsertChild(root, child1, 1);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_TRUE(PilatesNodeLayoutGetHadOverflow(root));

  PilatesNodeStyleSetFlexShrink(child1, 1);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_FALSE(PilatesNodeLayoutGetHadOverflow(root));
}

TEST_F(PilatesTest_HadOverflowTests, spacing_overflow_in_nested_nodes) {
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child0, 80);
  PilatesNodeStyleSetHeight(child0, 40);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeTop, 10);
  PilatesNodeStyleSetMargin(child0, PilatesEdgeBottom, 10);
  PilatesNodeInsertChild(root, child0, 0);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1, 80);
  PilatesNodeStyleSetHeight(child1, 40);
  PilatesNodeInsertChild(root, child1, 1);
  const PilatesNodeRef child1_1 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(child1_1, 80);
  PilatesNodeStyleSetHeight(child1_1, 40);
  PilatesNodeStyleSetMargin(child1_1, PilatesEdgeBottom, 5);
  PilatesNodeInsertChild(child1, child1_1, 0);

  PilatesNodeCalculateLayout(root, 200, 100, PilatesDirectionLTR);

  ASSERT_TRUE(PilatesNodeLayoutGetHadOverflow(root));
}
