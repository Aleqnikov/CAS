#ifndef FACTORSTRUCTURES_H
#define FACTORSTRUCTURES_H


#include "groups.h"
#include "commuttative_algebra.h"
#include "rings.h"

/**
 * @brief В данном файле созданы основные шаблоны, методы, для создания какой либо факторструктуры.
 */


/**
 * @brief Факторкольцо R/I
 */
template<typename R, typename I>
requires UnitaryRing<typename R::SetType, typename R::AdditionOp, typename R::MultiplicationOp> 
      && Ideal<I, R>
class FactorRing {
protected:
    R representative;

public:
    FactorRing(R value) : representative(I::representative(value)) {}

    class QAdd : public BinaryOperation<QAdd, FactorRing>,
                 public Associative,
                 public Commutative,
                 public Identity,
                 public Inverse
    {
    public:
        static FactorRing calc(FactorRing a, FactorRing b) {
            R sum = a.representative + b.representative;
            return FactorRing(sum);
        }
    };

    class QMul : public BinaryOperation<QMul, FactorRing>,
                 public Associative,
                 public Commutative,
                 public Identity
    {
    public:
        static FactorRing calc(FactorRing a, FactorRing b) {
            R product = a.representative * b.representative;
            return FactorRing(product);
        }
    };

    FactorRing operator+(const FactorRing& other) const {
        return QAdd::execute(*this, other);
    }

    FactorRing operator*(const FactorRing& other) const {
        return QMul::execute(*this, other);
    }


    FactorRing operator/(const FactorRing& other) const;

    FactorRing operator-(const FactorRing& other) const {
        R diff = representative - other.representative;
        return FactorRing(diff);
    }

    bool operator==(const FactorRing& other) const {
        return representative == other.representative;
    }

    static FactorRing zero() {
        return FactorRing(R::zero());
    }

    static FactorRing identity() {
        return FactorRing(R::identity());
    }

    bool isNegative() const {
        return representative.isNegative();
    }

    const R& get() const { return representative; }

    std::string toString() const {
        return representative.toString();
    }
public:

	using SetType = FactorRing;
	using AdditionOp = QAdd;
	using MultiplicationOp = QMul;
};



/**
 * @brief Факторполе R/I (когда I максимален)
 */
template<typename R, typename I>
requires UnitaryRing<typename R::SetType, typename R::AdditionOp, typename R::MultiplicationOp> 
      && MaximalIdeal<I, R>
class FactorField : public FactorRing<R, I> {
public:
    FactorField(FactorRing<R, I> other) : FactorRing<R, I>(std::move(other)) {}

    using FactorRing<R, I>::FactorRing;

    class QAdd : public BinaryOperation<QAdd, FactorField>,
                 public Associative, public Commutative, public Identity, public Inverse
    {
    public:
        static FactorField calc(FactorField a, FactorField b) {
            return FactorField(static_cast<const FactorRing<R, I>&>(a) + static_cast<const FactorRing<R, I>&>(b));
        }
    };

    class QMul : public BinaryOperation<QMul, FactorField>,
                 public Associative, public Commutative, public Identity, public Inverse
    {
    public:
        static FactorField calc(FactorField a, FactorField b) {
            return FactorField(static_cast<const FactorRing<R, I>&>(a) * static_cast<const FactorRing<R, I>&>(b));
        }
    };

    using SetType = FactorField;
    using AdditionOp = QAdd;
    using MultiplicationOp = QMul;

    FactorField operator+(const FactorField& other) const { return QAdd::execute(*this, other); }
    FactorField operator*(const FactorField& other) const { return QMul::execute(*this, other); }

    FactorField operator/(const FactorField& other) const {
        if (other == FactorField::zero())
            throw UniversalStringException("Division by zero in field");

        return QMul::execute(*this, inverse(other));
    }


	FactorField operator-(const FactorField& other) const {
    	// Вызываем базовый оператор- и оборачиваем результат в конструктор поля
    	return FactorField(FactorRing<R, I>::operator-(other));
    }

	// Также стоит переопределить унарный минус для удобства (если он есть)
	FactorField operator-() const {
    	return FactorField(R::zero() - this->representative);
    }

private:
    static FactorField inverse(FactorField a) {
        return FactorField(R(I::compute_inverse(a.get())));
    }
};








#endif //FACTORSTRUCTURES_H