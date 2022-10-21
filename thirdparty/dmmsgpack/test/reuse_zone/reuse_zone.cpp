// MessagePack for C++ example
//
// Copyright (C) 2015 KONDO Takatoshi
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
#include "gtest.h"
#include <iostream>
#include <sstream>
#include <cassert>

#include <string>
#include <vector>

#include <msgpack.hpp>


TEST(reuse_zone,reuse_zone) {
    std::vector<int> v;
    v.push_back(1);
    v.push_back(42);
    std::string s("ABC");

    std::stringstream ss;
    msgpack::pack(ss, v);
    msgpack::pack(ss, s);

    msgpack::zone z;
    std::size_t offset = 0;

    // msgpack array is constructed on z.
    std::string const& ps = ss.str();
    msgpack::object obj = msgpack::unpack(z, ps.data(), ps.size(), offset);
    std::cout << obj << std::endl;
    assert(obj.as<std::vector<int> >() == v);

    // msgpack str is constructed on z.
    std::string const& str = msgpack::unpack(z, ps.data(), ps.size(), offset).as<std::string>();
    std::cout << str << std::endl;
    assert(str == s);
}
