#pragma once
#include "panel button.hpp"

struct Bot_Panel : Panel_Button {
	Bot_Panel(const int& y = HEIGHT / 2);

public:
	void draw() override;
	void choose_left() override;
	void choose_right() override;
};