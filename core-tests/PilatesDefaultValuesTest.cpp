/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, assert_default_values) {
  const PilatesNodeRef root = PilatesNodeNew();

  ASSERT_EQ(0, PilatesNodeGetChildCount(root));
  ASSERT_EQ(NULL, PilatesNodeGetChild(root, 1));

  ASSERT_EQ(PilatesDirectionInherit, PilatesNodeStyleGetDirection(root));
  ASSERT_EQ(PilatesFlexDirectionColumn, PilatesNodeStyleGetFlexDirection(root));
  ASSERT_EQ(PilatesJustifyFlexStart, PilatesNodeStyleGetJustifyContent(root));
  ASSERT_EQ(PilatesAlignFlexStart, PilatesNodeStyleGetAlignContent(root));
  ASSERT_EQ(PilatesAlignStretch, PilatesNodeStyleGetAlignItems(root));
  ASSERT_EQ(PilatesAlignAuto, PilatesNodeStyleGetAlignSelf(root));
  ASSERT_EQ(PilatesPositionTypeRelative, PilatesNodeStyleGetPositionType(root));
  ASSERT_EQ(PilatesWrapNoWrap, PilatesNodeStyleGetFlexWrap(root));
  ASSERT_EQ(PilatesOverflowVisible, PilatesNodeStyleGetOverflow(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeStyleGetFlexGrow(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeStyleGetFlexShrink(root));
  ASSERT_EQ(PilatesNodeStyleGetFlexBasis(root).unit, PilatesUnitAuto);

  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeLeft).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeTop).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeRight).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeBottom).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeStart).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPosition(root, PilatesEdgeEnd).unit, PilatesUnitUndefined);

  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeLeft).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeTop).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeRight).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeBottom).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeStart).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMargin(root, PilatesEdgeEnd).unit, PilatesUnitUndefined);

  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeLeft).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeTop).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeRight).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeBottom).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeStart).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetPadding(root, PilatesEdgeEnd).unit, PilatesUnitUndefined);

  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeLeft)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeTop)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeRight)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeBottom)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeStart)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeStyleGetBorder(root, PilatesEdgeEnd)));

  ASSERT_EQ(PilatesNodeStyleGetWidth(root).unit, PilatesUnitAuto);
  ASSERT_EQ(PilatesNodeStyleGetHeight(root).unit, PilatesUnitAuto);
  ASSERT_EQ(PilatesNodeStyleGetMinWidth(root).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMinHeight(root).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMaxWidth(root).unit, PilatesUnitUndefined);
  ASSERT_EQ(PilatesNodeStyleGetMaxHeight(root).unit, PilatesUnitUndefined);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetBottom(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeLeft));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeTop));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeRight));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetMargin(root, PilatesEdgeBottom));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetPadding(root, PilatesEdgeLeft));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetPadding(root, PilatesEdgeTop));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetPadding(root, PilatesEdgeRight));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetPadding(root, PilatesEdgeBottom));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetBorder(root, PilatesEdgeLeft));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetBorder(root, PilatesEdgeTop));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetBorder(root, PilatesEdgeRight));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetBorder(root, PilatesEdgeBottom));

  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeLayoutGetWidth(root)));
  ASSERT_TRUE(PilatesFloatIsUndefined(PilatesNodeLayoutGetHeight(root)));
  ASSERT_EQ(PilatesDirectionInherit, PilatesNodeLayoutGetDirection(root));

  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, assert_webdefault_values) {
  PilatesConfig *config = PilatesConfigNew();
  PilatesConfigSetUseWebDefaults(config, true);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  ASSERT_EQ(PilatesFlexDirectionRow, PilatesNodeStyleGetFlexDirection(root));
  ASSERT_EQ(PilatesAlignStretch, PilatesNodeStyleGetAlignContent(root));
  ASSERT_FLOAT_EQ(1.0f, PilatesNodeStyleGetFlexShrink(root));

  PilatesNodeFreeRecursive(root);
  PilatesConfigFree(config);
}

TEST(PilatesTest, assert_webdefault_values_reset) {
  PilatesConfig *config = PilatesConfigNew();
  PilatesConfigSetUseWebDefaults(config, true);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeReset(root);

  ASSERT_EQ(PilatesFlexDirectionRow, PilatesNodeStyleGetFlexDirection(root));
  ASSERT_EQ(PilatesAlignStretch, PilatesNodeStyleGetAlignContent(root));
  ASSERT_FLOAT_EQ(1.0f, PilatesNodeStyleGetFlexShrink(root));

  PilatesNodeFreeRecursive(root);
  PilatesConfigFree(config);
}

TEST(PilatesTest, assert_legacy_stretch_behaviour) {
  PilatesConfig *config = PilatesConfigNew();
  PilatesConfigSetUseLegacyStretchBehaviour(config, true);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetWidth(root, 500);
  PilatesNodeStyleSetHeight(root, 500);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetAlignItems(root_child0, PilatesAlignFlexStart);
  PilatesNodeInsertChild(root, root_child0, 0);

  const PilatesNodeRef root_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root_child0_child0, 1);
  PilatesNodeInsertChild(root_child0, root_child0_child0, 0);

  const PilatesNodeRef root_child0_child0_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexGrow(root_child0_child0_child0, 1);
  PilatesNodeStyleSetFlexShrink(root_child0_child0_child0, 1);
  PilatesNodeInsertChild(root_child0_child0, root_child0_child0_child0, 0);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetLeft(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetTop(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetWidth(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(500, PilatesNodeLayoutGetHeight(root_child0_child0_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}
