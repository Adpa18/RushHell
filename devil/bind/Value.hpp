//
// Created by wery_a on 04/12/16.
//

#ifndef TEST_INSPECTOR_VALUE_HPP
#define TEST_INSPECTOR_VALUE_HPP

template <typename T>
class Value {
public:
    Value(T &value): m_value(value) {};

private:
    T   &m_value;

public:
    T   &get(void) {
        return m_value;
    }

    T const &get(void) const {
        return m_value;
    }
};

template <typename T>
class GetType {
public:
    typedef Value<T>    Type;
};

template <typename T>
class TypeTraits {};



#endif //TEST_INSPECTOR_VALUE_HPP
