#include "CombatHandler.h"
#include <iostream>

#pragma region Base
CombatHandler::CombatHandler() {
}
CombatHandler::~CombatHandler() {
}
#pragma endregion

#pragma region Publics
void CombatHandler::Init(sf::RenderWindow* window, float* frameTime, float* viewPosition) {
	_window = window;
	_frameTime = frameTime;
	_viewPosition = viewPosition;
}
void CombatHandler::Collisions(Player &player, Enemy &enemy) {
	// Enemy player collision
	if (player.GetRect().Intersects(enemy.GetRect())) {
		player.CollisionEnemy(enemy.GetRect());
		enemy.CollisionPlayer();
	} else {

		// OBS! Check so that the particular enemy is not attacking first
		// Player in danger zone (Too close to enemies)
		if (!player.Stunned()) {
			if (enemy.GetRect().Left - player.GetRect().Right < 170) {
				enemy.ChargePlayer();
			}
		}
	}

	// Bullet hits
	for (int i=0; i<_playerBullets.size(); i++) {
		if (_playerBullets[i].Collision(enemy.GetRect())) {
			_playerBullets.erase(_playerBullets.begin() + i);
			enemy.HitByBullet();
			
			// OBS Don't count up after erase
			i--;
		}
	}

	for (int i=0; i<_enemyBullets.size(); i++) {
		if (_enemyBullets[i].Collision(player.GetRect())) {
			_enemyBullets.erase(_enemyBullets.begin() + i);
			player.HitByBullet();
			
			// OBS Don't count up after erase
			i--;
		}
	}
}
void CombatHandler::UpdateBullets() {
	for (int i=0; i<_playerBullets.size(); i++) {
		_playerBullets[i].Move();
		if (!_playerBullets[i].OnScreen()) {
			_playerBullets.erase(_playerBullets.begin() + i);
			// OBS Don't count up after erase
			i--;
		}
	}
	for (int i=0; i<_enemyBullets.size(); i++) {
		_enemyBullets[i].Move();
		if (!_enemyBullets[i].OnScreen()) {
			_enemyBullets.erase(_enemyBullets.begin() + i);
			// OBS Don't count up after erase
			i--;
		}
	}
}
void CombatHandler::PlayerShoot(sf::Vector2f pos) {
	Bullet bullet(pos, sf::Vector2f(1, 0), false);
	bullet.Init(_window, _frameTime, _viewPosition);
	_playerBullets.push_back(bullet);
}
void CombatHandler::EnemyShoot(sf::Vector2f pos, sf::Vector2f dir) {
	Bullet bullet(pos, dir, true);
	bullet.Init(_window, _frameTime, _viewPosition);
	_enemyBullets.push_back(bullet);
}
void CombatHandler::DrawBullets() {
	for (int i=0; i<_playerBullets.size(); i++) {
		_playerBullets[i].Draw();
	}
	for (int i=0; i<_enemyBullets.size(); i++) {
		_enemyBullets[i].Draw();
	}
}

#pragma endregion 

#pragma region Privates



#pragma endregion
