#pragma once
#include <SFML/Graphics.hpp>


enum {
	HEIGHT = 630,
	WIDTH = 16 * HEIGHT / 9,
	S_WIDTH = (int)(1.2f*WIDTH)
};

#define P_LENGTH 12
const sf::Vector2f positions[P_LENGTH]{
	{81.f, 81.f},
	{WIDTH - 81.f, HEIGHT - 81.f},
	{WIDTH - 81.f, 81.f},
	{81.f, HEIGHT - 81.f},
	{WIDTH / 2 - 1.f, HEIGHT / 2 + 1.f},
	{S_WIDTH / 3, HEIGHT * 0.44f},
	{WIDTH - 81.f, HEIGHT / 2 + 1.f},
	{WIDTH/2, 81.f},
	{81.f, HEIGHT /2},
	{S_WIDTH / 2, 30 },
	{S_WIDTH / 3, 3 * HEIGHT / 4},
	{2 * S_WIDTH / 3,  1 * HEIGHT / 4}
};


#define MAX_POINTS_PER_PLAYER 5
#define MAX_SCORE (count_players_init() * MAX_POINTS_PER_PLAYER)

//colors
#define BLUE (sf::Color)sf::Color::Blue
#define BLACK (sf::Color)sf::Color::Black
#define GREEN (sf::Color)sf::Color::Green
#define RED (sf::Color)sf::Color::Red
#define YELLOW (sf::Color)sf::Color::Yellow
#define CYAN (sf::Color)sf::Color::Cyan
#define WHITE (sf::Color)sf::Color::White
#define PEACH sf::Color(255, 229, 180, 255)
#define MAGENTA sf::Color(255,0,255, 255)
#define PASTEL_GREEN sf::Color(139, 226, 139, 255)

#define CHAR_SIZE 50

#define SPACE sf::Keyboard::Space
#define ESCAPE sf::Keyboard::Escape
#define ENTER sf::Keyboard::Enter
#define UNKNOWN sf::Keyboard::Unknown
#define M_LEFT sf::Mouse::Left

#define ORIGIN sf::Vector2f(0, 0)

# define PI 3.14159265358979323846f
