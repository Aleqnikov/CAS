#ifndef RATIONAL_STRUCTURE_H
#define RATIONAL_STRUCTURE_H

#include "../../abstract/types/integer.h"
#include "../../abstract/types/natural.h"
#include "../../abstract/types/rational.h"
#include "../../abstract/structures/groups.h"
#include "../../abstract/structures/rings.h"
#include "../Rational/operations.h"



/**
 * @brief Обертка рациональных чисел с операторами.
 * Структура: Абелева группа по сложению и Абелева группа по умножению
 * Поле!
 */
class Q {
private:
    Rational value;

public:
    // Определяем типы операций для концептов
    using AdditionOp = Rat::Add;
    using MultiplicationOp = Rat::Mul;
	using SetType = Rational;

    Q(Rational v) : value(std::move(v)) {}
    Q(Z numerator, N denumerator) : value(numerator, denumerator) {}


    Q operator+(const Q& other) const { 
        return Q(Rat::Add::execute(value, other.value));
    }

    Q operator*(const Q& other) const {
        return Q(Rat::Mul::execute(value, other.value));
    }

    Q operator-(const Q& other) const {
        return Q(Rat::Sub::execute(value, other.value));
    }

    Q operator/(const Q& other) const {
        return Q(Rat::Div::execute(value, other.value));
    }


    bool operator>(const Q& other) const {
        return Rat::Cmp::execute(value, other.value) == 2;
    }

    bool operator<(const Q& other) const {
        return Rat::Cmp::execute(value, other.value) == 1;
    }

    bool operator==(const Q& other) const {
        return Rat::Cmp::execute(value, other.value) == 0;
    }

    void reduce(){
       value = Rat::Red::execute(value);
    }

    bool isNegative() const { return value.numerator.isNegative(); }

    static Q zero() { return Q(Z::zero(), N({1})); }
    static Q identity() { return Q(Z::identity(), N({1})); }  // 1/1

    std::string toString() const {
        return Rat::toString::execute(value);
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

#endif //RATIONAL_STRUCTURE_H