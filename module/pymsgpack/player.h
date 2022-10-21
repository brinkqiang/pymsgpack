
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "creature.h"
// export_begin
uint64_t GNextID();
// export_end
#include "msgpack.hpp"

class CPlayer : public CCreature
{
public:
// export_begin
    CPlayer();
    CPlayer(int level, const std::string& strName);
    CPlayer(const std::string& strName);
    virtual ~CPlayer();

    void Init();
    void OnChange();
    void NotChange();
    void SystemChange();
    void LoadFromDB();
    void SaveDB();

    int GetLevel();
    const std::string& GetName();
// export_end
public:
    int m_nLevel;
    std::string m_strName;

    MSGPACK_DEFINE(m_nLevel, m_strName);
};

#endif // __PLAYER_H__