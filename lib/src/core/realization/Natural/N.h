#ifndef NATURAL_STRUCTURE_H
#define NATURAL_STRUCTURE_H

#include "../../abstract/types/natural.h"
#include "../../abstract/structures/groups.h"
#include "../../abstract/structures/rings.h"
#include "operations.h"




/**
 * @brief Обертка натуральных чисел с операторами.
 * Структура: моноид по сложению и умножению
 */
class N {
private:
    Natural value;

public:
    // Определяем типы операций для концептов
    using AdditionOp = NatOper::Add;
    using MultiplicationOp = NatOper::Mul;

    N(Natural v) : value(std::move(v)) {}
    N(const std::vector<uint8_t>& nums) : value(nums) {}


    N operator+(const N& other) const {
        return N(NatOper::Add::execute(value, other.value));
    }

    N operator*(const N& other) const {
        return N(NatOper::Mul::execute(value, other.value));
    }

    N operator-(const N& other) const {
        return N(NatOper::Sub::execute(value, other.value));
    }

    N operator/(const N& other) const {
        return N(NatOper::Div::execute(value, other.value));
    }

    N operator%(const N& other) const {
        return N(NatOper::Rem::execute(value, other.value));
    }

    bool operator>(const N& other) const {
        return NatOper::Cmp::execute(value, other.value) == 2;
    }

    bool operator<(const N& other) const {
        return NatOper::Cmp::execute(value, other.value) == 1;
    }

    bool operator==(const N& other) const {
        return NatOper::Cmp::execute(value, other.value) == 0;
    }

    static N gcd(const N& a, const N& b) {
        return N(NatOper::Gcd::execute(a.get(), b.get()));
    }

    static N lcm(const N& a, const N& b) {
        return N(NatOper::Lcm::execute(a.get(), b.get()));
    }


    const Natural& get() const { return value; }

    std::string toString() {
        return NatOper::toString::execute(value);
    }
};



/**
 * Пример использования в полиноме:
 * 
 * @code
 * template<typename T>
 * requires Field<T, typename T::AdditionOp, typename T::MultiplicationOp>
 * class Polynomial {
 *     // Polynomial<N> poly; // ОШИБКА КОМПИЛЯЦИИ!
 * };
 * @endcode
 */

#endif //NATURAL_STRUCTURE_H