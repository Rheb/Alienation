#include "Imagebank.h"

#include <iostream>

// Global Imagebank
Imagebank imagebank;

Imagebank::Imagebank() {
	// Load the imagebank
	load("Player", "Player.png");
	load("Bullets", "Bullets.png");
	load("Enemy", "Enemy.png");


	//// Create the editor shadow image
	//sf::Image MarkingShadow(W_TILE, W_TILE, sf::Color(50,100,0,60));
	//images_.insert(std::pair<const std::string, sf::Image>("MarkingShadow", MarkingShadow));
	//
	//// Create the one colored screen and board images
	//sf::Image BlackBoard(W_BOARD, H_BOARD, sf::Color(0,0,0));
	//images_.insert(std::pair<const std::string, sf::Image>("BlackBoard", BlackBoard));
	//sf::Image BlackScreen(W_SCREEN, H_SCREEN, sf::Color(0,0,0));
	//images_.insert(std::pair<const std::string, sf::Image>("BlackScreen", BlackScreen));
	//sf::Image RedBoard(W_BOARD, H_BOARD, sf::Color(60,0,0));
	//images_.insert(std::pair<const std::string, sf::Image>("RedBoard", RedBoard));
	//sf::Image RedBoardFilter(W_BOARD, H_BOARD, sf::Color(80,15,15,40));
	//images_.insert(std::pair<const std::string, sf::Image>("RedBoardFilter", RedBoardFilter));
}
sf::Image &Imagebank::operator[](const std::string &id) {
	if (_images.find(id) == _images.end()) {
		std::cout << "Could not find " << id << " in imagebank.\n";
		std::cin.get();
	}
	return _images[id];
}
void Imagebank::load(const std::string &id, const std::string &fileName) {
	sf::Image image;
	if (!(image.LoadFromFile("Data/Images/" + fileName))){
		std::cout << "Data/Images/" + fileName << " did not load!";
		std::cin.get();
	}
	_images.insert(std::pair<const std::string, sf::Image>(id, image));
}