#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

#include "Consts.h"

class Bullet {
public:
	Bullet(sf::Vector2f pos, sf::Vector2f dir, bool hostile);
	~Bullet();

	void Init(sf::RenderWindow* window, float* frameTime, float* viewPosition);
	void Move();
	void Draw();

	bool Collision(sf::Rect<float> otherRect);
	bool OnScreen();
private:
	sf::Sprite        _sprite;
	sf::Rect<float>   _rect;
	sf::Vector2f      _speed;

	sf::RenderWindow* _window;
	float*			  _frameTime;
	float*            _viewPosition;
};
#endif