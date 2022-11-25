
#pragma once

#include <string>
#include "msgpack.hpp"

class Fix32 {
public:
// export_begin
    explicit Fix32() : value(0) {}
    int64_t value;
// export_end
    MSGPACK_DEFINE(value);
// export_begin
    std::string to_string()
    {
        return "Fix32(" + std::to_string(value) + ")";
    }
    std::string __str__()
    {
        return "Fix32(" + std::to_string(value) + ")";
    }
// export_end
};

class Fix32Vec2 {
public:
    Fix32 x;
    Fix32 y;
    MSGPACK_DEFINE(x, y);
};

class Fix32Vec3 {
public:
    Fix32 x;
    Fix32 y;
    Fix32 z;
    MSGPACK_DEFINE(x, y, z);
};


bool isStr(const std::string& type);
bool isUInt32(const std::string& type);
bool isFix32(const std::string& type);
bool isFixed32Vec2(const std::string& type);
bool isFixed32Vec3(const std::string& type);

Fix32 msgpack_str2Fix32(const std::string& strData);
//Fix32Vec2 msgpack_str2Fix32Vec2(const std::string& strData);
//Fix32Vec3 msgpack_str2Fix32Vec3(const std::string& strData);

enum msgpack_ext_type
{
    msgpack_ext_type_fix32 = 101,
    msgpack_ext_type_fix32Vec2 = 102,
    msgpack_ext_type_fix32Vec3 = 103,
};