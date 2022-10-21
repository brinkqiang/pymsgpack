
#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>
#include "msgpack.hpp"

class CPlayerInfo
{
public:
// export_begin
    CPlayerInfo();
    virtual ~CPlayerInfo();

    int GetLevel();
    const std::string& GetName();
    void SetLevel(int Level){ m_nLevel = Level;}
    void SetName(const std::string& strName){ m_strName = strName;}
public:
    int m_nLevel;
    std::string m_strName;
    MSGPACK_DEFINE(m_nLevel, m_strName);
// export_end
};

class CPlayerInfoData
{
public:
// export_begin
    CPlayerInfoData();
    virtual ~CPlayerInfoData();

    std::string to_msgpack();
    void from_msgpack(const std::string& data);
public:
    std::map<std::string, CPlayerInfo> mapInfo;
    MSGPACK_DEFINE(mapInfo);
// export_end
};

#endif // __PLAYER_INFO_H__