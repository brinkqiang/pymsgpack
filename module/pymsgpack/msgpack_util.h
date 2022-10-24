
#ifndef __MSGPACK_UTIL_H_INCLUDE__
#define __MSGPACK_UTIL_H_INCLUDE__

#include <vector>
#include "msgpack.hpp"

#define TO_MSGPACK()
inline std::vector<char> to_msgpack()\
{\
    std::stringstream ss;\
    msgpack::pack(ss, *this);\
    auto str = ss.str();\
    std::vector<char> v;\
    v.assign(str.begin(), str.end());\
    return v;\
}

#define FROM_MSGPACK()
inline void from_msgpack(const std::vector<char>& data)\
{\
    auto oh = msgpack::unpack(data.data(), data.size());\
    oh.get().convert(*this);\
}

#define EXPORT_MSGPACK() 
        TO_MSGPACK()\
        FROM_MSGPACK()

#endif // __MSGPACK_UTIL_H_INCLUDE__