#include "stdafx.h"
#include "PathFinding.h"
#include "Base.h"

CPathFinding* CPathFinding::m_instance = 0;

CPathFinding& CPathFinding::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new CPathFinding();
    }
    return *m_instance;
}

std::vector<Vector2> CPathFinding::FindPath(Vector2 startPoint, Vector2 destinationPoint, bool ignoreDynamicMap /*= false*/)
{
    Vec2i start = ToMapCoords(startPoint);
    Vec2i destination = ToMapCoords(destinationPoint);
    if (start == destination)
    {
        std::vector<Vector2> path(1);
        path.push_back(ToWoorldCoords(start));
        return path;
    }
    if (m_staticMap[start] || m_staticMap[destination]/* || m_dynamicMap[start]*/ || (!ignoreDynamicMap && m_dynamicMap[destination]))
    {
        return std::vector<Vector2>();
    }
    CMap pathMap(m_mapWidth, m_mapHeight);
    std::deque<Vec2i> wave;
    wave.push_back(start);
    size_t counter = 0;
    Vec2i current = wave.front();

    auto checkTile = [this, &wave, &pathMap, ignoreDynamicMap, &current](int x, int y)
    {
        if (!isInMap(x, y))
        {
            return;
        }
        Vec2i next = Vec2i(x, y);
        if (!m_staticMap[next] && (ignoreDynamicMap || !m_dynamicMap[next]) && !pathMap[next])
        {
            pathMap[next] = pathMap[current] + 10;
            wave.push_back(next);
        }
    };

    auto checkCornerTile = [this, &wave, &pathMap, ignoreDynamicMap, &current](int x, int y)
    {
        if (!isInMap(x, y))
        {
            return;
        }
        Vec2i next = Vec2i(x, y);
        if (!m_staticMap[next] && (ignoreDynamicMap || !m_dynamicMap[next]) && !pathMap[next])
        {
            Vec2i check1 = Vec2i(current.X, y);
            Vec2i check2 = Vec2i(x, current.Y);
            if ((!m_staticMap[check1] && !m_dynamicMap[check1]) || (!m_staticMap[check2] && !m_dynamicMap[check2]))
            {
                pathMap[next] = pathMap[current] + 14;
                wave.push_back(next);
            }
        }
    };

    while (!wave.empty() && !pathMap[destination])
    {
        current = wave.front();
        checkTile(current.X - 1, current.Y);
        checkTile(current.X, current.Y - 1);
        checkTile(current.X + 1, current.Y);
        checkTile(current.X, current.Y + 1);
        checkCornerTile(current.X - 1, current.Y - 1);
        checkCornerTile(current.X - 1, current.Y + 1);
        checkCornerTile(current.X + 1, current.Y - 1);
        checkCornerTile(current.X + 1, current.Y + 1);
        wave.pop_front();
    }
    pathMap[start] = 0;
    if (pathMap[destination])
    {
        std::list<Vec2i> backwardPath;
        Vec2i current = destination;
        backwardPath.push_back(current);

        auto checkNext = [this, &pathMap, start, &current, &backwardPath](int x, int y, int diff)
        {
            if (!isInMap(x, y))
            {
                return;
            }
            Vec2i next = Vec2i(x, y);
            if ((pathMap[next] || next == start) && pathMap[next] == pathMap[current] - diff)
            {
                backwardPath.push_back(next);
                current = next;
            }
        };

        while (current != start)
        {
            checkNext(current.X - 1, current.Y, 10);
            checkNext(current.X, current.Y - 1, 10);
            checkNext(current.X + 1, current.Y, 10);
            checkNext(current.X, current.Y + 1, 10);
            checkNext(current.X - 1, current.Y - 1, 14);
            checkNext(current.X - 1, current.Y + 1, 14);
            checkNext(current.X + 1, current.Y - 1, 14);
            checkNext(current.X + 1, current.Y + 1, 14);
        }
        std::vector<Vector2>path(backwardPath.size());
        auto it = path.begin();
        for (auto bIt = backwardPath.rbegin(); bIt != backwardPath.rend(); bIt++, it++)
        {
            *it = ToWoorldCoords(*bIt);
        }
        return path;
    }
    else
    {
        return std::vector<Vector2>();
    }
}

