
#pragma once

#include <vector>
#include "msgpack.hpp"
#include <memory>
#include <variant>
#include "msgpack_fix32.hpp"

typedef std::variant<std::string, bool, int64_t, uint64_t, double, Fix32> variant_type;

struct creature_attr_def
{
// export_begin
    creature_attr_def(){}
    virtual ~creature_attr_def(){}

    std::string maximun;
    std::string minimun;
    std::string use_centimeter;

    std::string key;
    std::string defs;
    std::string type;
    std::string desc;
    std::string desc_bit;
// export_end
    MSGPACK_DEFINE(maximun, minimun, use_centimeter, key, defs, type, desc, desc_bit);
};

typedef std::map<std::string, creature_attr_def> map_creature_attr_def;

struct creature_attr_def_data
{
// export_begin
    map_creature_attr_def datas;
// export_end
    MSGPACK_DEFINE(datas);

// export_begin
   creature_attr_def_data(){}
   virtual ~creature_attr_def_data(){}

    void add(const std::string& key, creature_attr_def& value)
    {
        datas[key] = value;
    }

    creature_attr_def* get(const std::string& key)
    {
        auto it = datas.find(key);
        if (it == datas.end())
        {
            return nullptr;
        }

        return &it->second;
    }


    inline std::vector<uint8_t> to_msgpack()
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, *this);
        std::vector<uint8_t> v;
        v.assign(sbuf.data(), sbuf.data() + sbuf.size());
        return std::move(v);
    }

    inline void from_msgpack(const std::vector<uint8_t>& data)
    {
        auto oh = msgpack::unpack((char*)data.data(), data.size());
        oh.get().convert(*this);
    }
// export_end
};

class CMsgPackLoader
{
public:
// export_begin
    CMsgPackLoader();
    virtual ~CMsgPackLoader();

    bool load();
    bool save();
// export_end

public:
// export_begin
    creature_attr_def_data creature_attr_def_info;
// export_end

};