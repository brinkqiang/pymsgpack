
#pragma once

#include <variant>
#include <iostream>
#include "msgpack_fix32.hpp"
#include "msgpack_variant.hpp"

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

namespace msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {

            // Place class template specialization here
            template<>
            struct convert<variant_type> {
                msgpack::object const& operator()(msgpack::object const& o, variant_type& v) const {
                    switch (o.type)
                    {
                    case MSGPACK_OBJECT_POSITIVE_INTEGER:
                    {
                        v = o.as<int64_t>();
                    }
                    break;
                    case MSGPACK_OBJECT_FLOAT:
                    case MSGPACK_OBJECT_FLOAT32:
                    {
                        v = o.as<double>();
                    }
                    break;
                    case MSGPACK_OBJECT_STR:
                    {
                        v = o.as<std::string>();
                    }
                    break;
                    case MSGPACK_OBJECT_BOOLEAN:
                    {
                        v = o.as<bool>();
                    }
                    break;
                    case MSGPACK_OBJECT_BIN:
                    {
                        v = o.as<std::string>();
                    }
                    break;
                    case MSGPACK_OBJECT_EXT:
                    {
                        msgpack::type::ext_ref ext(o.via.ext.ptr, o.via.ext.size + 1);
                        if (ext.type() == msgpack_ext_type_fix32)
                        {
                            v = msgpack_str2Fix32(ext.str());
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
            struct pack<variant_type> {
                template <typename Stream>
                packer<Stream>& operator()(msgpack::packer<Stream>& o, variant_type const& v) const {
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
                        }, v);
                    return o;
                }
            };

            template <>
            struct object_with_zone<variant_type> {
                void operator()(msgpack::object::with_zone& o, variant_type const& v) const
                {
                }
            };
        } // namespace adaptor
    } // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack