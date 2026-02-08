#ifndef ZP_H
#define ZP_H

#include "principal_ideal_z.h"
#include "../../abstract/structures/factor.h"

/**
 * @brief Z/pZ - поле вычетов по модулю p (p простое)
 */
template<size_t p>
using Zp = FactorField<Z, PrincipalIdealZ<p>>;



#endif // ZP_H