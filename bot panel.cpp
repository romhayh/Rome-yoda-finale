#include "bot panel.hpp"
#include "bot.hpp"

extern Bot* bots;

Bot_Panel::Bot_Panel(const int & y)

{
	this->text = Button("0", sf::Vector2f(S_WIDTH / 6, y), SIZE, bots[0].get_color(), 80);
	this->text.black_part.setFillColor(bots[0].get_color());
	this->left = Button(" ", sf::Vector2f(S_WIDTH / 2, y), SIZE, bots[1].get_color(), 80);
	this->right = Button(" ", sf::Vector2f(3 * S_WIDTH / 4, y), SIZE, bots[2].get_color(), 80);

}

void Bot_Panel::draw()
{
	this->text.draw();
	this->left.draw();
	this->right.draw();
}

void Bot_Panel::choose_left()
{
	if (this->left.hovered_on() && this->left.clicked()) {
		if (!bots[1].isInitialized()) {
			this->left.black_part.setFillColor(bots[1].get_color());
			bots[1].initialize();
		}
		else {
			this->left.black_part.setFillColor(BLACK);
			bots[1].uninitialize();
		}
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.3f);
	}
}

void Bot_Panel::choose_right()
{
	if (this->right.hovered_on() && this->right.clicked()) {
		if (!bots[2].isInitialized()) {
			this->right.black_part.setFillColor(bots[2].get_color());
			bots[2].initialize();
		}
		else {
			this->right.black_part.setFillColor(BLACK);
			bots[2].uninitialize();
		}
		sf::Clock clock;
		while (clock.getElapsedTime().asSeconds() < 0.3f);
	}

}
