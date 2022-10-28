

#include "msgpack_fix32.hpp"

bool isStr(const std::string& type)
{
    return type == "Str";
}

bool isUInt32(const std::string& type)
{
    return type == "UInt32";
}

bool isFix32(const std::string& type)
{
    return type == "Fixed";
}

bool isFixed32Vec2(const std::string& type)
{
    return type == "Fixed32Vec2";
}

bool isFixed32Vec3(const std::string& type)
{
    return type == "Fixed32Vec3";
}

Fix32 msgpack_str2Fix32(const std::string& strData)
{
    Fix32 fix32 {0};
    int len = strlen("Fix32(");

    const char* p = strstr(strData.c_str(), "Fix32(");
    if (nullptr == p)
    {
        return fix32;
    }

    auto back = strData.back();
    if (back != ')')
    {
        return fix32;
    }

    std::string strRet = strData.data() + len;
    strRet.pop_back();
    fix32.value = stoll(strRet);
    return fix32;
}
//Fix32Vec2 msgpack_str2Fix32Vec2(const std::string& strData)
//{
//    return Fix32Vec2::from_string(strData.c_str());
//}
//
//Fix32Vec3 msgpack_str2Fix32Vec3(const std::string& strData)
//{
//    return Fix32Vec3::from_string(strData.c_str());
//}
