//
// Created by wery_a on 04/12/16.
//

#ifndef TEST_INSPECTOR_TRAITS_HPP
#define TEST_INSPECTOR_TRAITS_HPP

#include "Value.hpp"
#include "TypeList.hpp"

struct Traits0 {
    typedef TypeList0   Type;
};

template <typename P1>
struct Traits1 {
    typedef typename GetType<P1>::Type TP1;
    typedef TypeList1 <TP1> Type;
};

template < typename P1, typename P2>
struct Traits2 {
    typedef typename GetType < P1 >::Type TP1;
    typedef typename GetType < P2 >::Type TP2;
    typedef TypeList2 < TP1, TP2> Type;
};

template < typename P1, typename P2, typename P3>
struct Traits3 {
    typedef typename GetType < P1 >::Type TP1;
    typedef typename GetType < P2 >::Type TP2;
    typedef typename GetType < P3 >::Type TP3;
    typedef TypeList3 < TP1, TP2, TP3> Type;
};

template < typename P1, typename P2, typename P3, typename P4>
struct Traits4 {
    typedef typename GetType < P1 >::Type TP1;
    typedef typename GetType < P2 >::Type TP2;
    typedef typename GetType < P3 >::Type TP3;
    typedef typename GetType < P4 >::Type TP4;
    typedef TypeList4 < TP1, TP2, TP3, TP4> Type;
};

template < typename P1, typename P2, typename P3, typename P4, typename P5>
struct Traits5 {
    typedef typename GetType < P1 >::Type TP1;
    typedef typename GetType < P2 >::Type TP2;
    typedef typename GetType < P3 >::Type TP3;
    typedef typename GetType < P4 >::Type TP4;
    typedef typename GetType < P5 >::Type TP5;
    typedef TypeList5 < TP1, TP2, TP3, TP4, TP5> Type;
};

template < typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
struct Traits6 {
    typedef typename GetType < P1 >::Type TP1;
    typedef typename GetType < P2 >::Type TP2;
    typedef typename GetType < P3 >::Type TP3;
    typedef typename GetType < P4 >::Type TP4;
    typedef typename GetType < P5 >::Type TP5;
    typedef typename GetType < P6 >::Type TP6;
    typedef TypeList6 < TP1, TP2, TP3, TP4, TP5, TP6> Type;
};

#endif //TEST_INSPECTOR_TRAITS_HPP
