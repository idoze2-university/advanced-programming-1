
#include "Expression.h"
using namespace std;
/**
 * Variable Interface
 */
class Variable : Expression
{
    string name;
    double value;

public:
    double calculate() { return GetValue(); }
    string GetName() { return name; }
    double GetValue() { return value; }
    Variable(string name, double value)
    {
        this->name = name;
        this->value = value;
    }
    Variable *operator++() { this->value++; }
    Variable operator++(int) { this->value++; }
    Variable operator--() { this->value--; }
    Variable operator--(int) { this->value--; }
    virtual ~Variable() {}
};

/**
 * UnaryOperator Interface
 */
class UnaryOperator : Expression
{
    Expression *e;

public:
    double calculate() { return e->calculate(); };
    UnaryOperator(Expression *e)
    {
        this->e = e;
    }
};
