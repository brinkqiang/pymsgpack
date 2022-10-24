
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
    std::string creature_attr_def_path = DMGetRootPath() + PATH_DELIMITER_STR + "creature_attr_def.py.bin";

    std::string strData = DMLoadFile(creature_attr_def_path);

    msgpack::object_handle oh = msgpack::unpack(strData.data(), strData.size());

    oh.get().convert(creature_attr_def_info);
    return true;
}

bool CMsgPackLoader::save()
{
    //E:\svn\up1\src\Engine\Binaries\Win64\..\..\..\Server\server\engine\dm\commons\datas\

    std::string creature_attr_def_path = DMGetRootPath() + PATH_DELIMITER_STR + "creature_attr_def.py.bin";

    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, creature_attr_def_info);
    std::string strData = std::string(sbuf.data(), sbuf.size());
    return DMWriteFile(creature_attr_def_path, strData);
}
