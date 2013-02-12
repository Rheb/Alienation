#ifndef IMAGEBANK_H
#define IMAGEBANK_H

// Includes
#include <SFML/Graphics.hpp>

// All images gathered
class Imagebank {
	public:
		Imagebank();
		sf::Image &operator[](const std::string &);
	private:
		void load(const std::string &, const std::string &);
		std::map<const std::string, sf::Image> _images;
};
#endif
