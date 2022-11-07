
#pragma once

#include <variant>
#include <iostream>
#include "msgpack_fix32.hpp"

typedef std::variant<std::string, int64_t, double, bool, Fix32> variant_type;

class CVariant
{
public:
// export_begin
    CVariant() {}
    ~CVariant() {}

    variant_type value;
// export_end
    //template<typename T>
    //T getValue()
    //{
    //    return std::get<T>(value);
    //}
//
    //template<typename T>
    //void setValue(const T& t)
    //{
    //    value = t;
    //}
};
