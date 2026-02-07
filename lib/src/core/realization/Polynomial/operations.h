#ifndef OPERATIONS_POLYNOM_H
#define OPERATIONS_POLYNOM_H


#include "../../abstract/types/polynom.h"

#include "../../abstract/transformations/operations/unary.h"
#include "../../abstract/transformations/operations/binary.h"

#include "Exceptions/UniversalStringException.h"

namespace Poly {

/**
 * @brief Старший коэфициент
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Lc : public Mapping<Lc<T>, T, Polynomial<T>>
{
public:
    static T calc(Polynomial<T> p1) {
        return p1.coefficients.back();
    }
};



/**
 * @brief Сложение полиномов
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Add : public BinaryOperation<Add<T>, Polynomial<T>>,
            public Associative,
            public Commutative,
            public Identity,
			public Inverse
{
public:
    static Polynomial<T> calc(Polynomial<T> p1, Polynomial<T> p2) {
        size_t max_size = std::max(p1.coefficients.size(), p2.coefficients.size());
        std::vector<T> result;
        result.reserve(max_size);
        
        T zero = T::zero();
        
        for (size_t i = 0; i < max_size; ++i) {
            T c1 = (i < p1.coefficients.size()) ? p1.coefficients[i] : zero;
            T c2 = (i < p2.coefficients.size()) ? p2.coefficients[i] : zero;
            result.push_back(c1 + c2);
        }

        while (result.size() > 1 && result.back() == zero) {
            result.pop_back();
        }
        
        // Если все коэффициенты обнулились, оставляем [0]
        if (result.empty()) {
            result.push_back(zero);
        }
        
        return Polynomial<T>(result);
    }
};


/**
 * @brief Вычитание полиномов
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Sub : public BinaryOperation<Sub<T>, Polynomial<T>>
{
public:
    static Polynomial<T> calc(Polynomial<T> p1, Polynomial<T> p2) {
        size_t max_size = std::max(p1.coefficients.size(), p2.coefficients.size());
        std::vector<T> result;
        result.reserve(max_size);
        
        T zero = T::zero();
        
        for (size_t i = 0; i < max_size; ++i) {
            T c1 = (i < p1.coefficients.size()) ? p1.coefficients[i] : zero;
            T c2 = (i < p2.coefficients.size()) ? p2.coefficients[i] : zero;
            result.push_back(c1 - c2);
        }

        while (result.size() > 1 && result.back() == zero) {
            result.pop_back();
        }
        
        if (result.empty()) {
            result.push_back(zero);
        }
        
        return Polynomial<T>(result);
    }
};


/**
 * @brief Умножение полинома на скаляр (элемент поля)
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class MulScalar : public Mapping<MulScalar<T>, Polynomial<T>,  Polynomial<T>, T>
{
public:
    static Polynomial<T> calc(Polynomial<T> poly, T scalar) {
        T zero = T::zero();

        if (scalar == zero) {
            return Polynomial<T>({zero});
        }
        
        std::vector<T> result;
        result.reserve(poly.coefficients.size());
        
        for (const T& coeff : poly.coefficients) {
            result.push_back(coeff * scalar);
        }
        
        return Polynomial<T>(result);
    }
};


/**
 * @brief Умножение полиномов
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Mul : public BinaryOperation<Mul<T>, Polynomial<T>>,
            public Associative,
            public Commutative,
            public Identity
{
public:
    static Polynomial<T> calc(Polynomial<T> p1, Polynomial<T> p2) {
        T zero = T::zero();
        
        bool p1_zero = (p1.coefficients.size() == 1 && p1.coefficients[0] == zero);
        bool p2_zero = (p2.coefficients.size() == 1 && p2.coefficients[0] == zero);
        
        if (p1_zero || p2_zero)
            return Polynomial<T>({zero});
        
        size_t n = p1.coefficients.size();
        size_t m = p2.coefficients.size();
        
        std::vector<T> result;
        try {
            result.assign(n + m - 1, zero);
        } catch (const std::bad_alloc&) {
            throw UniversalStringException("Polynomial: not enough memory for multiplication");
        }
        

        for (size_t i = 0; i < n; ++i) {
            if (p1.coefficients[i] == zero) continue;
            
            for (size_t j = 0; j < m; ++j) {
                if (p2.coefficients[j] == zero) continue;
                
                result[i + j] = result[i + j] + (p1.coefficients[i] * p2.coefficients[j]);
            }
        }
        
        // Удаляем ведущие нули
        while (result.size() > 1 && result.back() == zero) {
            result.pop_back();
        }
        
        if (result.empty()) {
            result.push_back(zero);
        }
        
        return Polynomial<T>(result);
    }
};


/**
 * @brief Деление полиномов (возвращает частное)
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Div : public BinaryOperation<Div<T>, Polynomial<T>>
{
public:
    static Polynomial<T> calc(Polynomial<T> dividend, Polynomial<T> divisor) {
        T zero = T::zero();
        
        if (divisor.coefficients.back() == zero)
            throw UniversalStringException("Polynomial: cannot divide by zero polynomial");
        
        size_t divisor_size = divisor.coefficients.size();
        size_t dividend_size = dividend.coefficients.size();
        
        if (dividend_size < divisor_size)
            return Polynomial<T>({zero});
        
        std::vector<T> remainder = dividend.coefficients;
        std::vector<T> quotient(dividend_size - divisor_size + 1, zero);
        
        const T& divisor_leading = divisor.coefficients.back();
        
        // Деление "уголком"
        for (size_t pos = dividend_size; pos >= divisor_size; --pos) {
            size_t quotient_idx = pos - divisor_size;
            
            if (remainder[pos - 1] == zero)
                continue;
            
            T coeff = remainder[pos - 1] / divisor_leading;
            quotient[quotient_idx] = coeff;
            
            for (size_t j = 0; j < divisor_size; ++j) {
                remainder[quotient_idx + j] = remainder[quotient_idx + j] - (divisor.coefficients[j] * coeff);
            }
        }
        
        // Удаляем ведущие нули
        while (quotient.size() > 1 && quotient.back() == zero) {
            quotient.pop_back();
        }
        
        if (quotient.empty()) {
            quotient.push_back(zero);
        }
        
        return Polynomial<T>(quotient);
    }
};


/**
 * @brief Остаток от деления полиномов
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
class Rem : public BinaryOperation<Rem<T>, Polynomial<T>>
{
public:
    static Polynomial<T> calc(Polynomial<T> dividend, Polynomial<T> divisor) {
        Polynomial<T> quotient = Div<T>::execute(dividend, divisor);
        Polynomial<T> product = Mul<T>::execute(quotient, divisor);
        return Sub<T>::execute(dividend, product);
    }
};

template<typename T>
class Derivative : public UnaryOperation<Derivative<T>, Polynomial<T>>
{
public:
    static Polynomial<T> calc(Polynomial<T> poly) {
        T zero = T::zero();
        
        if (poly.degree() == 0)
            return Polynomial<T>({zero});
        
        std::vector<T> result;
        result.reserve(poly.coefficients.size() - 1);
        
        for (size_t i = 1; i < poly.coefficients.size(); ++i) {
            // i * coefficients[i] = coefficients[i] + ... + coefficients[i] (i раз)
            T coeff = poly.coefficients[i];
            for (size_t k = 1; k < i; ++k) {
                coeff = coeff + poly.coefficients[i];
            }
            result.push_back(coeff);
        }
        
        return Polynomial<T>(result);
    }
};

/**
 * @brief Преобразование полинома в строку
 */
template<typename T>
class toString : public Mapping<toString<T>, std::string, Polynomial<T>>
{
public:
    static std::string calc(Polynomial<T> poly) {
        if (poly.coefficients.empty())
            throw UniversalStringException("Polynomial: cannot have empty coefficients");
        
        T zero = T::zero();
        std::string result;
        
        for (int i = poly.coefficients.size() - 1; i >= 0; --i) {
            const T& coeff = poly.coefficients[i];
            
            if (coeff == zero && !(i == 0 && poly.coefficients.size() == 1)) {
                continue;
            }
            
            if (i != static_cast<int>(poly.coefficients.size()) - 1) {
                result += " ";
                result += coeff.isNegative() ? "- " : "+ ";
            } else if (coeff.isNegative()) {
                result += "-";
            }
            
            std::string coeff_str = coeff.toString();
            if (coeff.isNegative() && coeff_str[0] == '-') {
                coeff_str = coeff_str.substr(1); 
            }
            
            T abs_coeff = coeff.isNegative() ? (zero - coeff) : coeff;
            if (!(abs_coeff == T::identity() && i > 0)) {
                result += coeff_str;
            }
            
            if (i > 0) {
                if (!(abs_coeff == T::identity())) {
                    result += "*";
                }
                result += "x";
                if (i > 1) {
                    result += "^" + std::to_string(i);
                }
            }
        }
        
        return result.empty() ? "0" : result;
    }
};


}

/**
 * @brief Регистрация дистрибутивности: умножение дистрибутивно относительно сложения.
 */
template<typename T>
struct Distributive<Poly::Mul<T>, Poly::Add<T>> {};

#endif //OPERATIONS_POLYNOM_H