#include "binary.h"


template<>
class Add<N> : public IBinaryOperation<N> {
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