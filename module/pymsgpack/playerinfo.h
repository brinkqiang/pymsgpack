
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
// export_end
private:
    int m_nLevel;
    std::string m_strName;

    MSGPACK_DEFINE(m_nLevel, m_strName);
};

#endif // __PLAYER_INFO_H__