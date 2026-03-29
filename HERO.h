#pragma once // #pragma: Aspects of compilation. once: Include once, preventing multiple definitions.
/*
Standar C++ 17
SFML-3.0.2
*/

#include "SFML/Graphics.hpp"
#include <iostream>
#include "CppSFMLutilities.h"

using namespace sf;

class HERO
{
private:
	Texture texture;
	Sprite* sprite;
	Vector2f pos;
	int jumpCount = 0; // because the player can sometimes double-jump
	float facG; // Gravity factor
	float Vy; // When jump
	const float g = 9.8f; // g positive (downward)
	float Yo = 768.0f * 0.75f; // 768 is the height of original window. 768*0.75: position of ground.
	bool grounded; // when the player is on the ground can they start jumping
public:
	// HERO(); // Error
	HERO() {

	};
	~HERO() { // When window.close(), it run.
		//std::cout << "Delete hero" << std::endl;
		delete(sprite);

	};
	void Init(std::string texturePath, Vector2f position, float factorGravity) {
		pos = position;
		facG = factorGravity;

		grounded = false; // Can be start from a high part and fall to init.

		sprite = SFML_FEDE::CreateSprite(texture, texturePath/*.c_str()*/);
		sprite->setPosition(pos);
		sprite->setOrigin(Vector2f((float)(texture.getSize().x) / 2, (float)(texture.getSize().y) / 2));

	};
	void Update(float dt) {
		Vy += facG * g * dt; // dVy = aceleration dt
		pos.y += Vy * dt; // dy = Vy dt

		sprite->setPosition(pos);

		if (pos.y >= Yo) { 
			pos.y = Yo;
			Vy = 0.0f;
			grounded = true;
			jumpCount = 0;
		}

	};
	void Jump(float Voy) { // The init Voy must be negative (upward)
		if (jumpCount < 2) { // Only jump twice.
			jumpCount++;
			Vy = Voy;
			grounded = false;
		}
	};
	Sprite* GetSprite() { // Used for drawing
		return sprite;
	};

};

