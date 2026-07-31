#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    std::cout << "test";
    sf::RenderWindow window(sf::VideoMode({800u, 600u}), "SFML 3");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}
