/*
Standar C++ 17
*/

#include "SFML/Graphics.hpp"

using namespace sf;

Vector2f viewSize(1024.0f, 768.0f);
VideoMode vm(Vector2u((unsigned)viewSize.x, (unsigned)viewSize.y));
RenderWindow window(vm, "Interactive App", Style::Default); // Default combines the ability to resize a window, close it, and add a title bar.

Texture skyTexture;
Sprite* skySprite;

Texture bgTexture;
Sprite* bgSprite;

Texture heroTexture;
Sprite* heroSprite;

bool IfKeyPressed(std::optional<Event> event, Keyboard::Key keyPress) {
    return (event->is<Event::KeyPressed>() && event->getIf<Event::KeyPressed>()->code == keyPress);
}

void updateInput() {
    
    while (std::optional<Event> e = window.pollEvent()) {
        /*if (e->is<Event::Closed>() || (e->is<Event::KeyPressed>() && e->getIf<Event::KeyPressed>()->code == Keyboard::Key::Escape)) {
            window.close();
        }*/
        if (e->is<Event::Closed>() || IfKeyPressed(e, Keyboard::Key::Escape)) {
            window.close();
        }
    }
}
void init() {
    skyTexture.loadFromFile("Assets/graphics/sky.png");
    skySprite = new Sprite(skyTexture);

    bgTexture.loadFromFile("Assets/graphics/bg.png");
    bgSprite = new Sprite(bgTexture);

    heroTexture.loadFromFile("Assets/graphics/hero.png");
    heroSprite = new Sprite(heroTexture);
    heroSprite->setPosition(Vector2f(viewSize.x / 2, viewSize.y / 2));
    heroSprite->setOrigin(Vector2f((float)(heroTexture.getSize().x) / 2, (float)(heroTexture.getSize().y) / 2));

}
void draw() {
    window.draw(*skySprite);
    window.draw(*bgSprite);
    window.draw(*heroSprite);
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
    init();


    while (window.isOpen()) {
        // Handle Keyboard Events
        // Update Game Objects in the scene
        //window.clear(Color::Red); // Fills the whole window.
        updateInput();
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



