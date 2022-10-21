
#ifndef __CREATURE_H_INCLUDE__
#define __CREATURE_H_INCLUDE__

#include "object.h"

class CCreature : public CObject
{
public:
// export_begin
    CCreature(): m_llHP(0), m_llMP(0){}
    virtual ~CCreature(){}

    int64_t GetHP(){ return m_llHP;}
    void SetHP(int64_t HP) { m_llHP = HP; }
    void AddHP(int64_t HP) { m_llHP += HP; }

    int64_t GetMP(){ return m_llMP;}
    void SetMP(int64_t MP) { m_llMP = MP; }
    void AddMP(int64_t MP) { m_llMP += MP; }
// export_end
private:
    int64_t m_llHP;
    int64_t m_llMP;
};

#endif // __CREATURE_H_INCLUDE__