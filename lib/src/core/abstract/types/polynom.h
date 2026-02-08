#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <concepts>
#include "../../abstract/structures/rings.h"

/**
 * @brief Тип полинома над полем T.
 * Полином представлен как вектор коэффициентов [a0, a1, a2, ...] → a0 + a1*x + a2*x^2 + ...
 * 
 * @tparam T Тип поля (должен удовлетворять концепту Field)
 */
template<typename T>
requires Field<typename T::SetType, typename T::AdditionOp, typename T::MultiplicationOp>
struct Polynomial {
    using SetType = typename T::SetType;
    std::vector<T> coefficients;  // Коэффициенты [a0, a1, a2, ...]

	Polynomial(const std::vector<T>& coeffs) : coefficients(coeffs) {
		T zero = T::zero();

		while (coefficients.size() > 1 && coefficients.back() == zero) {
			coefficients.pop_back();
		}

		if (coefficients.empty()) {
			coefficients.push_back(zero);
		}
	}


	size_t degree() const {
		T zero = T::zero();

		if (coefficients.size() == 1 && coefficients[0] == zero) {
			return 0;
		}
		return coefficients.size() - 1;
	}
};

#endif // POLYNOMIAL_H