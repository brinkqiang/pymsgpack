
#pragma once

#include <vector>
#include "msgpack.hpp"
#include <memory>
#include <variant>
#include "msgpack_fix32.hpp"

typedef std::variant<std::string, bool, int64_t, uint64_t, float, double, Fix32, Fix32Vec2, Fix32Vec2> variant_type;

struct creature_attr_def
{
    variant_type maximun;
    variant_type minimun;
    bool use_centimeter;

    std::string key;
    variant_type def;
    std::string type;
    std::string desc;
    int64_t desc_bit;

    //MSGPACK_DEFINE(maximun, minimun, use_centimeter, key, def, type, desc, desc_bit);
};

typedef std::map<std::string, creature_attr_def> map_creature_attr_def;

struct creature_attr_def_data
{
    map_creature_attr_def defs;

    creature_attr_def* get(const std::string& key)
    {
        auto it = defs.find(key);
        if (it == defs.end())
        {
            return nullptr;
        }

        return &it->second;
    }

    void msgpack_unpack(msgpack::object const& object)
    {
        if (object.type != MSGPACK_OBJECT_ARRAY)
        {
            return;
        }
        for (int i = 0; i < object.via.array.size; i++)
        {
            auto o = object.via.array.ptr[i];

            if (o.type != MSGPACK_OBJECT_MAP)
            {
                return;
            }

            creature_attr_def def;

            for (int j = 0; j < o.via.map.size; j++)
            {

                auto __map = o.via.map.ptr[j];
                auto __key = __map.key.as<std::string>();

                variant_type vData;

                switch (__map.val.type)
                {
                case MSGPACK_OBJECT_POSITIVE_INTEGER:
                case MSGPACK_OBJECT_NEGATIVE_INTEGER:
                {
                    vData = __map.val.as<int64_t>();
                }
                break;
                case MSGPACK_OBJECT_FLOAT:
                case MSGPACK_OBJECT_FLOAT32:
                {
                    vData = __map.val.as<double>();
                }
                break;
                case MSGPACK_OBJECT_STR:
                {
                    vData = __map.val.as<std::string>();
                }
                break;
                case MSGPACK_OBJECT_BOOLEAN:
                {
                    vData = __map.val.as<bool>();
                }
                break;
                case MSGPACK_OBJECT_BIN:
                {
                    vData = __map.val.as<std::string>();
                }
                break;
                case MSGPACK_OBJECT_EXT:
                {
                    msgpack::type::ext_ref ext(__map.val.via.ext.ptr, __map.val.via.ext.size+1);
                    if (ext.type() == msgpack_ext_type_fix32)
                    {
                        vData = msgpack_str2Fix32(ext.str());
                    }
                    if (ext.type() == msgpack_ext_type_fix32Vec2)
                    {
                    }

                }
                break;
                default:
                    break;
                }

                if (__key == "maximun")
                {
                    def.maximun = vData;
                }
                else if (__key == "minimun")
                {
                    def.minimun = vData;
                }
                else if (__key == "use_centimeter")
                {
                    def.use_centimeter = std::get<bool>(vData);;
                }
                else if (__key == "key")
                {
                    def.key = std::get<std::string>(vData);
                }
                else if (__key == "default")
                {
                    def.def = vData;
                }
                else if (__key == "type")
                {
                    def.type = std::get<std::string>(vData);
                }
                else if (__key == "desc")
                {
                    def.desc = std::get<std::string>(vData);
                }
                else if (__key == "desc_bit")
                {
                    def.desc_bit = std::get<int64_t>(vData);
                }
            }

            defs[def.key] = def;
        }
    }

};

class CMsgPackLoader
{
public:
    CMsgPackLoader();
    virtual ~CMsgPackLoader();

    // interface
    bool Load();

private:

    std::shared_ptr<creature_attr_def_data> creature_attr_def_info;

};