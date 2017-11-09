#pragma once
#include "LowLevelTmxMap.hpp"
#include "stdafx.h"
#include "BasicUnit.h"

enum class EObjectType
{
    None = 0,
    Wall,
    Tank1,
    Tank2,
    SimpleMob1Spawn,
    SimpleMob2Spawn,
    Tower1,
    Tower2,
    Base1,
    Base2,
    MeeleeMobs1Spawn,
    MeeleeMobs2Spawn,
    RangeMobs1Spawn,
    RangeMobs2Spawn,
    Flag
};

struct SActorTraits
{
    bool is_Static;
    ESideIdentificator side;
    EActorType type;
    string spriteSrc;
    Vector2 pos;
    Vector2 size;
};

class CTmxMap
{
public:
    CTmxMap(std::string const & filename);
    ~CTmxMap() = default;
	std::string const& GetBackground() const;
    size_t GetWidth() const;
    size_t GetHeight() const;
    SActorTraits const & GetCurrent() const;
    void NextObject();
    bool End() const;

private:
    void SetNextObjectTraits();

private:
    std::unique_ptr<STmxMap> m_map;
    SActorTraits m_current;
    size_t m_actualSize;
    size_t m_actualIndex = 0;
};

