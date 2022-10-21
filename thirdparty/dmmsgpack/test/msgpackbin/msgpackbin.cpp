// MessagePack for C++ example
//
// Copyright (C) 2015 KONDO Takatoshi
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
#include "gtest.h"
#include <msgpack.hpp>
#include "dmfile.h"
#include "dmutil.h"
#include "msgpack_loader.hpp"

TEST(msgpack_loader, msgpack_loader)
{
    CMsgPackLoader oLoader;
    oLoader.Load();
}