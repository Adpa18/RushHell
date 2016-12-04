//
// Created by wery_a on 04/12/16.
//

#ifndef TEST_INSPECTOR_INSPECTOR_HPP
#define TEST_INSPECTOR_INSPECTOR_HPP

#include <typeinfo>
#include <iostream>

template <size_t size> struct Coffe {};

template <typename Flux, typename Object>
struct IsPrintable {

    typedef struct {char tab;} Yes;
    typedef struct {char tab[2];} No;

    template <typename Obj>
    static No   isPrintable(...);

    template <typename Obj>
    static Yes  isPrintable(Obj *a, Coffe<sizeof(*(Flux*)0 << *(Obj*)0)>* = 0);

    static const bool ISPRINTABLE = (sizeof(isPrintable<Object>((Object*)0)) == sizeof(Yes));
};

template <bool Cond, typename T = void*>
struct enable_if {
    typedef T type;
};

template <typename T>
struct enable_if<false, T> {};

template <typename Flux>
struct Printer {
    template <typename Object>
    static void print(Flux &a, Object const &o, typename enable_if<IsPrintable<Flux, Object>::ISPRINTABLE>::type* = 0) {
        a << o << std::endl;
    }

    template <typename Object>
    static void print(Flux &a, Object const &o, typename enable_if<!IsPrintable<Flux, Object>::ISPRINTABLE>::type* = 0) {
        a << typeid(o).name() << std::endl;
    }
};


template <typename Object>
void inspect(const Object& o) {
    Printer<std::ostream>::print(std::cout, o);
}

#endif //TEST_INSPECTOR_INSPECTOR_HPP
