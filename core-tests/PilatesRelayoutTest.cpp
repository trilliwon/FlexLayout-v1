/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>

TEST(PilatesTest, dont_cache_computed_flex_basis_between_layouts) {
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetExperimentalFeatureEnabled(config, PilatesExperimentalFeatureWebFlexBasis, true);

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeightPercent(root, 100);
  PilatesNodeStyleSetWidthPercent(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetFlexBasisPercent(root_child0, 100);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, 100, PilatesUndefined, PilatesDirectionLTR);
  PilatesNodeCalculateLayout(root, 100, 100, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(100, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}

TEST(PilatesTest, recalculate_resolvedDimonsion_onchange) {
  const PilatesNodeRef root = PilatesNodeNew();

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetMinHeight(root_child0, 10);
  PilatesNodeStyleSetMaxHeight(root_child0, 10);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);
  ASSERT_FLOAT_EQ(10, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeStyleSetMinHeight(root_child0, PilatesUndefined);
  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_FLOAT_EQ(0, PilatesNodeLayoutGetHeight(root_child0));

  PilatesNodeFreeRecursive(root);
}
