
#pragma once

#ifndef __MSGPACK_LOADER_H_INCLUDE__
#define __MSGPACK_LOADER_H_INCLUDE__

#include <vector>
#include <memory>
#include <variant>

#include "dmsingleton.h"
#include "data.msgpack.hpp"

/* in python

import framecore
node = framecore.GetMsgPackLoader().creature_attr_def_info.get("bar_name")
print(node.key.getValue())
obj = creature_attr_def()
obj.key.setValue("12345")
obj.type.setValue("67890")
GetMsgPackLoader().creature_attr_def_info.add("12345", obj)
obj2 = GetMsgPackLoader().creature_attr_def_info.get("12345")
print(obj2.key.getValue())
print(obj2.type.getValue())

*/

class CMsgPackLoader
{
public:
// export_begin
    CMsgPackLoader();
    virtual ~CMsgPackLoader();

    virtual bool Init();
    virtual bool UnInit();

    bool Load();
    bool Reload();

    bool Save();
// export_end

public:
// export_begin
    creature_attr_def_data creature_attr_def_info;
    model_data             model_info;
// export_end

};
// export_begin
CMsgPackLoader* GetMsgPackLoader();
// export_end

#define gCMsgPackLoader  CDMSingleton<CMsgPackLoader>::Instance()

#endif // __MSGPACK_LOADER_H_INCLUDE__
