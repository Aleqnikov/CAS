#include <gtest/gtest.h>
#include "core/realization/Integer/Z.h"

using namespace Int;

// Z1 - Abs
TEST(IntegerAbs1, Basic) {
    Z pos(Natural({3, 2, 1}), false);  // 123
    Z neg(Natural({3, 2, 1}), true);   // -123
    EXPECT_EQ(Z::abs(pos).toString(), "123");
    EXPECT_EQ(Z::abs(neg).toString(), "123");
}



// Z3 - Negate (унарный минус)
TEST(IntegerNegate1, Basic) {
    Z pos(Natural({3, 2, 1}), false);  // 123
    Z neg(Natural({3, 2, 1}), true);   // -123
    Z zero(Natural({0}), false);       // 0
    EXPECT_EQ(Z(Neg::execute(pos.get())).toString(), "-123");
    EXPECT_EQ(Z(Neg::execute(neg.get())).toString(), "123");
    EXPECT_EQ(Z(Neg::execute(zero.get())).toString(), "0");
}

// Z6 - Add (сложение)
TEST(IntegerAdd1, PositivePositive) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({0, 5}), false);     // 50
    EXPECT_EQ((a + b).toString(), "150");
}

TEST(IntegerAdd2, NegativeNegative) {
    Z a(Natural({0, 0, 1}), true);   // -100
    Z b(Natural({0, 5}), true);      // -50
    EXPECT_EQ((a + b).toString(), "-150");
}

TEST(IntegerAdd3, PositiveNegative) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({0, 3}), true);      // -30
    EXPECT_EQ((a + b).toString(), "70");
}

TEST(IntegerAdd4, ResultZero) {
    Z a(Natural({0, 5}), false);     // 50
    Z b(Natural({0, 5}), true);      // -50
    EXPECT_EQ((a + b).toString(), "0");
}

// Z7 - Sub (вычитание)
TEST(IntegerSub1, Basic) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({0, 3}), false);     // 30
    EXPECT_EQ((a - b).toString(), "70");
}

TEST(IntegerSub2, ResultNegative) {
    Z a(Natural({0, 3}), false);     // 30
    Z b(Natural({0, 0, 1}), false);  // 100
    EXPECT_EQ((a - b).toString(), "-70");
}

// Z8 - Mul (умножение)
TEST(IntegerMul1, PositivePositive) {
    Z a(Natural({2, 1}), false);     // 12
    Z b(Natural({5}), false);        // 5
    EXPECT_EQ((a * b).toString(), "60");
}

TEST(IntegerMul2, PositiveNegative) {
    Z a(Natural({2, 1}), false);     // 12
    Z b(Natural({5}), true);         // -5
    EXPECT_EQ((a * b).toString(), "-60");
}

TEST(IntegerMul3, NegativeNegative) {
    Z a(Natural({2, 1}), true);      // -12
    Z b(Natural({5}), true);         // -5
    EXPECT_EQ((a * b).toString(), "60");
}

TEST(IntegerMul4, WithZero) {
    Z a(Natural({3, 2, 1}), false);  // 123
    Z zero(Natural({0}), false);     // 0
    EXPECT_EQ((a * zero).toString(), "0");
}

// Z9 - Div (деление)
TEST(IntegerDiv1, PositivePositive) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({3, 2}), false);     // 23
    EXPECT_EQ((a / b).toString(), "4");
}

TEST(IntegerDiv2, PositiveNegative) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({3, 2}), true);      // -23
    EXPECT_EQ((a / b).toString(), "-4");
}

TEST(IntegerDiv3, ThrowsOnZero) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z zero(Natural({0}), false);     // 0
    EXPECT_THROW(a / zero, UniversalStringException);
}

// Z10 - Rem (остаток)
TEST(IntegerRem1, Basic) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z b(Natural({3, 2}), false);     // 23
    EXPECT_EQ((a % b).toString(), "8");
}

TEST(IntegerRem2, ThrowsOnZero) {
    Z a(Natural({0, 0, 1}), false);  // 100
    Z zero(Natural({0}), false);     // 0
    EXPECT_THROW(a % zero, UniversalStringException);
}