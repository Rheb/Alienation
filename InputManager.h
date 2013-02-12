#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "CombatHandler.h"

class InputManager {
public:
	InputManager();
	~InputManager();

	void Init(sf::RenderWindow* window, float* frameTime);
	bool Exit();
	void PlayerAction(Player &player, CombatHandler &combat);
private:
	bool IsKeyDown(sf::Key::Code);

	float _shotCooldown;

	sf::RenderWindow* _window;
	float*            _frameTime;
};
#endif
