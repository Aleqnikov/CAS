#ifndef POLYNOMIAL_STRUCTURE_H
#define POLYNOMIAL_STRUCTURE_H

#include "../../abstract/types/polynom.h"
#include "../../abstract/structures/groups.h"
#include "../../abstract/structures/rings.h"
#include "../Polynomial/operations.h"

/**
 * @brief Обертка полиномов с операторами.
 * Структура: кольцо (не поле!)
 * 
 * @tparam T Тип поля коэффициентов (должен удовлетворять Field)
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class P {
private:
    Polynomial<T> value;

public:
    using AdditionOp = Poly::Add<T>;
    using MultiplicationOp = Poly::Mul<T>;
    using SetType = Polynomial<T>;

    P(Polynomial<T> v) : value(std::move(v)) {}
    P(const std::vector<T>& coeffs) : value(coeffs) {}

    P operator+(const P& other) const { 
        return P(Poly::Add<T>::execute(value, other.value));
    }

    P operator*(const P& other) const {
        return P(Poly::Mul<T>::execute(value, other.value));
    }

    P operator-(const P& other) const {
        return P(Poly::Sub<T>::execute(value, other.value));
    }

    P operator/(const P& other) const {
        return P(Poly::Div<T>::execute(value, other.value));
    }

    P operator%(const P& other) const {
        return P(Poly::Rem<T>::execute(value, other.value));
    }

    P operator*(const T& scalar) const {
        return P(Poly::MulScalar<T>::execute(value, scalar));
    }

    P derivative() const {
        return P(Poly::Derivative<T>::execute(value));
    }

    bool operator==(const P& other) const {
        if (value.coefficients.size() != other.value.coefficients.size())
            return false;
        for (size_t i = 0; i < value.coefficients.size(); ++i) {
            if (!(value.coefficients[i] == other.value.coefficients[i]))
                return false;
        }
        return true;
    }

    size_t degree() const {
        return value.degree();
    }

    std::string toString() const {
        return Poly::toString<T>::execute(value);
    }

    const T& operator[](size_t i) const {
        if (i >= value.coefficients.size())
            throw UniversalStringException("Polynomial: index out of bounds");
        return value.coefficients[i];
    }

    static P zero() {
        return P({T::zero()});
    }

    static P identity() {
        return P({T::identity()});
    }

	const Polynomial<T>& get() const { return value; }
};



#endif //POLYNOMIAL_STRUCTURE_H