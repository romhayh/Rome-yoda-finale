#include <iostream>
#include <thread>
#include <chrono>

#include "bot.hpp"
#include "gameplay.hpp"
#include "button.hpp"


extern Player* players;
extern Bot* bots;
extern std::vector<sf::Vector2f> marked;
extern sf::RenderWindow* window;
extern int state;
extern int pvp_cp_timer;
extern int pvp_timer;
extern int ai_cp_timer;
extern int ai_timer;


void gameplay::pause()
{
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	sf::Event e;
	sf::Clock clock;
	while (clock.getElapsedTime().asSeconds() < 0.3f);
	bool goon{ true };
	while (goon) {

		while (window->pollEvent(e))
		{
			if (e.type == sf::Event::KeyReleased) {
				if (e.key.code == SPACE) {
					goon = false;
				}
			}
			if (false);
			else if (e.type == sf::Event::Closed) {
				goon = false;
				window->close();
			}
			else if (sf::Keyboard::isKeyPressed(ESCAPE)) {
				marked.clear();
				for (int i = 0; i < 5; i++) {
					players[i].erase_left();
					players[i].erase_right();
					players[i].kill();
					players[i].set_score(0);
				}
				for (int i = 0; i < 3; i++) {
					bots[i].kill();
					bots[i].set_score(0);
				}
				pvp_cp_timer = 0;
				pvp_timer = 0;
				ai_cp_timer = 0;
				ai_timer = 0;
				state = 0;
				goon = false;
			goon = false;
			}

		}


	}
	

}

extern Button* scores;
sf::RectangleShape rect(sf::Vector2f(S_WIDTH - WIDTH - 3, HEIGHT));
	  

void gameplay::show_score(){

	static int ss_timer{ 0 };
	if (ss_timer == 0) {
		rect.setFillColor(BLACK);
		rect.setPosition(WIDTH + 3, 0);
		ss_timer++;
	}
	window->draw(rect);
	for (int i{ 0 }; i < 5; i++)
	{	
		if (players[i].has_left() && players[i].has_right()) {
			scores[i].set_text(players[i].get_name() + ": " + std::to_string(players[i].get_score()));
			scores[i].draw_text();
		}
	}
	if (state == 5) {
		for (int i{ 5 }; i < 8; i++) {
			if (bots[i - 5].isInitialized()) {
				scores[i].set_text(bots[i - 5].get_name() + ": " + std::to_string(bots[i - 5].get_score()));
				scores[i].draw_text();
			}
		}
	}

}


void gameplay::reset_board()
{
	marked.clear();
	for (int i = 0; i < 5; i++) {
		if (players[i].has_left() && players[i].has_right()) {
			players[i].raise();
			players[i].init_position();
			players[i].init_movement();
		}
	}
	Player::players_alive = count_players_alive();
	if (state > 4) {
		for (int i = 0; i < 3; i++) {
			bots[i].raise();
			bots[i].init_position();
			bots[i].init_movement();
		}
	}
}


//const std::string& text, sf::Vector2f&& position, int&& c_size, const sf::Color& color, const int& state
Button win1;
void gameplay::win(Entity* p){
	
	win1 = Button((std::string)(p->get_name() + " is the winner!!"), sf::Vector2f(S_WIDTH / 2, HEIGHT / 2), 100, p->get_color(), -1);
	if (state < 4) {
		state = 3;
	}
	else {
		state = 6;
	}
}


Entity* highest_score()
{
	int max = players[0].score;
	int idx = 0;
	if (state < 4) {
		for (int i = 0; i < 5; i++) {
			if (!players[i].def_left || !players[i].def_right) {
				continue;
			}
			if (players[i].score > max) {
				max = players[i].score;
				idx = i;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (i == idx) continue;
			if (players[i].score == max) return nullptr;
		}
		return (players + idx);
	}
	else {
		//redot idx =0
		//greental
		//jermy idx = 2
		//dylan
		//xaea-12
		if (!(!players[1].def_left || !players[1].def_right) && players[1].score > max) {
			idx = 1;
		}
		for (int i = 0; i < 3; i++) {
			if (bots[i].score > max) {
				max = bots[i].score;
				idx = 2 + i;
			}
		}
		for (int i = 0; i < 2; i++) {
			if (i == idx) continue;
			if (players[i].score == max) return nullptr;
		}
		for (int i = 0; i < 3; i++) {
			if (i == idx -2) continue;
			if (bots[i].score == max) return nullptr;
		}
		if (idx < 2) {
			return players + idx;
		}
		else {
			return bots + idx - 2;
		}
	}

	
}

