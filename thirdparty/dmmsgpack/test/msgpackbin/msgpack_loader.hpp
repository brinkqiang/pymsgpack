
#pragma once

#include <vector>
#include "msgpack.hpp"
#include <memory>

struct creature_attr_def
{
    std::string maximun;
    std::string minimun;
    bool use_centimeter;

    std::string key;
    std::string def;
    std::string type;
    std::string desc;
    std::string desc_bit;

    void msgpack_unpack(msgpack::object const& o)
    {
        if (o.type != msgpack::type::MAP)
        {
            return;
        }

        for (int j = 0; j < o.via.map.size; j++)
        {
            auto map = o.via.map.ptr[j];
            auto __key = map.key.as<std::string>();

            std::string strData;

            switch (map.val.type)
            {
            case msgpack::type::POSITIVE_INTEGER:
            {
                strData = std::to_string(map.val.as<int64_t>());
            }
            break;
            case msgpack::type::STR:
            {
                strData = map.val.as<std::string>();
            }
            break;
            case msgpack::type::BOOLEAN:
            {
                strData = std::to_string(map.val.as<bool>());
            }
            break;
            case msgpack::type::BIN:
            {
                strData = map.val.as<std::string>();
            }
            break;
            default:
                break;
            }

            if (__key == "maximun")
            {
                maximun = strData;
            }
            else if(__key == "minimun")
            {
                minimun = strData;
            }
            else if (__key == "use_centimeter")
            {
                use_centimeter = std::stoi(strData);
            }
            else if (__key == "key")
            {
                key = strData;
            }
            else if (__key == "def")
            {
                def = strData;
            }
            else if (__key == "type")
            {
                type = strData;
            }
            else if (__key == "desc")
            {
                desc = strData;
            }
            else if (__key == "desc_bit")
            {
                desc_bit = strData;
            }
        }
    }
};

typedef std::vector<creature_attr_def> vec_creature_attr_def;

struct creature_attr_def_data
{
    vec_creature_attr_def creature_attr_def;
    MSGPACK_DEFINE(creature_attr_def);
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