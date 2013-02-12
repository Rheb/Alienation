#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "InputManager.h"
#include "Enemy.h"

#include "EnemyVector.h"
#include "CombatHandler.h"
//#include "Music.h"
//#include "Sound.h"
//#include "Background.h"

class Game {
public:
	Game();
	~Game();

	void Init();
	void Loop();

private:
	sf::RenderWindow* _window;
	GameState*        _state;
	float*            _frameTime;
	float*            _viewPosition;

	InputManager      _input;
	Player            _player;
	EnemyVector       _enemyVector;
	CombatHandler     _combat;

	Enemy			  _enemy;

	//Music			  _music;
	//Sound			  _sound;
};
#endif 