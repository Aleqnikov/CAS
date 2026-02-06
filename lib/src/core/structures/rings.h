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


/**
 * Пример создания алгебраической структуры Поля (Field) на основе концепта.
 * * @code
 * template<typename T, typename AddOp, typename MulOp>
 * requires Field<T, AddOp, MulOp>
 * class FieldWrapper {
 * private:
 * T value;
 * public:
 * FieldWrapper(T v) : value(std::move(v)) {}
 * * // Операция сложения (из аддитивной абелевой группы)
 * FieldWrapper operator+(const FieldWrapper& other) const {
 * return FieldWrapper(AddOp::execute(value, other.value));
 * }
 * * // Операция умножения (из мультипликативной абелевой группы)
 * FieldWrapper operator*(const FieldWrapper& other) const {
 * return FieldWrapper(MulOp::execute(value, other.value));
 * }
 * * // Обратный элемент по сложению (ноль)
 * static FieldWrapper zero() {
 * return FieldWrapper(AddOp::get_identity());
 * }
 * * // Обратный элемент по умножению (единица)
 * static FieldWrapper one() {
 * return FieldWrapper(MulOp::get_identity());
 * }
 * };
 * @endcode
 */


#endif //RINGS_H