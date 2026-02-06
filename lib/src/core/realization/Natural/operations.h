#ifndef OPERATIONS_NATURAL_H
#define OPERATIONS_NATURAL_H

#include <string>
#include <iostream>

#include "../../abstract/types/natural.h"
#include "../../abstract/transformations/operations/binary.h"
#include "../../abstract/transformations/operations/unary.h"

#include "../../abstract/transformations/mapping.h"

#include "../../abstract/structures/axioms.h"


#include "Exceptions/UniversalStringException.h"

namespace NatOper {

/**
 * @brief Реализация операции сложения для Natural. Это уже именно реализация, которая зависит от типа, 
 * над которым происходи действие.
 */
class Add : public BinaryOperation<Add, Natural>, 
            public Associative, 
            public Commutative, 
            public Identity
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        size_t n = num1.nums.size();
        size_t m = num2.nums.size();
        size_t maxlen = std::max(n, m);
        std::vector<uint8_t> res;
        res.reserve(maxlen + 1);
        uint8_t carry = 0;
        for (size_t i = 0; i < maxlen; ++i) {
            uint8_t a = (i < n) ? num1.nums[i] : 0;
            uint8_t b = (i < m) ? num2.nums[i] : 0;
            uint8_t s = a + b + carry;
            res.push_back(s % 10);
            carry = s / 10;
        }
        if (carry) res.push_back(carry);
        return Natural(res); 
    }
};


/**
 * @brief Умножение на натуральных числах.
 */
class Mul : public BinaryOperation<Mul, Natural>, 
            public Associative, 
            public Commutative, 
            public Identity
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        if ((num1.nums.size() == 1 && num1.nums[0] == 0) ||
            (num2.nums.size() == 1 && num2.nums[0] == 0)) {
            return Natural(std::vector<uint8_t>{0});
        }
        std::vector<uint8_t> res(num1.nums.size() + num2.nums.size(), 0);
        for (size_t i = 0; i < num1.nums.size(); ++i) {
            uint8_t carry = 0;
            for (size_t j = 0; j < num2.nums.size() || carry; ++j) {
                unsigned long long cur = res[i + j] +
                                        static_cast<unsigned long long>(num1.nums[i]) *
                                        (j < num2.nums.size() ? num2.nums[j] : 0) +
                                        carry;
                res[i + j] = static_cast<uint8_t>(cur % 10);
                carry = static_cast<uint8_t>(cur / 10);
            }
        }
        while (res.size() > 1 && res.back() == 0)
            res.pop_back();
        return Natural(res);
    }
};



/**
 * @brief Оператор сравнения элементов в натуральных числах.
 */
class Cmp : public Mapping<Cmp, int, Natural, Natural>
{
public:
    static int calc(Natural num1, Natural num2) { 
        if (num1.nums.size() > num2.nums.size()) return 2;
        if (num1.nums.size() < num2.nums.size()) return 1;
        for (size_t i = num1.nums.size(); i-- > 0;) {
            uint8_t a = num1.nums[i];
            uint8_t b = num2.nums[i];
            if (a > b) return 2;
            if (a < b) return 1;
        }
        return 0;
    }
};


// Вспомогательная функция, нужна для других важный функций Натуральных чисел.
inline Natural multiplyByPowerOfTen(Natural& num1, std::size_t k)
{
    if (Cmp::execute(num1, Natural({0})) == 0)
		return num1;

	if (num1.nums.size() > SIZE_MAX - k) {
		throw UniversalStringException("Natural:  The size of number is greater than " + std::to_string(SIZE_MAX));
	}

	std::vector<uint8_t> res;
	res.reserve(num1.nums.size() + k);

	res.assign(k, 0);
	res.insert(res.end(), num1.nums.begin(), num1.nums.end());

	return Natural(res);
}

// Вспомогательная функция, нужна для других важный функций Натуральных чисел.
inline Natural multibleByDigit(const Natural& num1, std::size_t b)
{
    if (b > 9) {
        throw UniversalStringException("Natural:  digit out of range (" + std::to_string(b) + ")");
    }
    if (b == 0) return Natural(std::vector<uint8_t>{0});
    std::vector<uint8_t> res;
    res.reserve(num1.nums.size() + 1);
    unsigned int carry = 0;
    for (size_t i = 0; i < num1.nums.size(); ++i) {
        unsigned int prod = static_cast<unsigned int>(num1.nums[i]) * b + carry;
        res.push_back(static_cast<uint8_t>(prod % 10));
        carry = prod / 10;
    }
    while (carry > 0) {
        res.push_back(static_cast<uint8_t>(carry % 10));
        carry /= 10;
    }
    return Natural(res);
}


/**
 * @brief Вычитание на натуральных числах.
 */
