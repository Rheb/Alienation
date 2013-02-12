#ifndef CONSTS_H
#define CONSTS_H

#include <SFML/Graphics.hpp>

const sf::Vector2f SCREEN_SIZE(1920, 1080);

const sf::Vector2f PLAYER_RECT_POS(30, 7);
const sf::Vector2f PLAYER_SIZE(167, 167);
const float PLAYER_SPEED		   = 550.0f;
const float PLAYER_KNOCKBACK_SPEED = 1200.0f;
const float PLAYER_START_POS	   = 20000.0f;
const float PLAYER_START_HEALTH    = 500.0f;
const float PLAYER_SHOT_COOLDOWN   = 0.4f;

const sf::Vector2f ENEMY_RECT_POS(20, 16);
const sf::Vector2f ENEMY_SIZE(156, 132);
const float ENEMY_STABLE_POS	 = 1580.0f;
const float ENEMY_SPEED			 = 475.0f;
const float ENEMY_ATTACK_SPEED	 = 800.0f;
const float ENEMY_PUSH_DAMAGE	 = 30.0f;
const float ENEMY_BULLET_DAMAGE	 = 30.0f;
const float ENEMY_KNOCKBACK_TIME = 0.5f;

const float BOARD_EDGE_TOP   = 50.0f;
const float BOARD_EDGE_BOT   = 950.0f;
const float BOARD_EDGE_LEFT  = 150.0f;
const float BOARD_EDGE_RIGHT = 700.0f;

const sf::Vector2f BULLET_SIZE(170, 64);
const float BULLET_SPEED = 1100;

enum GameState {GS_START_SCREEN, GS_PAUS_SCREEN, GS_INTRO, GS_OUTRO, GS_PUSHBACK, GS_GAMEPLAY};
#endif 