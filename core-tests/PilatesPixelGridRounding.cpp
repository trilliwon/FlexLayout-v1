#include <gtest/gtest.h>
#include <pilates/Pilates.h>

// This test scrutinize next behaviours:
// - pixel grid snapping in 1e4..0 coordinate range
// - ability to layout nodes with smallest possible dimensions (one pixel separators)
// - providing text node layout with bounds strictly larger than sized

TEST(PilatesTest, pixel_grid_rounding_table) {
  const float kPointScale = 3;

  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetPointScaleFactor(config, kPointScale);

  const float kSeparatorHeight = 1 / kPointScale;
  const float kCellContentHeight = 44.5;
  const int kCellsCount = 100;

  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);

  int subnodesCount = 0;

  for (int i = 0; i < kCellsCount; i++) {
    const PilatesNodeRef separator = PilatesNodeNewWithConfig(config);
    PilatesNodeStyleSetHeight(separator, kSeparatorHeight);
    PilatesNodeInsertChild(root, separator, subnodesCount++);

    const PilatesNodeRef cell = PilatesNodeNewWithConfig(config);
    PilatesNodeSetNodeType(cell, PilatesNodeTypeText);
    PilatesNodeStyleSetHeight(cell, kCellContentHeight);
    PilatesNodeInsertChild(root, cell, subnodesCount++);
  }

  const PilatesNodeRef separator = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetHeight(separator, kSeparatorHeight);
  PilatesNodeInsertChild(root, separator, subnodesCount++);

  PilatesNodeCalculateLayout(root, 375, PilatesUndefined, PilatesDirectionLTR);

  EXPECT_LE(kCellsCount * (kSeparatorHeight + kCellContentHeight) + kSeparatorHeight, PilatesNodeLayoutGetHeight(root));
  EXPECT_FLOAT_EQ(375, PilatesNodeLayoutGetWidth(root));

  for (int i = 0; i < PilatesNodeGetChildCount(root); i++) {
    const PilatesNodeRef child = PilatesNodeGetChild(root, i);
    const float childHeight = PilatesNodeLayoutGetHeight(child);

    if (PilatesNodeGetNodeType(child) == PilatesNodeTypeText) {
      EXPECT_GT(childHeight, kCellContentHeight);
    } else {
      EXPECT_GT(childHeight, 0);
    }
  }

  PilatesNodeFreeRecursive(root);

  PilatesConfigFree(config);
}
