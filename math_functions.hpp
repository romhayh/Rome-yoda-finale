#pragma once
#include <SFML/Graphics.hpp>
#include "constants.hpp"


void rotate(sf::Vector2f& v, const float& angle);

float distance(const sf::Vector2f& a, const sf::Vector2f& b = ORIGIN);

bool operator==(const sf::Vector2f& a, const sf::Vector2f& b);

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& a);

void normalize(sf::Vector2f& v,const float& length);

float getAngle(const sf::Vector2f& v);