#pragma once // #pragma: Aspects of compilation. once: Include once, preventing multiple definitions.
/*
Standar C++ 17
SFML-3.0.2
*/

#include "SFML/Graphics.hpp"
#include <iostream>
#include "CppSFMLutilities.h"

using namespace sf;

class ENEMY {
private:
	Texture texture;
	Sprite* sprite;
	Vector2f pos;
	float Vx;

public:
	ENEMY() {

	}
	~ENEMY() {
		delete(sprite);
	}
	void Init(std::string pathTexture, Vector2f position, float Vx) {
		this->Vx = Vx;
		pos = position;

		sprite = SFML_FEDE::CreateSprite(texture, pathTexture/*.c_str()*/);
		/*if (!texture.loadFromFile(pathTexture))
			std::cerr << "Warning: No found texture " << std::endl;
		sprite = new Sprite(texture);*/
		sprite->setPosition(pos);
		sprite->setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));
	}
	void Update(float dt) {
		sprite->move(Vector2f(Vx * dt, 0.0f));
	}
	Sprite* GetSprite() { // Used for drawing
		return sprite;
	}
};