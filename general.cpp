
#include "game phase.hpp"


std::vector<sf::Vector2f> marked;
Player* players = new Player[5];
Bot* bots = new Bot[3];
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(S_WIDTH, HEIGHT), "Rome");
sf::Font* font = new sf::Font();
Button* scores = new Button[8];
Panel_Button* p_buttons = new Panel_Button[5];
Bot_Panel* b_button = new Bot_Panel();
int state{ 0 };
Button* ready = new Button;
Button* b1 = new Button("pvp", HEIGHT / 4, 1);
Button* b2 = new Button("ai", HEIGHT / 2, 10000);


int Player::players_alive{ 0 };



void initialize_players() {
	//redot
	players[0] = Player(RED, "redot", ORIGIN);
	//greental
	players[1] = Player(GREEN, "greental", ORIGIN);
	//benny
	players[2] = Player(BLUE, "benny", ORIGIN);
	//supreme
	players[3] = Player(WHITE, "supreme", ORIGIN);
	//homer
	players[4] = Player(YELLOW, "homer", ORIGIN);

}


void game::setup()
{


	std::srand(std::time(0));
	if (!font->loadFromFile("C:\\Users\\romha\\Desktop\\projects\\c++\\achtung\\achtung\\fonts\\old_stamper.ttf")) {
		throw("Error");
	}
	initialize_players();
	initialize_bots();
	using PB = Panel_Button;
	p_buttons[0] = PB("Redot:", sf::Color::Red, HEIGHT / 4);
	p_buttons[1] = PB("Greental:", sf::Color::Green, 3 * HEIGHT / 8);
	p_buttons[2] = PB("Benny:", sf::Color::Blue, HEIGHT / 2);
	p_buttons[3] = PB("Supreme:", sf::Color::White, 5 * HEIGHT / 8);
	p_buttons[4] = PB("Homer:", sf::Color::Yellow, 3 * HEIGHT / 4);
	*b_button = Bot_Panel();
	for (int i = 0; i < 5; i++) {
		p_buttons[i].serial_number = i;
	}

	*ready = Button("ready!", sf::Vector2f(WIDTH, 7 * HEIGHT / 8 + 30), WIDTH / 11, sf::Color::White, 2);

	//player scores:
	scores[0] = Button((std::string)(players[0].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 1 * HEIGHT / 9), CHAR_SIZE, RED);
	scores[1] = Button((std::string)(players[1].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 2 * HEIGHT / 9), CHAR_SIZE, GREEN);
	scores[2] = Button((std::string)(players[2].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 3 * HEIGHT / 9), CHAR_SIZE, BLUE);
	scores[3] = Button((std::string)(players[3].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 4 * HEIGHT / 9), CHAR_SIZE, WHITE);
	scores[4] = Button((std::string)(players[4].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 5 * HEIGHT / 9), CHAR_SIZE, YELLOW);
	
	//bot scores:
	scores[5] = Button((std::string)(bots[0].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 3 * HEIGHT / 9), CHAR_SIZE, PEACH);
	scores[6] = Button((std::string)(bots[1].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 4 * HEIGHT / 9), CHAR_SIZE, MAGENTA);
	scores[7] = Button((std::string)(bots[2].get_name() + ": " + "0"), sf::Vector2f(1.1f * WIDTH, 5 * HEIGHT / 9), CHAR_SIZE, PASTEL_GREEN);

}

void game::update()
{
	switch (state)
	{
	case 0:
		main_menu();
		break;
	case 1:
		pvp_controls_page();
		break;
	case 2:
		pvp_play_state();
		break;
	case 3:
		win_page();
		break;
	case 4:
		ai_controls_page();
		break;
	case 5:
		ai_play_state();
		break;
	case 6:
		win_page();
		break;
	default:
		break;
	}
}



void game::main_menu() {

	static int timer{ 0 };
	if (timer < 5) {// clear window
		timer++;
		window->clear();
	}
	Button* b1 = new Button("pvp", HEIGHT / 4, 1);
	Button* b2 = new Button("ai", HEIGHT / 2, 4);


	b1->set_state_if_clicked(state);
	b2->set_state_if_clicked(state);

	if (state == 0) {

		b1->draw();
		b2->draw();
	}


	if (state != 0) {
		timer = 0;
	}

}

extern Button win1;
void game::win_page() {
	win1.draw();
	if (sf::Keyboard::isKeyPressed(ENTER)) {
		gameplay::reset_board();
		for (int i{ 0 }; i < 5; i++) {
			players[i].set_score(0);
		}
		for (int i = 0; i < 3; i++) {
			bots[i].set_score(0);
		}
		if (state == 3) state = 1;
		if (state == 6) state = 4;
	}
	else if (sf::Keyboard::isKeyPressed(ESCAPE)) {
		for (int i = 0; i < 5; i++) {
			players[i].kill();
			players[i].set_score(0);
		}
		for (int i = 0; i < 3; i++) {
			bots[i].kill();
			bots[i].set_score(0);
		}
		state = 0;
	}

}