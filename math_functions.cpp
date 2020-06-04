#include <SFML/Graphics.hpp>
#include "math_functions.hpp"


/**
s-----------------s
rotate by the following formula:
x' =  xcos(a) - ysin(a)
y' =  xsin(a) + ycos(a)
e-----------------e
*/
void rotate(sf::Vector2f& v, const float& angle) {
	sf::Vector2f rv(0.f, 0.f);
	rv.x = (v.x * std::cos(angle)) - (v.y * std::sin(angle));
	rv.y = (v.x * std::sin(angle)) + (v.y * std::cos(angle));
	normalize(rv, distance(v));
	v = rv;
}


/*
*calculate the distance betwin a and b
*/
float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
	return std::sqrtf(std::powf(a.x - b.x, 2) + std::powf(a.y - b.y, 2)); 
}

bool operator==(const sf::Vector2f& a,const sf::Vector2f& b) {
	return (a.x == b.x && a.y == b.y);
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& a) {
	os << "{x = " << a.x << ", y = " << a.y << "}";
	return os;
}

void normalize(sf::Vector2f& v, const  float& length) {
	float l1 = distance(v);
	float adjl = length / l1;
	v *= adjl;
}

float getAngle(const sf::Vector2f & v)
{
	//the y axis is fliped, so i need to change the the sign of the v.y 
	float temp = -v.y / v.x;
	float angle = std::atan(temp);
	angle = 180 * angle / PI;
	if (-v.y + 0.000001f >= 0 && v.x >= 0) {
		return angle;
	}
	else if (-v.y + 0.000001f >= 0 && v.x < 0) {
		return 180 + angle;
	}
	else if (-v.y + 0.000001f < 0 && v.x < 0) {
		return 180 + angle;
	}
	else {
		//v.y < 0
		return 360 + angle;
	}
}
