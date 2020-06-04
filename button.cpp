#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <thread>

#include "button.hpp"
#include "player.hpp"

extern sf::RenderWindow* window;
extern sf::Font* font;

Button::Button(std::string&& text, const float& y, const int& state):
	position(S_WIDTH /2.f, y), state(state)
{
	this->size = sf::Vector2f(300, 100);
	this->color = sf::Color(255,255,255,255);
	
	auto rect = sf::RectangleShape(sf::Vector2f(300, 100));
	rect.setFillColor(this->color);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->color_part = rect;

	rect = sf::RectangleShape(sf::Vector2f(280, 80));
	rect.setFillColor(sf::Color(0,0,0));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->black_part = rect;

	// Create a text
	this->text.setFont(*font);
	this->text.setCharacterSize(98);
	this->text.setFillColor(this->color);
	this->text.setString(text);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);
	
}

Button::Button(std::string&& text, sf::Vector2f&& position, const sf::Vector2f& size, const sf::Color& color, const int& state)
	:position(position),
	size(size),
	color(color),
	state(state)
{
	auto rect = sf::RectangleShape(size);
	rect.setFillColor(this->color);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->color_part = rect;
	
	auto b_size{ 0.8f * size };
	rect = sf::RectangleShape(b_size);
	rect.setFillColor(sf::Color(0, 0, 0));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->black_part = rect;

	// Create a text
	this->text.setFont(*font);
	this->text.setCharacterSize(49 * size.y / 50);
	this->text.setFillColor(this->color);
	this->text.setString(text);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);

}

Button::Button(const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const int& state)
	:position(position),
	size(size),
	color(color),
	state(state)
{
	auto rect = sf::RectangleShape(size);
	rect.setFillColor(this->color);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->color_part = rect;

	auto b_size{ 0.8f * size };
	rect = sf::RectangleShape(b_size);
	rect.setFillColor(sf::Color(0, 0, 0));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->black_part = rect;

	// Create a text
	this->text.setFont(*font);
	this->text.setCharacterSize(49 * size.y / 50);
	this->text.setFillColor(this->color);
	this->text.setString(text);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);

}

Button::Button(std::string&& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const int& state)
	:position(position),
	size(size),
	color(color),
	state(state)
{
	auto rect = sf::RectangleShape(size);
	rect.setFillColor(this->color);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->color_part = rect;

	auto b_size{ 0.8f * size };
	rect = sf::RectangleShape(b_size);
	rect.setFillColor(sf::Color(0, 0, 0));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->black_part = rect;

	// Create a text
	this->text.setFont(*font);
	this->text.setCharacterSize(49 * size.y / 50);
	this->text.setFillColor(this->color);
	this->text.setString(text);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);

}

/**
deafault constructor that sets size by the length of the text
*/
Button::Button(const std::string& text, sf::Vector2f&& position, int&& c_size, const sf::Color& color, const int& state) :
	position(position),
	color(color),
	state(state)
{
	std::cout << text << " button was created" << std::endl;

	// Create a text
	this->text.setFont(*font);
	this->text.setCharacterSize(49 * c_size / 50);
	this->text.setFillColor(this->color);
	this->text.setString(text);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);
	
	auto rect = sf::RectangleShape(sf::Vector2f((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x), c_size));
	rect.setFillColor(this->color);
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->size = rect.getSize();
	this->color_part = rect;

	auto b_size{ 0.8f * sf::Vector2f((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x), c_size) };
	rect = sf::RectangleShape(b_size);
	rect.setFillColor(sf::Color(0, 0, 0));
	rect.setOrigin(rect.getSize().x / 2, rect.getSize().y / 2); //pinning the origin to the middle
	rect.setPosition(this->position);
	this->black_part = rect;

	
	this->text.setCharacterSize(30 * c_size / 50);
	this->text.setOrigin((this->text.findCharacterPos(text.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);

}

Button::~Button() {
	std::cout << "button was destructed" << std::endl;
}

Button::Button(const Button & other)
{
	this->black_part = other.black_part;
	this->color = other.color;
	this->color_part = other.color_part;
	this->position = other.position;
	this->text = other.text;

}

Button& Button::operator=(const Button& other) {

	this->black_part = other.black_part;
	this->color = other.color;
	this->color_part = other.color_part;
	this->position = other.position;
	this->text = other.text;

	return *this;
}

Button & Button::operator=(Button && other)
{

	this->black_part = other.black_part;
	this->color = other.color;
	this->color_part = other.color_part;
	this->position = other.position;
	this->text = other.text;

	return *this;
}

void Button::set_state_if_clicked(int& state) {
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono; // nanoseconds, system_clock, seconds

	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + nanoseconds(17000000));



	if (this->hovered()) {
		
		sf::Color h_color = this->color - sf::Color(30,30,30,0);
		this->color_part.setFillColor(h_color);
		this->text.setFillColor(h_color);

		if (this->clicked()) {
			state = this->state;
		}
	}
	else {
		if (this->color_part.getFillColor() != this->color) {
			this->color_part.setFillColor(this->color);
			this->text.setFillColor(this->color);
		}
	}
	
}

bool Button::hovered_on()
{
	if (this->hovered()) {
		this->set_fill_color(this->color - sf::Color(50, 50, 50, 0));
		return true;
	}
	
	else {
		this->set_fill_color(this->color);
		return false;
	}
}

void Button::draw() {

	window->draw(this->color_part);
	window->draw(this->black_part);
	window->draw(this->text);
}

void Button::draw_text() {
	window->draw(this->text);
}

void Button::erase()
{
	window->draw(this->black_part);
	window->draw(this->black_part);
	window->draw(this->black_part);

}

const sf::Vector2f Button::get_size() const
{
	return this->size;
}

void Button::set_text(const std::string & str)
{

	this->text.setString(str);
	this->text.setOrigin((this->text.findCharacterPos(str.length()).x - this->text.findCharacterPos(0).x) / 2, this->text.getCharacterSize() * (0.648f));
	this->text.setPosition(this->position);
	
}

void Button::setPosition(const sf::Vector2f& v) {
	this->black_part.setPosition(v);
	this->color_part.setPosition(v);
	this->text.setPosition(v);
	this->position = position;
}

const sf::Vector2f Button::getPosition() const
{
	return this->position;
}

bool Button::hovered() {
	auto pos = sf::Mouse::getPosition(*window);
	float x = pos.x;
	float y = pos.y;
	if (x < this->x + this->size.x / 2 && x > this->x - this->size.x / 2 &&
		y > this->y - this->size.y / 2 && y < this->y + this->size.y / 2) {
		return true;
	}
	else return false;
}

bool Button::clicked() {
	if (this->hovered()) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			std::cout << (std::string)this->text.getString() << " was clicked" << std::endl;
		}
	}
	else {
		return false;
	}
}

void Button::set_fill_color(sf::Color&& color) {
	this->color_part.setFillColor(color);
	this->text.setFillColor(color);
}

void Button::set_fill_color(const sf::Color &)
{
	this->color_part.setFillColor(color);
	this->text.setFillColor(color);
}

const sf::Color Button::get_color() const
{
	return this->color;
}
