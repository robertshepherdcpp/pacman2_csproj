#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<utility>
#include<unordered_map>
#include<string>

struct Pacman {
	Pacman(sf::Texture& pc_tx) : pm_sp(pc_tx) {
		pm_sp.setPosition(sf::Vector2f(250, 250));
	}

	auto draw(sf::RenderWindow& rw) {
		rw.draw(pm_sp);
	}

	auto update() {
		pm_sp.move(sf::Vector2f(float(dir.first), float(dir.second)));
	}

	auto move_up() { dir = directions["up"]; }
	auto move_down() { dir = directions["down"]; }
	auto move_left() { dir = directions["left"]; }
	auto move_right() { dir = directions["right"]; }

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

};