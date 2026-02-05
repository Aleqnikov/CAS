#ifndef BINARY_H
#define BINARY_H

/**
 * @brief В данном файле находятся все бинарные операци для основных типов, объявлен сам интерфейс для
 * любой бинарной операции, а также объявлены основные функции, например сложение, умножение.
 */

#include "../../types/nums.h"

template<typename D, typename C>
class IBinaryOperation {
public:
	virtual C execute(const D& a, const D& b) const = 0;
};

template<typename T>
class Add : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Mul : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Sub : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Cmp : public IBinaryOperation<T, int> {
public:
	static int run(const T& a, const T& b); // Возвращает int
	int execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Div : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Rem : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Gcd : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};

template<typename T>
class Lcm : public IBinaryOperation<T, T> {
public:
	static T run(const T& a, const T& b);
	T execute(const T& a, const T& b) const override { return run(a, b); }
};




#endif //BINARY_H
