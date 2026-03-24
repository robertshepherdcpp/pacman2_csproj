#include <SFML/Graphics.hpp>

#include<chrono>
#include<string>
#include<iostream>
#include<fstream>

#include "Pacman.hpp"
#include "Map.hpp"
#include "Blinky.hpp"

int main()
{
    // initialize the window - with dimensions to match the grid size
    sf::RenderWindow window(sf::VideoMode({ 660, 580 }), "Pacman");

    sf::Texture wall; wall.loadFromFile("./Wall.png");
    sf::Texture blank; blank.loadFromFile("./BlankCell.png");
    sf::Texture energy; energy.loadFromFile("./Energy.png");
    sf::Texture special_token; special_token.loadFromFile("./ExtraEnergy.png");

    Map m("./grid.txt", wall, blank, energy, special_token);

    // initialize the pacman class
    sf::Texture PacmanTextureRight;
    PacmanTextureRight.loadFromFile("./Pacman.png");
    sf::Texture PacmanTextureLeft;
    PacmanTextureLeft.loadFromFile("./PacmanLeft.png");
    sf::Texture PacmanTextureDown;
    PacmanTextureDown.loadFromFile("./PacmanDown.png");
    sf::Texture PacmanTextureUp;
    PacmanTextureUp.loadFromFile("./PacmanUp.png");
    Pacman p(PacmanTextureRight, m.getEnergyCount(), PacmanTextureLeft, PacmanTextureDown, PacmanTextureUp);

    // initialize blinky class
    sf::Texture BlinkyTexture;
    BlinkyTexture.loadFromFile("./EnemyA.png");
    Blinky b(BlinkyTexture, {13, 13});

    sf::Sprite test(wall); test.setPosition(sf::Vector2f(20, 20));

    // the last time point, so we can use it for updates.
    std::chrono::system_clock::time_point last = std::chrono::system_clock::now();

    // after how many seconds do we update the characters i.e. move them (every 0.1 seconds)
    auto update_interval = std::chrono::milliseconds(10);

    //// only print the grid once.
    //int count = 0;

    // the main game loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            // check if the window should be closed.
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            // check if a key has been pressed
            else if (const auto* keyEvent = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyEvent->code == sf::Keyboard::Key::A)
                {
                    std::cout << "go left\n";
                    p.move_left();
                }
                else if (keyEvent->code == sf::Keyboard::Key::W)
                {
                    std::cout << "go up\n";
                    p.move_up();
                }
                else if (keyEvent->code == sf::Keyboard::Key::S)
                {
                    std::cout << "go down\n";
                    p.move_down();
                }
                else if (keyEvent->code == sf::Keyboard::Key::D)
                {
                    std::cout << "go right\n";
                    p.move_right();
                }
            }
        }

        // every update interval update the entities.
        if (std::chrono::system_clock::now() - last > update_interval) {
            p.update(m.get_map());
            last = std::chrono::system_clock::now();
        }

        //b.update(p, m);

        window.clear();

        // print the pacman sprite
        //window.draw(test);
        m.draw(window);
        p.draw(window);
        b.draw(window);
        

        window.display();
    }
}