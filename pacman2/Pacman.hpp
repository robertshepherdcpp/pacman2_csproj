#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<utility>
#include<unordered_map>
#include<string>

struct Pacman {
	Pacman(sf::Texture& pc_tx) : pm_sp(pc_tx) {
		pm_sp.setPosition(sf::Vector2f(240, 240));
	}

	auto draw(sf::RenderWindow& rw) {
		rw.draw(pm_sp);
	}

	auto update() {
		std::cout << pm_sp.getPosition().x << ", " << pm_sp.getPosition().y << "\n";
		if (to_move) {
			if ((int(pm_sp.getPosition().x) % 20 == 0) and (int(pm_sp.getPosition().y) % 20 == 0)) {
				dir = directions[move_to];
				to_move = false;
			}
		}

		pm_sp.move(sf::Vector2f(float(dir.first), float(dir.second)));
	}

	auto move_up() {  
		if (dir == directions["none"]) {
			dir = directions["up"];
		}
		else {
			to_move = true;
			move_to = "up";
		}
	}
	auto move_down() { 
		if (dir == directions["none"]) {
			dir = directions["down"];
		}
		else {
			to_move = true;
			move_to = "down";
		}
	}
	auto move_left() { 
		if (dir == directions["none"]) {
			dir = directions["left"];
		}
		else {
			to_move = true;
			move_to = "left";
		}
	}
	auto move_right() { 
		if (dir == directions["none"]) {
			dir = directions["right"];
		}
		else {
			to_move = true;
			move_to = "right";
		}
	}

private:
	sf::Sprite pm_sp;

	std::unordered_map<std::string, std::pair<int, int>> directions = {
		{ "up", { 0, -1 } },
		{ "left", {-1, 0} },
		{ "down", {0, 1} },
		{ "right", {1, 0} },
		{"none", {0, 0}}
	};
	std::pair<int, int> dir = directions["none"];

	bool to_move = false;
	std::string move_to{};
};