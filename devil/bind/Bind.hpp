//
// Created by wery_a on 04/12/16.
//

#ifndef TEST_INSPECTOR_BINDFUNC_HPP
#define TEST_INSPECTOR_BINDFUNC_HPP

#include "Value.hpp"
#include "TypeList.hpp"
#include "Caller.hpp"
#include "Traits.hpp"

template < typename ReturnType>
Caller <ReturnType, ReturnType(*)(void), typename Traits0::Type>
bind(ReturnType(*f)(void)) {

    typedef Traits0::Type TypeList;

    TypeList l;
    return Caller<ReturnType, ReturnType(*)(void), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1,
        typename Param1>
Caller < ReturnType, ReturnType(*)(X1), typename Traits1<Param1>::Type >
bind(ReturnType(*f)(X1), Param1 p1) {

    typedef typename Traits1<Param1>::Type TypeList;

    TypeList l(p1);
    return Caller<ReturnType, ReturnType(*)(X1), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1, typename X2,
        typename Param1, typename Param2>
Caller < ReturnType, ReturnType(*)(X1,X2), typename Traits2<Param1, Param2>::Type >
bind(ReturnType(*f)(X1, X2), Param1 p1, Param2 p2) {

    typedef typename Traits2<Param1, Param2>::Type TypeList;

    TypeList l(p1, p2);
    return Caller<ReturnType, ReturnType(*)(X1, X2), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1, typename X2, typename X3,
        typename Param1, typename Param2, typename Param3>
Caller < ReturnType, ReturnType(*)(X1,X2, X3), typename Traits3<Param1, Param2, Param3>::Type >
bind(ReturnType(*f)(X1, X2, X3), Param1 p1, Param2 p2, Param3 p3) {

    typedef typename Traits3<Param1, Param2, Param3>::Type TypeList;

    TypeList l(p1, p2, p3);
    return Caller<ReturnType, ReturnType(*)(X1, X2, X3), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1, typename X2, typename X3, typename X4,
        typename Param1, typename Param2, typename Param3, typename Param4>
Caller < ReturnType, ReturnType(*)(X1,X2, X3, X4), typename Traits4<Param1, Param2, Param3, Param4>::Type >
bind(ReturnType(*f)(X1, X2, X3, X4), Param1 p1, Param2 p2, Param3 p3, Param4 p4) {

    typedef typename Traits4<Param1, Param2, Param3, Param4>::Type TypeList;

    TypeList l(p1, p2, p3, p4);
    return Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1, typename X2, typename X3, typename X4, typename X5,
        typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
Caller < ReturnType, ReturnType(*)(X1,X2, X3, X4, X5), typename Traits5<Param1, Param2, Param3, Param4, Param5>::Type >
bind(ReturnType(*f)(X1, X2, X3, X4, X5), Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) {

    typedef typename Traits5<Param1, Param2, Param3, Param4, Param5>::Type TypeList;

    TypeList l(p1, p2, p3, p4, p5);
    return Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5), TypeList>(f, l);
}

template < typename ReturnType,
        typename X1, typename X2, typename X3, typename X4, typename X5, typename X6,
        typename Param1, typename Param2, typename Param3, typename Param4, typename Param5, typename Param6>
Caller < ReturnType, ReturnType(*)(X1,X2, X3, X4, X5, X6), typename Traits6<Param1, Param2, Param3, Param4, Param5, Param6>::Type >
bind(ReturnType(*f)(X1, X2, X3, X4, X5, X6), Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) {

    typedef typename Traits6<Param1, Param2, Param3, Param4, Param5, Param6>::Type TypeList;

    TypeList l(p1, p2, p3, p4, p5, p6);
    return Caller<ReturnType, ReturnType(*)(X1, X2, X3, X4, X5, X6), TypeList>(f, l);
}

#endif //TEST_INSPECTOR_BINDFUNC_HPP
