#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<utility>
#include<unordered_map>
#include<string>

struct Pacman {
	Pacman(sf::Texture& pc_tx, int m_energy_count, sf::Texture& left, sf::Texture& down, sf::Texture& up) : pm_sp(pc_tx) {
		pm_sp.setPosition(sf::Vector2f(240, 240));
		energy_count = m_energy_count;
		m_right = pc_tx; m_left = left; m_down = down; m_up = up;
	}

	auto draw(sf::RenderWindow& rw) {
		rw.draw(pm_sp);
	}

	auto update(std::vector<std::vector<char>>* vec) {
		if (energy_count == 0) {
			std::cout << "you have won.\n";
			energy_count = -1;
		}
		//std::cout << pm_sp.getPosition().x << ", " << pm_sp.getPosition().y << "\n";
		if ((int(pm_sp.getPosition().x) % 20 == 0) and (int(pm_sp.getPosition().y) % 20 == 0)) {
			auto cpy = dir;
			if (to_move) {
				dir = directions[move_to];
				to_move = false;
			}
			// update the positions (this is for the grid to check if we have collided with a wall.
			position.first = pm_sp.getPosition().x / 20;
			position.second = pm_sp.getPosition().y / 20;
		}
		// we need to check before we do this move that its actually possible to do so i.e. we wont be going over the bounds
		auto pos = pm_sp.getPosition();
		pos.x += float(dir.first);
		pos.y += float(dir.second);

		// if the position is out of bounds
		if (pos.x < 0 or pos.x > 600) {
			// then we would make the pacman go to the other side
			if (pos.x < 0) {
				pos.x = 600;
			}
			if (pos.x > 600) {
				pos.x = 0;
			}
			pm_sp.setPosition(pos);
			position = { int(pos.x) / 20, int(pos.y) / 20 };
		}
		else { // the position is in bounds.
			//std::cout << "attempting to access position: " << int(pos.x / 20) << ", " << int(pos.y / 20) << "\n";
			// char val = (*vec)[int(pos.y / 20)][int(pos.x / 20)];
			// we have to calculate which cell its actually moving into
			auto d = dir;
			int x_coord{}; int y_coord{};
			if (int(pos.y) % 20 == 0 and int(pos.x) % 20 == 0) {
				y_coord = int(pos.y / 20);
				x_coord = int(pos.x / 20);
			} else {
				if (d == directions["left"]) {
					// this means that the position will simply be same y value, but the x value will just be the rounded down
					y_coord = int(pos.y / 20);
					x_coord = int(pos.x / 20);
				}
				else if (d == directions["right"]) {
					// this means the y pos is the same, x value will be the x value rounded down + 1
					y_coord = int(pos.y / 20);
					x_coord = int(pos.x / 20 + 1);
				}
				else if (d == directions["down"]) {
					// x coord is the same, y value will be the y value rounded down
					y_coord = int(pos.y / 20 + 1);
					x_coord = int(pos.x / 20);
				}
				else if (d == directions["up"]) {
					// the y coord is the same, y value will be the y value rounded down + 1
					y_coord = int(pos.y / 20);
					x_coord = int(pos.x / 20);
				}
			}
			char val = (*vec)[y_coord][x_coord];
			if (val == '#') {
				// then we cant move anymore we just stay as is.
				//pm_sp.setPosition(pos);

			}
			else if (val == '.') {
				// then we have got to consume this token. we still move the player
				score += 1;
				(*vec)[y_coord][x_coord] = ' ';
				energy_count -= 1;

				pm_sp.setPosition(pos);
				position = { x_coord, y_coord };
			}
			else if (val == 'o') {
				// then we have a special token - the one that allows to ghosts to become edible. we still move the player
				score += 10;
				(*vec)[y_coord][x_coord] = ' ';
				energy_count -= 1;

				// TODO: actually handle eating it, like change the ghost's state.

				pm_sp.setPosition(pos);

				position = { x_coord, y_coord };
			}
			else if (val == ' ') {
				// then nothing, we just move.
				pm_sp.setPosition(pos);

				position = { x_coord, y_coord };
			}
			else if (val == 'A' or val == 'B' or val == 'C' or val == 'D' or val == 'P') {
				// then we have hit a ghost.
				// TODO actually do something with the collision with the ghost.
				pm_sp.setPosition(pos);

				position = { x_coord, y_coord };
			}
		}
	}

	auto move_up() {  
		if (dir == directions["none"]) {
			dir = directions["up"];
		}
		else {
			to_move = true;
			move_to = "up";
			pm_sp.setTexture(m_up);
		}
	}
	auto move_down() { 
		if (dir == directions["none"]) {
			dir = directions["down"];
		}
		else {
			to_move = true;
			move_to = "down";
			pm_sp.setTexture(m_down);
		}
	}
	auto move_left() { 
		if (dir == directions["none"]) {
			dir = directions["left"];
		}
		else {
			to_move = true;
			move_to = "left";
			pm_sp.setTexture(m_left);
		}
	}
	auto move_right() { 
		if (dir == directions["none"]) {
			dir = directions["right"];
		}
		else {
			to_move = true;
			move_to = "right";
			pm_sp.setTexture(m_right);
		}
	}

	auto getCoord() -> std::pair<int, int> {
		return position;
	}

	auto die() {
		// handle death.
		std::cout << "Pacman death\n.";
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

	std::pair<int, int> position{12, 12};

	int score = 0;
	int energy_count = 0;

	sf::Texture m_left; sf::Texture m_right; sf::Texture m_down; sf::Texture m_up;
};