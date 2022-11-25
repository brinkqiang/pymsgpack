
#include "msgpack_loader.hpp"
#include "data.py.inl"
#include "creature_attr_def.py.inl"
#include "msgpack_loader.inl"

CMsgPackLoader::CMsgPackLoader()
{
}

CMsgPackLoader::~CMsgPackLoader()
{

}

bool CMsgPackLoader::Init()
{
    data_init_py();
    creature_attr_def_init_py();
    msgpack_loader_init_py();

    if (!Load())
    {
        return false;
    }

    return true;
}

bool CMsgPackLoader::UnInit()
{
    return true;
}


bool CMsgPackLoader::Load()
{
    if (!creature_attr_def_info.load())
    {
        return false;
    }
    return true;
}

bool CMsgPackLoader::Reload()
{
    CMsgPackLoader oLoader;
    if (!oLoader.Load())
    {
        return false;
    }

    std::swap(oLoader.creature_attr_def_info, this->creature_attr_def_info);

    return true;
}

bool CMsgPackLoader::Save()
{
    if (!creature_attr_def_info.save())
    {
        return false;
    }

    return  true;
}

CMsgPackLoader* GetMsgPackLoader()
{
    return CDMSingleton<CMsgPackLoader>::Instance();
}
