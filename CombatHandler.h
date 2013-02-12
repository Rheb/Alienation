#ifndef COMBATHANDLER_H
#define COMBATHANDLER_H

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"

class CombatHandler {
public:
	CombatHandler();
	~CombatHandler();

	void Init(sf::RenderWindow* window, float* _frameTime, float* viewPosition);
	void Collisions(Player &player, Enemy &enemy);
	void UpdateBullets();
	void PlayerShoot(sf::Vector2f pos);
	void EnemyShoot(sf::Vector2f pos, sf::Vector2f dir);
	void DrawBullets();
private:
	std::vector <Bullet> _playerBullets;
	std::vector <Bullet> _enemyBullets;

	sf::RenderWindow* _window;
	float*			  _frameTime;
	float*            _viewPosition;
};
#endif