//
// Created by babiole on 02/12/16.
//

#ifndef TEST_FUNCTION_FUNCTION_HPP_H
#define TEST_FUNCTION_FUNCTION_HPP_H

template <typename T>
class				Function : public T
{
public:
    Function()
    {
    }

    Function(const T &rhs)
    {
    }

    Function					&operator=(const T &rhs)
    {
        return (*this);
    }
};

template <typename T>
class				Function <T(void)>
{
    struct			IFunctor
    {
        virtual T operator()() = 0;
    };

    template <typename F>
    struct			Functor : public IFunctor
    {
        F			func;

        Functor(F _func) : func(_func)
        {
        }
        virtual T	operator()()
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

    T				operator()()
    {
        return ((*func)());
    };
private:
    IFunctor	*func;
};

template <typename T, typename  U>
class				Function <T(U)>
{
    struct			IFunctor
    {
        virtual T operator()(U arg) = 0;
    };

    template <typename F>
    struct			Functor : public IFunctor
    {
        F			func;

        Functor(F _func) : func(_func)
        {
        }
        virtual T	operator()(U arg)
        {
            return (func(arg));
        }
    };

public:
    template <typename F>
    Function(F f)
    {
        func = new Functor<F>(f);
    }

    T				operator()(U arg)
    {
        return ((*func)(arg));
    };
private:
    IFunctor	*func;
};

template <typename T, typename  U, typename V>
class				Function <T(U, V)>
{
    struct			IFunctor
    {
        virtual T operator()(U arg, V arg1) = 0;
    };

    template <typename F>
    struct			Functor : public IFunctor
    {
        F			func;

        Functor(F _func) : func(_func)
        {
        }
        virtual T	operator()(U arg, V arg1)
        {
            return (func(arg, arg1));
        }
    };

public:
    template <typename F>
    Function(F f)
    {
        func = new Functor<F>(f);
    }

    T				operator()(U arg, V arg1)
    {
        return ((*func)(arg, arg1));
    };
private:
    IFunctor	*func;
};

template <typename T, typename  U, typename V, typename W>
class				Function <T(U, V, W)>
{
    struct			IFunctor
    {
        virtual T operator()(U arg, V arg1, W arg2) = 0;
    };

    template <typename F>
    struct			Functor : public IFunctor
    {
        F			func;

        Functor(F _func) : func(_func)
        {
        }
        virtual T	operator()(U arg, V arg1, W arg2)
        {
            return (func(arg, arg1, arg2));
        }
    };

public:
    template <typename F>
    Function(F f)
    {
        func = new Functor<F>(f);
    }

    T				operator()(U arg, V arg1, W arg2)
    {
        return ((*func)(arg, arg1, arg2));
    };
private:
    IFunctor	*func;
};

#endif //TEST_FUNCTION_FUNCTION_HPP_H