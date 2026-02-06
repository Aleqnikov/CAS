#ifndef ISOMORPHISM_H
#define ISOMORPHISM_H

#include "../mapping.h"


/**
 * В данном файле объявлен  интерфейс любого изоморфизма в программе, при реализации
 * необходимо наследоваться от него. Ответственность за соблюдение того, что отображение,
 * которое пишет, является изоморфизмом лежит целиком и полностью на человеке.
 */


/**
 * @brief Базовый класс для изоморфизмов (биективных отображений между различными структурами).
 * * Является общим случаем отображения из области определения в кообласть.
 * В отличие от операций, не требует замкнутости (типы T и Z могут быть разными).
 * * @tparam Derived Класс-реализация конкретного морфизма.
 * @tparam T Тип входного объекта (Domain).
 * @tparam Z Тип результирующего объекта (Codomain).
 * * @par Пример реализации и использования (Преобразование типа):
 * @code
 * template<typename From, typename To>
 * class Cast : public Isomorphism<Cast<From, To>, From, To> {
 * public:
 * static To calc(From a) { return static_cast<To>(a); }
 * };
 * * auto res = Cast<double, int>::execute(4.5); // Результат: 4
 * @endcode
 */
template<typename Derived, typename T, typename Z>
class Isomorphism : public Mapping<Derived, Z, T> {};

#endif //ISOMORPHISM_H