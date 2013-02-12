#include "InputManager.h"


#pragma region Base
InputManager::InputManager() {
}
InputManager::~InputManager() {
}
#pragma endregion

#pragma region Publics

void InputManager::Init(sf::RenderWindow* window, float* frameTime) {
	_window = window;
	_frameTime = frameTime;

	_shotCooldown = 0;
}
bool InputManager::Exit() {
	if (IsKeyDown(sf::Key::Escape)) {
		return true;
	} else {
		return false;
	}
}
void InputManager::PlayerAction(Player &player, CombatHandler &combat) {
	sf::Vector2i dir(0,0);

	if (IsKeyDown(sf::Key::Up)) {
		dir.y = -1;
	} else if (IsKeyDown(sf::Key::Down)) {
		dir.y = 1;
	}

	if (IsKeyDown(sf::Key::Left)) {
		dir.x = -1;
	} else if (IsKeyDown(sf::Key::Right)) {
		dir.x = 1;
	}

	player.Move(dir);

	// Fire bullets
	if (_shotCooldown <= 0) {
		if (IsKeyDown(sf::Key::S)) {
			_shotCooldown = PLAYER_SHOT_COOLDOWN;
			
			sf::Vector2f pos(player.GetRect().Right, player.GetRect().Top+PLAYER_SIZE.y/2.0f);
			combat.PlayerShoot(pos);
		} 
	} else {
		_shotCooldown -= *_frameTime;
	}
}

#pragma endregion 

#pragma region Privates

bool InputManager::IsKeyDown(sf::Key::Code key) { 
	return _window->GetInput().IsKeyDown(key); 
}

#pragma endregion
