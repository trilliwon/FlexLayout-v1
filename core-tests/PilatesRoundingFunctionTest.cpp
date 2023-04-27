/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/Pilates.h>
#include <pilates/Pilates-internal.h>

TEST(PilatesTest, rounding_value) {
  // Test that whole numbers are rounded to whole despite ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(6.000001, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(6.000001, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(6.000001, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(5.999999, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(5.999999, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(5.999999, 2.0, false, true));

  // Test that numbers with fraction are rounded correctly accounting for ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(6.1, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.5, PilatesRoundValueToPixelGrid(6.1, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(6.1, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(5.9, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, PilatesRoundValueToPixelGrid(5.9, 2.0, true, false));
  ASSERT_FLOAT_EQ(5.5, PilatesRoundValueToPixelGrid(5.9, 2.0, false, true));

  // Are we able to treat value as rounded for reasonably large number?
  ASSERT_FLOAT_EQ(527.6666666, PilatesRoundValueToPixelGrid(527.666, 3.0, false, true));
  ASSERT_FLOAT_EQ(527.6666666, PilatesRoundValueToPixelGrid(527.666, 3.0, true, false));
  ASSERT_FLOAT_EQ(527.6666666, PilatesRoundValueToPixelGrid(527.666, 3.0, true, true));
}
