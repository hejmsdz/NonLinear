#ifndef FUNCTION_H
#define FUNCTION_H


class Function
{
public:
    virtual long double evaluate(long double x) = 0;
    virtual ~Function() {};
};

#endif // FUNCTION_H
