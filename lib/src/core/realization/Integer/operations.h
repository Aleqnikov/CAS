#ifndef OPERATIONS_INTEGER_H
#define OPERATIONS_INTEGER_H


#include "../../abstract/types/integer.h"
#include "../Natural/N.h"

#include "../../abstract/transformations/operations/unary.h"
#include "../../abstract/transformations/operations/binary.h"


namespace Int {

/**
 * @brief Оператор модуля в целых чиселах
 */
class Abs : public Mapping<Abs, N, Integer>
{
public:
    static N calc(Integer num) { 
        return num.natural;
    }
};


// Вспомогательная функция для целых чисел
uint8_t getSign(Integer num) {
    if (!(num.natural != N({0})))
        return 0;
    return num.is_neg ? 1 : 2;
}


/**
 * @brief Оператор смены знака в целых чиселах
 */
class Neg : public UnaryOperation<Neg, Integer>
{
public:
    static Integer calc(Integer num) { 
        return Integer(num.natural, !num.is_neg);
    }
};


/**
 * @brief Реализация операции сложения для Integer. Это уже именно реализация, которая зависит от типа, 
 * над которым происходи действие.
 */
class Add : public BinaryOperation<Add, Integer>, 
            public Associative, 
            public Commutative, 
            public Identity,
            public Inverse
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        N abs_this = Abs::execute(num1);
        N abs_other = Abs::execute(num2);
        
        if (getSign(num1) == getSign(num2)) {
            N sum = abs_this + abs_other;
            return Integer(sum, num1.is_neg);
        } else {


            if (abs_this == abs_other){
                return Integer(N({0}), false);
            } else if (abs_this > abs_other) {
                N diff = abs_this - abs_other;
                return Integer(diff, num1.is_neg);
            }else {
                N diff = abs_other - abs_this;
                return Integer(diff, num2.is_neg);
            }
        }
    }
};


/**
 * @brief Умножение на целых числах.
 */
class Mul : public BinaryOperation<Mul, Integer>, 
            public Associative, 
            public Commutative, 
            public Identity
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        uint8_t sign_this = getSign(num1);
        uint8_t sign_other = getSign(num2);
        
        if (sign_this == 0 || sign_other == 0)
            return Integer(N({0}), false);
        
        N abs_this = Abs::execute(num1);
        N abs_other = Abs::execute(num2);
        N product = abs_this * abs_other;
        
        bool result_negative = (sign_this != sign_other);
        return Integer(product, result_negative);
    }
        
};

/**
 * @brief Вычитание на целых числах.
 */
class Sub : public BinaryOperation<Sub, Integer>
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        Integer neg_other = Neg::execute(num2);
        return Add::execute(num1, neg_other);
    }
};

/**
 * @brief Деление на целых числах.
 */
class Div : public BinaryOperation<Div, Integer>
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        if (getSign(num2) == 0)
            throw UniversalStringException("Integer:  cannot divide by zero");
    
        N dividend = Abs::execute(num1);
        N divisor = Abs::execute(num2);
        
        if (divisor > dividend)
            return Integer(N({0}), false);
        
        N quotient = dividend / divisor;
        Integer result(quotient, false);
        
        return (getSign(num1) != getSign(num2)) ? Neg::execute(result) : result;
    }
};

/**
 * @brief Остаток от деления на целых чисел.
 */
class Rem : public BinaryOperation<Rem, Integer>
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        if (getSign(num2) == 0)
            throw UniversalStringException("Integer: cannot divide by zero");
    
        N dividend_abs = Abs::execute(num1);
        N divisor_abs = Abs::execute(num2);
        
        if (dividend_abs < divisor_abs) {
            if (num1.is_neg) {
                return Integer(divisor_abs - dividend_abs, false);
            }
            return num1;
        }
        
        Integer quotient_result = Div::execute(num1, num2);
        Integer product = Mul::execute(num2, quotient_result);
        Integer remainder = Sub::execute(num1, product);
        
        if (remainder.is_neg) {
            remainder = Add::execute(remainder, Integer(divisor_abs, false));
        }
        
        return remainder;
    }
};

/**
 * @brief НОД целых чисел
 */
class Gcd : public BinaryOperation<Gcd, Integer>
{
public:
    static Integer calc(Integer num1, Integer num2) { 
       return Integer(N::gcd(Abs::execute(num1), Abs::execute(num2)), false);
    }
};

/**
 * @brief НОК целых чисел
 */
class Lcm : public BinaryOperation<Lcm, Integer>
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        return Integer(N::lcm(Abs::execute(num1), Abs::execute(num2)), false);
    }
};

/**
 * @brief Оператор сравнения элементов в целых числах.
 */
class Cmp : public Mapping<Cmp, int, Integer, Integer>
{
public:
    static int calc(Integer num1, Integer num2) { 
        bool sign1 = num1.is_neg;
        bool sign2 = num2.is_neg;

        if (!sign1 && sign2) return 2;  
        if (sign1 && !sign2) return 1;  

        N abs1 = Abs::execute(num1);
        N abs2 = Abs::execute(num2);

        if (abs1 == abs2) return 0; 

        bool abs1_greater = abs1 > abs2;


        if (!sign1) 
            return abs1_greater ? 2 : 1;
        

        return abs1_greater ? 1 : 2;
    }
};

/**
 * @brief Оператор перевода целых числа в строку.
 */
class toString : public Mapping<toString, std::string, Integer>
{
public:
    static std::string calc(Integer num) { 
        return (num.is_neg ? "-" : "") + num.natural.toString();
    }
};

}

/**
 * @brief Регистрация дистрибутивности: умножение дистрибутивно относительно сложения.
 */
template<>
struct Distributive<Int::Mul, Int::Add> {};  

#endif //OPERATIONS_INTEGER_H