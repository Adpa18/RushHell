//
// Created by wery_a on 04/12/16.
//

#ifndef TEST_INSPECTOR_CALLER_HPP
#define TEST_INSPECTOR_CALLER_HPP

#include "Traits.hpp"

template <typename ReturnType, typename Callable, typename List>
class Caller {
public:
    Caller(Callable const &callable, List const &list): m_callable(callable), m_list(list) {

    };

    ReturnType  operator()() {
        TypeTraits<ReturnType>  t;
        return m_list(t, m_callable, m_list);
    }

    template <typename T1>
    ReturnType  operator()(T1 &t1) {
        TypeTraits<ReturnType>  t;
        typename Traits1<T1>::Type l(t1);
        return m_list(t, m_callable, l);
    }

    template <typename T1, typename T2>
    ReturnType  operator()(T1 &t1, T2 &t2) {
        TypeTraits<ReturnType>  t;
        typename Traits2<T1, T2>::Type l(t1, t2);
        return m_list(t, m_callable, l);
    }

    template <typename T1, typename T2, typename T3>
    ReturnType  operator()(T1 &t1, T2 &t2, T3 &t3) {
        TypeTraits<ReturnType>  t;
        typename Traits3<T1, T2, T3>::Type l(t1, t2, t3);
        return m_list(t, m_callable, l);
    }

    template <typename T1, typename T2, typename T3, typename T4>
    ReturnType  operator()(T1 &t1, T2 &t2, T3 &t3, T4 &t4) {
        TypeTraits<ReturnType>  t;
        typename Traits4<T1, T2, T3, T4>::Type l(t1, t2, t3, t4);
        return m_list(t, m_callable, l);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5>
    ReturnType  operator()(T1 &t1, T2 &t2, T3 &t3, T4 &t4, T5 t5) {
        TypeTraits<ReturnType>  t;
        typename Traits5<T1, T2, T3, T4, T5>::Type l(t1, t2, t3, t4, t5);
        return m_list(t, m_callable, l);
    }

    template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    ReturnType  operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6) {
        TypeTraits<ReturnType>  t;
        typename Traits6<T1, T2, T3, T4, T5, T6>::Type l(t1, t2, t3, t4, t5, t6);
        return m_list(t, m_callable, l);
    }

private:
    Callable    m_callable;
    List        m_list;
};


#endif //TEST_INSPECTOR_CALLER_HPP

