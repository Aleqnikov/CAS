#include <iostream>
#include "core/realization/Integer/Z.h"
#include "core/realization/Rational/Q.h"
#include "core/realization/Polynomial/P[x].h"
#include "core/realization/deductionclass/pZ.h"



int main() {
	// Z/5Z - поле из 5 элементов
	Zp<5> a(Z(N({6})));  // 3
	Zp<5> b(Z(N({4})));  // 4

	P<Zp<5>> poly({a ,b});

	std::cout << poly.toString() << std::endl;

	auto res = poly + poly;

	std::cout << res.toString() << std::endl;
    return 0;
}