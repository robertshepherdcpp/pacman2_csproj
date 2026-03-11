#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<string>
#include<fstream>

struct Map {
	Map(std::string filename, sf::Texture& t_wall, sf::Texture& t_blank, sf::Texture& t_energy, sf::Texture& t_special_token)
        : wall(t_wall), blank(t_blank), energy(t_energy), special_token(t_special_token)
    { // initialize the map array
        // get the grid, it is stored in grid.txt and we need to get it into a vector.
        std::ifstream file("grid.txt");
        std::vector<std::string> lines{};
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        // this stage works.
        /*std::cout << "got the lines from the grid:\n";
        for (const auto line : lines) {
            std::cout << line << ", ";
        }
        std::cout << "\n";*/

        // now we find the longest line in the vector
        int largest = 0;
        for (auto& i : lines) {
            std::cout << "size of i: " << i.size() << "\n";
            std::cout << "is i greather than largest, i: " << i.size() << ", largest: " << largest << ", the result: " << (i.size() > largest) << "\n";
            if (i.size() > largest) {
                largest = i.size();
            }
        }
        std::cout << "the longest line: " << largest << "\n";
        //// now we can actually create the grid
        std::vector<std::vector<char>> vec{};
        for (int i = 0; i < lines.size(); i++) {
            std::vector<char> temp{};
            for (auto j : lines[i]) {
                temp.push_back(j);
            }
            if (lines[i].size() < largest) {
                for (int j = 0; j < (largest - lines[i].size()); j++) {
                    temp.push_back(' ');
                }
            }
            vec.push_back(temp);
        }
        std::cout << "printing the grid:\n";
        for (const auto v : vec) {
            std::cout << "{";
            for (const char x : v) {
                std::cout << x << ",";
            }
            std::cout << "}";
        }
        m_grid = vec;

        std::cout << "\nall good setting up the grid\n";
	}

    auto get_map() -> std::vector<std::vector<char>>* {
        return &m_grid;
    }

    // to draw the sprites of the grid. here we wont be drawing pacman and the ghosts though, they will act on their own.
    auto draw(sf::RenderWindow& rw) -> void {
        //for (int i = 0; i < m_grid.size(); i++) {
        //    for (int j = 0; j < m_grid[0].size(); j++) {
        //        // here the i is the y value (the amount of rows)
        //        sf::Vector2f pos = sf::Vector2f(20 * j, 20 * i);
        //        if (m_grid[i][j] == '#') {
        //            wall.setPosition(pos);
        //            rw.draw(wall);
        //            std::cout << "printing a wall\n";
        //        }
        //        else if (m_grid[i][j] == '.') {
        //            energy.setPosition(pos);
        //            rw.draw(energy);
        //            std::cout << "printing an energy token\n";
        //        }
        //        else if (m_grid[i][j] == 'o') {
        //            special_token.setPosition(pos);
        //            rw.draw(energy);
        //            std::cout << "printing an extra energy token\n";
        //        }
        //        else {
        //            blank.setPosition(pos);
        //            rw.draw(blank);
        //            std::cout << "printing a blank space\n";
        //        }
        //    }
        //}
        /*wall.setPosition(sf::Vector2f(60, 60));
        rw.draw(wall);*/

        for (int i = 0; i < m_grid.size(); i++) {
            for (int j = 0; j < m_grid[0].size(); j++) {
                if (m_grid[i][j] == '#') {
                    wall.setPosition(sf::Vector2f(j * 20, i * 20));
                    rw.draw(wall);
                }
                else if (m_grid[i][j] == '.') {
                    energy.setPosition(sf::Vector2f(j * 20, i * 20));
                    rw.draw(energy);
                }
                else if (m_grid[i][j] == 'o') {
                    special_token.setPosition(sf::Vector2f(j * 20, i * 20));
                    rw.draw(special_token);
                }
            }
        }
    }
private:
    std::vector<std::vector<char>> m_grid{};

    sf::Sprite blank;
    sf::Sprite wall;
    sf::Sprite energy;
    sf::Sprite special_token;
};