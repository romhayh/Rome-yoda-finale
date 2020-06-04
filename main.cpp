
#include "game phase.hpp"


extern std::vector<sf::Vector2f>* marked;
extern Player* players;
extern sf::RenderWindow* window;
extern sf::Font* font;
extern int state;
extern Button* scores;
extern Button* ready;
extern Button* b1;
extern Button* b2;
extern int pvp_cp_timer;
extern int pvp_timer;

int main()
{	
	game::setup();

	while (window->isOpen())
	{
		
		sf::Event event;
		while (window->pollEvent(event))
		{
			switch (event.type) {

			case (sf::Event::Closed):
				window->close();
				break;
			case (sf::Event::KeyReleased): 
				if (event.key.code == SPACE && (state == 2 || state == 5) ) {
					gameplay::pause();
				}
				else if (state == 2 && event.key.code == ESCAPE) {
					for (int i = 0; i < 5; i++) {
						players[i].erase_left();
						players[i].erase_right();
						players[i].kill();
						players[i].set_score(0);
					}
					pvp_cp_timer = 0;
					pvp_timer = 0;
					state = 0;
				}
				
				break;
			}

		}
		game::update();
		
		window->display();
	
	}
	
	//all heap allocated objects will automaticly be destroyed at the end of the program;
	std::cin.get();
	return 0;
}