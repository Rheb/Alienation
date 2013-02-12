#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"

#pragma region Base
Game::Game() {
}
Game::~Game() {
	delete _window;
	delete _state;
	delete _frameTime;
}
#pragma endregion


#pragma region Publics

#pragma region Init
void Game::Init() {
	// Try getting the desctop window mode in order to create a window of an appropriate size
	sf::VideoMode desktopMode = sf::VideoMode::GetDesktopMode();

	float wWindow = SCREEN_SIZE.x;
	float hWindow = SCREEN_SIZE.y;
	float winPosX = 60;
	float winPosY = 60;

	// Choke point W/H how large do I make my window. KEEP SCALING
	if ((desktopMode.Width == 0) || (desktopMode.Height == 0)) {
		// ERROR
		std::cout << "ERROR: Could not get desktop video mode\n";
	} else {
		if ((desktopMode.Width*1.0f/desktopMode.Height) > (SCREEN_SIZE.x*1.0f/SCREEN_SIZE.y)) {
			hWindow = desktopMode.Height;
			wWindow = hWindow * SCREEN_SIZE.x/(float)SCREEN_SIZE.y;

			//std::cout << "Height\n";
		} else {
			wWindow = desktopMode.Width;
			hWindow = wWindow * SCREEN_SIZE.y/(float)SCREEN_SIZE.x;

			//std::cout << "Width\n";
		}
		winPosX = (desktopMode.Width - wWindow*0.85)/2.0f;
		winPosY = (desktopMode.Height - hWindow*0.85)/3.0f;
	}


	// Create the window (Res 32, standard)
	_window = new sf::RenderWindow(sf::VideoMode(SCREEN_SIZE.x, SCREEN_SIZE.y, 32), "Alienation", sf::Style:: Close);
	
	// Position, resizing
	_window->SetPosition(winPosX, winPosY);
	_window->SetSize(wWindow*0.85, hWindow*0.85);

	_state  = new GameState;
	*_state = GS_GAMEPLAY;

	_frameTime  = new float;
	*_frameTime = 0.0f;

	_viewPosition  = new float;
	*_viewPosition = PLAYER_START_POS;

	// Init variables
	_input.Init(_window, _frameTime);
	_player.Init(_window, _frameTime, _viewPosition);
	_enemy.Init(_window, _frameTime, _viewPosition);
	_combat.Init(_window, _frameTime, _viewPosition);

	// Init random genertor
	srand(time(0));
	for (int i=0; i<100; i++) {
		rand();
	}
}
#pragma endregion

void Game::Loop() {
	// Create a clock for handling time
	sf::Clock clock;
	float     oldTime     = 0.0f;
	float     currentTime = 0.0f;

	// If the window is still open, run the game loop
	while(_window->IsOpened()) {
		// Update time
		oldTime = currentTime;
		currentTime = clock.GetElapsedTime();
		*_frameTime = currentTime - oldTime;

		// Events
		// Loop through the event stack while there are any events in it
		sf::Event eventStack;
		while((_window->GetEvent(eventStack)) && (_window->IsOpened())) {
			if(eventStack.Type == sf::Event::Closed) { 
				_window->Close();
			} else if (eventStack.Type == sf::Event::LostFocus) {
				// Sleep while focus is lost
				// OBS Paus Music
				bool sleeping = true;
				while (sleeping) {
					// Sleep some then get new event
					sf::Sleep(0.05);
					while (_window->GetEvent(eventStack)){
						// Close window : exit
						if (eventStack.Type == sf::Event::Closed){
							_window->Close();
							sleeping = false;
						}
						if (eventStack.Type == sf::Event::GainedFocus){
							sleeping = false;
						}
					}
				}
				// OBS Start Music

				// Reset time elasped
				currentTime = clock.GetElapsedTime();
			}
		}

		// Input
		if (_input.Exit()) {
			_window->Close();
		}
		
		// Check game state
		if (*_state == GS_GAMEPLAY) {
			// Check player input
			_input.PlayerAction(_player, _combat);

			// Update enemies
			_enemy.Update(_player.GetRect(), _combat);

			// Update bullets
			_combat.UpdateBullets();

			// Collision check
			_combat.Collisions(_player, _enemy); 

			// Draw
			_player.Draw();
			_enemy.Draw();
			_combat.DrawBullets();
		}	

		// Display window
		_window->Display();
		_window->Clear();

		// Sleep a short while aiming for 60 fps
		float thisFrameTime = clock.GetElapsedTime() - currentTime;
		if (thisFrameTime < 0.016) {
			sf::Sleep(0.016 - thisFrameTime);
		} else {
			// Note: Below 60 fps. Sleep some anyway to reduce CPU time.
			sf::Sleep(0.005);
		}
	}
}

#pragma endregion 

#pragma region Privates



#pragma endregion
