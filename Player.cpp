#include <iostream>
#include "Player.h"

#include "Imagebank.h"

// Externally declared imagebank
extern Imagebank imagebank;

#pragma region Base
Player::Player() {
}
Player::~Player() {
}
#pragma endregion

#pragma region Publics

void Player::Init(sf::RenderWindow* window, float* frameTime, float* viewPosition) {
	_window = window;
	_frameTime = frameTime;
	_viewPosition = viewPosition;

	_sprite.SetImage(imagebank["Player"]);
	_sprite.SetCenter(PLAYER_RECT_POS);

	_rect.Top    = PLAYER_START_POS + 420;
	_rect.Bottom = PLAYER_START_POS + 420 + PLAYER_SIZE.y;
	_rect.Left   = PLAYER_START_POS + 300;
	_rect.Right  = PLAYER_START_POS + 300 + PLAYER_SIZE.x;

	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);

	_knockbackTime = 0.0f;
	_health        = PLAYER_START_HEALTH;
}
void Player::Move(sf::Vector2i dir) {
	float delta = *_frameTime;
	if (_knockbackTime <= 0) {
		delta *= PLAYER_SPEED;

		if((dir.x != 0) && (dir.y != 0)) {
			delta /= 1.414;
		}

		_rect.Offset(dir.x * delta, dir.y * delta);
		//std::cout << "top: " << _rect.Top << "  bot: " << _rect.Bottom << "  left: " << _rect.Left << "  right: " << _rect.Right << "\n";
	} else {
		delta *= PLAYER_KNOCKBACK_SPEED;
		_rect.Offset(-delta, 0);

		_knockbackTime -= *_frameTime;
		if (_knockbackTime < 0) {
			_knockbackTime = 0;
		}
	}

	// Top collision
	if (_rect.Top < BOARD_EDGE_TOP) {
		_rect.Offset(0, BOARD_EDGE_TOP - _rect.Top);
	} else if (_rect.Bottom > BOARD_EDGE_BOT) {
		_rect.Offset(0, BOARD_EDGE_BOT - _rect.Bottom);
	}
	// Check scrolling for horizontal movement outside edges.
	if (_rect.Left - *_viewPosition < BOARD_EDGE_LEFT) {
		*_viewPosition = _rect.Left - BOARD_EDGE_LEFT;
	} else if (_rect.Right - *_viewPosition > BOARD_EDGE_RIGHT) {
		*_viewPosition = _rect.Right - BOARD_EDGE_RIGHT;
	}

	// Check for wastelands end
	if (*_viewPosition < 0) {
		*_viewPosition = 0;
		if (_rect.Left < BOARD_EDGE_LEFT) {
			_rect.Left  = BOARD_EDGE_LEFT;
			_rect.Right = BOARD_EDGE_LEFT + PLAYER_SIZE.x;
		}
	}
	
	_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);

	//std::cout << *_viewPosition << "\n";
}
void Player::Draw() {
	_window->Draw(_sprite);
}

void Player::CollisionEnemy(sf::Rect<float> enemyRect) {
	if (_knockbackTime <= 0) {
		// OBS! Probably not optimal... Get behind the enemy
		_rect.Offset(enemyRect.Left - _rect.Right, 0);
		_sprite.SetPosition(_rect.Left - *_viewPosition, _rect.Top);

		// Knock back
		_health -= ENEMY_PUSH_DAMAGE;
		_knockbackTime = ENEMY_KNOCKBACK_TIME;
	}
}
void Player::HitByBullet() {
	if (_knockbackTime <= 0) {
		// Knock back
		_health -= ENEMY_BULLET_DAMAGE;
		_knockbackTime = ENEMY_KNOCKBACK_TIME;
	}
}
sf::Rect<float> Player::GetRect() {
	return _rect;
}
bool Player::Stunned() {
	if (_knockbackTime > 0) {
		return true;
	} else {
		return false;
	}
}

#pragma endregion 

#pragma region Privates



#pragma endregion