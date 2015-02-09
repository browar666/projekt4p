#ifndef STATIC_TILED_MAP_INCLUDED
#define STATIC_TILED_MAP_INCLUDED
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>
class TileMap : public sf::Drawable, public sf::Transformable
{
	public:
		bool loadFromXML(const std::string name);
	private:
		void appendTile(const sf::Int32, const sf::Int32, const sf::Int32);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		//Mapka
	    sf::VertexArray m_vertices;
	    //Tileset
		sf::Texture m_tileset;
		// Szerokość podana w kafelkach
		sf::Uint32 width_in_tiles;
		// Wysokość podana w kafelkach
		sf::Uint32 height_in_tiles;
		// Szerokość kafla
		sf::Uint32 tile_width;
		// Wysokość kafla
		sf::Uint32 tile_height;
		// Rozmiary tilemapy
		sf::Uint32 img_width;
		sf::Uint32 img_height;
		
};
#endif //STATIC_TILED_MAP_INCLUDED
