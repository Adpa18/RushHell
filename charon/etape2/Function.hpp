//
// Created by babiole on 02/12/16.
//

#ifndef TEST_FUNCTION_FUNCTION_HPP_H
#define TEST_FUNCTION_FUNCTION_HPP_H

template <typename  T>
class Function : public T
{
public:
    Function() {};

    Function(const T &func) {};

    Function &operator=(const T &func)
    {
        return (*this);
    }
};

template <typename  T>
class Function<T(void)>
{
    struct IFunctor
    {
        virtual T operator()() = 0;
        virtual ~IFunctor() {};
    };

    template <typename F>
    struct Functor : IFunctor
    {
        F func;

        Functor(F _func) : func(_func) {}

        virtual T operator()()
        {
            return (func());
        }
    };
public:
    template <typename F>
    Function(F f)
    {
        func = new Functor<F>(f);
    }

    T operator()()
    {
        return ((*func());
    }

private:
    IFunctor *func;
};
#endif //TEST_FUNCTION_FUNCTION_HPP_H
