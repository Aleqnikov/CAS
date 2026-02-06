#ifndef BINARY_H
#define BINARY_H

#include "../mapping.h"


/**
 * В данном файле объявлен  интерфейс любой бинарной операции
 * при создании любой операции, необходимо наследоваться от него, это необходимо
 * для универсальной типизации СКА. Предполагается, что бинарная операция, это преобразование
 * множества в себя, поэтому на вход она получает два объекта одного типа, и возвращяет на 
 * выход новый объект того же типа. 
 */



/**
 * @brief Базовый класс для бинарных операций, являющийся частным случаем отображения (Mapping).
 * * Реализует паттерн  для статического полиморфизма. Фиксирует n-арность (2) и 
 * замкнутость операции на множестве @p T (T x T -> T).
 * * @tparam Derived Класс-наследник, реализующий логику calc.
 * @tparam T Тип данных (математическое множество), над которым определена операция Codomain = Domain.
 * * @par Пример реализации и использования:
 * @code
 * template<typename Type>
 * class Add : public BinaryOperation<Add<Type>, Type> {
 * public:
 * static Type calc(Type a, Type b) { return a + b; }
 * };
 * * auto res = Add<int>::execute(4, 4);
 * @endcode
 */
template<typename Derived, typename T>
class BinaryOperation : public Mapping<Derived, T, T, T> {};

#endif //BINARY_H