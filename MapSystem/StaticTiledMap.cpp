#include "StaticTiledMap.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#define __DEBUG_MAP
bool TileMap::loadFromXML(const std::string name)
{
	TiXmlDocument mapFile(name.c_str());
	if(!mapFile.LoadFile())
	{
		#ifdef __DEBUG_MAP
		std::cout << "Błąd, nie wczytano pliku \"" << name << "\"." << std::endl;
		#endif
		return false; 
	}
	// Rozmiary w kaflach oraz rozmiary kafli
	TiXmlElement *map = mapFile.FirstChildElement("map");
	width_in_tiles 	  = atoi(map->Attribute("width"));
	height_in_tiles   = atoi(map->Attribute("height"));
	tile_width	  = atoi(map->Attribute("tilewidth"));
	tile_height       = atoi(map->Attribute("tileheight"));
	//rozmiary i typ
	m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(width_in_tiles * height_in_tiles * 4);     
	// misc
	TiXmlElement *tilesetElement;
	tilesetElement = map->FirstChildElement("tileset");
	int firstTID = atoi(tilesetElement->Attribute("firstgid"));
	// image data
	TiXmlElement *image;
	image = tilesetElement->FirstChildElement("image");
	std::string imgpath = image->Attribute("source");
	img_width = atoi(image->Attribute("width"));
	img_height = atoi(image->Attribute("height"));
	// load check
	if(!m_tileset.loadFromFile(imgpath))
	{
		#ifdef __DEBUG_MAP
		std::cout << "Nie udało sie wczytać tilemapki" << std::endl;
		#endif
		return false;
	}
	TiXmlElement *layer = map->FirstChildElement("layer");
	int numz = 0;
	int layerNum = -1;
	sf::Uint32 x,y;
	x=y=0;
	while(layer)
	{
		TiXmlElement* layerData = layer->FirstChildElement("data"); // znacznik data
		if(layerData == NULL)
		{
			#ifdef __DEBUG_MAP
			std::cout << "Nie znaleziono <data>" << std::endl;
			#endif
			return false;
		}
		TiXmlElement *tile = layerData->FirstChildElement("tile");
		if(tile == NULL)
		{
			#ifdef __DEBUG_MAP
			std::cout << "Nie znaleziono <tile>" << std::endl;
			#endif
			return false;
		}
			
		while(tile)
		{
			int tileNumber = atoi(tile->Attribute("gid"))-firstTID;
			// Dodajemy kafla
			appendTile(x,y,tileNumber);
			// Jedziem dalej;	
			tile = tile->NextSiblingElement("tile");		           
			x++;
            if (x >= width_in_tiles)
            {
                x = 0;
                y++;
                if (y >= height_in_tiles)
                {
                    y = 0;
                }
            }
            #ifdef __DEBUG_MAP 
			 printf("GIDNUM:%i LAYER:%i X:%i Y:%i\n",numz,layerNum,x,y);
            #endif
				
			numz++;
		}
		layer = layer->NextSiblingElement("layer");
		layerNum++; // layerów będzie więcej.
	}
	// Obiekty
	TiXmlElement *objectsGroup;
	if(map->FirstChildElement("objectgroup") != NULL)
	{
		objectsGroup = map->FirstChildElement("objectgroup");
		while(objectsGroup)
		{
			TiXmlElement *object = objectsGroup->FirstChildElement("object");
			while(object)
			{
				std::string id;
				if(object->Attribute("id") != NULL)
					id = object->Attribute("id");
				
				#ifdef __DEBUG_MAP	
					printf("Id:%s\n", id.c_str());
				#endif
				object = object->NextSiblingElement("object");
			}
			objectsGroup = objectsGroup->NextSiblingElement("objectgroup");			
		}
	}
	return true;
}
void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
 states.transform *= getTransform();
 states.texture = &m_tileset;
 target.draw(m_vertices, states);
}
void TileMap::appendTile(sf::Int32 x, sf::Int32 y, sf::Int32 GID)
{
	sf::Int32 tu = GID % (m_tileset.getSize().x / tile_width);
	sf::Int32 tv = GID / (m_tileset.getSize().x / tile_height);
	sf::Vertex* quad = &m_vertices[(x + y * width_in_tiles) * 4];
             
	quad[0].position = sf::Vector2f(x * tile_width, y * tile_height);
	quad[1].position = sf::Vector2f((x + 1) * tile_width, y * tile_height);
	quad[2].position = sf::Vector2f((x + 1) * tile_width, (y + 1) * tile_height);
	quad[3].position = sf::Vector2f(x * tile_width, (y + 1) * tile_height);
			
	quad[0].texCoords = sf::Vector2f(tu * tile_width, tv * tile_height);
	quad[1].texCoords = sf::Vector2f((tu + 1) * tile_width, tv * tile_height);
	quad[2].texCoords = sf::Vector2f((tu + 1) * tile_width, (tv + 1) * tile_height);
	quad[3].texCoords = sf::Vector2f(tu * tile_width, (tv + 1) * tile_height);
}