class Sub : public BinaryOperation<Sub, Natural>
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        uint8_t cmp = Cmp::execute(num1, num2);
        if (cmp == 1) {
            throw UniversalStringException("Natural:  subtrahend larger than minuend");
        }
        if (cmp == 0) return Natural(std::vector<uint8_t>{0});
        std::vector<uint8_t> res(num1.nums.size(), 0);
        int borrow = 0;
        for (size_t i = 0; i < num1.nums.size(); ++i) {
            int a = num1.nums[i];
            int b = (i < num2.nums.size()) ? num2.nums[i] : 0;
            int diff = a - b - borrow;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res[i] = static_cast<uint8_t>(diff);
        }

    	while (res.size() > 1 && res.back() == 0) {
    		res.pop_back();
    	}
        return Natural(res);
    }
};


// Вспомогательная функция, нужна для других важный функций Натуральных чисел.
inline Natural subMultipied(const Natural& num1, const Natural& num2, std::size_t c)
{
    if (c > 9)
		throw UniversalStringException("Natural:  The multiplier is not a digit from 0 to 9!");
	Natural multiplied = multibleByDigit(num2 ,c);
	if (Cmp::execute(num1, multiplied) == 1)
		throw UniversalStringException("Natural:  the subtracted is greater than the reduced");
	return Sub::execute(num1, multiplied);
}


/**
 * @brief Деление на натуральных числах.
 */
class Div : public BinaryOperation<Div, Natural>
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        if (Cmp::execute(num2, Natural({0})) == 0) {
            throw UniversalStringException("Natural: can not divide by zero");
        }
        if (Cmp::execute(num1, num2) == 1) {
            return Natural(std::vector<uint8_t>{0});
        }
        Natural current(std::vector<uint8_t>{0});
        std::vector<uint8_t> result;
        result.reserve(num1.nums.size());
        for (int i = static_cast<int>(num1.nums.size()) - 1; i >= 0; --i) {
            current = multiplyByPowerOfTen(current, 1);
            current = Add::execute(current, Natural(std::vector<uint8_t>{num1.nums[i]}));
            uint8_t q = 0;
            if (Cmp::execute(current, num2) != 1) {
                for (int digit = 9; digit >= 1; --digit) {
                    Natural candidate = multibleByDigit(num2, static_cast<std::size_t>(digit));
                    try {
                        Natural newCurrent = Sub::execute(current, candidate);
                        q = static_cast<uint8_t>(digit);
                        current = std::move(newCurrent);
                        break;
                    } catch (const UniversalStringException&) {
                        continue;
                    }
                }
            }
            result.push_back(q);
        }
        std::reverse(result.begin(), result.end());
        while (result.size() > 1 && result.back() == 0) {
            result.pop_back();
        }
        return Natural(result);
    }
};

/**
 * @brief Остаток от деления на натуральных числах.
 */
class Rem : public BinaryOperation<Rem, Natural>
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        if (Cmp::execute(num2, Natural({0})) == 0) {
            throw UniversalStringException("Natural:  can not divide by zero");
        }
        if (Cmp::execute(num1, num2) == 1) return num1;
        Natural q = Div::execute(num1, num2);
        Natural product = Mul::execute(num2, q);
        return Sub::execute(num1, product);
    }
};

/**
 * @brief НОД натуральных чисел
 */
class Gcd : public BinaryOperation<Gcd, Natural>
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        Natural first = num1;
        Natural second = num2;
        if (Cmp::execute(second, Natural({0})) == 0 && Cmp::execute(first, Natural({0})) == 0) {
            throw UniversalStringException("Natural: the gcd for two zeros is not uniquely defined");
        }
        if (Cmp::execute(second, Natural({0})) == 0) {
            return first;
        }
        while (Cmp::execute(second, Natural({0})) != 0) {
            Natural tmp = Rem::execute(first,  second);
            first = second;
            second = tmp;
        }
        return first;
    }
};


/**
 * @brief НОК натуральных чисел
 */
class Lcm : public BinaryOperation<Lcm, Natural>
{
public:
    static Natural calc(Natural num1, Natural num2) { 
        if (Cmp::execute(num1, Natural({0})) == 0 || Cmp::execute(num2, Natural({0})) == 0 ) {
            throw UniversalStringException("Natural:  the lcm for zeros is not uniquely defined");
        }
        return Div::execute(Mul::execute(num1, num2), Gcd::execute(num1, num2));
    }
};


/**
 * @brief Оператор перевода натурального числа в строку.
 */
class toString : public Mapping<toString, std::string, Natural>
{
public:
    static std::string calc(Natural num) { 
        if (num.nums.empty()) {
            throw UniversalStringException("Natural: atypical behavior, the vector of numbers should not be empty");
        }

        std::string result(num.nums.size(), '0');

        for (int i = static_cast<int>(num.nums.size()) - 1; i >= 0; --i) {
            result[num.nums.size() - i - 1] = '0' + num.nums[i];
        }

        return result;
    }
};

}

/**
 * @brief Регистрация дистрибутивности: умножение дистрибутивно относительно сложения.
 */
template<>
struct Distributive<NatOper::Mul, NatOper::Add> {};  

#endif //OPERATIONS_NATURAL_H