#pragma once

#include<SFML/Graphics.hpp>

#include<iostream>

#include<queue>
#include<map>

#include "Pacman.hpp"
#include "Map.hpp"

inline auto shortest_path(Map& m, std::pair<int, int> start, std::pair<int, int> to) {
	std::vector<std::pair<int, int>> res{};

	// need to calculate the shortest path between 2 points, and then return the list of moves that got to that position.
	// will do using bfs.
	std::vector<std::vector<char>> copy = *m.get_map();

	std::queue<std::pair<int, int>> q;
	q.push(start);

	std::map<std::pair<int, int>, bool> visited{};
	std::map<std::pair<int, int>, std::pair<int, int>> parent{};

	std::vector<std::pair<int, int>> dirs{ {-1, 0},{1, 0},{0, -1},{0, 1} };

	visited[start] = true;

	while (!q.empty()) {
		auto value = q.front();
		q.pop();

		if (value == to) {
			break;
		}

		auto prev = value;

		for (auto d : dirs) {
			value = { prev.first + d.first, prev.second + d.second };
			if (copy[value.first][value.second] != '#') {
				parent[value] = prev;
				visited[value] = true;
				q.push(value);
			}
		}
	}

	// we have got to our value now we need to retrace
	std::vector<std::pair<int, int>> moves{};
	auto curr = to;
	while (curr != from) {

	}


	return res;
}

// Blinky directly targets the pacman
struct Blinky {
	Blinky(sf::Texture& tx, std::pair<int, int> p) : position(p), bl_sp(tx) {
		bl_sp.setPosition(sf::Vector2f(float(p.first * 20), float(p.second * 20)));
	}
	auto update(Pacman& p, Map& m) {
		// the position of the pacman
		auto crd = p.getCoord();
		sf::Vector2f pos{ float(crd.first * 20), float(crd.second * 20) };

		// first check that they arent intersecting, i.e. no collision
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
			// they arent intersecting, so we have to update the path that should be taken.
			auto pacman_pos = p.getCoord();
			if (pacman_pos == last_position) { // checking if there is any point in recalculating.
				// same as last time, then we dont calculate a new path
			}
			else {
				// calculate the shortest path
				moves = shortest_path(m, position, pacman_pos);
				index = 0;
			}
			// if there are any moves to be had:
			if (moves.size() > 0) {
				// move the ghost
				auto move = moves[index];
				bl_sp.move(sf::Vector2f(float(move.first), float(move.second)));
				auto new_pos = bl_sp.getPosition();
				index += 1;

				// update the coordinate of the ghost, if it is at a coordinate that is directly on a grid cell.
				if (int(new_pos.x) % 20 == 0 and int(new_pos.y) % 20 == 0) {
					position = { float(new_pos.x / 20), float(new_pos.y / 20) };
				}
			}
		}
	}

	auto die() -> void {
		// TODO implement
		std::cout << "ghost death\n.";

		// need to change the sprite into eyes and go back to the center.
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