
#include "game phase.hpp"

extern sf::RenderWindow* window;
extern Panel_Button* p_buttons;
extern Button* ready;
extern int state;
extern Player* players;

int pvp_cp_timer{ 0 };
void game::pvp_controls_page() {
	using PB = Panel_Button;
	if (sf::Keyboard::isKeyPressed(ESCAPE)) {
		state = 0;
		for (int i = 0; i < 5; i++) {
			players[i].erase_left();
			players[i].erase_right();
			players[i].kill();
		}
		pvp_cp_timer = 0;
	}
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	
	window->clear();
	
	if (pvp_cp_timer < 5) {// clear window
		pvp_cp_timer++;
		window->clear();
	}

	else {
		
		for (int i = 0; i < 5; i++) {
			p_buttons[i].draw();
			p_buttons[i].choose_left();
			p_buttons[i].choose_right();
		}
		
		if (ready->hovered_on()) {
			if (ready->clicked()) {
				if (count_players_alive() > 1) {
					window->clear();
					Player::players_alive = count_players_init();
					state = 2;
				}
			}
		}
		if (state == 2) {
			for (int i = 0; i < 5; i++) { 
				if (players[i].isAlive()) {
					players[i].init_position();
					players[i].init_movement();
				}
			}
			std::cout << "state == 2" << std::endl;
		}
		ready->draw();
		
	}

}

int pvp_timer{ 0 };
void game::pvp_play_state() {

	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	
	if (pvp_timer < 5 ) {
		pvp_timer++;
		window->clear();
	}
	else if (pvp_timer < 10) {
		static sf::RectangleShape cushion(sf::Vector2f(2, HEIGHT));// the word "buffer" hs another meaning in cs :(
		cushion.setPosition(WIDTH , 0);
		cushion.setFillColor(sf::Color::Cyan);
		window->draw(cushion);
		pvp_timer++;
	}
	
	else if (pvp_timer == 10) {
		gameplay::pause();
		pvp_timer++;
		
	}

	gameplay::show_score();
	if (pvp_timer > 10) {
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + nanoseconds(8000000));
	}
	for (int i = 0; i < 5; i++) {
		Player& p = players[i]; // no foreach for c-style array arguments
		if (p.isAlive() && pvp_timer > 5 && p.has_right() && p.has_right()) {
		
			p.update_last_steps();
			p.collision();
			p.move();
			window->draw(p.get_circle());
			
		}
	}
	if (Player::players_alive <= 1) {
		gameplay::reset_board();
		std::srand(std::time(nullptr));
		gameplay::pause();
		pvp_timer = 0;
		if (highest_score() != nullptr) {
			if (highest_score()->get_score() >= MAX_SCORE) {
				gameplay::win(highest_score());
				
			}
		}
	}
	
}




