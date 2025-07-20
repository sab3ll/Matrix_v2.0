#include "s21_matrix_oop.hpp"

#include "gtest/gtest.h"

TEST(Constructors, Standart) {
  S21Matrix test_matrix_1;
  ASSERT_TRUE(test_matrix_1.GetCols() == 0);
  ASSERT_TRUE(test_matrix_1.GetRows() == 0);
}

TEST(Constructors, Parameterized_1) {
  S21Matrix test_matrix_1(2, 3);
  ASSERT_TRUE(test_matrix_1.GetCols() == 3);
  ASSERT_TRUE(test_matrix_1.GetRows() == 2);
}

TEST(Constructors, Parameterized_2) {
  ASSERT_NO_THROW(S21Matrix test_matrix_1(2, 3));
}

TEST(Constructors, Parameterized_3) {
  EXPECT_THROW(S21Matrix test_matrix_1(-2, 3), std::length_error);
}

TEST(Constructors, Copy_1) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2 = test_matrix_1;
  ASSERT_TRUE(test_matrix_2.GetCols() == 3);
  ASSERT_TRUE(test_matrix_2.GetRows() == 2);
}

TEST(Constructors, Move) {
  S21Matrix test_matrix_1(2, 3);
  ASSERT_NO_THROW(S21Matrix test_matrix_2 = std::move(test_matrix_1));
}

TEST(Overload, AccessElement_1) {
  S21Matrix test_matrix_1(2, 3);
  test_matrix_1(1, 1) = 5.0;
  ASSERT_NO_THROW(test_matrix_1(1, 1) = 5.0);
  ASSERT_TRUE(test_matrix_1(1, 1) == 5.0);
}

TEST(Overload, AccessElement_2) {
  S21Matrix test_matrix_1(2, 3);
  EXPECT_THROW((test_matrix_1(-1, 1) = 1), std::out_of_range);
}

TEST(Overload, AccessElementConst_1) {
  const S21Matrix test_matrix_1(2, 3);
  test_matrix_1(1, 1) = 5;
  ASSERT_NO_THROW(std::cout << test_matrix_1(1, 1) << std::endl);
  ASSERT_TRUE(test_matrix_1(1, 1) == 5.0);
}

TEST(Overload, AccessElementConst_2) {
  const S21Matrix test_matrix_1(2, 3);
  EXPECT_THROW((test_matrix_1(-1, 1) = 1), std::out_of_range);
}

TEST(Overload, Equality_1) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(2, 3);
  ASSERT_TRUE(test_matrix_1 == test_matrix_2);
}

TEST(Overload, Equality_2) {
  S21Matrix test_matrix_1(2, 3);
  test_matrix_1(1, 1) = 5.0;
  S21Matrix test_matrix_2(2, 3);
  ASSERT_FALSE(test_matrix_1 == test_matrix_2);
}

TEST(Overload, Equality_3) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 2);
  ASSERT_FALSE(test_matrix_1 == test_matrix_2);
}

TEST(Overload, Assignment_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = 5.0;

  test_matrix_1 = test_matrix_2;
  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Overload, Summation_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = 5.0;
  test_matrix_1 += test_matrix_2;
  ASSERT_TRUE(test_matrix_2.EqMatrix(test_matrix_3));
}

TEST(Overload, Summation_2) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = 5.0;
  EXPECT_THROW(test_matrix_1 += test_matrix_2, std::range_error);
}

TEST(Overload, Summation_3) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);
  S21Matrix test_matrix_4(3, 3);

  test_matrix_1(2, 2) = 5.0;
  test_matrix_2(2, 2) = 5.0;
  test_matrix_4(2, 2) = 5.0;

  test_matrix_3 = test_matrix_1 + test_matrix_2;
  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_4));
}

TEST(Overload, Summation_4) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);
  S21Matrix test_matrix_4(3, 3);

  test_matrix_1(1, 1) = 5.0;
  test_matrix_2(1, 1) = 5.0;
  test_matrix_4(1, 1) = 5.0;

  EXPECT_THROW(test_matrix_3 = test_matrix_1 + test_matrix_2, std::range_error);
}

TEST(Overload, Subtraction_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = -5.0;

  test_matrix_1 -= test_matrix_2;
  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Overload, Subtraction_2) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = -5.0;
  EXPECT_THROW(test_matrix_1 -= test_matrix_2, std::range_error);
}

TEST(Overload, Subtraction_3) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);
  S21Matrix test_matrix_4(3, 3);

  test_matrix_1(2, 2) = 5.0;
  test_matrix_2(2, 2) = 5.0;
  test_matrix_4(2, 2) = -5.0;

  test_matrix_3 = test_matrix_1 - test_matrix_2;
  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_4));
}

TEST(Overload, Subtraction_4) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);
  S21Matrix test_matrix_4(3, 3);

  test_matrix_1(1, 1) = 5.0;
  test_matrix_2(1, 1) = 5.0;
  test_matrix_4(1, 1) = -5.0;

  EXPECT_THROW(test_matrix_3 = test_matrix_1 - test_matrix_2, std::range_error);
}

