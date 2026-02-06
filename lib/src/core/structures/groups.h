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
concept Monoid = Semigroup<T, Op> && Identity<T>;

/**
 * @brief Концеп группы 
 */
template<typename T, typename Op>
concept Group = Monoid<T, Op> && Inverse<T>;

/**
 * @brief Концепт Абелевой группы
 */
template<typename T, typename Op>
concept AbelianGroup = Group<T, Op> && IsCommutative<Op>;                                                         
                                                                

#endif //GROUPS_H