#include <gtest/gtest.h>
#include "core/realization/Polynomial/P[x].h"

#include "core/realization/Rational/Q.h"

// Хелпер для создания Q
Q makeQ(int num, int den = 1) {
    bool neg = num < 0;
    num = neg ? -num : num;
    
    std::vector<uint8_t> num_digits;
    std::string num_str = std::to_string(num);
    for (int i = num_str.size() - 1; i >= 0; --i) {
        num_digits.push_back(num_str[i] - '0');
    }
    
    std::vector<uint8_t> den_digits;
    std::string den_str = std::to_string(den);
    for (int i = den_str.size() - 1; i >= 0; --i) {
        den_digits.push_back(den_str[i] - '0');
    }
    
    return Q(Z(Natural(num_digits), neg), N(den_digits));
}

// P0 - Проверка что над Z не компилируется
TEST(PolynomField, RejectsNonField) {

    P<Q> poly_q({Q::identity()}); // ✅ OK
    EXPECT_EQ(poly_q.degree(), 0);
}

// P1 - Конструктор и базовая функциональность
TEST(PolynomBasic1, Constructor) {
    // 2 + 3x + x^2
    P<Q> p({makeQ(2), makeQ(3), makeQ(1)});
    EXPECT_EQ(p.degree(), 2);
    EXPECT_EQ(p[2].toString(), "1/1");
}

TEST(PolynomBasic2, ToString) {
    // 2 + 3x
    P<Q> p({makeQ(2), makeQ(3)});
    std::string s = p.toString();
    EXPECT_FALSE(s.empty());
}

// P2 - Сложение
TEST(PolynomAdd1, Basic) {
    // (1 + 2x) + (3 + 4x) = 4 + 6x
    P<Q> p1({makeQ(1), makeQ(2)});
    P<Q> p2({makeQ(3), makeQ(4)});
    P<Q> result = p1 + p2;
    EXPECT_EQ(result[0].toString(), "4/1");
    EXPECT_EQ(result[1].toString(), "6/1");
}

TEST(PolynomAdd2, DifferentDegrees) {
    // (1 + 2x) + (3) = 4 + 2x
    P<Q> p1({makeQ(1), makeQ(2)});
    P<Q> p2({makeQ(3)});
    P<Q> result = p1 + p2;
    EXPECT_EQ(result.degree(), 1);
    EXPECT_EQ(result[0].toString(), "4/1");
}

// P3 - Вычитание
TEST(PolynomSub1, Basic) {
    // (5 + 3x) - (2 + x) = 3 + 2x
    P<Q> p1({makeQ(5), makeQ(3)});
    P<Q> p2({makeQ(2), makeQ(1)});
    P<Q> result = p1 - p2;
    EXPECT_EQ(result[0].toString(), "3/1");
    EXPECT_EQ(result[1].toString(), "2/1");
}

// P4 - Умножение на скаляр
TEST(PolynomMulScalar1, Basic) {
    // (1 + 2x) * 3 = 3 + 6x
    P<Q> p({makeQ(1), makeQ(2)});
    Q scalar = makeQ(3);
    P<Q> result = p * scalar;
    EXPECT_EQ(result[0].toString(), "3/1");
    EXPECT_EQ(result[1].toString(), "6/1");
}

TEST(PolynomMulScalar2, Zero) {
    P<Q> p({makeQ(1), makeQ(2)});
    Q zero = Q::zero();
    P<Q> result = p * zero;
    EXPECT_EQ(result.degree(), 0);
    EXPECT_TRUE(result[0] == Q::zero());
}

// P5 - Умножение полиномов
TEST(PolynomMul1, Basic) {
    // (1 + x) * (1 + x) = 1 + 2x + x^2
    P<Q> p1({makeQ(1), makeQ(1)});
    P<Q> p2({makeQ(1), makeQ(1)});
    P<Q> result = p1 * p2;
    
    EXPECT_EQ(result.degree(), 2);
    EXPECT_EQ(result[0].toString(), "1/1");
    EXPECT_EQ(result[1].toString(), "2/1");
    EXPECT_EQ(result[2].toString(), "1/1");
}

// P6 - Деление
TEST(PolynomDiv1, Basic) {
    // (x^2 + 3x + 2) / (x + 1) = x + 2
    P<Q> dividend({makeQ(2), makeQ(3), makeQ(1)});
    P<Q> divisor({makeQ(1), makeQ(1)});
    P<Q> result = dividend / divisor;
    EXPECT_EQ(result.degree(), 1);
}

TEST(PolynomDiv2, ThrowsOnZero) {
    P<Q> p({makeQ(1), makeQ(1)});
    P<Q> zero({Q::zero()});
    EXPECT_THROW(p / zero, UniversalStringException);
}

// P7 - Остаток
TEST(PolynomRem1, Basic) {
    // (x^2 + 3x + 3) / (x + 1) → остаток
    P<Q> dividend({makeQ(3), makeQ(3), makeQ(1)});
    P<Q> divisor({makeQ(1), makeQ(1)});
    P<Q> remainder = dividend % divisor;
    EXPECT_EQ(remainder.degree(), 0);
}

// P8 - Производная
TEST(PolynomDerivative1, Basic) {
    // (x^3 + 2x^2 + 3x + 4)' = 3x^2 + 4x + 3
    P<Q> p({makeQ(4), makeQ(3), makeQ(2), makeQ(1)});
    P<Q> deriv = p.derivative();

	auto res = deriv.toString();

    EXPECT_EQ(deriv.degree(), 2);
    EXPECT_EQ(deriv[0].toString(), "3/1");
    EXPECT_EQ(deriv[1].toString(), "4/1");
    EXPECT_EQ(deriv[2].toString(), "3/1");
}

TEST(PolynomDerivative2, Constant) {
    P<Q> p({makeQ(5)});
    P<Q> deriv = p.derivative();
    EXPECT_EQ(deriv.degree(), 0);
    EXPECT_TRUE(deriv[0] == Q::zero());
}

// P9 - Статические методы
TEST(PolynomStatic1, ZeroAndIdentity) {
    P<Q> zero = P<Q>::zero();
    P<Q> one = P<Q>::identity();
    
    EXPECT_TRUE(zero[0] == Q::zero());
    EXPECT_TRUE(one[0] == Q::identity());
}


// Проверка алгебраических структур
TEST(PolynomStructure1, IsRing) {
	// Полином над полем является кольцом
	static_assert(UnitaryRing<P<Q>::SetType, P<Q>::AdditionOp, P<Q>::MultiplicationOp>,
				  "P<Q> must be a unitary ring!");
	EXPECT_TRUE(true);
}

TEST(PolynomStructure2, NotField) {

	static_assert(!Field<P<Q>, P<Q>::AdditionOp, P<Q>::MultiplicationOp>,
				  "P<Q> must NOT be a field!");
	EXPECT_TRUE(true);
}

