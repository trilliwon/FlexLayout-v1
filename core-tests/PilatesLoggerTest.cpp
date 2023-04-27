/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <stdarg.h>
#include <pilates/Pilates.h>

namespace {
char writeBuffer[4096];
int _unmanagedLogger(const PilatesConfigRef config,
                     const PilatesNodeRef node,
                     PilatesLogLevel level,
                     const char *format,
                     va_list args) {
  return vsnprintf(writeBuffer + strlen(writeBuffer),
                   sizeof(writeBuffer) - strlen(writeBuffer),
                   format,
                   args);
}
}

TEST(PilatesTest, logger_default_node_should_print_no_style_info) {
  writeBuffer[0] = '\0';
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetLogger(config, _unmanagedLogger);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeCalculateLayout(root, PilatesUnitUndefined, PilatesUnitUndefined, PilatesDirectionLTR);
  PilatesNodePrint(root,
              (PilatesPrintOptions)(PilatesPrintOptionsLayout | PilatesPrintOptionsChildren |
                               PilatesPrintOptionsStyle));
  PilatesConfigSetLogger(config, NULL);
  PilatesNodeFree(root);

  const char *expected = "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" ></div>";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(PilatesTest, logger_node_with_percentage_absolute_position_and_margin) {
  writeBuffer[0] = '\0';
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetLogger(config, _unmanagedLogger);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  PilatesNodeStyleSetPositionType(root, PilatesPositionTypeAbsolute);
  PilatesNodeStyleSetWidthPercent(root, 50);
  PilatesNodeStyleSetHeightPercent(root, 75);
  PilatesNodeStyleSetFlex(root, 1);
  PilatesNodeStyleSetMargin(root, PilatesEdgeRight, 10);
  PilatesNodeStyleSetMarginAuto(root, PilatesEdgeLeft);
  PilatesNodeCalculateLayout(root, PilatesUnitUndefined, PilatesUnitUndefined, PilatesDirectionLTR);
  PilatesNodePrint(root,
              (PilatesPrintOptions)(PilatesPrintOptionsLayout | PilatesPrintOptionsChildren |
                               PilatesPrintOptionsStyle));
  PilatesConfigSetLogger(config, NULL);
  PilatesNodeFree(root);

  const char *expected = "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"flex: 1; "
                         "margin-left: auto; margin-right: 10px; width: 50%; height: 75%; "
                         "position: absolute; \" ></div>";
  ASSERT_STREQ(expected, writeBuffer);
}

TEST(PilatesTest, logger_node_with_children_should_print_indented) {
  writeBuffer[0] = '\0';
  const PilatesConfigRef config = PilatesConfigNew();
  PilatesConfigSetLogger(config, _unmanagedLogger);
  const PilatesNodeRef root = PilatesNodeNewWithConfig(config);
  const PilatesNodeRef child0 = PilatesNodeNewWithConfig(config);
  const PilatesNodeRef child1 = PilatesNodeNewWithConfig(config);
  PilatesNodeInsertChild(root, child0, 0);
  PilatesNodeInsertChild(root, child1, 1);
  PilatesNodeCalculateLayout(root, PilatesUnitUndefined, PilatesUnitUndefined, PilatesDirectionLTR);
  PilatesNodePrint(root,
              (PilatesPrintOptions)(PilatesPrintOptionsLayout | PilatesPrintOptionsChildren |
                               PilatesPrintOptionsStyle));
  PilatesConfigSetLogger(config, NULL);
  PilatesNodeFreeRecursive(root);

  const char *expected = "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" >\n  "
                         "<div layout=\"width: 0; height: 0; top: 0; left: 0;\" style=\"\" "
                         "></div>\n  <div layout=\"width: 0; height: 0; top: 0; left: 0;\" "
                         "style=\"\" ></div>\n</div>";
  ASSERT_STREQ(expected, writeBuffer);
}
