
#include "creature_attr_def.msgpack.hpp"
#include "dmfile.h"
#include "dmutil.h"

void creature_attr_def_data::add(const std::string& key, creature_attr_def& v)
{
    data[key] = v;
}

const creature_attr_def* creature_attr_def_data::get(const std::string& key)
{
    auto it = data.find(key);
    if (it == data.end())
    {
        return nullptr;
    }

    return &it->second;
}

vec_bin creature_attr_def_data::to_msgpack()
{
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, *this);
    vec_bin v;
    v.assign(sbuf.data(), sbuf.data() + sbuf.size());
    return std::move(v);
}

void creature_attr_def_data::from_msgpack(const vec_bin& data)
{
    auto oh = msgpack::unpack(data.data(), data.size());
    oh.get().convert(*this);
}

bool creature_attr_def_data::load()
{
    std::string creature_attr_def_path = DMGetWorkPath() + PATH_DELIMITER_STR + R"(creature_attr_def.py.bin)";

    std::string strData = DMLoadFile(creature_attr_def_path);
    if (strData.empty())
    {
        return false;
    }

    this->data.clear();

    msgpack::object_handle oh = msgpack::unpack(strData.data(), strData.size());
    try
    {
        oh.get().convert(*this);
    }
    catch (std::exception& e)
    {
        std::cerr << "CMsgPackLoader::load error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

bool creature_attr_def_data::save()
{
    std::string creature_attr_def_path = DMGetWorkPath() + PATH_DELIMITER_STR + R"(creature_attr_def.py.bin)";


    msgpack::sbuffer sbuf;
    try
    {
        msgpack::pack(sbuf, *this);
    }
    catch (std::exception& e)
    {
        std::cerr << "CMsgPackLoader::save error: " << e.what() << std::endl;
        return false;
    }

    std::string strData = std::string(sbuf.data(), sbuf.size());
    return DMWriteFile(creature_attr_def_path, strData);
}
