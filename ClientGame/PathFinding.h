#pragma once

#include "stdafx.h"
#include "BasicUnit.h"

#define thePath CPathFinding::GetInstance()

class CMap
{
public:
    CMap() = default;
    CMap(size_t width, size_t height);
    CMap(std::vector<size_t> map, size_t width, size_t height);
    size_t& at(size_t x, size_t y);
    const size_t& at(size_t x, size_t y) const;
    size_t& operator[] (Vec2i pos);
    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    size_t m_mapWidth;
    size_t m_mapHeight;
    std::vector<size_t> m_map;
};

class CPathFinding
{
public:
    static CPathFinding& GetInstance();
    std::vector<Vector2> FindPath(Vector2 start, Vector2 destination, bool ignoreDynamicMap = false);
    std::vector<Vector2> FindPath(CBasicUnit *unit, Vector2 destination, bool ignoreDynamicMap = false);
    void SetStaticMap(CMap& map);
    void ShredMap();
    void SetDynamicMap(std::list<std::shared_ptr<CBasicUnit>>& units);
    void SetTileSize(size_t size);
    Vector2 ToWoorldCoords(Vec2i);
    Vec2i ToMapCoords(Vector2);
    void AddUnitToDynamicMap(std::shared_ptr<CBasicUnit> unit);
    bool checkTileAndUnit(Vec2i tile, CBasicUnit* unit);
    bool isInMap(int x, int y);

private:
    CPathFinding() {}

private:
    static CPathFinding* m_instance;
    CMap m_staticMap;
    CMap m_dynamicMap;
    int m_mapWidth;
    int m_mapHeight;
    int m_tileSize;
};