#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

#include "panel button.hpp"
#include "bot panel.hpp"
#include "game phase.hpp"
#include "gameplay.hpp"
#include "bot.hpp"

void initialize_players();
void initialize_bots();

namespace game{
	
	void setup();
	void update();


	void main_menu();
	void pvp_controls_page();
	void pvp_play_state();

	void win_page();

	void ai_controls_page();
	void ai_play_state();
}