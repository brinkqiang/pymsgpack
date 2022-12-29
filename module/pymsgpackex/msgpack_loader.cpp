
#include "msgpack_loader.hpp"

CMsgPackLoader::CMsgPackLoader()
{
}

CMsgPackLoader::~CMsgPackLoader()
{

}

bool CMsgPackLoader::Init()
{
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
    if (!model_info.load())
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
    std::swap(oLoader.model_info, this->model_info);

    return true;
}

bool CMsgPackLoader::Save()
{
    if (!creature_attr_def_info.save())
    {
        return false;
    }
    if (!model_info.save())
    {
        return false;
    }
    return  true;
}

CMsgPackLoader* GetMsgPackLoader()
{
    return CDMSingleton<CMsgPackLoader>::Instance();
}
