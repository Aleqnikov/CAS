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
    using AdditionOp = Add;
    using MultiplicationOp = Mul;

    N(Natural v) : value(std::move(v)) {}
    N(const std::vector<uint8_t>& nums) : value(nums) {}


    N operator+(const N& other) const {
        return N(Add::execute(value, other.value));
    }

    N operator*(const N& other) const {
        return N(Mul::execute(value, other.value));
    }

    N operator-(const N& other) const {
        return N(Sub::execute(value, other.value));
    }

    N operator/(const N& other) const {
        return N(Div::execute(value, other.value));
    }

    N operator%(const N& other) const {
        return N(Rem::execute(value, other.value));
    }

    bool operator>(const N& other) const {
        return Cmp::execute(value, other.value) == 2;
    }

    bool operator<(const N& other) const {
        return Cmp::execute(value, other.value) == 1;
    }

    bool operator==(const N& other) const {
        return Cmp::execute(value, other.value) == 0;
    }

    const Natural& get() const { return value; }

    std::string toString() {
        return toString::execute(value);
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