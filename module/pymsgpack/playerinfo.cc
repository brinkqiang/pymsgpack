
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
