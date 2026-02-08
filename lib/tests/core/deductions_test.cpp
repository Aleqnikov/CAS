#include <gtest/gtest.h>
#include "core/realization/deductionclass/pZ.h"

// Хелпер для создания Z
Z makeZ(int value) {
    bool neg = value < 0;
    value = neg ? -value : value;
    
    std::vector<uint8_t> digits;
    if (value == 0) {
        digits.push_back(0);
    } else {
        while (value > 0) {
            digits.push_back(value % 10);
            value /= 10;
        }
    }
    
    return Z(Natural(digits), neg);
}

// ZP1 - Конструктор и toString
TEST(Zp1, Constructor) {
    Zp<5> a(makeZ(3));
    EXPECT_EQ(a.toString(), "3");
}

TEST(Zp2, ModuloReduction) {
    Zp<5> a(makeZ(7));  // 7 mod 5 = 2
    EXPECT_EQ(a.toString(), "2");
}

TEST(Zp3, NegativeModulo) {
    Zp<7> a(makeZ(-3));  // -3 mod 7 = 4
    EXPECT_EQ(a.toString(), "4");
}

// ZP2 - Сложение
TEST(ZpAdd1, Basic) {
    Zp<5> a(makeZ(2));
    Zp<5> b(makeZ(3));
    auto c = a + b;  // 5 mod 5 = 0
    EXPECT_EQ(c.toString(), "0");
}

TEST(ZpAdd2, WithOverflow) {
    Zp<7> a(makeZ(5));
    Zp<7> b(makeZ(6));
    auto c = a + b;  // 11 mod 7 = 4
    EXPECT_EQ(c.toString(), "4");
}

TEST(ZpAdd3, WithZero) {
    Zp<5> a(makeZ(3));
    Zp<5> zero = Zp<5>::zero();
    auto c = a + zero;
    EXPECT_EQ(c.toString(), "3");
}

// ZP3 - Вычитание
TEST(ZpSub1, Basic) {
    Zp<5> a(makeZ(3));
    Zp<5> b(makeZ(1));
    auto c = a - b;  // 2
    EXPECT_EQ(c.toString(), "2");
}

TEST(ZpSub2, WithUnderflow) {
    Zp<7> a(makeZ(2));
    Zp<7> b(makeZ(5));
    auto c = a - b;  // -3 mod 7 = 4
    EXPECT_EQ(c.toString(), "4");
}

TEST(ZpSub3, ToZero) {
    Zp<5> a(makeZ(3));
    auto c = a - a;
    EXPECT_EQ(c.toString(), "0");
}

// ZP4 - Умножение
TEST(ZpMul1, Basic) {
    Zp<5> a(makeZ(2));
    Zp<5> b(makeZ(3));
    auto c = a * b;  // 6 mod 5 = 1
    EXPECT_EQ(c.toString(), "1");
}

TEST(ZpMul2, WithOverflow) {
    Zp<7> a(makeZ(4));
    Zp<7> b(makeZ(5));
    auto c = a * b;  // 20 mod 7 = 6
    EXPECT_EQ(c.toString(), "6");
}

TEST(ZpMul3, WithZero) {
    Zp<5> a(makeZ(3));
    Zp<5> zero = Zp<5>::zero();
    auto c = a * zero;
    EXPECT_EQ(c.toString(), "0");
}

TEST(ZpMul4, WithIdentity) {
    Zp<5> a(makeZ(3));
    Zp<5> one = Zp<5>::identity();
    auto c = a * one;
    EXPECT_EQ(c.toString(), "3");
}

// ZP5 - Деление (обратный элемент)
TEST(ZpDiv1, Basic) {
    Zp<5> a(makeZ(3));
    Zp<5> b(makeZ(2));
    auto c = a / b;  // 3 * 2^(-1) mod 5 = 3 * 3 = 9 mod 5 = 4
    EXPECT_EQ(c.toString(), "4");
}

TEST(ZpDiv2, DivideByOne) {
    Zp<7> a(makeZ(5));
    Zp<7> one = Zp<7>::identity();
    auto c = a / one;
    EXPECT_EQ(c.toString(), "5");
}

TEST(ZpDiv3, SelfDivision) {
    Zp<5> a(makeZ(3));
    auto c = a / a;  // Должно быть 1
    EXPECT_EQ(c.toString(), "1");
}

TEST(ZpDiv4, ThrowsOnZero) {
    Zp<5> a(makeZ(3));
    Zp<5> zero = Zp<5>::zero();
    EXPECT_THROW(a / zero, UniversalStringException);
}

// ZP6 - Сравнение
TEST(ZpCmp1, Equal) {
    Zp<5> a(makeZ(3));
    Zp<5> b(makeZ(3));
    EXPECT_TRUE(a == b);
}

TEST(ZpCmp2, EqualAfterReduction) {
    Zp<5> a(makeZ(3));
    Zp<5> b(makeZ(8));  // 8 mod 5 = 3
    EXPECT_TRUE(a == b);
}

TEST(ZpCmp3, NotEqual) {
    Zp<5> a(makeZ(2));
    Zp<5> b(makeZ(3));
    EXPECT_FALSE(a == b);
}

// ZP7 - Статические методы
TEST(ZpStatic1, Zero) {
    auto zero = Zp<5>::zero();
    EXPECT_EQ(zero.toString(), "0");
}

TEST(ZpStatic2, Identity) {
    auto one = Zp<7>::identity();
    EXPECT_EQ(one.toString(), "1");
}

// ZP8 - Проверка что это поле
TEST(ZpField1, IsField) {
    // Компиляция этого теста доказывает что Zp<5> — поле
    static_assert(Field<Zp<5>, Zp<5>::AdditionOp, Zp<5>::MultiplicationOp>);
    EXPECT_TRUE(true);
}

TEST(ZpField2, MultipleFields) {
    static_assert(Field<Zp<2>, Zp<2>::AdditionOp, Zp<2>::MultiplicationOp>);
    static_assert(Field<Zp<3>, Zp<3>::AdditionOp, Zp<3>::MultiplicationOp>);
    static_assert(Field<Zp<7>, Zp<7>::AdditionOp, Zp<7>::MultiplicationOp>);
    EXPECT_TRUE(true);
}

// ZP9 - Комплексные операции
TEST(ZpComplex1, ChainedOperations) {
    Zp<5> a(makeZ(2));
    Zp<5> b(makeZ(3));
    Zp<5> c(makeZ(4));
    
    auto result = (a + b) * c;  // (2+3)*4 = 5*4 = 20 mod 5 = 0
    EXPECT_EQ(result.toString(), "0");
}

TEST(ZpComplex2, DivisionAndMultiplication) {
    Zp<7> a(makeZ(6));
    Zp<7> b(makeZ(2));
    
    auto result = (a / b) * b;  // Должно вернуть a
    EXPECT_EQ(result.toString(), "6");
}

// ZP10 - Унарный минус
TEST(ZpNeg1, Basic) {
    Zp<5> a(makeZ(3));
    auto neg_a = -a;  // -3 mod 5 = 2
    EXPECT_EQ(neg_a.toString(), "2");
}

TEST(ZpNeg2, DoubleNegation) {
    Zp<7> a(makeZ(4));
    auto result = -(-a);
    EXPECT_EQ(result.toString(), "4");
}

TEST(ZpNeg3, ZeroNegation) {
    auto zero = Zp<5>::zero();
    auto neg_zero = -zero;
    EXPECT_EQ(neg_zero.toString(), "0");
}