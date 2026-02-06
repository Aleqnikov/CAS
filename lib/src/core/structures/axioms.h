#ifndef AXIOMS_H
#define AXIOMS_H

#include <concepts>


/**
 * В данном файле находяся "аксиомы" для бинарных операций на множестве.
 * Они реализованы при помощи концептов cpp. Концепт проверяет что, результат
 *  операции принадлежит тому или иному типу итп. И если это не выполняется то вызывает ошибку.
 */


/**
 * @brief Аксиома (концепт) замкнутости бинарной операции.
 */
template<typename Op, typename T>
concept Сlosed = requires(T a, T b) {
    { Op::execute(a, b) } -> std::same_as<T>;
};



/**
 * @brief Аксиома (концепт) нейтрального элемента бинарной операции.
 */
template<typename T>
concept Identity = requires() {
    { T::identity() } -> std::same_as<T>;
};


/**
 * @brief Аксиома (концепт) обратного элемента бинарной операции.
 */
template<typename T>
concept Inverse = requires(T a) {
    { a.inverse() } -> std::same_as<T>;
};



/**
 * Так как компилятор не может проверить ассоциативность, коммутативность, дистрибутивность, 
 * пользователь сам должен накладывать эти теги на бинарные операции. Ответственность лежит 
 * целиком и полностью на пользователе.
 */

// Тэги которые говорят что операция выполняет какое либо свойство.
struct Associative {};
struct Commutative {};

template<typename Op1, typename Op2>
struct Distributive {};


/**
 * @brief Аксиома (концепт) ассоциативность бинарной операции.
 */
template<typename Op>
concept IsAssociative = std::derived_from<Op, Associative>;

/**
 * @brief Аксиома (концепт) коммутативность бинарной операции.
 */
template<typename Op>
concept IsCommutative = std::derived_from<Op, Commutative>;

/**
 * @brief Аксиома (концепт) дистрибутивность двух бинарных операций. 
 */
template<typename BinOp1, typename BinOp2, typename T>
concept IsDistributive = requires {
    // Проверяем, существует ли наследование от тега для этих конкретных операций
    requires std::derived_from<Distributive<BinOp1, BinOp2>, Distributive<BinOp1, BinOp2>>;
};


#endif //AXIOMS_H