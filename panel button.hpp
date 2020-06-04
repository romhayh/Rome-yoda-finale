#pragma once
#include <string>

#include "button.hpp"

const sf::Vector2f SIZE(S_WIDTH / 6, 60);

struct Panel_Button {
	Button text;
	Button left;
	Button right;

	int serial_number;

	Panel_Button();
	Panel_Button(const std::string& text,const sf::Color& color, const unsigned int& y);
	Panel_Button(Panel_Button&& other);
	Panel_Button::Panel_Button(const Panel_Button& other);
	~Panel_Button();
	Panel_Button& operator=(const Panel_Button& other);

	virtual void draw();
	virtual void choose_left();
	virtual void choose_right();

	
};