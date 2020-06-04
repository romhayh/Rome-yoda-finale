#pragma once
#include "entity.hpp"



class Player : public Entity {
	
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;

	//bool alive = true;
	//std::array<sf::Vector2f, 4> last_steps;

	bool def_left{ false };
	bool def_right{ false };

public:
	static int players_alive;


public:
	//constructors and deconstructor

	Player();
	Player(sf::Color&& color, std::string&& name ,const sf::Vector2f& position = sf::Vector2f(0,0));
	Player(const Player& other);
	Player(Player&& other);
	~Player();

	Player& operator=(const Player&);
	Player& operator=(Player&&);

public: 
	//collision and movement

	void move() override;
	void collision() override;

public:
	//getters and setters 
	
	void Player::init_position() override;

	void set_controls(sf::Keyboard::Key&& left, sf::Keyboard::Key&& right);

	void set_left(const sf::Keyboard::Key& left){
		std::cout << this->name << "'s left was set to " << left << std::endl;
		this->left = left;
		this->def_left = true;
	}

	void set_right(const sf::Keyboard::Key& right) {
		std::cout << this->name << "'s right was set to " << right << std::endl;
		this->right = right;
		this->def_right = true;
	}

	bool has_left() {
		return this->def_left;
	}

	bool has_right() {
		return this->def_right;
	}

	void erase_left();

	void erase_right();



	friend const unsigned int count_players_alive();
	friend const unsigned int count_players_init();
	friend Entity* highest_score();
	
};

const unsigned int count_players_alive();
Entity* highest_score();
