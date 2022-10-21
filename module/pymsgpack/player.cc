
#include "player.h"
#include "gtest.h"
#include "dmsnowflake.hpp"

uint64_t GNextID()
{
    static CDMIDGenerator gen;
    return gen.GetNextID();
}

CPlayer::CPlayer()
{

}

CPlayer::CPlayer(int level, const std::string& strName)
    : m_nLevel(level), m_strName(strName)
{

}

CPlayer::CPlayer(const std::string& strName)
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Init()
{

}

void CPlayer::OnChange()
{

}

void CPlayer::NotChange()
{

}

void CPlayer::SystemChange()
{

}

void CPlayer::LoadFromDB()
{

}

void CPlayer::SaveDB()
{

}


int CPlayer::GetLevel()
{
    return m_nLevel;
}

const std::string& CPlayer::GetName()
{
    return m_strName;
}
