#include "stdafx.h"
#include "StatManager.h"

CStatManager* CStatManager::ms_statManager = NULL;

size_t CStatManager::GetPlayerGold(ESideIdentificator side)
{
    return m_playerCurrentGold[side];
}

void CStatManager::TakePlayerGold(size_t amountOfMoney, ESideIdentificator side)
{
    m_playerCurrentGold[side] -= amountOfMoney;
    m_playtimeInfo[side].SetDisplayString(std::to_string(m_playerCurrentGold[side]) + "G");
}

void CStatManager::GetFinalScore()
{
    for (auto it : m_playtimeInfo)
    {
        it.second.SetDisplayString(std::to_string(m_playerEntireGameGold[it.first]) + "G");
    }
}

void CStatManager::Reset()
{
    delete ms_statManager;
    ms_statManager = nullptr;
}

CStatManager::CStatManager()
{
    RegisterFont("Resources\\Fonts\\28DaysLater.ttf", 40, "ScoreConsole");
    InitSide(ESideIdentificator::Side1);
    InitSide(ESideIdentificator::Side2);
}


void CStatManager::InitSide(ESideIdentificator side)
{
    m_playerCurrentGold[side] = 0;
    m_playerEntireGameGold[side] = 0;
    m_playtimeInfo[side] = TextActor("ScoreConsole", std::to_string(m_playerCurrentGold[side]) + "G", TXT_Center);

    m_background[side].SetColor(1, 1, 1, 0.9f);
    m_background[side].SetDrawShape(ADS_Square);
    m_background[side].SetSprite("Resources/Images/gg.jpg");
    m_background[side].SetSize(2, 1);
    if (side == ESideIdentificator::Side1)
    {
        m_background[ESideIdentificator::Side1].SetPosition(MathUtil::ScreenToWorld(0, 0) +
            Vector2(m_background[ESideIdentificator::Side1].GetSize().X, -m_background[ESideIdentificator::Side1].GetSize().Y) / 2);
    }
    else if (side == ESideIdentificator::Side2)
    {
        m_background[ESideIdentificator::Side2].SetPosition(MathUtil::ScreenToWorld(theCamera.GetWindowWidth(), 0) -
            m_background[ESideIdentificator::Side2].GetSize() / 2);
    }
    m_playtimeInfo[side].SetPosition(m_background[side].GetPosition().X,
        m_background[side].GetPosition().Y - m_background[side].GetSize().Y * 0.375f);
}

CStatManager & CStatManager::GetInstance()
{
    if (ms_statManager == NULL)
    {
        ms_statManager = new CStatManager();
    }
    return *ms_statManager;
}

CStatManager::~CStatManager()
{
}

void CStatManager::ReceiveInfo(ESideIdentificator sideOfConflict, size_t bounty)
{
    m_playerCurrentGold[sideOfConflict] += bounty;
    m_playerEntireGameGold[sideOfConflict] += bounty;
    m_playtimeInfo[sideOfConflict].SetDisplayString(std::to_string(m_playerCurrentGold[sideOfConflict]) + "G");
}

void CStatManager::Render()
{
    for (auto it : m_background)
    {
        it.second.Render();
    }
    for (auto it : m_playtimeInfo)
    {
        it.second.Render();
    }
}
