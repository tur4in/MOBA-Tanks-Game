#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "rapidxml.hpp"
#include "../ClientGame/PlaySides.h"
#include <iostream>

enum class EActorType {
	None,
	Wall,
	Base,
	Tower,
	Tank,
	SimpleMob,
	MeeleeMob,
	RangeMob,
	Flag
};

using namespace std;

struct STileInfo
{
	EActorType type;
	string src;
	ESideIdentificator side;
};

struct STmxMapTileset {
    int firstGid;
    string name;
    int tileWidth;
    int tileHeight;
    string filename;
};


struct STmxMapLayer {
    string name;
    int width;
    int height;
    int* data;
    
    ~STmxMapLayer() {
        delete [] data;
    }
};


struct STmxMap {
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    
    unique_ptr<STmxMapTileset> tileset;
    unique_ptr<STmxMapLayer> layer;
	map<int, STileInfo> tiles;
	std::string background;
};

STmxMap* LoadTmxMap(std::string const& filename);


