#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "tinyxml/tinyxml.h"
#include "MapSystem/StaticTiledMap.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tilemap");
    TileMap map;
    sf::View cam=window.getDefaultView();
	map.loadFromXML("mapx.tmx");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                cam.zoom(1.05f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                cam.move(0.f,-10.f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                cam.zoom(0.95f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                cam.move(-10.f,0.f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                cam.move(0.f,10.f);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                cam.move(10.f,0.f);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				return 1;

        }

        // draw the map
        window.setView(cam);
        window.clear();
        window.draw(map);
        window.display();
    }
	
    return 0;
}
