#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Mi primer programa C++"
    );

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        sf::RectangleShape rectangle(sf::Vector2f(100.0f, 50.0f));
        rectangle.setPosition(sf::Vector2f(350.0f, 275.0f));

        window.draw(rectangle);
        window.display();
    }

    return 0;
}
