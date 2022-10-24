
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
    oInfo.SetName("ÖÐÎÄ");

    mapInfo[oInfo.GetName()] = oInfo;
}

std::vector<char> CPlayerInfoData::to_msgpack()
{
    std::stringstream ss;
    msgpack::pack(ss, *this);
    auto str = ss.str();
    std::vector<char> v;
    v.assign(str.begin(), str.end());
    return v;
}

void CPlayerInfoData::from_msgpack(const std::vector<char>& data)
{
   auto oh = msgpack::unpack(data.data(), data.size());
   oh.get().convert(*this);
}
