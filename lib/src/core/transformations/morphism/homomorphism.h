#ifndef HOMOMORPHISM_H
#define HOMOMORPHISM_H

#include "../mapping.h"


/**
 * В данном файле объявлен  интерфейс любого гомоморфизма в программе, при реализации
 * необходимо наследоваться от него. Ответственность за соблюдение того, что отображение,
 * которое пишет, является изоморфизмом лежит целиком и полностью на человеке.
 */


/**
 * @brief Базовый класс для гомоморфизмов (отображений между различными структурами).
 * * Является общим случаем унарного отображения из области определения (Domain) 
 * в кообласть (Codomain). В отличие от операций, не требует замкнутости (типы T и Z могут отличаться).
 * * @tparam Derived Класс-реализация конкретного морфизма.
 * @tparam T Тип входного объекта (Domain).
 * @tparam Z Тип результирующего объекта (Codomain).
 * * @par Пример реализации и использования (Преобразование типа):
 * @code
 * template<typename From, typename To>
 * class Cast : public Homomorphism<Cast<From, To>, From, To> {
 * public:
 * static To calc(From a) { return static_cast<To>(a); }
 * };
 * * auto res = Cast<double, int>::execute(4.5); // Результат: 4
 * @endcode
 */
template<typename Derived, typename T, typename Z>
class Homomorphism : public Mapping<Derived, Z, T> {};

#endif //HOMOMORPHISM_H