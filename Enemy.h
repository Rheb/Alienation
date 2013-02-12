#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Consts.h"

class CombatHandler;

class Enemy {
public:
	Enemy();
	~Enemy();

	void Init(sf::RenderWindow* window, float* frameTime, float* viewPosition);
	void Update(sf::Rect<float> playerRect, CombatHandler &combat);
	void Draw();
	
	void CollisionPlayer();
	void ChargePlayer();
	void HitByBullet();
	sf::Rect<float> GetRect();
private:
	sf::Sprite        _sprite;
	sf::Rect<float>   _rect;

	bool              _chargePlayer;
	float             _bulletTime;

	sf::RenderWindow* _window;
	float*			  _frameTime;
	float*            _viewPosition;
};
#endif
