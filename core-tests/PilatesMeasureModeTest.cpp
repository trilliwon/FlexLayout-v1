/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <pilates/PilatesNode.h>
#include <pilates/Pilates.h>

struct _MeasureConstraint {
  float width;
  PilatesMeasureMode widthMode;
  float height;
  PilatesMeasureMode heightMode;
};

struct _MeasureConstraintList {
  uint32_t length;
  struct _MeasureConstraint *constraints;
};

static PilatesSize _measure(PilatesNodeRef node,
                       float width,
                       PilatesMeasureMode widthMode,
                       float height,
                       PilatesMeasureMode heightMode) {
  struct _MeasureConstraintList* constraintList =
      (struct _MeasureConstraintList*)node->getContext();
  struct _MeasureConstraint *constraints = constraintList->constraints;
  uint32_t currentIndex = constraintList->length;
  (&constraints[currentIndex])->width = width;
  (&constraints[currentIndex])->widthMode = widthMode;
  (&constraints[currentIndex])->height = height;
  (&constraints[currentIndex])->heightMode = heightMode;
  constraintList->length = currentIndex + 1;

  return PilatesSize{
      .width = widthMode == PilatesMeasureModeUndefined ? 10 : width,
      .height = heightMode == PilatesMeasureModeUndefined ? 10 : width,
  };
}

TEST(PilatesTest, exactly_measure_stretched_child_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  //  root_child0->setContext(&constraintList);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  //  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(PilatesMeasureModeExactly, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, exactly_measure_stretched_child_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  //  root_child0->setContext(&constraintList);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, at_most_main_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, at_most_cross_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, at_most_main_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, at_most_cross_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetWidth(root, 100);
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, flex_child) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(2, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].heightMode);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[1].height);
  ASSERT_EQ(PilatesMeasureModeExactly, constraintList.constraints[1].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, flex_child_with_flex_basis) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetHeight(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  PilatesNodeStyleSetFlexGrow(root_child0, 1);
  PilatesNodeStyleSetFlexBasis(root_child0, 0);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, overflow_scroll_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetOverflow(root, PilatesOverflowScroll);
  PilatesNodeStyleSetHeight(root, 100);
  PilatesNodeStyleSetWidth(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].widthMode);

  ASSERT_TRUE(PilatesFloatIsUndefined(constraintList.constraints[0].height));
  ASSERT_EQ(PilatesMeasureModeUndefined, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}

TEST(PilatesTest, overflow_scroll_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const PilatesNodeRef root = PilatesNodeNew();
  PilatesNodeStyleSetAlignItems(root, PilatesAlignFlexStart);
  PilatesNodeStyleSetFlexDirection(root, PilatesFlexDirectionRow);
  PilatesNodeStyleSetOverflow(root, PilatesOverflowScroll);
  PilatesNodeStyleSetHeight(root, 100);
  PilatesNodeStyleSetWidth(root, 100);

  const PilatesNodeRef root_child0 = PilatesNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  PilatesNodeInsertChild(root, root_child0, 0);

  PilatesNodeCalculateLayout(root, PilatesUndefined, PilatesUndefined, PilatesDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_TRUE(PilatesFloatIsUndefined(constraintList.constraints[0].width));
  ASSERT_EQ(PilatesMeasureModeUndefined, constraintList.constraints[0].widthMode);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(PilatesMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  PilatesNodeFreeRecursive(root);
}
