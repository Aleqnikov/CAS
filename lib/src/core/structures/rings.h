#ifndef RINGS_H
#define RINGS_H

#include "groups.h"

/**
 * @brief Концепт кольца.
 * 1. По сложению — Абелева группа.
 * 2. По умножению — Полугруппа.
 */
template<typename T, typename AddOp, typename MultOp>
concept Ring = 
    AbelianGroup<T, AddOp> && 
    Semigroup<T, MultOp> && 
    IsDistributive<MultOp, AddOp, T>;

/**
 * @brief Концепт кольца с единицей (Unitary Ring)
 * 1. По сложению — Абелева группа.
 * 2. По умножению — моноидом.
 */
template<typename T, typename AddOp, typename MultOp>
concept UnitaryRing = 
    Ring<T, AddOp, MultOp> && 
    Monoid<T, MultOp>;

/**
 * @brief Концепт поля
 * 1. По сложению — Абелева группа.
 * 2. По умножению — Абелева группа.
 */
template<typename T, typename AddOp, typename MultOp>
concept Field = 
    UnitaryRing<T, AddOp, MultOp> && 
    AbelianGroup<T, MultOp>;



#endif //RINGS_H