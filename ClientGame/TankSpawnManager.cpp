#include "stdafx.h"
#include "TankSpawnManager.h"
#include "Tank.h"
#include "PlayerCommander.h"
#include "TunedInfo.h"

CTankSpawnPoint::CTankSpawnPoint(Vector2 pos, ESideIdentificator side) : CBasicSpawnPoint(pos, side, theTuning.GetFloat("TankSpawnDelay"), false)
{
    SetSpawnAtStart(true);
    m_tankIsDead = false;
    m_loadingActor.LoadSpriteFrames("Resources/Images/loading_sprites/load_01.png");
    m_loadingActor.SetPosition(pos);
}

void CTankSpawnPoint::Spawn(std::list<std::shared_ptr<CBasicUnit>>& list, std::unique_ptr<CBasicCommander>& commander)
{
    if (!commander->HasCommandable() && !m_tankIsDead)
    {
        m_timeTillLastSpawn = 0;
        m_tankIsDead = true;
        StartLoading();
    }
    if (m_tankIsDead && SpawnTimeIsUp())
    {
        StopLoading();
        m_tankIsDead = false;
        auto player = std::make_shared<CTank>();
        player->SetSideOfConflict(m_side);
        player->SetPosition(m_spawnPosition);
        TunedInfo::SetProps(player);
        player->SetBeem(true);
        player->InitPhysics();
        player->GetWeapon()->SetOwnedByPlayer(true);
        list.emplace_back(player);
        (dynamic_cast<CPlayerCommander*>(commander.get()))->SetTank(player);
    }

}

void CTankSpawnPoint::UpdateSpawnTime(float dt)
{
    m_timeTillLastSpawn += dt;
    if (m_loading)
    {
        UpdateLoader(dt);
    }
}

void CTankSpawnPoint::Render()
{
    if (m_loading)
    {
        m_loadingActor.Render();
    }
}

void CTankSpawnPoint::StartLoading()
{
    m_loadingActor.PlaySpriteAnimation((m_spawnDelay + theSession[m_side]->GetBasicSpawnDelay()) / 8, SAT_OneShot, 0, 7);
    m_loading = true;
}

void CTankSpawnPoint::StopLoading()
{
    m_loading = false;
}

void CTankSpawnPoint::UpdateLoader(float dt)
{
    m_loadingActor.Update(dt);
}

void CTankSpawnPoint::RenderLoader()
{
    m_loadingActor.Render();
}
