#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "player.hpp"

class Button {
	sf::RectangleShape color_part;
	sf::RectangleShape black_part;
	sf::Text text;
	
	union {
		sf::Vector2f position;
		struct {
			float x, y;
		};
	};

	union{
		sf::Vector2f size;
		struct {
			float width, height;
		};
	};

	sf::Color color;

	int state;

	friend struct Panel_Button;
	friend struct Bot_Panel;
public:
	Button(std::string&& text = (std::string)" ", const float& y = WIDTH, const int& state = -1);
	Button(std::string&& text, sf::Vector2f&& position, const sf::Vector2f& size,const sf::Color& color, const int& state);
	Button(std::string&& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const int& state);
	Button(const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color, const int& state);
	Button(const std::string& text, sf::Vector2f&& position, int&& c_size, const sf::Color& color, const int& state = -1);
	~Button();
	Button(const Button& other);
	Button& operator=(const Button& other);
	Button& operator=(Button&& other);

public:

	void set_text(const std::string&);
	void setPosition(const sf::Vector2f&);
	const sf::Vector2f getPosition() const;
	void set_state_if_clicked(int&);
	bool hovered_on();
	bool hovered();
	bool clicked();
	void draw();
	void draw_text();
	void erase();
	const sf::Vector2f get_size() const;
	void set_fill_color(sf::Color&&);
	void set_fill_color(const sf::Color&);
	const sf::Color get_color() const;
};