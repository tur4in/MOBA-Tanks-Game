#pragma once
#include "TmxMap.h"
#include "Game.h"

class MapObject
{
private:
    MapObject() = delete;
    MapObject(MapObject const&) = delete;
    MapObject& operator=(MapObject const&) = delete;
    static void EmplaceBuildings(CommandList& clist, SActorTraits const& traits);
    static void EmplaceMobs(CommandList& clist, SActorTraits const& traits);
    static void EmplaceTank(CommandList& clist, SActorTraits const& traits);

public:
    static void AddSpawnerAndCommanderToList(CommandList& list, SActorTraits const& traits);
    static void AddStaticObjectToList(std::vector<std::shared_ptr<PhysicsActor>>& list, SActorTraits const& traits);
    static std::map<ESideIdentificator, Vector2> basePositions;
};