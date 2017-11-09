#include "stdafx.h"
#include <iostream>
#include "TmxMap.h"
#include "PathFinding.h"



CTmxMap::CTmxMap(std::string const & filename)
{
    m_map.reset(LoadTmxMap(filename));
    CMap map(m_map->width, m_map->height);
    for (int i = 0; i < m_map->height; i++) {
        for (int j = 0; j < m_map->width; j++) {
            if (m_map->tiles[m_map->layer->data[i*GetWidth() + j] - m_map->tileset->firstGid].type == EActorType::Wall)
            {
                map.at(j, i) = 1;
            }
        }
    }
    thePath.SetStaticMap(map);
    thePath.SetTileSize(m_map->tileset->tileWidth);
    m_actualSize = m_map->width * m_map->height;
    SetNextObjectTraits();
}

std::string const & CTmxMap::GetBackground() const
{
	return m_map->background;
}

size_t CTmxMap::GetWidth() const
{
    return m_map->width;
}

size_t CTmxMap::GetHeight() const
{
    return m_map->height;
}

SActorTraits const & CTmxMap::GetCurrent() const
{
    return m_current;
}

void CTmxMap::NextObject()
{
    m_actualIndex++;
    if (m_actualIndex < m_actualSize)
    {
        SetNextObjectTraits();
    }
}

bool CTmxMap::End() const
{
    return m_actualIndex == m_actualSize;
}

void CTmxMap::SetNextObjectTraits()
{
    int tyleid = m_map->layer->data[m_actualIndex] - m_map->tileset->firstGid;
    m_current.type = m_map->tiles[tyleid].type;
    m_current.side = m_map->tiles[tyleid].side;
    m_current.is_Static = m_current.type == EActorType::Wall || m_current.type == EActorType::Flag;
    m_current.spriteSrc = m_map->tiles[tyleid].src;
    m_current.pos = Vector2(m_map->tileset->tileWidth * ((m_actualIndex) % GetWidth()) + m_map->tileset->tileWidth / 2,
        m_map->tileset->tileHeight * (m_actualIndex / GetWidth()) + m_map->tileset->tileHeight / 2);
    m_current.pos = MathUtil::ScreenToWorld(m_current.pos.X, m_current.pos.Y);
    m_current.size.X = abs((MathUtil::ScreenToWorld(m_map->tileset->tileWidth, m_map->tileset->tileHeight) - MathUtil::ScreenToWorld(0, 0)).X);
    m_current.size.Y = abs((MathUtil::ScreenToWorld(m_map->tileset->tileWidth, m_map->tileset->tileHeight) - MathUtil::ScreenToWorld(0, 0)).Y);
}