TEST(Overload, multiplication_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);

  double num = 3.0;

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_1 *= num;
  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_2));
}

TEST(Overload, multiplication_2) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  double num = 3.0;

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_3 = test_matrix_1 * num;
  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Overload, MulMatrix_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);
  S21Matrix test_matrix_4(3, 3);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(0, 2) = 126;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;
  test_matrix_3(1, 2) = 288;
  test_matrix_3(2, 0) = 306;
  test_matrix_3(2, 1) = 378;
  test_matrix_3(2, 2) = 450;

  test_matrix_4 = test_matrix_1 * test_matrix_2;

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_4));
}

TEST(Overload, MulMatrix_2) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 2);
  S21Matrix test_matrix_3(2, 2);
  S21Matrix test_matrix_4(2, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;

  test_matrix_4 = test_matrix_1 * test_matrix_2;

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_4));
}

TEST(Overload, MulMatrix_3) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 2);
  S21Matrix test_matrix_3(2, 2);
  S21Matrix test_matrix_4(2, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  EXPECT_THROW(test_matrix_4 = test_matrix_1 * test_matrix_2, std::logic_error);
}

TEST(Overload, MulMatrix_4) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(0, 2) = 126;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;
  test_matrix_3(1, 2) = 288;
  test_matrix_3(2, 0) = 306;
  test_matrix_3(2, 1) = 378;
  test_matrix_3(2, 2) = 450;

  test_matrix_1 *= test_matrix_2;

  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Overload, MulMatrix_5) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 2);
  S21Matrix test_matrix_3(2, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;

  test_matrix_1 *= test_matrix_2;

  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Overload, MulMatrix_6) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  EXPECT_THROW(test_matrix_1 *= test_matrix_2, std::logic_error);
}

TEST(Operations, Equality_1) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(2, 3);
  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_2));
}

TEST(Operations, Equality_2) {
  S21Matrix test_matrix_1(2, 3);
  test_matrix_1(1, 1) = 5.0;
  S21Matrix test_matrix_2(2, 3);
  ASSERT_FALSE(test_matrix_1.EqMatrix(test_matrix_2));
}
TEST(Operations, Equality_3) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 3);
  ASSERT_FALSE(test_matrix_1.EqMatrix(test_matrix_2));
}

TEST(Operations, Summation_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = 5.0;

  test_matrix_1.SumMatrix(test_matrix_2);
  ASSERT_TRUE(test_matrix_2.EqMatrix(test_matrix_3));
}

TEST(Operations, Summation_2) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = 5.0;

  EXPECT_THROW(test_matrix_1.SumMatrix(test_matrix_2), std::range_error);
}

TEST(Operations, Subtraction_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = -5.0;

  test_matrix_1.SubMatrix(test_matrix_2);
  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Operations, Subtraction_2) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_2(2, 2) = 5.0;
  test_matrix_3(2, 2) = -5.0;

  EXPECT_THROW(test_matrix_1.SubMatrix(test_matrix_2), std::range_error);
}

TEST(Operations, MulNumber_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);

  double num = 3.0;

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_1.MulNumber(num);

  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_2));
}

TEST(Operations, MulMatrix_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = 9;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(1, 2) = 18;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;
  test_matrix_2(2, 2) = 27;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(0, 2) = 126;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;
  test_matrix_3(1, 2) = 288;
  test_matrix_3(2, 0) = 306;
  test_matrix_3(2, 1) = 378;
  test_matrix_3(2, 2) = 450;

  test_matrix_1.MulMatrix(test_matrix_2);

  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Operations, MulMatrix_2) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 2);
  S21Matrix test_matrix_3(2, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  test_matrix_3(0, 0) = 90;
  test_matrix_3(0, 1) = 108;
  test_matrix_3(1, 0) = 198;
  test_matrix_3(1, 1) = 243;

  test_matrix_1.MulMatrix(test_matrix_2);

  ASSERT_TRUE(test_matrix_1.EqMatrix(test_matrix_3));
}

TEST(Operations, MulMatrix_3) {
  S21Matrix test_matrix_1(2, 2);
  S21Matrix test_matrix_2(3, 2);
  S21Matrix test_matrix_3(2, 2);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;

  test_matrix_2(0, 0) = 3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(1, 0) = 12;
  test_matrix_2(1, 1) = 15;
  test_matrix_2(2, 0) = 21;
  test_matrix_2(2, 1) = 24;

  EXPECT_THROW(test_matrix_1.MulMatrix(test_matrix_2), std::logic_error);
}

