#include <gtest/gtest.h>
#include "core/operations/binary/natural.h"
#include "core/operations/binary/binary.h"


// Хелперы для удобства тестов
N fromStr(const std::string& str) {
    std::vector<uint8_t> digits;
    for (int i = str.size() - 1; i >= 0; --i) {
        digits.push_back(str[i] - '0');
    }
    return N(digits);
}

std::string toStr(const N& n) {
    if (n.nums.empty()) return "0";
    std::string s = "";
    for (int i = n.nums.size() - 1; i >= 0; --i) {
        s += std::to_string(n.nums[i]);
    }
    return s;
}


// N1 — Cmp
TEST(NaturalCmp1, Basic) {
    N a = fromStr("123"), b = fromStr("124");
    EXPECT_EQ(Cmp<N>::run(a, b), 1); // a < b
    EXPECT_EQ(Cmp<N>::run(b, a), 2); // b > a
    EXPECT_EQ(Cmp<N>::run(a, a), 0); // a == a
}

// N4 — Add
TEST(NaturalAdd1, Basic) {
    N a = fromStr("97"), b = fromStr("25");
    EXPECT_EQ(toStr(Add<N>::run(a, b)), "122");
}

// N5 — Sub
TEST(NaturalSubtract1, Basic) {
    N a = fromStr("122"), b = fromStr("25");
    EXPECT_EQ(toStr(Sub<N>::run(a, b)), "97");
}

// N6 — multibleByDigit
TEST(NaturalMultiplyByDigit1, Basic) {
    N a = fromStr("123");
    EXPECT_EQ(toStr(multibleByDigit(a, 3)), "369");
}

// N7 — multiplyByPowerOfTen
TEST(NaturalMultiplyByPowerOfTen1, Basic) {
    N a = fromStr("123");
    EXPECT_EQ(toStr(multiplyByPowerOfTen(a, 2)), "12300");
}

// N8 — Mul
TEST(NaturalMultiply1, Basic) {
    N a = fromStr("12"), b = fromStr("13");
    EXPECT_EQ(toStr(Mul<N>::run(a, b)), "156");
}

// N11 — Div
TEST(NaturalQuotient1, Basic) {
    N a = fromStr("100"), b = fromStr("23");
    EXPECT_EQ(toStr(Div<N>::run(a, b)), "4");
}

// N12 — Rem
TEST(NaturalRemainder1, Basic) {
    N a = fromStr("100"), b = fromStr("23");
    EXPECT_EQ(toStr(Rem<N>::run(a, b)), "8");
}

// N13 — Gcd
TEST(NaturalGCD1, Basic) {
    N a = fromStr("48"), b = fromStr("18");
    EXPECT_EQ(toStr(Gcd<N>::run(a, b)), "6");
}

// N14 — Lcm
TEST(NaturalLCM1, Basic) {
    N a = fromStr("48"), b = fromStr("18");
    EXPECT_EQ(toStr(Lcm<N>::run(a, b)), "144");
}

// Дополнительные проверки логики
TEST(NaturalExtra1, EdgeCases) {
    // Вычитание в ноль
    N a = fromStr("123");
    EXPECT_EQ(toStr(Sub<N>::run(a, a)), "0");
    
    // Ошибка при вычитании большего из меньшего
    EXPECT_THROW(Sub<N>::run(fromStr("50"), fromStr("100")), UniversalStringException);
    
    // Деление на ноль
    EXPECT_THROW(Div<N>::run(fromStr("10"), fromStr("0")), UniversalStringException);
}