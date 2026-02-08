# Как создавать собственный класс объектов.
Во первых, в папке types необходимо сделать тип под ваш объект. Например вот как сделан типо целых чисел 
```c++
struct Integer {
    N natural;
    bool is_neg;                  // false - положительный 

    // Ноль по умолчанию всегда положительный.
    Integer (N number, bool sign): natural(number), is_neg(sign)  {if (number == N({0})) is_neg = false;};
};
```

Затем нужно в данной директоии сделать новый папку с название вашего типа. После этого сделать файл где вы расписываете
все необходимые для вас операции, где каждая операция наследуется от типов - отображение или бинарная операция, или унарная операция. 
Для того, чтобы ваша структуру программа понимала как поле или кольцо необходимо ввести специфические тэги. Намеример сложение
целых представлено ниже
```c++
class Add : public BinaryOperation<Add, Integer>, 
            public Associative, 
            public Commutative, 
            public Identity,
            public Inverse
{
public:
    static Integer calc(Integer num1, Integer num2) { 
        N abs_this = Abs::execute(num1);
        N abs_other = Abs::execute(num2);
        
        if (getSign(num1) == getSign(num2)) {
            N sum = abs_this + abs_other;
            return Integer(sum, num1.is_neg);
        } else {


            if (abs_this == abs_other){
                return Integer(N({0}), false);
            } else if (abs_this > abs_other) {
                N diff = abs_this - abs_other;
                return Integer(diff, num1.is_neg);
            }else {
                N diff = abs_other - abs_this;
                return Integer(diff, num2.is_neg);
            }
        }
    }
};
```

Замечу, что  если вы добавляете тэги то вы должны реализовать их в классе, то есть, есть есть тэг identity то вы должны сделать
метод которые возвращяет нейтральный элемент по этой операции. \
В итоге, после описания всех операций, вы должны сделать итоговый класс ваших чисел, он должен иметь обязательные методы, и
по структуре должен быть вот таким

```c++
class Z {
private:
    Integer value;

public:
    // Определяем типы операций для концептов
    using AdditionOp = Int::Add;
    using MultiplicationOp = Int::Mul;
	using SetType = Integer;

    // Конструкторы

    // Операторы
    Z operator+(const Z& other) const { 
        return Z(Int::Add::execute(value, other.value));
    }

    Z operator*(const Z& other) const {
        return Z(Int::Mul::execute(value, other.value));
    }

    Z operator-(const Z& other) const {
        return Z(Int::Sub::execute(value, other.value));
    }

    Z operator/(const Z& other) const {
        return Z(Int::Div::execute(value, other.value));
    }

    bool isNegative() const { return value.is_neg; }

    static Z zero() { return Z(Natural({0}), false); }
    static Z identity() { return Z(Natural({1}), false); }  // Единица


    std::string toString()const {}
};
```

В итоге у вас получится новый тип, который программа будет понимать как кольцо.