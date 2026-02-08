#ifndef COMMUTATIVE_ALGEBRA_H
#define COMMUTATIVE_ALGEBRA_H

#include "groups.h"

/**
 * @brief В данном файле находятся определения, концепты для коммутативной алгебры, пока здесь есть только идеалы
 * но в дальнейшем этот раздел будет пополнятся.
 */



/**
 * Концепт идеала, необходимо чтобы он был подгруппой, коммутативность умножения.
 * 
 * Таким образом, любой класс идеала должен содержать метод, который проверят 
 * что элемент принадлежит этому идеалу.
 * А также метод, который возврящяется элемент, который возвращяет эквивалентный элемент.
 * 
 * 
 */
template<typename I, typename T>
concept Ideal = requires(typename I::element_type ideal_elem, 
                          T ring_elem) {
    // Тип элемента идеала совпадает с типом кольца
    requires std::same_as<typename I::element_type, T>;
    
    // Замкнутость относительно умножения на элементы кольца
    {  ring_elem +  ideal_elem }
        -> std::same_as<typename I::element_type>;
    {  ideal_elem * ring_elem }
        -> std::same_as<typename I::element_type>;
    
    // Методы идеала
    { I::contains(ideal_elem) } -> std::same_as<bool>;
    { I::representative(ideal_elem) } -> std::same_as<typename I::element_type>;
};      


/**
 * @brief Тэги, которые навешиваются на идеал самостоятельно!!
 * 
 * Тэг maximal нужен, если мы хоти получить фактор поле. те G/I - поле если I - максимальный идеал G.
 */
struct Maximal {};

template<typename I, typename T>
concept MaximalIdeal = Ideal<I, T> && std::derived_from<I, Maximal>;







#endif //COMMUTATIVE_ALGEBRA_H