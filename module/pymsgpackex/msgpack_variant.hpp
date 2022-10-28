
#pragma once

#include <variant>
#include <iostream>
#include "msgpack_fix32.hpp"

typedef std::variant<std::string, int64_t, double, bool, Fix32> variant_type;

class CVariant
{
public:
    CVariant() {}
    ~CVariant() {}

    variant_type value;

    template<typename T>
    T getValue()
    {
        return std::get<T>(value);
    }

    template<typename T>
    void setValue(const T& t)
    {
        value = t;
    }
};

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {

            // Place class template specialization here
            template<>
            struct convert<CVariant> {
                msgpack::object const& operator()(msgpack::object const& o, CVariant& v) const {
                    switch (o.type)
                    {
                    case MSGPACK_OBJECT_POSITIVE_INTEGER:
                    {
                        v.value = o.as<int64_t>();
                    }
                    break;
                    case MSGPACK_OBJECT_FLOAT:
                    case MSGPACK_OBJECT_FLOAT32:
                    {
                        v.value = o.as<double>();
                    }
                    break;
                    case MSGPACK_OBJECT_STR:
                    {
                        v.value = o.as<std::string>();
                    }
                    break;
                    case MSGPACK_OBJECT_BOOLEAN:
                    {
                        v.value = o.as<bool>();
                    }
                    break;
                    case MSGPACK_OBJECT_BIN:
                    {
                        v.value = o.as<std::string>();
                    }
                    break;
                    case MSGPACK_OBJECT_EXT:
                    {
                        msgpack::type::ext_ref ext(o.via.ext.ptr, o.via.ext.size + 1);
                        if (ext.type() == msgpack_ext_type_fix32)
                        {
                            v.value = msgpack_str2Fix32(ext.str());
                        }
                    }
                    break;
                    default:
                        break;
                    }
                    return o;
                }
            };

            template<>
            struct pack<CVariant> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, CVariant const& v) const {
                    // packing member variables as an array.
                    std::visit(overloaded{
                          [&](const std::string& data)
                          {
                            o.pack(data);
                          },
                          [&](int64_t data)
                          {
                            o.pack(data);
                          },
                          [&](double data)
                          {
                            o.pack(data);
                          },
                          [&](bool data)
                          {
                            o.pack(data);
                          },
                          [&](Fix32 data)
                          {
                            auto s = data.to_string();
                            msgpack::type::ext ext(msgpack_ext_type_fix32, s.data(), s.size());
                            o.pack(ext);
                          }
                        }, v.value);
                    return o;
                }
            };

            template <>
            struct object_with_zone<CVariant> {
                void operator()(msgpack::object::with_zone& o, CVariant const& v) const
                {
                }
            };
        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack