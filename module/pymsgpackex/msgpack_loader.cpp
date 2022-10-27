
#include "msgpack_loader.hpp"
#include "dmutil.h"
#include "dmfile.h"

CMsgPackLoader::CMsgPackLoader()
{

}

CMsgPackLoader::~CMsgPackLoader()
{

}

bool CMsgPackLoader::load()
{
    std::string creature_attr_def_path = DMGetWorkPath() + PATH_DELIMITER_STR + "creature_attr_def.py.bin";

    std::string strData = DMLoadFile(creature_attr_def_path);
    if (strData.empty())
    {
        return false;
    }

    msgpack::object_handle oh = msgpack::unpack(strData.data(), strData.size());
    try
    {
        oh.get().convert(creature_attr_def_info);
    }
    catch (std::exception& e)
    {
        std::cerr << "msgpack load error: " << e.what() << std::endl;
        return false;
    }
    
    return true;
}

bool CMsgPackLoader::save()
{
    //E:\svn\up1\src\Engine\Binaries\Win64\..\..\..\Server\server\engine\dm\commons\datas\

    std::string creature_attr_def_path = DMGetWorkPath() + PATH_DELIMITER_STR + "creature_attr_def.py.bin";

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, creature_attr_def_info);
    std::string strData = std::string(sbuf.data(), sbuf.size());
    return DMWriteFile(creature_attr_def_path, strData);
}
