#include <iostream>
#include "ex1.h"
#include <stack>
using namespace std;

int prec(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '/':
    case '*':
        return 2;
    default:
        return 0;
    }
}

// Determines if x is in string str
int instr(char x, string str)
{
    return str.find(x) != string::npos;
}

// Returns 1 * 10 ^ (-times)
double divBy10(int times)
{
    if (times == 0)
    {
        return 1;
    }
    return divBy10(times - 1) / 10;
}
int isOp(char op)
{
    return instr(op, "-+*/");
}

Expression *applyUnary(Expression *e, op op)
{
    switch (op)
    {
    case op::UM:
        return new UMinus(e);
    case op::UP:
        return new UPlus(e);
    }
}
Expression *applyBinary(Expression *e1, Expression *e2, op op)
{
    switch (op)
    {
    case op::Mi:
        return new Minus(e1, e2);
    case op::Pl:
        return new Plus(e1, e2);
    case op::Mu:
        return new Mul(e1, e2);
    case op::Di:
        return new Div(e1, e2);
    }
}
//Interprets;
Expression *Interpreter::interpret(string exp)
{
    stack<Expression *> vals; //Values
    stack<op> ops;            //Operations
    for (int i = 0; i < exp.length; i++)
    {
        if (exp[i] == ' ')
            continue;

        if (exp[i] == '(')
            ops.push(op::OpenBracket);

        else if (instr(exp[i], DIGS)) //NumberFound
        {
            double v = 0.0;
            int decimal = 0;
            for (; i < exp.length && (instr(exp[i], DIGS) || exp[i] == '.'); i++)
            {
                if (exp[i] == '.')
                    if (decimal)
                        return nullptr;
                    else
                        decimal = 1;
                else if (decimal)
                    v += (exp[i] - '0') * divBy10(-(++decimal));
                else
                    v = v * 10 + (exp[i] - '0');
            }
            vals.push(new Value(v));
        }
        else if (exp[i] == ')')
        {
            while (!ops.empty() && ops.top() != op::OpenBracket)
            {
                auto op = ops.top();
                ops.pop();

                auto val = vals.top();
                vals.pop();

                if (op < 10)
                {
                    vals.push(applyUnary(val, op));
                }
                else
                {
                    auto val2 = vals.top();
                    vals.pop();
                    vals.push(applyBinary(val, val2, op));
                }
            }
        }
        else if (isOp(exp[i]))
        {
            switch (exp[i])
            {
            case '-':
                try
                {
                    if (exp[i + 1] == '-')
                    {
                    }
                }
                catch (exception &e)
                {
                    0;
                }

                break;
            case '+':
                break;
            case '*':
                break;
            case '/':
                break;
            default:
                break;
            }
        }
        else
        {
        }
    }
}

void Interpreter::setVariables(string exp)
{
}

int main()
{
    Interpreter *i1 = new Interpreter();
    Expression *e4 = nullptr;
    try
    {
        e4 = i1->interpret("-(2*(3+4))");
        std::cout << "4: " << e4->calculate() << std::endl; //-14
        delete e4;
        delete i1;
    }
    catch (const char *e)
    {
        if (e4 != nullptr)
        {
            delete e4;
        }
        if (i1 != nullptr)
        {
            delete i1;
        }
        std::cout << e << std::endl;
    }
}