
#include "msgpack_loader.hpp"
#include "dmutil.h"
#include "dmfile.h"

CMsgPackLoader::CMsgPackLoader()
: creature_attr_def_info(new creature_attr_def_data())
{

}

CMsgPackLoader::~CMsgPackLoader()
{

}

bool CMsgPackLoader::Load()
{
    //E:\svn\up1\src\Engine\Binaries\Win64\..\..\..\Server\server\engine\dm\commons\datas\

    std::string creature_attr_def_path = DMGetRootPath() + PATH_DELIMITER_STR + "creature_attr_def.py.bin";

    std::string strData = DMLoadFile(creature_attr_def_path);

    msgpack::object_handle oh =  msgpack::unpack(strData.data(), strData.size());

    oh.get().convert(creature_attr_def_info->creature_attr_def);

    return true;
}
