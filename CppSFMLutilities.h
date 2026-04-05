#pragma once
/*
Standar C++ 20
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
			std::cerr << "Warning: No found texture file " << std::endl;
		//return std::make_unique<Sprite>(skyTexture);
		return new Sprite(texture);
	}
	static Text* CreateText(Font& font, std::string pathFont, std::string str = "", unsigned charSize = 30, Color color = Color::Black) {
		if (!font.openFromFile(pathFont))
			std::cerr << "Warning: No found font file " << std::endl;
		Text* text = new Text(font, str, charSize);
		text->setFillColor(color);
		return text;
	}
	static Text* CreateText(Font& font, std::string str = "", unsigned charSize = 30, Color color = Color::Black) {
		Text* text = new Text(font, str, charSize);
		text->setFillColor(color);
		return text;
	}
	static void SetPositionText(Text* text, Vector2f newPosition) { // Using when change de size (i.e. change the string).
		FloatRect hb = text->getLocalBounds();
		text->setOrigin(Vector2f(hb.size.x / 2, hb.size.y / 2));
		text->setPosition(newPosition);
	}
	static Sound* CreateSound(SoundBuffer& buffer, std::string pathSound) {
		if (!buffer.loadFromFile(pathSound))
			std::cerr << "Warning: No found sound file" << std::endl;
		//return std::make_unique<Sprite>(skyTexture);
		return new Sound(buffer);
	}
};