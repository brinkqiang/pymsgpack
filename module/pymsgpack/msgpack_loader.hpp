
#pragma once

#include <vector>
#include "msgpack.hpp"
#include <memory>
#include <variant>
#include "msgpack_fix32.hpp"

struct creature_attr_def
{
// export_begin
    std::string maximun;
    std::string minimun;
    std::string use_centimeter;

    std::string key;
    std::string def;
    std::string type;
    std::string desc;
    std::string desc_bit;
// export_end
    MSGPACK_DEFINE(maximun, minimun, use_centimeter, key, def, type, desc, desc_bit);
};

typedef std::map<std::string, creature_attr_def> map_creature_attr_def;

struct creature_attr_def_data
{
// export_begin
    map_creature_attr_def defs;
// export_end
    MSGPACK_DEFINE(defs);

// export_begin
    creature_attr_def* get(const std::string& key)
    {
        auto it = defs.find(key);
        if (it == defs.end())
        {
            return nullptr;
        }

        return &it->second;
    }


    inline std::vector<char> to_msgpack()
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, *this);
        std::vector<char> v;
        v.assign(sbuf.data(), sbuf.data() + sbuf.size());
        return std::move(v);
    }

    inline void from_msgpack(const std::vector<char>& data)
    {
        auto oh = msgpack::unpack(data.data(), data.size());
        oh.get().convert(*this);
    }
// export_end
};

class CMsgPackLoader
{
public:
    CMsgPackLoader();
    virtual ~CMsgPackLoader();

// export_begin
    bool load();
    bool save();
// export_end

private:

    std::shared_ptr<creature_attr_def_data> creature_attr_def_info;

};