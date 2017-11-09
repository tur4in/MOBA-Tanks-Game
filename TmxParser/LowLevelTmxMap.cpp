#include "LowLevelTmxMap.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

void SetTileSide(std::string const& side, STileInfo& tile)
{
	if (side == "1")
	{
		tile.side = ESideIdentificator::Side1;
	}
	else if (side == "2")
	{
		tile.side = ESideIdentificator::Side2;
	}
	else if (side == "n")
	{
		tile.side = ESideIdentificator::Neutrals;
	}
}

void SetTileType(std::string const& type, STileInfo& tile)
{
	if (type == "wall")
	{
		tile.type = EActorType::Wall;
	}
	else if (type == "tank")
	{
		tile.type = EActorType::Tank;
	}
	else if (type == "tower")
	{
		tile.type = EActorType::Tower;
	}
	else if (type == "base")
	{
		tile.type = EActorType::Base;
	}
	else if (type == "simplemob")
	{
		tile.type = EActorType::SimpleMob;
	}
	else if (type == "rangemob")
	{
		tile.type = EActorType::RangeMob;
	}
	else if (type == "meeleemob")
	{
		tile.type = EActorType::MeeleeMob;
	}
	else if (type == "flag")
	{
		tile.type = EActorType::Flag;
	}
	else
	{
		tile.type = EActorType::None;
	}
}


STmxMap* LoadTmxMap(const std::string& filename)
{
	xml_document<> doc;
	rapidxml::file<> xfile(filename.c_str());
	doc.parse<0>(xfile.data());

	xml_node<> *mapnode = doc.first_node("map");
	STmxMap* map = new STmxMap();
	map->width = atoi(mapnode->first_attribute("width")->value());
	map->height = atoi(mapnode->first_attribute("height")->value());
	map->tileWidth = atoi(mapnode->first_attribute("tilewidth")->value()) / 1.4;
	map->tileHeight = atoi(mapnode->first_attribute("tileheight")->value()) / 1.4;

	xml_node<> *tilesetnode = mapnode->first_node("tileset");
	STmxMapTileset* tileset = new STmxMapTileset();
	tileset->firstGid = atoi(tilesetnode->first_attribute("firstgid")->value());
	tileset->name = tilesetnode->first_attribute("name")->value();
	tileset->tileWidth = atoi(tilesetnode->first_attribute("tilewidth")->value()) / 1.4;
	tileset->tileHeight = atoi(tilesetnode->first_attribute("tileheight")->value()) / 1.4;
	auto tilenode = tilesetnode->first_node("tile");
	while (tilenode)
	{
		int id = atoi(tilenode->first_attribute("id")->value());
		map->tiles[id].src = tilenode->first_node("image")->first_attribute("source")->value();
		auto sidenode = tilenode->first_node("properties")->first_node("property");
		auto typenode = sidenode->next_sibling("property");
		SetTileSide(sidenode->first_attribute("value")->value(), map->tiles[id]);
		SetTileType(typenode->first_attribute("value")->value(), map->tiles[id]);

		tilenode = tilenode->next_sibling("tile");
	}
	map->tileset.reset(tileset);

	auto imagelayernode = mapnode->first_node("imagelayer");
	map->background = imagelayernode->first_node("image")->first_attribute("source")->value();

	const char *separators = " \t,\n\r";
	xml_node<> *layernode = mapnode->first_node("layer");
	STmxMapLayer* layer = new STmxMapLayer();

	layer->name = layernode->first_attribute("name")->value();
	layer->width = atoi(layernode->first_attribute("width")->value());
	layer->height = atoi(layernode->first_attribute("height")->value());

	const char* data = layernode->first_node("data")->value();

	layer->data = new int[layer->width * layer->height];

	char* copy = (char*)malloc(strlen(data) + 1);
	strcpy_s(copy, strlen(data) + 1, data);
	char* nextitem = nullptr;
	char* item = strtok_s(copy, separators, &nextitem);

	int index = 0;
	while (item) {
		layer->data[index] = atoi(item);
		index++;

		item = strtok_s(0, separators, &nextitem);
	}
	free(copy);
	map->layer.reset(layer);

	return map;
}