std::vector<Vector2> CPathFinding::FindPath(CBasicUnit* unit, Vector2 destinationPoint, bool ignoreDynamicMap /*= false*/)
{
    Vec2i start = ToMapCoords(unit->GetPosition());
    Vec2i destination = ToMapCoords(destinationPoint);
    if (start == destination)
    {
        std::vector<Vector2> path(1);
        path.push_back(ToWoorldCoords(start));
        return path;
    }
    if (m_staticMap[start] || m_staticMap[destination]/* || m_dynamicMap[start]*/ || (!ignoreDynamicMap && m_dynamicMap[destination]))
    {
        return std::vector<Vector2>();
    }
    CMap pathMap(m_mapWidth, m_mapHeight);
    std::deque<Vec2i> wave;
    wave.push_back(start);
    size_t counter = 0;
    Vec2i current = wave.front();

    auto checkTile = [this, &wave, &pathMap, ignoreDynamicMap, &current, unit](int x, int y)
    {
        if (!isInMap(x, y))
        {
            return;
        }
        Vec2i next = Vec2i(x, y);
        if (!m_staticMap[next] && (ignoreDynamicMap || !m_dynamicMap[next] || checkTileAndUnit(next, unit)) && !pathMap[next])
        {
            pathMap[next] = pathMap[current] + 10;
            wave.push_back(next);
        }
    };

    auto checkCornerTile = [this, &wave, &pathMap, ignoreDynamicMap, &current, unit](int x, int y)
    {
        if (!isInMap(x, y))
        {
            return;
        }
        Vec2i next = Vec2i(x, y);
        if (!m_staticMap[next] && (ignoreDynamicMap || !m_dynamicMap[next] || checkTileAndUnit(next, unit)) && !pathMap[next])
        {
            Vec2i check1 = Vec2i(current.X, current.Y - 1);
            Vec2i check2 = Vec2i(current.X - 1, current.Y);
            if ((!m_staticMap[check1] && (ignoreDynamicMap || !m_dynamicMap[check1] || checkTileAndUnit(check1, unit)))
                || (!m_staticMap[check2] && (ignoreDynamicMap || !m_dynamicMap[check2] || checkTileAndUnit(check2, unit))))
            {
                pathMap[next] = pathMap[current] + 14;
                wave.push_back(next);
            }
        }
    };

    while (!wave.empty() && !pathMap[destination])
    {
        current = wave.front();
        checkTile(current.X - 1, current.Y);
        checkTile(current.X, current.Y - 1);
        checkTile(current.X + 1, current.Y);
        checkTile(current.X, current.Y + 1);
        checkCornerTile(current.X - 1, current.Y - 1);
        checkCornerTile(current.X - 1, current.Y + 1);
        checkCornerTile(current.X + 1, current.Y - 1);
        checkCornerTile(current.X + 1, current.Y + 1);
        wave.pop_front();
    }
    pathMap[start] = 0;
    if (pathMap[destination])
    {
        std::list<Vec2i> backwardPath;
        Vec2i current = destination;
        backwardPath.push_back(current);

        auto checkNext = [this, &pathMap, start, &current, &backwardPath](int x, int y, int diff)
        {
            if (!isInMap(x, y))
            {
                return;
            }
            Vec2i next = Vec2i(x, y);
            if ((pathMap[next] || next == start) && pathMap[next] == pathMap[current] - diff)
            {
                backwardPath.push_back(next);
                current = next;
            }
        };

        while (current != start)
        {
            Vec2i prev = current;
            checkNext(current.X - 1, current.Y, 10);
            checkNext(current.X, current.Y - 1, 10);
            checkNext(current.X + 1, current.Y, 10);
            checkNext(current.X, current.Y + 1, 10);
            checkNext(current.X - 1, current.Y - 1, 14);
            checkNext(current.X - 1, current.Y + 1, 14);
            checkNext(current.X + 1, current.Y - 1, 14);
            checkNext(current.X + 1, current.Y + 1, 14);
            if (prev == current)
            {
                return std::vector<Vector2>();
            }
        }
        std::vector<Vector2>path(backwardPath.size());
        auto it = path.begin();
        for (auto bIt = backwardPath.rbegin(); bIt != backwardPath.rend(); bIt++, it++)
        {
            *it = ToWoorldCoords(*bIt);
        }
        return path;
    }
    else
    {
        return std::vector<Vector2>();
    }
}

void CPathFinding::SetStaticMap(CMap& map)
{
    m_staticMap = map;
    m_mapWidth = map.GetWidth();
    m_mapHeight = map.GetHeight();
    m_dynamicMap = CMap(m_mapWidth, m_mapHeight);
}

