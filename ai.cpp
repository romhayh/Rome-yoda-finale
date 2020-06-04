
#include "game phase.hpp"

extern sf::RenderWindow* window;
extern Bot* bots;
extern Panel_Button* p_buttons;
extern Button* ready;
extern int state;
extern Player* players;
extern Bot_Panel* b_button;

void initialize_bots()
{
	bots[0] = Bot(PEACH, "jermy");
	bots[0].initialize();
	bots[1] = Bot(MAGENTA, "dylan");
	bots[1].uninitialize();
	bots[2] = Bot(PASTEL_GREEN, "xaea-12");
	bots[2].uninitialize();
	
}



int ai_cp_timer{ 0 };
void game::ai_controls_page()
{

	using PB = Panel_Button;

	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	window->clear();
	if (sf::Keyboard::isKeyPressed(ESCAPE)) {
		state = 0;
		for (int i = 0; i < 5; i++) {
			players[i].erase_left();
			players[i].erase_right();
			players[i].kill();
		}
		ai_cp_timer = 0;
	}
	if (ai_cp_timer < 5) {// clear window
		ai_cp_timer++;
		window->clear();
	}
	else {

		b_button->draw();
		b_button->choose_left();
		b_button->choose_right();
		for (int i = 0; i < 2; i++) {
			p_buttons[i].draw();
			p_buttons[i].choose_left();
			p_buttons[i].choose_right();
		}
		Player::players_alive = count_players_init();
		if (ready->hovered_on()) {
			if (ready->clicked()) {
				if (Player::players_alive > 0) {
					window->clear();
					state = 5;
				}
			}
		}
		if (state == 5) {
			std::cout << "state == 5" << std::endl;
			for (int i = 0; i < 3; i++) {
				bots[i].raise();
				bots[i].init_position();
				bots[i].init_movement();
			}
			for (int i = 0; i < 2; i++) {
				if (players[i].isAlive()) {
					players[i].init_position();
					players[i].init_movement();
				}
			}
		}
		ready->draw();
	}
}


int ai_timer{ 0 };
void game::ai_play_state() {

	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds
	

	if (ai_timer < 5) {
		ai_timer++;
		window->clear();
	}
	else if (ai_timer < 10) {
		static sf::RectangleShape cushion(sf::Vector2f(2, HEIGHT));// the word "buffer" hs another meaning in cs :(
		cushion.setPosition(WIDTH, 0);
		cushion.setFillColor(sf::Color::Cyan);
		window->draw(cushion);
		ai_timer++;
	}
	else if (ai_timer == 10) {
		gameplay::pause();
		ai_timer++;
		
	}
	else if (ai_timer > 10) {
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + nanoseconds(7000000));
	}

	gameplay::show_score();

	for (int i = 0; i < 2; i++) {
		if (players[i].isAlive() && ai_timer > 5) {
			players[i].update_last_steps();
			players[i].collision();
			players[i].move();
			window->draw(players[i].get_circle());
		}
	}
	for (int i = 0; i < 3; i++) {
		if (bots[i].isAlive() && ai_timer > 5 && bots[i].isInitialized()) {
			bots[i].bound_check();
			bots[i].collision();
			bots[i].move();
			bots[i].update_last_steps();
			window->draw(bots[i].get_circle());
		}
	}
	if (count_entities_alive() <= 1) {
		gameplay::reset_board();
		ai_timer = 0;
		auto ptr = highest_score();
		if (ptr != nullptr) {
			if (ptr->get_score() > MAX_SCORE + count_bots_init() * MAX_POINTS_PER_PLAYER) {
				gameplay::win(ptr);
			}
		}
	}
	//std::cout << "there are " << count_entities_alive() << " entities that are alive" << std::endl;

}

int count_bots_init()
{
	int inx{ 0 };
	for (int i = 0; i < 3; i++) {
		if (bots[i].init) inx++;
	}
	return inx;
}

int count_entities_alive()
{
	int es_alive = 0; //entities alive
	for (int i = 0; i < 3; i++) {
		if (bots[i].alive && bots[i].init) es_alive++;
	}
	for (int i = 0; i < 2; i++) {
		if (players[i].isAlive()) es_alive++;
	}
	return es_alive;
}