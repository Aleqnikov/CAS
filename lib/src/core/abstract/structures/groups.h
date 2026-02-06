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
 * Пример создание какой то групповой структуры.
 * 
 * @code
 * template<typename T, typename Op>
 * requires Group<T, Op>
 * class GL {...}
 * @endcode
 */

#endif //GROUPS_H