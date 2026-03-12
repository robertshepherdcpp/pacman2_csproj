#pragma once

#include<SFML/Graphics.hpp>

#include<iostream>

#include "Pacman.hpp"

// Blinky directly targets the pacman
struct Blinky {
	Blinky(sf::Texture& tx, std::pair<int, int> p) : position(p), bl_sp(tx) {
		bl_sp.setPosition(sf::Vector2f(float(p.first * 20), float(p.second * 20)));
	}
	auto update(Pacman& p) {
		auto crd = p.getCoord();
		sf::Vector2f pos{ float(crd.first * 20), float(crd.second * 20) };

		// first check that they arent intersecting
		auto my_pos = bl_sp.getPosition();
		if (abs(my_pos.x - pos.x) < 20 and abs(my_pos.y - pos.y) < 20) {
			// then we have a collision.
			if (!eadible) {
				p.die();
			}
			else {
				die();
			}
		}
		else {
			// they arent intersecting, so we have to update the path that should be taken
		}
	}

	auto die() -> void {
		// TODO implement
		std::cout << "ghost death\n.";
	}

	auto draw(sf::RenderWindow& rw) -> void {
		rw.draw(bl_sp);
	}
private:
	std::vector<std::pair<int, int>> moves{};
	int index = 0;
	std::pair<int, int> last_position{-1, -1};

	std::pair<int, int> position{};

	sf::Sprite bl_sp;

	bool eadible = false;
};