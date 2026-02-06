#include "binary.h"

#include "Exceptions/UniversalStringException.h"


template<>
class Add<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
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
        return N(res);
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};

template<>
class Mul<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
        if ((num1.nums.size() == 1 && num1.nums[0] == 0) ||
            (num2.nums.size() == 1 && num2.nums[0] == 0)) {
            return N(std::vector<uint8_t>{0});
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
        return N(res);
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};


template<>
class Cmp<N> : public IBinaryOperation<N, int> {
public:
    static int run(const N& num1, const N& num2) {
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

    int execute(const N& a, const N& b) const override { return run(a, b); }
};




// Вспомогательная функция, нужна для других важный функций Натуральных чисел.

N multiplyByPowerOfTen(N& num1, std::size_t k)
{
    if (Cmp<N>::run(num1, N({0})) == 0)
		return num1;

	if (num1.nums.size() > SIZE_MAX - k) {
		throw UniversalStringException("Natural:  The size of number is greater than " + std::to_string(SIZE_MAX));
	}

	std::vector<uint8_t> res;
	res.reserve(num1.nums.size() + k);

	res.assign(k, 0);
	res.insert(res.end(), num1.nums.begin(), num1.nums.end());

	return N(res);
}


N multibleByDigit(const N& num1, std::size_t b)
{
    if (b > 9) {
        throw UniversalStringException("Natural:  digit out of range (" + std::to_string(b) + ")");
    }
    if (b == 0) return N(std::vector<uint8_t>{0});
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
    return N(res);
}




template<>
class Sub<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
        uint8_t cmp = Cmp<N>::run(num1, num2);
        if (cmp == 1) {
            throw UniversalStringException("Natural:  subtrahend larger than minuend");
        }
        if (cmp == 0) return N(std::vector<uint8_t>{0});
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
        return N(res);
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};

N subMultipied(N& num1, N& num2, std::size_t c)
{
	if (c > 9)
		throw UniversalStringException("Natural:  The multiplier is not a digit from 0 to 9!");
	N multiplied = multibleByDigit(num2 ,c);
	if (Cmp<N>::run(num1, multiplied) == 1)
		throw UniversalStringException("Natural:  the subtracted is greater than the reduced");
	return Sub<N>::run(num1, multiplied);
}



template<>
class Div<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
       if (Cmp<N>::run(num2, N({0})) == 0) {
            throw UniversalStringException("Natural: can not divide by zero");
        }
        if (Cmp<N>::run(num1, num2) == 1) {
            return N(std::vector<uint8_t>{0});
        }
        N current(std::vector<uint8_t>{0});
        std::vector<uint8_t> result;
        result.reserve(num1.nums.size());
        for (int i = static_cast<int>(num1.nums.size()) - 1; i >= 0; --i) {
            current = multiplyByPowerOfTen(current, 1);
            current = Add<N>::run(current, N(std::vector<uint8_t>{num1.nums[i]}));
            uint8_t q = 0;
            if (Cmp<N>::run(current, num2) != 1) {
                for (int digit = 9; digit >= 1; --digit) {
                    N candidate = multibleByDigit(num2, static_cast<std::size_t>(digit));
                    try {
                        N newCurrent = Sub<N>::run(current, candidate);
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
        return N(result);
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};


template<>
class Rem<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
       if (Cmp<N>::run(num2, N({0})) == 0) {
            throw UniversalStringException("Natural:  can not divide by zero");
        }
        if (Cmp<N>::run(num1, num2) == 1) return num1;
        N q = Div<N>::run(num1, num2);
        N product = Mul<N>::run(num2, q);
        return Sub<N>::run(num1, product);
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};



template<>
class Gcd<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
        N first = num1;
        N second = num2;
        if (Cmp<N>::run(second, N({0})) == 0 && Cmp<N>::run(first, N({0})) == 0) {
            throw UniversalStringException("Natural: the gcd for two zeros is not uniquely defined");
        }
        if (Cmp<N>::run(second, N({0})) == 0) {
            return first;
        }
        while (Cmp<N>::run(second, N({0})) != 0) {
            N tmp = Rem<N>::run(first,  second);
            first = second;
            second = tmp;
        }
        return first;
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};



template<>
class Lcm<N> : public IBinaryOperation<N, N> {
public:
    static N run(const N& num1, const N& num2) {
        if (Cmp<N>::run(num1, N({0})) == 0 || Cmp<N>::run(num2, N({0})) == 0 ) {
            throw UniversalStringException("Natural:  the lcm for zeros is not uniquely defined");
        }
        return Div<N>::run(Mul<N>::run(num1, num2), Gcd<N>::run(num1, num2));
    }
    N execute(const N& a, const N& b) const override { return run(a, b); }
};


