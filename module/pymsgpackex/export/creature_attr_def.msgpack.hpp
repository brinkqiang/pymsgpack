
#ifndef __CREATURE_ATTR_DEF_MSGPACK_H_INCLUDE__
#define __CREATURE_ATTR_DEF_MSGPACK_H_INCLUDE__

#include "msgpack_variant.hpp"

struct creature_attr_def
{
    // export_begin
    creature_attr_def() {}
    virtual ~creature_attr_def() {}
    variant_type maximun;
    variant_type minimun;
    variant_type use_centimeter;
    variant_type key;
    variant_type defs;
    variant_type type;
    variant_type desc;
    variant_type desc_bit;

    std::string __str__()
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, *this);
        vec_bin v;
        v.assign(sbuf.data(), sbuf.data() + sbuf.size());

        auto oh = msgpack::unpack((char*)v.data(), v.size());
        std::stringstream ss;
        ss << oh.get();
        return ss.str();
    }
    // export_end
    MSGPACK_DEFINE_MAP(maximun, minimun, use_centimeter, key, defs, type, desc, desc_bit);


};

typedef std::map<std::string, creature_attr_def> map_creature_attr_def;

struct creature_attr_def_data
{
    // export_begin
    map_creature_attr_def data;
    // export_end
    MSGPACK_DEFINE_MAP(data);

    // export_begin
    creature_attr_def_data() {}
    virtual ~creature_attr_def_data() {}

    void add(const std::string& key, creature_attr_def& v);

    const creature_attr_def* get(const std::string& key);

    vec_bin to_msgpack();

    void from_msgpack(const vec_bin& data);

    std::string to_str();

    bool load();
    bool save();


    // export_end
};


#endif // __CREATURE_ATTR_DEF_MSGPACK_H_INCLUDE__
