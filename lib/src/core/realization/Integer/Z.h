#ifndef INTEGER_STRUCTURE_H
#define INTEGER_STRUCTURE_H

#include "../../abstract/types/integer.h"
#include "../../abstract/types/natural.h"
#include "../../abstract/structures/groups.h"
#include "../../abstract/structures/rings.h"
#include "../Integer/operations.h"



/**
 * @brief Обертка натуральных чисел с операторами.
 * Структура: Абелева группа по сложению и моноид по умножению
 * Кольцо!
 */
class Z {
private:
    Integer value;

public:
    // Определяем типы операций для концептов
    using AdditionOp = Int::Add;
    using MultiplicationOp = Int::Mul;
	using SetType = Integer;

    Z(Integer v) : value(std::move(v)) {}
    Z(Natural num, bool is_neg) : value(num, is_neg) {}
    Z(N num) : value(num.get(), false) {}

    Z operator-() {
        return Int::Neg::execute(value);
    }

    Z operator+(const Z& other) const { 
        return Z(Int::Add::execute(value, other.value));
    }

    Z operator*(const Z& other) const {
        return Z(Int::Mul::execute(value, other.value));
    }

    Z operator-(const Z& other) const {
        return Z(Int::Sub::execute(value, other.value));
    }

    Z operator/(const Z& other) const {
        return Z(Int::Div::execute(value, other.value));
    }

    Z operator%(const Z& other) const {
        return Z(Int::Rem::execute(value, other.value));
    }

    bool operator>(const Z& other) const {
        return Int::Cmp::execute(value, other.value) == 2;
    }

    bool operator<(const Z& other) const {
        return Int::Cmp::execute(value, other.value) == 1;
    }

    bool operator==(const Z& other) const {
        return Int::Cmp::execute(value, other.value) == 0;
    }

    static Z gcd(const Z& a, const Z& b) {
        return Z(Int::Gcd::execute(a.get(), b.get()));
    }

    static Z lcm(const Z& a, const Z& b) {
        return Z(Int::Lcm::execute(a.get(), b.get()));
    }

    static N abs(Z&a) {
        return Int::Abs::execute(a.get());
    }

    bool isNegative() const { return value.is_neg; }

    static Z zero() { return Z(Natural({0}), false); }
    static Z identity() { return Z(Natural({1}), false); }  // Единица

    const Integer& get() const { return value; }

    std::string toString()const {
        return Int::toString::execute(value);
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

#endif //INTEGER_STRUCTURE_H