#ifndef INTEGER_h
#define INTEGER_h

#include <vector>
#include <iostream>


#include "../../realization/Natural/N.h"

/**
 * В файлах в директории types мы, условно, задаем типы объектов, которыми мы манипулируем в программе
 * от части, они являются, в каком то смысле, множествами, над которыми выполняются операции и тп,
 * но в угоду тому, что они не могут быть бесконечными, мы ограничиваеся только описанием типо, структуры и тп.
 */


/**
 * @brief Простейшая структура целого числа, здесь есть базовый конструктор, и базовая структура числа.
 */
struct Integer {
    N natural;
    bool is_neg;                  // false - положительный 

    // Ноль по умолчанию всегда положительный.
    Integer (N number, bool sign): natural(number), is_neg(sign)  {if (number == N({0})) is_neg = false;};
};


#endif //INTEGER_h