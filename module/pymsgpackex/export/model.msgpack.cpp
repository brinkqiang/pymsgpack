
#include "model.msgpack.hpp"
#include "dmfile.h"
#include "dmutil.h"

void model_data::add(const std::int64_t key, model& v)
{
    data[key] = v;
}

const model* model_data::get(const std::int64_t key)
{
    auto it = data.find(key);
    if (it == data.end())
    {
        return nullptr;
    }

    return &it->second;
}

vec_bin model_data::to_msgpack()
{
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, *this);
    vec_bin v;
    v.assign(sbuf.data(), sbuf.data() + sbuf.size());
    return std::move(v);
}

void model_data::from_msgpack(const vec_bin& data)
{
    auto oh = msgpack::unpack(data.data(), data.size());
    oh.get().convert(*this);
}

bool model_data::load()
{
    std::string model_path = DMGetWorkPath() + PATH_DELIMITER_STR + R"(..\..\..\Server\server\engine\dm\commons\datas\model.py.bin)";

    std::string strData = DMLoadFile(model_path);
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

bool model_data::save()
{
    std::string model_path = DMGetWorkPath() + PATH_DELIMITER_STR + R"(..\..\..\Server\server\engine\dm\commons\datas\model.py.bin)";


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
    return DMWriteFile(model_path, strData);
}