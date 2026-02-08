#ifndef PRINCIPAL_IDEAL_Z_H
#define PRINCIPAL_IDEAL_Z_H

#include "../Integer/Z.h"
#include "../../abstract/structures/commuttative_algebra.h"


/**
 * @brief Главный идеал в Z, порожденный элементом n
 * I = nZ = {n·k | k ∈ Z}
 */
template<size_t n>
class PrincipalIdealZ : public Maximal {  
public:
    using element_type = Z;

    static constexpr size_t generator = n;
    
    static bool contains(Z x) {
        Z n_z = makeZ(n);
        return (x % n_z) == Z::zero();
    }
    
    static Z representative(Z x) {
        Z n_z = makeZ(n);
        Z rem = x % n_z;
        
        // Приводим к [0, n)
        if (rem.isNegative()) {
            rem = rem + n_z;
        }
        return rem;
    }
    
    static Z compute_inverse(Z a) {
        return modular_inverse(a, makeZ(n));
    }

private:
    static Z makeZ(size_t value) {
        std::vector<uint8_t> digits;
        if (value == 0) {
            digits.push_back(0);
        } else {
            while (value > 0) {
                digits.push_back(value % 10);
                value /= 10;
            }
        }
        return Z(Natural(digits), false);
    }
    
    static Z modular_inverse(Z a, Z mod) {
        Z t = Z::zero(), newt = Z::identity();
        Z r = mod, newr = a;
        
        while (newr != Z::zero()) {
            Z quotient = r / newr;
            
            Z temp_t = t;
            t = newt;
            newt = temp_t - quotient * newt;
            
            Z temp_r = r;
            r = newr;
            newr = temp_r - quotient * newr;
        }
        
        if (r > Z::identity()) {
            throw UniversalStringException("Element is not invertible");
        }
        
        if (t.isNegative()) {
            t = t + mod;
        }
        
        return t;
    }
};


#endif // PRINCIPAL_IDEAL_Z_H