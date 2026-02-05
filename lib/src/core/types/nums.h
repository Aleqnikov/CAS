#include <iostream>
#include <vector>




/**
 * @brief В данном файле объявлены основные числовые структуры, которые есть в данной СКА.
 * Необходимы для дальнейших операций и созданий более сложных алгебраических структур.
 */



struct N  {
    std::vector<uint8_t> nums;

    N(const std::vector<uint8_t>& numsCopy) : nums(numsCopy) {}
};


struct Z
{
    N num;
    bool sign;
    Z (const N& number, bool sgn) : num(number), sign(sgn) {};
};


struct Q
{
    N numerator;
    Z denumerator;

    Q (const Z& n1, const N& n2) : denumerator(n1), numerator(n2) {};
};






