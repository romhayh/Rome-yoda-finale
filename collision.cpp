#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>

#include "math_functions.hpp"
#include "player.hpp"
#include "bot.hpp"



extern std::vector<sf::Vector2f> marked;
extern int state;
extern Player* players;
extern Bot* bots;


void Player::collision() {
	if (this->collision_check()) {
		this->alive = false;
		for (int i = 0; i < 5; i++) {
			if (players[i].name != this->name && players[i].alive && players[i].def_left && players[i].def_right) {
				players[i].inc_score();
			}
		}
		if (state == 5) {
			for (int i = 0; i < 3; i++) {
				if (bots[i].isAlive() && bots[i].isInitialized()) {
					bots[i].inc_score();
				}
			}
		}
		Player::players_alive = count_players_alive();
	}
}