TEST(Operations, Transpose_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = 1;
  test_matrix_2(0, 1) = 4;
  test_matrix_2(0, 2) = 7;
  test_matrix_2(1, 0) = 2;
  test_matrix_2(1, 1) = 5;
  test_matrix_2(1, 2) = 8;
  test_matrix_2(2, 0) = 3;
  test_matrix_2(2, 1) = 6;
  test_matrix_2(2, 2) = 9;

  test_matrix_3 = test_matrix_1.Transpose();

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Operations, Transpose_2) {
  S21Matrix test_matrix_1(1, 3);
  S21Matrix test_matrix_2(3, 1);
  S21Matrix test_matrix_3(3, 1);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;

  test_matrix_2(0, 0) = 1;
  test_matrix_2(1, 0) = 2;
  test_matrix_2(2, 0) = 3;

  test_matrix_3 = test_matrix_1.Transpose();

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Operations, Determinant_1) {
  S21Matrix test_matrix_1(3, 3);
  double test_determinant = 0.0;

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_determinant = test_matrix_1.Determinant();

  ASSERT_TRUE(test_determinant == 0);
}

TEST(Operations, Determinant_2) {
  S21Matrix test_matrix_1(1, 1);
  double test_determinant = 0.0;

  test_matrix_1(0, 0) = 5;

  test_determinant = test_matrix_1.Determinant();

  ASSERT_TRUE(test_determinant == 5);
}

TEST(Operations, Determinant_3) {
  S21Matrix test_matrix_1(2, 3);
  double test_determinant = 0.0;

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  std::cout << test_determinant << std::endl;
  EXPECT_THROW(test_determinant = test_matrix_1.Determinant(),
               std::logic_error);
}

TEST(Operations, CalcComplements_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = 3;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;
  test_matrix_1(2, 0) = 7;
  test_matrix_1(2, 1) = 8;
  test_matrix_1(2, 2) = 9;

  test_matrix_2(0, 0) = -3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = -3;
  test_matrix_2(1, 0) = 6;
  test_matrix_2(1, 1) = 6;
  test_matrix_2(1, 2) = -10;
  test_matrix_2(2, 0) = -3;
  test_matrix_2(2, 1) = -6;
  test_matrix_2(2, 2) = 7;

  test_matrix_3 = test_matrix_1.CalcComplements();

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Operations, CalcComplements_2) {
  S21Matrix test_matrix_1(1, 1);
  S21Matrix test_matrix_2(1, 1);
  S21Matrix test_matrix_3(1, 1);

  test_matrix_1(0, 0) = 1;
  test_matrix_2(0, 0) = 0;

  test_matrix_3 = test_matrix_1.CalcComplements();

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Operations, CalcComplements_3) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = 1;
  test_matrix_1(0, 1) = 2;
  test_matrix_1(0, 2) = 3;
  test_matrix_1(1, 0) = 4;
  test_matrix_1(1, 1) = 5;
  test_matrix_1(1, 2) = 6;

  test_matrix_2(0, 0) = -3;
  test_matrix_2(0, 1) = 6;
  test_matrix_2(0, 2) = -3;
  test_matrix_2(1, 0) = 6;
  test_matrix_2(1, 1) = 6;
  test_matrix_2(1, 2) = -10;
  test_matrix_2(2, 0) = -3;
  test_matrix_2(2, 1) = -6;
  test_matrix_2(2, 2) = 7;

  EXPECT_THROW(test_matrix_3 = test_matrix_1.CalcComplements(),
               std::logic_error);
}

TEST(Operations, InverseMatrix_1) {
  S21Matrix test_matrix_1(3, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = -9;
  test_matrix_1(0, 1) = -7;
  test_matrix_1(0, 2) = 5;
  test_matrix_1(1, 0) = 8;
  test_matrix_1(1, 1) = 9;
  test_matrix_1(1, 2) = -8;
  test_matrix_1(2, 0) = -6;
  test_matrix_1(2, 1) = -6;
  test_matrix_1(2, 2) = 5;

  test_matrix_2(0, 0) = -3;
  test_matrix_2(0, 1) = 5;
  test_matrix_2(0, 2) = 11;
  test_matrix_2(1, 0) = 8;
  test_matrix_2(1, 1) = -15;
  test_matrix_2(1, 2) = -32;
  test_matrix_2(2, 0) = 6;
  test_matrix_2(2, 1) = -12;
  test_matrix_2(2, 2) = -25;

  test_matrix_3 = test_matrix_1.InverseMatrix();

  ASSERT_TRUE(test_matrix_3.EqMatrix(test_matrix_2));
}

TEST(Operations, InverseMatrix_2) {
  S21Matrix test_matrix_1(2, 3);
  S21Matrix test_matrix_2(3, 3);
  S21Matrix test_matrix_3(3, 3);

  test_matrix_1(0, 0) = -9;
  test_matrix_1(0, 1) = -7;
  test_matrix_1(0, 2) = 5;
  test_matrix_1(1, 0) = 8;
  test_matrix_1(1, 1) = 9;
  test_matrix_1(1, 2) = -8;

  test_matrix_2(0, 0) = -3;
  test_matrix_2(0, 1) = 5;
  test_matrix_2(0, 2) = 11;
  test_matrix_2(1, 0) = 8;
  test_matrix_2(1, 1) = -15;
  test_matrix_2(1, 2) = -32;
  test_matrix_2(2, 0) = 6;
  test_matrix_2(2, 1) = -12;
  test_matrix_2(2, 2) = -25;

  EXPECT_THROW(test_matrix_3 = test_matrix_1.InverseMatrix(), std::logic_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
