/*
Standar C++ 17
SFML-3.0.2
*/

#include "SFML/Graphics.hpp"
#include <iostream>
#include "CppSFMLutilities.h"
#include "HERO.h"
#include "ENEMY.h"

using namespace sf;

Vector2f viewSize(1024.0f, 768.0f);
VideoMode vm(Vector2u((unsigned)viewSize.x, (unsigned)viewSize.y));
RenderWindow window(vm, "Interactive App", Style::Default); // Default combines the ability to resize a window, close it, and add a title bar.

void SpawnEnemy(); // Prototype: Definition later.

Texture skyTexture;
Sprite* skySprite;

Texture bgTexture;
Sprite* bgSprite;

//Vector2f playerPosition;
//bool playerMoving = false;
HERO hero;

std::vector<ENEMY*> enemies;  // *: otherwise, the reference to the texture is lost and the texture won't display when the enemy is spawned
float To/* = 0.0f*/; 
float Dt = 1.125f; // Interval, in seconds, between spawn the enemies.
float t;

void Init() {

    skySprite = SFML_FEDE::CreateSprite(skyTexture, "Assets/graphics/sky.png");

    bgSprite = SFML_FEDE::CreateSprite(bgTexture, "Assets/graphics/bg.png");

    hero.Init("Assets/graphics/hero.png", Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200.0f);

    srand((unsigned)time(0)); // Seed of rand.

    t = 0.0f;
    To = t;
    
}
void SpawnEnemy() {
    int rnd = rand() % 3; // rand() -> int from 0 to 0x7fff (15 bits). rand() % 3: Random of 0, 1 , 2.
    Vector2f pos;
    float Vx;
    switch (rnd) {
    case 0:
        pos = Vector2f(viewSize.x, viewSize.y * 0.75f); // viewSize.y * 0.75f -> Ground
        Vx = -400.0f;
        break;
    case 1:
        pos = Vector2f(viewSize.x, viewSize.y * 0.6f); // viewSize.y * 0.6f -> Middle
        Vx = -550.0f;
        break;
    case 2:
        pos = Vector2f(viewSize.x, viewSize.y * 0.4f); // viewSize.y * 0.4f -> Top
        Vx = -650.0f;
        break;
    default:
        std::cerr << "Error of rand()" << std::endl;
        return; // enemy doesn't spawn in a random location.
    }
    ENEMY* enemy = new ENEMY(); // *: otherwise, the reference to the texture is lost and the texture won't display when the enemy is spawned
    enemy->Init("Assets/graphics/enemy.png", pos, Vx);
    enemies.push_back(enemy);
}
void UpdateInput() {
    std::optional<Event> event;
    while (event = window.pollEvent()) {
        if (SFML_FEDE::IfKeyPressed(event, Keyboard::Key::Up))
            hero.Jump(-750.0f);
        //if (SFML_FEDE::IfKeyPressed(event, Keyboard::Key::Right)) {
        //    playerMoving = true;
        //    //std::cout << " ->";
        //}
        //if (SFML_FEDE::IfKeyReleased(event, Keyboard::Key::Right)) {
            //playerMoving = false;
        //    //std::cout << " stop";
        //}

        if (event->is<Event::Closed>() || SFML_FEDE::IfKeyPressed(event, Keyboard::Key::Escape)) {
            // Automatically, call to ~HERO() and ~Sprite().
            window.close();
        }
    }
}
void Update(float dt) {
    //std::cout << "fps " << 1.0f / dt << std::endl;
    hero.Update(dt);

    t += dt; // In seconds
    if (t >= To + Dt) { // Dt is the interval, in seconds, between spawn the enemies.
        SpawnEnemy();
        To = t;
    }

    // Update and clear enemies offscreen
    for (int n = 0; n < enemies.size(); n++) {
        ENEMY* enemy = enemies[n]; // Is it necessary???
        enemies[n]->Update(dt);
        if (enemies[n]->GetSprite()->getPosition().x < 0) {
            //std::cout << "Enemies before erase: " << enemies.size() << std::endl;
            enemies.erase(enemies.begin() + n);
            delete(enemy); // Is it necessary???
            //std::cout << "Enemies after erase: " << enemies.size() << std::endl;
        }
    }

    

    //if (playerMoving) {
    //    heroSprite->move(Vector2f(50.0f * dt, 0.0f)); // 50.0f: Speed.
    //}
}
void Draw() {
    window.draw(*skySprite);
    window.draw(*bgSprite);
    window.draw(*hero.GetSprite());
    for (ENEMY* n : enemies) {
        window.draw(*n->GetSprite());
    }
}
int main() {
    Clock clock;
    window.setFramerateLimit(60);

    /*
    RectangleShape rect(Vector2f(500.0f, 300.0f)); // Size.
    rect.setFillColor(Color::Yellow);
    rect.setPosition({ viewSize.x / 2, viewSize.y / 2 }); // Move the center of rect.
    //rect.setPosition(Vector2f(0, 0));
    rect.setOrigin(Vector2f(rect.getSize().x / 2, rect.getSize().y / 2)); // Origin to rotate (pivot).

    CircleShape circle(100); // Ridius
    circle.setFillColor(Color::Green);
    circle.setPosition({viewSize.x/2, viewSize.y/2});
    circle.setOrigin(Vector2f(circle.getRadius(), circle.getRadius()));

    ConvexShape triangle;
    triangle.setPointCount(3); // 3 vertex: 0 to 2
    triangle.setPoint(0, Vector2f(-100, 0)); // Relative to itself.
    triangle.setPoint(1, Vector2f(0, -100)); // -100: triangle is pointing upward.
    triangle.setPoint(2, Vector2f(100, 0)); 
    triangle.setFillColor(Color(128, 0, 128, 255)); //Red, Green, Blue, Alpha. Alpha 255: fully opaque.
    triangle.setPosition({ viewSize.x / 2, viewSize.y / 2 });
    */
    

    Init();

    while (window.isOpen()) {
        // Handle Keyboard Events
        UpdateInput();
        // Update Game Objects in the scene
        Time dt = clock.restart();
        Update(dt.asSeconds()); 
        //window.clear(Color::Red); // Fills the whole window.
        // Render Game Objects
        /*
        window.draw(rect);
        window.draw(circle);
        window.draw(triangle);
        */
        Draw();


        window.display();
    }
    return 0;
}



