
#include "playerinfo.h"

CPlayerInfo::CPlayerInfo()
{

}

CPlayerInfo::~CPlayerInfo()
{

}

int CPlayerInfo::GetLevel()
{
    return m_nLevel;
}

const std::string& CPlayerInfo::GetName()
{
    return m_strName;
}

CPlayerInfoData::CPlayerInfoData()
{

}

CPlayerInfoData::~CPlayerInfoData()
{

}

void CPlayerInfoData::test()
{
    CPlayerInfo oInfo;
    oInfo.SetLevel(99);
    oInfo.SetName("����");

    mapInfo[oInfo.GetName()] = oInfo;
}
