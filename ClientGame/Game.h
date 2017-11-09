#pragma once

#include "stdafx.h"
#include "Tank.h"
#include "TmxMap.h"
#include "BasicCommander.h"
#include "BasicSpawnManager.h"
#include "PlayerCommander.h"
#include "ExplosionSystem.h"

typedef std::unordered_map<std::string, std::pair<std::unique_ptr<CBasicCommander>, std::vector<std::unique_ptr<CBasicSpawnPoint>>>> CommandList;

class CGame
{
public:
    CGame(std::string const& levelName);
    ~CGame() = default;
	CTmxMap const& GetMap() const;
    void Update(float dt);
    void Pause();
    void Continue();
    void Render();

private:
    void ConstructLevel();
    void DeleteDeadActors();
    void Spawn(float dt);

private:
    CTmxMap m_level;
    std::list<std::shared_ptr<CBasicUnit>> m_actors;
    std::vector<std::shared_ptr<PhysicsActor>> m_staticActors;
    CommandList m_commandList;
    bool m_isActive;
};

