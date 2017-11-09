#pragma once
#include <vector>
#include "BasicUnit.h"

#define theStatistic CStatManager::GetInstance()

class CStatManager
{
public:
    ~CStatManager();
    void Render();
    static void Reset();
    void GetFinalScore();
    size_t GetPlayerGold(ESideIdentificator side);
    static CStatManager& GetInstance();
    void TakePlayerGold(size_t amountOfMoney, ESideIdentificator side);
    void ReceiveInfo(ESideIdentificator sideOfConflict, size_t bounty);

private:
    static CStatManager* ms_statManager;
    std::map<ESideIdentificator, TextActor> m_playtimeInfo;
    std::map<ESideIdentificator, size_t> m_playerEntireGameGold;
    std::map <ESideIdentificator, size_t> m_playerCurrentGold;
    Actor m_background1;
    Actor m_background2;
    std::map<ESideIdentificator, Actor> m_background;

    CStatManager();
    void InitSide(ESideIdentificator side);
};

