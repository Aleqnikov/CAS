#ifndef GROUPS_H
#define GROUPS_H

#include "axioms.h"

/**
 * В данном файла определены все возможные групповые стрктуры, которые могут быть.
 * Выполнимость аксиом - ответственность человека.
 */


/**
 * @brief Концепт магмы (группойда) 
 */
template<typename T, typename Op>
concept Magma = Closed<Op, T>;

/**
 * @brief Концепт полугруппы 
 */
template<typename T, typename Op>
concept Semigroup = Magma<T, Op> && IsAssociative<Op>;

/**
 * @brief Концепт моноида 
 */
template<typename T, typename Op>
concept Monoid = Semigroup<T, Op> && HasIdentity<Op>;

/**
 * @brief Концеп группы 
 */
template<typename T, typename Op>
concept Group = Monoid<T, Op> && HasInverse<Op>;

/**
 * @brief Концепт Абелевой группы
 */
template<typename T, typename Op>
concept AbelianGroup = Group<T, Op> && IsCommutative<Op>;       



/**
 * @brief Концепт подгруппы
 * 
 * То есть он говорит, что группа должна иметь метод принадлежности, а также перегруженные операции сложения
 * и унарного минуса. Определять принадлежит ли ей элемент.
 */
template<typename H, typename G>
concept Subgroup = requires(H subgroup, typename H::element_type h_elem) {

    requires Group<H, typename H::AdditionOp>;
    
    // Элементы H принадлежат G
    requires std::same_as<typename H::element_type, typename G::element_type>;
    
    // Проверка принадлежности
    { subgroup.contains(h_elem) } -> std::same_as<bool>;
    
    // Замкнутость
    requires requires(typename H::element_type a, typename H::element_type b) {
        { a + b } -> std::same_as<typename H::element_type>;
        { -a } -> std::same_as<typename H::element_type>;
    };
};



/**
 * Пример создание какой то групповой структуры.
 * 
 * @code
 * template<typename T, typename Op>
 * requires Group<T, Op>
 * class GL {...}
 * @endcode
 */

#endif //GROUPS_H