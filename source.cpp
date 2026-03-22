/*
Standar C++ 17
SFML-3.0.2
*/

#include "SFML/Graphics.hpp"
#include <iostream>
#include "HERO.h"

using namespace sf;

Vector2f viewSize(1024.0f, 768.0f);
VideoMode vm(Vector2u((unsigned)viewSize.x, (unsigned)viewSize.y));
RenderWindow window(vm, "Interactive App", Style::Default); // Default combines the ability to resize a window, close it, and add a title bar.

Texture skyTexture;
Sprite *skySprite;

Texture bgTexture;
Sprite* bgSprite;

HERO hero;

Vector2f playerPosition;
//bool playerMoving = false;

bool IfKeyPressed(std::optional<Event> event, Keyboard::Key keyPress) {
    return (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == keyPress);
}
bool IfKeyReleased(std::optional<Event> event, Keyboard::Key keyRelease) {
    return (event->is<Event::KeyReleased>() && event->getIf<Event::KeyReleased>()->code == keyRelease);
}
void init() {
    if (!skyTexture.loadFromFile("Assets/graphics/sky.png"))
        std::cerr << "Warning: No found texture ";
    skySprite = new Sprite(skyTexture);

    if (!bgTexture.loadFromFile("Assets/graphics/bg.png"))
        std::cerr << "Warning: No found texture ";
    bgSprite = new Sprite(bgTexture);

    hero.Init("Assets/graphics/hero.png", Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200.0f);
    
}
void updateInput() {
    std::optional<Event> event;
    while (event = window.pollEvent()) {
        if (IfKeyPressed(event, Keyboard::Key::Up))
            hero.Jump(-750.0f);
        //if (IfKeyPressed(event, Keyboard::Key::Right)) {
        //    playerMoving = true;
        //    //std::cout << " ->";
        //}
        //if (IfKeyReleased(event, Keyboard::Key::Right)) {
            //playerMoving = false;
        //    //std::cout << " stop";
        //}

        if (event->is<Event::Closed>() || IfKeyPressed(event, Keyboard::Key::Escape)) {
            // Automatically, call to ~HERO() and ~Sprite().
            window.close();
        }
    }
}
void update(float dt) {
    hero.Update(dt);
    //if (playerMoving) {
    //    heroSprite->move(Vector2f(50.0f * dt, 0.0f)); // 50.0f: Speed.
    //}
}
void draw() {
    window.draw(*skySprite);
    window.draw(*bgSprite);

    window.draw(*hero.GetSprite());
}
int main() {
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
    Clock clock;
    window.setFramerateLimit(60);

    init();

    while (window.isOpen()) {
        // Handle Keyboard Events
        updateInput();
        // Update Game Objects in the scene
        Time dt = clock.restart();
        //std::cout << "fps " << 1.0f / dt.asSeconds() << std::endl;
        update(dt.asSeconds()/* * 10.0f*/); 
        //window.clear(Color::Red); // Fills the whole window.
        // Render Game Objects
        /*
        window.draw(rect);
        window.draw(circle);
        window.draw(triangle);
        */
        draw();


        window.display();
    }
    return 0;
}



