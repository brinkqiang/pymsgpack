
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

std::wstring CPlayerInfoData::to_msgpack()
{
    msgpack::sbuffer sbuf;
    msgpack::pack(sbuf, *this);
    return std::wstring(sbuf.data(), sbuf.size());
}

void CPlayerInfoData::from_msgpack(const std::wstring& data)
{
   auto oh = msgpack::unpack(data.data(), data.size());
   oh.get().convert(*this);
}
