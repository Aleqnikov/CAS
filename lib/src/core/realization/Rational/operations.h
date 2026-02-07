#ifndef OPERATIONS_RATIONAL_H
#define OPERATIONS_RATIONAL_H

#include "../../abstract/types/rational.h"

#include "../../abstract/transformations/operations/unary.h"
#include "../../abstract/transformations/operations/binary.h"

namespace Rat {


/**
 * @brief Оператор сравнения элементов в Рациональных числах.
 */
class Cmp : public Mapping<Cmp, int, Rational, Rational>
{
public:
    static int calc(Rational num1, Rational num2) { 
        Z left = num1.numerator * Z(num2.denominator);
        Z right = num2.numerator * Z(num1.denominator);
        
        if (left > right) return 2;
        if(left < right) return 1;

        return 0;

    }
};

/**
 * @brief Оператор сокращение дроби.
 */
class Red : public UnaryOperation<Red, Rational>
{
public:
    static Rational calc(Rational num) { 
        N numerator_abs = Z::abs(num.numerator);
        N gcd = N::gcd(numerator_abs, num.denominator);
        
        if (gcd == N({1}))
            return num;
        
        Z gcd_as_int = Z(gcd.get(), false);
        num.numerator = num.numerator / gcd_as_int;
        num.denominator = num.denominator / gcd;

        return num;
    }
};


/**
 * @brief Оператор проверки того что число целое
 */
class isInt : public Mapping<isInt, bool, Rational>
{
public:
    static bool calc(Rational num) { 
        return num.denominator == N({1});
    }
};



/**
 * @brief Реализация операции сложения для Rational. Это уже именно реализация, которая зависит от типа, 
 * над которым происходи действие.
 */
class Add : public BinaryOperation<Add, Rational>, 
            public Associative, 
            public Commutative, 
            public Identity,
            public Inverse
{
public:
    static Rational calc(Rational num1, Rational num2) { 
        N common_denom = N::lcm(num1.denominator, num2.denominator);
    
        N factor_this = common_denom / num1.denominator;
        N factor_other = common_denom / num2.denominator;

        Z new_num_this = num1.numerator * Z(factor_this);
        Z new_num_other = num2.numerator * Z(factor_other);
        
        Z sum_numerator = new_num_this + new_num_other;
        
        Rational result(sum_numerator, common_denom);
        result = Red::execute(result);
        return result;
    }
};

/**
 * @brief Вычитание на рациональных числах.
 */
class Sub : public BinaryOperation<Sub, Rational>
{
public:
    static Rational calc(Rational num1, Rational num2) { 
        num2.numerator = -num2.numerator;
        return Add::execute(num1, num2);
    }
};


/**
 * @brief Умножение на рациональных числах.
 */
class Mul : public BinaryOperation<Mul, Rational>, 
            public Associative, 
            public Commutative, 
            public Identity,
            public Inverse
{
public:
    static Rational calc(Rational num1, Rational num2) { 
        Z new_numerator = num1.numerator * num2.numerator;
        N new_denominator = num1.denominator * num2.denominator;
        
        Rational result(new_numerator, new_denominator);
        result = Red::execute(result);
        return result;
    }
        
};


/**
 * @brief Деление на рациональных числах.
 */
class Div : public BinaryOperation<Div, Rational>
{
public:
    static Rational calc(Rational num1, Rational num2) { 
         if (num2.numerator  == Z(N({0})))
            throw UniversalStringException("Rational:  cannot divide by zero");
        
        Z new_numerator = num1.numerator * Z(num2.denominator);
        
        N other_num_abs = Z::abs(num2.numerator);
        N new_denominator = num1.denominator * other_num_abs;
        
        if (num2.numerator < Z(N({0})))
            new_numerator = -new_numerator;
        
        Rational result(new_numerator, new_denominator);
        result = Red::execute(result);
        return result;
    }
};


/**
 * @brief Оператор перевода рациональных числа в строку.
 */
class toString : public Mapping<toString, std::string, Rational>
{
public:
    static std::string calc(Rational num) { 
        return num.numerator.toString() + "/" + num.denominator.toString();
    }
};

}

/**
 * @brief Регистрация дистрибутивности: умножение дистрибутивно относительно сложения.
 */
template<>
struct Distributive<Rat::Mul, Rat::Add> {};  



#endif //OPERATIONS_RATIONAL_H