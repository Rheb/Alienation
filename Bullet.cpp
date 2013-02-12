#include "Bullet.h"

#include <cstdlib>
#include <iostream>

#include "Imagebank.h"

// Externally declared imagebank
extern Imagebank imagebank;

#pragma region Base
Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, bool hostile) {
	_rect.Top    = pos.y;
	_rect.Bottom = pos.y + BULLET_SIZE.y;
	_rect.Left   = pos.x;
	_rect.Right  = pos.x + BULLET_SIZE.x;

	_speed.x = dir.x * BULLET_SPEED;
	_speed.y = dir.y * BULLET_SPEED;

	_sprite.SetImage(imagebank["Bullets"]);

	// Choose a rendom bullet image
	int randImg = rand()%4;
	int bulletType = 0;
	if (hostile) {
		bulletType = 1;
	}
	float left  = bulletType*BULLET_SIZE.x;
	float top   = randImg*BULLET_SIZE.y;
	float right = left + BULLET_SIZE.x;
	float bot   = top + BULLET_SIZE.y;
	_sprite.SetSubRect(sf::Rect<int>(left, top, right, bot));
}
Bullet::~Bullet() {
}
#pragma endregion

#pragma region Publics

void Bullet::Init(sf::RenderWindow* window, float* frameTime, float* viewPosition) {
	_window = window;
	_frameTime = frameTime;
	_viewPosition = viewPosition;

	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);
}
void Bullet::Move() {
	_rect.Offset(_speed.x * *_frameTime, _speed.y * *_frameTime);
	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);
}
void Bullet::Draw() {
	_window->Draw(_sprite);
}

bool Bullet::Collision(sf::Rect<float> otherRect) {
	if (_rect.Intersects(otherRect)) {
		return true;
	} else {
		return false;
	}
}
bool Bullet::OnScreen() {
	if ((_rect.Left > *_viewPosition + SCREEN_SIZE.x) ||
		(_rect.Right < *_viewPosition) ||
		(_rect.Bottom < 0) || 
		(_rect.Top > SCREEN_SIZE.y)) {
		return false;
	} else {
		return true;
	}
}

#pragma endregion 

#pragma region Privates



#pragma endregion
