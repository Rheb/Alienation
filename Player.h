#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Consts.h"

class Player {
public:
	Player();
	~Player();

	void Init(sf::RenderWindow* window, float* frameTime, float* viewPosition);
	void Move(sf::Vector2i dir);
	void Draw();

	void CollisionEnemy(sf::Rect<float> enemyRect);
	void HitByBullet();
	sf::Rect<float> GetRect();
	bool Stunned();
private:
	sf::Sprite        _sprite;
	sf::Rect<float>   _rect;
	sf::RenderWindow* _window;
	float*			  _frameTime;
	float*            _viewPosition;

	float            _knockbackTime;
	float            _health;
};
#endif

