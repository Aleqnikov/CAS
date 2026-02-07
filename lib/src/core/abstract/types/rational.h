#ifndef RATIONAL_H
#define RATIONAL_H

#include <vector>
#include <iostream>


#include "../../realization/Natural/N.h"
#include "../../realization/Integer/Z.h"

/**
 * В файлах в директории types мы, условно, задаем типы объектов, которыми мы манипулируем в программе
 * от части, они являются, в каком то смысле, множествами, над которыми выполняются операции и тп,
 * но в угоду тому, что они не могут быть бесконечными, мы ограничиваеся только описанием типо, структуры и тп.
 */


/**
 * @brief Простейшая структура рационального числа, здесь есть базовый конструктор, и базовая структура числа.
 */
struct Rational {
    Z numerator;
    N denominator;

    Rational(Z numerator, N denum) : numerator(numerator), denominator(denum) {
        if (denum == N({0})) throw UniversalStringException("denum do not be zero!");
    }
};


#endif //RATIONAL_H