#include <gtest/gtest.h>
#include "core/realization/Rational/Q.h"

// Хелпер для создания Q из строки вида "num/den"
Q fromFrac(const std::string& num_str, const std::string& den_str) {
    // Парсим числитель как Z
    bool neg = (num_str[0] == '-');
    std::string abs_num = neg ? num_str.substr(1) : num_str;
    
    std::vector<uint8_t> num_digits;
	for (int i = abs_num.size() - 1; i >= 0; --i) {
		num_digits.push_back(abs_num[i] - '0');
	}

    Z numerator(Natural(num_digits), neg);
    
    // Парсим знаменатель как N
    std::vector<uint8_t> den_digits;
    for (int i = den_str.size() - 1; i >= 0; --i) {
        den_digits.push_back(den_str[i] - '0');
    }
    N denominator(den_digits);
    
    return Q(numerator, denominator);
}

// Q1 - Конструкция и toString
TEST(RationalConstruct1, Basic) {
    Q r1 = fromFrac("1", "2");
	auto res = r1.toString();

    EXPECT_EQ(r1.toString(), "1/2");
}

TEST(RationalConstruct2, Negative) {
    Q r2 = fromFrac("-3", "4");
    EXPECT_EQ(r2.toString(), "-3/4");
}

TEST(RationalConstruct3, Integer) {
    Q r3 = fromFrac("5", "1");
    EXPECT_EQ(r3.toString(), "5/1");
}

// Q2 - Сокращение (если есть метод reduce)
TEST(RationalReduce1, Basic) {
    Q r1 = fromFrac("10", "20");
    r1.reduce();
    EXPECT_EQ(r1.toString(), "1/2");
}

TEST(RationalReduce2, NegativeOne) {
    Q r2 = fromFrac("-5", "5");
    r2.reduce();
    EXPECT_EQ(r2.toString(), "-1/1");
}

// Q3 - Сложение
TEST(RationalAdd1, Basic) {
    Q a = fromFrac("1", "2");
    Q b = fromFrac("1", "6");
    Q result = a + b;
    result.reduce();
    EXPECT_EQ(result.toString(), "2/3");
}

TEST(RationalAdd2, WithNegative) {
    Q a = fromFrac("1", "2");
    Q b = fromFrac("-1", "2");
    Q result = a + b;
    EXPECT_EQ(result.toString(), "0/1");
}

// Q4 - Вычитание
TEST(RationalSub1, Basic) {
    Q a = fromFrac("1", "4");
    Q b = fromFrac("1", "2");
    Q result = a - b;
    result.reduce();
    EXPECT_EQ(result.toString(), "-1/4");
}

// Q5 - Умножение
TEST(RationalMul1, Basic) {
    Q a = fromFrac("2", "3");
    Q b = fromFrac("3", "4");
    Q result = a * b;
    result.reduce();
    EXPECT_EQ(result.toString(), "1/2");
}

TEST(RationalMul2, WithZero) {
    Q a = fromFrac("5", "8");
    Q zero = fromFrac("0", "1");
    Q result = a * zero;
    EXPECT_EQ(result.toString(), "0/1");
}

// Q6 - Деление
TEST(RationalDiv1, Basic) {
    Q a = fromFrac("1", "2");
    Q b = fromFrac("2", "1");
    Q result = a / b;
    result.reduce();
    EXPECT_EQ(result.toString(), "1/4");
}

TEST(RationalDiv2, ThrowsOnZero) {
    Q a = fromFrac("1", "2");
    Q zero = fromFrac("0", "1");
    EXPECT_THROW(a / zero, UniversalStringException);
}

// Q7 - Сравнение
TEST(RationalCmp1, Equal) {
    Q a = fromFrac("1", "2");
    Q b = fromFrac("2", "4");
    EXPECT_TRUE(a == b);
}

TEST(RationalCmp2, Greater) {
    Q a = fromFrac("3", "4");
    Q b = fromFrac("1", "2");
    EXPECT_TRUE(a > b);
}

TEST(RationalCmp3, Less) {
    Q a = fromFrac("1", "3");
    Q b = fromFrac("1", "2");
    EXPECT_TRUE(a < b);
}

// Q8 - Edge cases
TEST(RationalEdge1, LargeNumbers) {
    Q big = fromFrac("1000000000", "2000000000");
    big.reduce();
    EXPECT_EQ(big.toString(), "1/2");
}

TEST(RingTestRational, bas5) {
	bool res = UnitaryRing<Q::SetType, Q::AdditionOp, Q::MultiplicationOp>;


	EXPECT_EQ(res, true);
}

TEST(FieldTestRational, base12) {
	bool res = Field<Q::SetType, Q::AdditionOp, Q::MultiplicationOp>;


	EXPECT_EQ(res, true);
}