#include "stdafx.h"
#include "MapObjectFactory.h"
#include "TankSpawnManager.h"
#include "TowerCommander.h"
#include "TowerSpawnPoint.h"
#include "MobCommander.h"
#include "MeeleeMobSpawnPoint.h"
#include "BaseSpawnPoint.h"
#include "RangeMobSpawnPoint.h"
#include "TakeFlag.h"

std::map<ESideIdentificator, Vector2> MapObject::basePositions;

void MapObject::EmplaceBuildings(CommandList& clist, SActorTraits const& traits)
{
    clist.try_emplace("towers", make_pair(make_unique<CTowerCommander>(), vector<unique_ptr<CBasicSpawnPoint>>()));
    switch (traits.type)
    {
    case EActorType::Base:
    {
        clist["towers"].second.emplace_back(make_unique<CBaseSpawnPoint>(traits.pos, traits.side));
        MapObject::basePositions[traits.side] = traits.pos;
    }
    break;
    case EActorType::Tower:
    {
        clist["towers"].second.emplace_back(make_unique<CTowerSpawnPoint>(traits.pos, traits.side));
    }
    break;
    }
}

void MapObject::EmplaceMobs(CommandList & clist, SActorTraits const & traits)
{
    clist.try_emplace("mobs", make_pair(make_unique<CMobCommander>(), vector<unique_ptr<CBasicSpawnPoint>>()));
    switch (traits.type)
    {
    case EActorType::MeeleeMob:
    {
        clist["mobs"].second.emplace_back(make_unique<CMeeleeMobSpawnPoint>(traits.pos, traits.side));
    }
    break;
    case EActorType::RangeMob:
    {
        clist["mobs"].second.emplace_back(make_unique<CRangeMobSpawnPoint>(traits.pos, traits.side));
    }
    break;
    case EActorType::SimpleMob:
    {
        clist["mobs"].second.emplace_back(make_unique<CMobSpawnPoint>(traits.pos, traits.side));
    }
    break;
    }
}

void MapObject::EmplaceTank(CommandList & clist, SActorTraits const & traits)
{
    switch (traits.side)
    {
    case ESideIdentificator::Side1:
    {
        clist.try_emplace("tank1", make_pair(make_unique<CPlayerKeyboardCommander>(), vector<unique_ptr<CBasicSpawnPoint>>()));
        clist["tank1"].second.emplace_back(make_unique<CTankSpawnPoint>(traits.pos, traits.side));
    }
    break;
    case ESideIdentificator::Side2:
    {
        clist.try_emplace("tank2", make_pair(make_unique<CPlayerControllerCommander>(), vector<unique_ptr<CBasicSpawnPoint>>()));
        clist["tank2"].second.emplace_back(make_unique<CTankSpawnPoint>(traits.pos, traits.side));
    }
    break;
    }
}

void MapObject::AddSpawnerAndCommanderToList(CommandList& clist, SActorTraits const& traits)
{
    using namespace std;

    switch (traits.type)
    {
    case EActorType::Base:
    case EActorType::Tower:
    {
        EmplaceBuildings(clist, traits);
    }
    break;
    case EActorType::SimpleMob:
    case EActorType::MeeleeMob:
    case EActorType::RangeMob:
    {
        EmplaceMobs(clist, traits);
    }
    break;
    case EActorType::Tank:
    {
        EmplaceTank(clist, traits);
    }
    break;
    }
}

void MapObject::AddStaticObjectToList(std::vector<std::shared_ptr<PhysicsActor>>& list, SActorTraits const & traits)
{
    switch (traits.type)
    {
    case EActorType::Wall:
    {
        auto wall = make_shared<PhysicsActor>();
        wall->SetDensity(0);
        wall->SetSprite(traits.spriteSrc);
        wall->SetPosition(traits.pos);
        wall->SetSize(traits.size.X, traits.size.Y);
        wall->SetFriction(0.0f);
        wall->InitPhysics();
        list.emplace_back(wall);
    }
    break;
    case EActorType::Flag:
    {
        auto flag = make_shared<CCaptureFlag>();
        flag->SetPosition(traits.pos);
        flag->SetSprite(theTuning.GetString("BaseSprite"));
        flag->Initialize();
        list.emplace_back(flag);
    }
    break;
    }
}
