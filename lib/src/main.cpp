#include <iostream>
#include "core/realization/Integer/Z.h"
#include "core/realization/Rational/Q.h"
#include "core/realization/Polynomial/P[x].h"


int main() {
    Z n1(Natural({1}), false);
    N n2({1});

	Q n3(n1, n2);
	P<Q> poly({n3, n3});


	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 7; i++)
		poly = poly * poly;

	auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    std::cout << "Execution time 1: " << duration.count() << " ms" << std::endl;



	auto start1 = std::chrono::high_resolution_clock::now();
    std::cout << "Result: " << (poly  ).toString() << std::endl;


	auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;

    std::cout << "Execution time 2: " << duration1.count() << " ms" << std::endl;
    return 0;
}