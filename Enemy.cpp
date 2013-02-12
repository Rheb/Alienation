#include "Enemy.h"

#include <iostream>
#include <cstdlib>

#include "Imagebank.h"
#include "CombatHandler.h"

// Externally declared imagebank
extern Imagebank imagebank;

#pragma region Base
Enemy::Enemy() {
}
Enemy::~Enemy() {
}
#pragma endregion

#pragma region Publics

void Enemy::Init(sf::RenderWindow* window, float* frameTime, float* viewPosition) {
	_window = window;
	_frameTime = frameTime;
	_viewPosition = viewPosition;

	_sprite.SetImage(imagebank["Enemy"]);
	_sprite.SetCenter(ENEMY_RECT_POS);

	_rect.Top    = 420;
	_rect.Bottom = 420 + ENEMY_SIZE.y;
	_rect.Left   = *_viewPosition + SCREEN_SIZE.x - 400;
	_rect.Right  = *_viewPosition + SCREEN_SIZE.x - 400 + ENEMY_SIZE.x;

	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);

	_chargePlayer = false;
	_bulletTime = 2;
}
void Enemy::Update(sf::Rect<float> playerRect, CombatHandler &combat) {
	if (_chargePlayer) {
		float yDist = playerRect.Top - _rect.Top;
		float xDist = playerRect.Left - _rect.Left;
		float tempY = yDist;

		yDist *= *_frameTime * ENEMY_ATTACK_SPEED / sqrt(yDist*yDist + xDist*xDist);
		xDist *= *_frameTime * ENEMY_ATTACK_SPEED / sqrt(tempY*tempY + xDist*xDist);

		_rect.Offset(xDist, yDist);
	} else if (_rect.Left > *_viewPosition + ENEMY_STABLE_POS) {
		_rect.Offset(*_frameTime * ENEMY_SPEED * -1, 0);
	}


	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);


	// Fire bullet
	if (_bulletTime <=0) {
		// Set new bullet time
		_bulletTime = 4 + rand()%3;

		float yDist = playerRect.Top - _rect.Top;
		float xDist = playerRect.Left - _rect.Left;
		float tempY = yDist;

		yDist /= sqrt(yDist*yDist + xDist*xDist);
		xDist /= sqrt(tempY*tempY + xDist*xDist);

		sf::Vector2f dir(xDist, yDist);

		sf::Vector2f pos(_rect.Left - BULLET_SIZE.x, _rect.Top+ENEMY_SIZE.y/2.0f);

		combat.EnemyShoot(pos, dir);
	} else {
		_bulletTime -= *_frameTime;
	}
}
void Enemy::Draw() {
	_window->Draw(_sprite);
}


void Enemy::CollisionPlayer() {
	_chargePlayer = false;
}
void Enemy::ChargePlayer() {
	_chargePlayer = true;
}
void Enemy::HitByBullet() {
	// OBS lose health
	//std::cout << "Enemy hit\n";
}
sf::Rect<float> Enemy::GetRect() {
	return _rect;
}

#pragma endregion 

#pragma region Privates



#pragma endregion
