#ifndef BINARY_H
#define BINARY_H

/**
 * @brief В данном файле находятся все бинарные операци для основных типов, объявлен сам интерфейс для
 * любой бинарной операции, а также объявлены основные функции, например сложение, умножение.
 */

#include "types/nums.h"

template<typename T>
class IBinaryOperation {
public:
	virtual T execute(const T& a, const T& b) const = 0;
};

template<typename T>
class Add : public IBinaryOperation<T> {
public:
	static T run(const T& a, const T& b) {
		return a + b;
	}


	T execute(const T& a, const T& b) const override {
		return run(a, b);
	}
};




#endif //BINARY_H