void CPathFinding::ShredMap()
{
    CMap newMap = CMap(m_mapWidth * 2, m_mapHeight * 2);
    for (int i = 0; i < m_mapWidth; i++)
    {
        for (int j = 0; j < m_mapHeight; j++)
        {
            newMap.at(2 * i, 2 * j) = m_staticMap.at(i, j);
            newMap.at(2 * i + 1, 2 * j) = m_staticMap.at(i, j);
            newMap.at(2 * i, 2 * j + 1) = m_staticMap.at(i, j);
            newMap.at(2 * i + 1, 2 * j + 1) = m_staticMap.at(i, j);
        }
    }
    m_mapWidth *= 2;
    m_mapHeight *= 2;
    m_tileSize /= 2;
    m_staticMap = newMap;
    m_dynamicMap = CMap(m_mapWidth, m_mapHeight);
    for (int j = 0; j < m_mapHeight; j++)
    {
        for (int i = 0; i < m_mapWidth; i++)
        {
            std::cout << m_staticMap.at(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

void CPathFinding::SetDynamicMap(std::list<std::shared_ptr<CBasicUnit>>& units)
{
    m_dynamicMap = CMap(m_mapWidth, m_mapHeight);
    for (auto unit : units)
    {
        if (!dynamic_cast<CBase*>(unit.get()))
        {
            AddUnitToDynamicMap(unit);
        }
    }
}

void CPathFinding::SetTileSize(size_t size)
{
    m_tileSize = size;
}

Vector2 CPathFinding::ToWoorldCoords(Vec2i coords)
{
    Vec2i screenCoords(coords.X * m_tileSize + m_tileSize / 2, coords.Y * m_tileSize + m_tileSize / 2);
    return MathUtil::ScreenToWorld(screenCoords);
}

Vec2i CPathFinding::ToMapCoords(Vector2 coords)
{
    Vector2 screenCoords = MathUtil::WorldToScreen(coords);
    Vec2i result = Vec2i(int(screenCoords.X) / m_tileSize, int(screenCoords.Y) / m_tileSize);
    return result;
}

void CPathFinding::AddUnitToDynamicMap(std::shared_ptr<CBasicUnit> unit)
{
    auto boundingBox = unit->GetBoundingBox();
    auto bBoxMin = ToMapCoords(boundingBox.Min);
    auto bBoxMax = ToMapCoords(boundingBox.Max);
    unit->GetBody()->GetFixtureList()->TestPoint(b2Vec2());
    for (int i = min(bBoxMin.X, bBoxMax.X); i <= max(bBoxMin.X, bBoxMax.X); i++)
    {
        for (int j = min(bBoxMin.Y, bBoxMax.Y); j <= max(bBoxMin.Y, bBoxMax.Y); j++)
        {
            Vec2i tile(i, j);
            if (isInMap(i, j) && checkTileAndUnit(tile, unit.get()))
            {
                m_dynamicMap[tile] = 1;
            }
        }
    }
}

bool CPathFinding::checkTileAndUnit(Vec2i tile, CBasicUnit* unit)
{
    Vec2i screenCoords1(tile.X * m_tileSize, tile.Y * m_tileSize);
    Vec2i screenCoords2((tile.X + 1) * m_tileSize, tile.Y * m_tileSize);
    Vec2i screenCoords3(tile.X * m_tileSize, (tile.Y + 1) * m_tileSize);
    Vec2i screenCoords4((tile.X + 1) * m_tileSize, (tile.Y + 1) * m_tileSize);
    Vector2 Tile1 = MathUtil::ScreenToWorld(screenCoords1);
    Vector2 Tile2 = MathUtil::ScreenToWorld(screenCoords2);
    Vector2 Tile3 = MathUtil::ScreenToWorld(screenCoords3);
    Vector2 Tile4 = MathUtil::ScreenToWorld(screenCoords4);
    return (unit->GetBody()->GetFixtureList()->TestPoint(b2Vec2(Tile1.X, Tile1.Y)) ||
        unit->GetBody()->GetFixtureList()->TestPoint(b2Vec2(Tile2.X, Tile2.Y)) ||
        unit->GetBody()->GetFixtureList()->TestPoint(b2Vec2(Tile3.X, Tile3.Y)) ||
        unit->GetBody()->GetFixtureList()->TestPoint(b2Vec2(Tile4.X, Tile4.Y)));
}

bool CPathFinding::isInMap(int x, int y)
{
    return !(x < 0 || y < 0 || x >= m_mapWidth || y >= m_mapHeight);
}

CMap::CMap(std::vector<size_t> map, size_t width, size_t height) : m_map(map), m_mapWidth(width), m_mapHeight(height)
{

}

CMap::CMap(size_t width, size_t height) : m_mapWidth(width), m_mapHeight(height), m_map(width * height)
{

}

const size_t& CMap::at(size_t x, size_t y) const
{
    return m_map[x + y*m_mapWidth];
}

size_t& CMap::at(size_t x, size_t y)
{
    return m_map[x + y*m_mapWidth];
}

size_t& CMap::operator[](Vec2i pos)
{
    return m_map[pos.X + pos.Y*m_mapWidth];
}

size_t CMap::GetWidth() const
{
    return m_mapWidth;
}

size_t CMap::GetHeight() const
{
    return m_mapHeight;
}
