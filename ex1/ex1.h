#include "Expression.h"

#define OPS "+-/*"
#define DIGS "0123456789"

enum op
{
    PP,
    MM,
    UP,
    UM,
    Mi = 10,
    Pl,
    Mu,
    Di,
    OpenBracket = -1,
    ClosingBracket = -2,
};
using namespace std;
/**
 * Variable Interface
 */
class Variable : public Expression
{
    string name;
    double value;

public:
    double calculate() { return GetValue(); }
    string GetName() { return name; }
    double GetValue() { return value; }
    void SetValue(double value) { this->value = value; }
    Variable(string name, double value) : name(name), value(value) {}
    Variable &operator++()
    {
        value++;
        return *this;
    }
    Variable &operator++(int)
    {
        value++;
        return *this;
    }
    Variable &operator--()
    {
        value--;
        return *this;
    }
    Variable &operator--(int)
    {
        value--;
        return *this;
    }
    Variable &operator+=(double x)
    {
        value += x;
        return *this;
    }
    Variable &operator-=(double x)
    {
        value -= x;
        return *this;
    }
    ~Variable() {}
};

/**
 * UnaryOperator Interface
 */
class UnaryOperator : public Expression
{
protected:
    Expression *e;

public:
    double calculate() { return e->calculate(); };
    UnaryOperator(Expression *e) : e(e) {}
    ~UnaryOperator() {}
};

/**
 * UPlus Interface
 */
class UPlus : public UnaryOperator
{
public:
    UPlus(Expression *e) : UnaryOperator(e) {}
    ~UPlus() {}
};

/**
 * UMinus Interface
 */
class UMinus : public UnaryOperator
{
public:
    double calculate() { return -e->calculate(); }
    UMinus(Expression *e) : UnaryOperator(e) {}
    ~UMinus() {}
};

/**
 * Value Interface
 */
class Value : public Expression
{
    double value;

public:
    double calculate() { return value; }
    Value(double value) { this->value = value; }
    ~Value() {}
};

/**
 * BinaryOperator Interface
 */
class BinaryOperator : public Expression
{
protected:
    Expression *right;
    Expression *left;

public:
    BinaryOperator(Expression *right, Expression *left) : right(right), left(left) {}
    ~BinaryOperator() {}
};

/**
 * Plus Interface
 */
class Plus : public BinaryOperator
{
public:
    double calculate() { return left->calculate() + right->calculate(); }
    Plus(Expression *right, Expression *left) : BinaryOperator(right, left) {}
    ~Plus() {}
};

/**
 * Minus Interface
 */
class Minus : public BinaryOperator
{
public:
    double calculate() { return left->calculate() - right->calculate(); }
    Minus(Expression *right, Expression *left) : BinaryOperator(right, left) {}
    ~Minus() {}
};

/**
 * Mul Interface
 */
class Mul : public BinaryOperator
{
public:
    double calculate() { return left->calculate() * right->calculate(); }
    Mul(Expression *right, Expression *left) : BinaryOperator(right, left) {}
    ~Mul() {}
};

/**
 * Div Interface
 */
class Div : public BinaryOperator
{
public:
    double calculate() { return left->calculate() / right->calculate(); }
    Div(Expression *right, Expression *left) : BinaryOperator(right, left) {}
};

/**
 * Interpreter Interface
 */
class Interpreter
{

public:
    Interpreter() {}
    Expression *interpret(string);
    void setVariables(string);
    ~Interpreter() {}
};