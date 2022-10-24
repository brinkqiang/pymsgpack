
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

    void test();
public:
    std::map<std::string, CPlayerInfo> mapInfo;
    MSGPACK_DEFINE(mapInfo);


    inline std::vector<char> to_msgpack()
    {
        msgpack::sbuffer sbuf;
        msgpack::pack(sbuf, *this);
        std::vector<char> v;
        v.assign(sbuf.data(), sbuf.data() + sbuf.size());
        return v;
    }

    inline void from_msgpack(const std::vector<char>& data)
    {
        auto oh = msgpack::unpack(data.data(), data.size());
        oh.get().convert(*this);
    }
// export_end
};

#endif // __PLAYER_INFO_H__