#include "stdafx.h"
#include "Game.h"
#include "Mob.h"
#include "Tower.h"
#include "TankSpawnManager.h"
#include "MobCommander.h"
#include "TowerCommander.h"
#include "MobSpawnManager.h"
#include "TowerSpawnPoint.h"
#include "MeeleeMobSpawnPoint.h"
#include "RangeMobSpawnPoint.h"
#include "BaseSpawnPoint.h"
#include "PathFinding.h"
#include "MapObjectFactory.h"

CGame::CGame(std::string const& levelName) : m_level(levelName)
{
    theWorld.SetupPhysics(Vector2(0, 0));
    theWorld.SetSideBlockers(true);
    ConstructLevel();
    theSpatialGraph.CreateGraph(0.5, BoundingBox(Vector2(-50, -50), Vector2(50, 50)));
    m_isActive = true;
    thePath.ShredMap();
    thePath.ShredMap();
}

CTmxMap const & CGame::GetMap() const
{
	return m_level;
}

void CGame::Update(float dt)
{
    DeleteDeadActors();
    Spawn(dt);
    thePath.SetDynamicMap(m_actors);
    for (auto & it : m_commandList)
    {
        it.second.first->Update(m_actors);
    }
    for (auto & it : m_actors)
    {
        it->Update(dt);
    }
    for (auto& it : m_staticActors)
    {
        it->Update(dt);
    }
}

void CGame::Pause()
{
    theWorld.PausePhysics();
}

void CGame::Continue()
{
    theWorld.ResumePhysics();
}

void CGame::Render()
{
    for (auto& it : m_actors)
    {
        it->RenderHighlight();
    }
    for (auto & it : m_staticActors)
    {
        it->Render();
    }
    for (auto& it : m_commandList)
    {
        for (auto & jt : it.second.second)
        {
            jt->Render();
        }
    }
    for (auto& it : m_actors)
    {
        it->Render();
    }
    for (auto& it : m_actors)
    {
        it->RenderHealthBar();
    }
}

void CGame::ConstructLevel()
{
    while (!m_level.End())
    {
        if (!m_level.GetCurrent().is_Static)
        {
            MapObject::AddSpawnerAndCommanderToList(m_commandList, m_level.GetCurrent());
        }
        else
        {
            MapObject::AddStaticObjectToList(m_staticActors, m_level.GetCurrent());
        }
        m_level.NextObject();
    }
}

void CGame::DeleteDeadActors()
{
    auto it = m_actors.begin();
    while (it != m_actors.end())
    {
        if (!(*it)->IsAlive())
        {
            (*it)->Destroy();
            it = m_actors.erase(it);
            continue;
        }
        ++it;
    }
}

void CGame::Spawn(float dt)
{
    for (auto & it : m_commandList)
    {
        for (auto & jt : it.second.second)
        {
            jt->UpdateSpawnTime(dt);
            jt->Spawn(m_actors, it.second.first);
        }
    }
}
