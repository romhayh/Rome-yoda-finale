#include <iostream>
#include <chrono>
#include <thread>
#include <map>

#include "panel button.hpp"
#include "dict.hpp"

using PB = Panel_Button;

PB::Panel_Button() {}


PB::Panel_Button(const std::string& text, const sf::Color& color, const unsigned int& y):
text(text, sf::Vector2f(S_WIDTH / 6, y), SIZE, color, 80),
left("<=", sf::Vector2f(S_WIDTH / 2, y), SIZE, color, 80),
right("=>", sf::Vector2f(3 * S_WIDTH / 4, y), SIZE, color, 80)
{}




void PB::draw() {
	this->text.draw_text();
	this->left.draw();
	this->right.draw();
}

using Key = sf::Keyboard::Key;
extern Player* players;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

void PB::choose_left() {
	auto color = this->left.color;
	if (this->left.hovered_on()) {
		auto h_color = this->left.color - sf::Color(60, 60, 60, 0);
		this->left.color_part.setFillColor(h_color);
		this->left.text.setFillColor(h_color);
		if (this->left.clicked()) {

			for (int i{ 0 }; i < 3; i++) {
				sleep_for(nanoseconds(10));
				sleep_until(system_clock::now() + nanoseconds(17000000));
			}

			static sf::Clock clock;
			clock.restart();
			this->left.text.setString(" ");
			bool stop{ false };
			while (clock.getElapsedTime().asSeconds() <= 30.f) {

				if (sf::Keyboard::isKeyPressed(ENTER) || sf::Mouse::isButtonPressed(M_LEFT)) {
					players[this->serial_number].erase_left();
					players[this->serial_number].kill();
					break;
				}
				for (auto const& key : dict::kts) {
					if (sf::Keyboard::isKeyPressed(key.first)) {
						players[this->serial_number].set_left(key.first);
						this->left.set_text(key.second);

						sleep_for(nanoseconds(10));
						sleep_until(system_clock::now() + nanoseconds(17000000));

						if (players[this->serial_number].has_right()) {
							players[this->serial_number].raise();
						}

						stop = true;
						break;
					}
				}
				if (stop) {
					break;
				}
			}


		}
	}
	else if (!players[this->serial_number].has_left()) {
		this->left.set_text("<=");
	}
}


void PB::choose_right() {
	auto color = this->right.color;
	if (this->right.hovered_on()) {
		auto h_color = this->right.color - sf::Color(60, 60, 60, 0);
		this->right.color_part.setFillColor(h_color);
		this->right.text.setFillColor(h_color);
		if (this->right.clicked()) {

			for (int i{ 0 }; i < 3; i++) {
				sleep_for(nanoseconds(10));
				sleep_until(system_clock::now() + nanoseconds(17000000));
			}

			static sf::Clock clock;
			clock.restart();
			this->right.text.setString(" ");
			bool stop{ false };
			while (clock.getElapsedTime().asSeconds() <= 30.f) {

				if (sf::Keyboard::isKeyPressed(ENTER) || sf::Mouse::isButtonPressed(M_LEFT)) {
					players[this->serial_number].erase_right();
					players[this->serial_number].kill();
					break;
				}

				for (auto const& key : dict::kts) {
					if (sf::Keyboard::isKeyPressed(key.first)) {
						players[this->serial_number].set_right(key.first);

						this->right.set_text(key.second);

						sleep_for(nanoseconds(10));
						sleep_until(system_clock::now() + nanoseconds(17000000));

						if (players[this->serial_number].has_left()) {
							players[this->serial_number].raise();
						}

						stop = true;
						break;
					}
				}
				if (stop) {
					break;
				}
			}


		}
	}
	else if (!players[this->serial_number].has_right()) {
		this->right.set_text("=>");
	}
}


PB& PB::operator=(const Panel_Button& other) {
	this->left = other.left;
	this->right = other.right;
	this->text = other.text;

	return *this;
}

PB::~Panel_Button() {
	std::cout << "panel button destroyed" << std::endl;
}

Panel_Button::Panel_Button(Panel_Button && other)
{
	this->left = other.left;
	this->right = other.right;
	this->text = other.text;

}

Panel_Button::Panel_Button(const Panel_Button& other)
{
	this->left = other.left;
	this->right = other.right;
	this->text = other.text;

}