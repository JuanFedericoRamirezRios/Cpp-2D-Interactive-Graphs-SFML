#pragma once
/*
Standar C++ 17
SFML-3.0.2
*/

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class SFML_FEDE {
private:

public:
	static bool IfKeyPressed(std::optional<Event> event, Keyboard::Key keyPress) {
		return (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == keyPress);
	}
	static bool IfKeyReleased(std::optional<Event> event, Keyboard::Key keyRelease) {
		return (event->is<Event::KeyReleased>() && event->getIf<Event::KeyReleased>()->code == keyRelease);
	}
	static Sprite* CreateSprite(Texture& texture, std::string pathTexture) {
		if (!texture.loadFromFile(pathTexture))
			std::cerr << "Warning: No found texture " << std::endl;
		//return std::make_unique<Sprite>(skyTexture);
		return new Sprite(texture);
	}
};