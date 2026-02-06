#include <gtest/gtest.h>
#include "core/realization/Natural/N.h"



// Хелпер для удобства тестов
N fromStr(const std::string& str) {
    std::vector<uint8_t> digits;
    for (int i = str.size() - 1; i >= 0; --i) {
        digits.push_back(str[i] - '0');
    }
    return N(digits);
}


// N1 — Cmp
TEST(NaturalCmp1, Basic) {
    N a = fromStr("123"), b = fromStr("124");
    EXPECT_TRUE(a < b);   // a < b
    EXPECT_TRUE(b > a);   // b > a
    EXPECT_TRUE(a == a);  // a == a
}

// N4 — Add
TEST(NaturalAdd1, Basic) {
    N a = fromStr("97"), b = fromStr("25");
    EXPECT_EQ((a + b).toString(), "122");
}

// N5 — Sub
TEST(NaturalSubtract1, Basic) {
    N a = fromStr("122"), b = fromStr("25");
    EXPECT_EQ((a - b).toString(), "97");
}

// N6 — multibleByDigit
TEST(NaturalMultiplyByDigit1, Basic) {
    N a = fromStr("123");
    EXPECT_EQ(N(NatOper::multibleByDigit(a.get(), 3)).toString(), "369");
}

// N7 — multiplyByPowerOfTen
TEST(NaturalMultiplyByPowerOfTen1, Basic) {
    N a = fromStr("123");
    Natural temp = a.get();
    EXPECT_EQ(N(NatOper::multiplyByPowerOfTen(temp, 2)).toString(), "12300");
}

// N8 — Mul
TEST(NaturalMultiply1, Basic) {
    N a = fromStr("12"), b = fromStr("13");
    EXPECT_EQ((a * b).toString(), "156");
}

// N11 — Div
TEST(NaturalQuotient1, Basic) {
    N a = fromStr("100"), b = fromStr("23");
    EXPECT_EQ((a / b).toString(), "4");
}

// N12 — Rem
TEST(NaturalRemainder1, Basic) {
    N a = fromStr("100"), b = fromStr("23");
    EXPECT_EQ((a % b).toString(), "8");
}

// N13 — Gcd
TEST(NaturalGCD1, Basic) {
    N a = fromStr("48"), b = fromStr("18");
    EXPECT_EQ(N::gcd(a, b).toString(), "6");
}

// N14 — Lcm
TEST(NaturalLCM1, Basic) {
    N a = fromStr("48"), b = fromStr("18");
    EXPECT_EQ(N::lcm(a, b).toString(), "144");
}

// Дополнительные проверки логики
TEST(NaturalExtra1, EdgeCases) {
    // Вычитание в ноль
    N a = fromStr("123");
    EXPECT_EQ((a - a).toString(), "0");
    
    // Ошибка при вычитании большего из меньшего
    EXPECT_THROW(fromStr("50") - fromStr("100"), UniversalStringException);
    
    // Деление на ноль
    EXPECT_THROW(fromStr("10") / fromStr("0"), UniversalStringException);
}

TEST(RingTestNaturel, baseN) {
	bool res = Ring<N::SetType, N::AdditionOp, N::MultiplicationOp>;
	EXPECT_EQ(res, false);
}