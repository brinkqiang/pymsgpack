
#ifndef __PLAYER_INFO_H__
#define __PLAYER_INFO_H__

#include <string>
#include "msgpack.hpp"
#include "msgpack_util.h"

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

    void test();
public:
    std::map<std::string, CPlayerInfo> mapInfo;
    MSGPACK_DEFINE(mapInfo);
    EXPORT_MSGPACK();
// export_end
};

#endif // __PLAYER_INFO_H__