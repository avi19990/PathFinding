#include <SFML/Graphics.hpp>

#include <vector>
#include <deque>
#include <iostream>
#include <Windows.h>

#include "PF_Algorithm.h"
#include "BoolMap.h"
#include "PF_BFS.h"
#include "PF_AStar.h"
#include "Vector2.h"
#include "PF_Visualizer.h"
#include "PF_BFS_Visualizer.h"

#define mapSize 10

int main()
{
    BoolMap* map = new BoolMap(mapSize, mapSize);

    PF_Algorithm* alg = new PF_AStar(map, Vector2(1, 1), Vector2(9, 9));
    PF_Visualizer* visual = new PF_BFS_Visualizer(alg, sf::IntRect(10, 10, 880, 880),
        { {"frontier", sf::Color(0, 0, 255)},
          {"cameFrom", sf::Color(0, 100, 0)},
          {"start", sf::Color(0, 255, 0)},
          {"finish", sf::Color(255, 0, 0)},
          {"current", sf::Color::Cyan},
          {"wall", sf::Color(0, 0, 0)},
          {"free", sf::Color(200, 200, 200)},
          {"path", sf::Color(200, 200, 0)} });

    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML works!");

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);

    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    alg->solveStep();
                    visual->update();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    alg->solve();
                    visual->update();
                break;
            }
        }

        window.clear(sf::Color(100, 100, 100));

        window.draw(*visual);
        window.draw(text);

        window.display();

        text.setString(std::to_string(1.0f / clock.restart().asSeconds()));
    }

    return 0;
}