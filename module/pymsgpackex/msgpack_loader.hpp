
#pragma once

#include <vector>
#include "msgpack.hpp"
#include <memory>
#include <variant>
#include "msgpack_fix32.hpp"
#include "msgpack_variant.hpp"
#include "msgpack_help.hpp"

typedef std::vector<char> vec_bin;

struct creature_attr_def
{
// export_begin
    creature_attr_def(){}
    virtual ~creature_attr_def(){}
    variant_type maximun;
    variant_type minimun;
    variant_type use_centimeter;
    variant_type key;
    variant_type defs;
    variant_type type;
    variant_type desc;
    variant_type desc_bit;

// export_end
    MSGPACK_DEFINE_MAP(maximun, minimun, use_centimeter, key, defs, type, desc, desc_bit);
};

//typedef std::map<std::string, creature_attr_def> map_creature_attr_def;
typedef std::map<std::string, creature_attr_def> map_creature_attr_def;

struct creature_attr_def_data
{
// export_begin
    map_creature_attr_def data;
// export_end
    MSGPACK_DEFINE_MAP(data);

// export_begin
   creature_attr_def_data(){}
   virtual ~creature_attr_def_data(){}

    void add(const std::string& key, creature_attr_def& v)
    {
        data[key] = v;
    }

    const creature_attr_def* get(const std::string& key) 
    {
        auto it = data.find(key);
        if (it == data.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    inline vec_bin to_msgpack()
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, *this);
        vec_bin v;
        v.assign(sbuf.data(), sbuf.data() + sbuf.size());
        return std::move(v);
    }

    inline void from_msgpack(const vec_bin& data)
    {
        auto oh = msgpack::unpack(data.data(), data.size());
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