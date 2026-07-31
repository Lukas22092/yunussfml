#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>

struct Player
{
    int posx;
    int posy;
    int sx;
    int sy;
};


struct Main
{
    std::vector<Object> objects;

    int start(Player player)
{
    // Fenstergröße etwas erhöht, damit man 550px Objekte sieht!
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Platformer");
    window.setFramerateLimit(60);

    sf::RectangleShape rec(sf::Vector2f(static_cast<float>(player.sx), static_cast<float>(player.sy)));
    rec.setFillColor(sf::Color::Green);
    
    float flightTime = 0;

    // Initial Position
    rec.setPosition({static_cast<float>(player.posx), static_cast<float>(player.posy)});

    while (window.isOpen())
    {
        // SFML 3 Event Loop
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color::Black);

        for (const Object &o : objects)
        {
            sf::RectangleShape ground(sf::Vector2f(static_cast<float>(o.sx), static_cast<float>(o.sy)));
            ground.setFillColor(sf::Color::Red);
            ground.setPosition({static_cast<float>(o.posx), static_cast<float>(o.posy)});
            window.draw(ground);
        }

        // Steuerung (isKeyPressed bleibt fast gleich, aber Key-Namespace beachten)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if(!leftWallCoalision(player, objects)) player.posx -= 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if(!rightWallCoalision(player, objects)) player.posx += 5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            if(!headCoalision(player, objects)) player.posy -= 10;
        }

        if(!groundCoalision(player, objects)) {
           player.posy += 5; 
        }
        rec.setPosition({static_cast<float>(player.posx), static_cast<float>(player.posy)});

        window.draw(rec);
        window.display();
    }
    return 0;
}

    bool leftWallCoalision(Player player, std::vector<Object> objects)
    {
        //Wandkoalision, wenn
        for (const Object &o : objects)
        {
            //Unterer Rand des Spielers(posy+sy) nicht 체ber oberer Rand des Objektes(oposy) => true
            //AND
            //x
            //linke seite des spielers nicht weiter rechts als rechte seite des objekts
            //rechte seite des spielers nicht weiter links als linke seite des objekts
            if ((player.posy+player.sy > o.posy && player.posy < o.posy+o.sy) && (player.posx - 5 < o.posx + o.sx) && (player.posx > o.posx)) {
                return true;
            }
        }
        
        return false;
    };

    bool rightWallCoalision(Player player, std::vector<Object> objects)
    {
        //Wandkoalision, wenn
        for (const Object &o : objects)
        {
            //Unterer Rand des Spielers(posy+sy) nicht 체ber oberer Rand des Objektes(oposy) => true
            //AND
            //x
            //linke seite des spielers nicht weiter rechts als rechte seite des objekts
            //rechte seite des spielers nicht weiter links als linke seite des objekts
            if ((player.posy+player.sy > o.posy && player.posy < o.posy+o.sy) && (player.posx + player.sx + 5 > o.posx) && (player.posx + player.sx < o.posx + o.sx)) {
                return true;
            }
        }
        
        return false;
    };

    bool groundCoalision(Player player, std::vector<Object> objects) 
    {
        //Bodenkollision
        for (const Object &o : objects)
        {
            if((player.posy+player.sy >= o.posy)&&(player.posy < o.posy)&& 
            (player.posx+player.sx>=o.posx)&&(player.posx<=o.posx+o.sx)) 
            {
                return true;
            }
        }
        
        return false;
    };

    bool headCoalision(Player player, std::vector<Object> objects) 
    {
        for (const Object &o : objects)
        {
            if((player.posy <= o.posy+o.sy + 10)&&(player.posy > o.posy)&& //Vertikale Schneidung
            (player.posx+player.sx>o.posx)&&(player.posx<o.posx+o.sx)) //Horizontale Schneidung
            {
                return true;
            }
        }
        return false;
    };
};
