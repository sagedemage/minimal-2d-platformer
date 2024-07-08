#include <iostream>

#define LEVEL_WIDTH 750
#define LEVEL_HEIGHT 500

sf::Vector2f player_boundary(sf::Vector2f position) {
    if (position.x+25 >= 750.f)
    {
        /* Right boundary */
        position.x = float(LEVEL_WIDTH - 25);
    }
    else if (position.x <= 0.f)
    {
        /* Left  boundary */
        position.x = 0.f;
    }
    if (position.y <= 0.f)
    {
        /* Top boudnary */
        position.y = 0.f;
    }
    else if (position.y+25 >= LEVEL_HEIGHT)
    {
        /* Bottom boudnary */
        position.y = float(LEVEL_HEIGHT - 25);
    }
    return position;
}

bool movePlayer(sf::RectangleShape& player, int speed, bool on_the_floor) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // move player left
        player.move(-speed, 0.f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // move player right
        player.move(speed, 0.f);
    }

    return on_the_floor;
}

bool playerWallCollision(sf::RectangleShape& player, sf::RectangleShape& wall, bool on_the_floor, int accel) {

    sf::Vector2f p_position = player.getPosition();
    int offset = 2;
    /* X Axis Collision */
    if (player.getPosition().y > wall.getPosition().y+offset &&
        player.getPosition().y < wall.getPosition().y + 25-offset) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25 > wall.getPosition().y+offset &&
        player.getPosition().y + 25 < wall.getPosition().y + 25-offset) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().y + 25/2 > wall.getPosition().y &&
        player.getPosition().y + 25/2 < wall.getPosition().y + 25) {
        if (player.getPosition().x+25 >= wall.getPosition().x &&
            player.getPosition().x+25 < wall.getPosition().x +25) {
            // left collision
            p_position.x-=2;
            player.setPosition(p_position);
        }
        else if (player.getPosition().x <= wall.getPosition().x+25 &&
            player.getPosition().x > wall.getPosition().x) {
            // right collision
            p_position.x+=2;
            player.setPosition(p_position);
        }
    }

    /* Y Axis Collision */
    if (player.getPosition().x > wall.getPosition().x &&
        player.getPosition().x < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y +25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25 > wall.getPosition().x &&
        player.getPosition().x + 25 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y +25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=2;
            player.setPosition(p_position);
        }
    }

    else if (player.getPosition().x + 25/2 > wall.getPosition().x &&
        player.getPosition().x + 25/2 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y +25) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
        else if (player.getPosition().y <= wall.getPosition().y+25 &&
            player.getPosition().y > wall.getPosition().y) {
            // bottom collision
            p_position.y+=2;
            player.setPosition(p_position);
        }
    }
    return on_the_floor;
}

bool playerPlatformCollision(sf::RectangleShape& player, sf::RectangleShape& wall, bool on_the_floor, int accel) {

    sf::Vector2f p_position = player.getPosition();

    /* Y Axis Collision */
    if (player.getPosition().x > wall.getPosition().x &&
        player.getPosition().x < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }

    else if (player.getPosition().x + 25 > wall.getPosition().x &&
        player.getPosition().x + 25 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }

    else if (player.getPosition().x + 25/2 > wall.getPosition().x &&
        player.getPosition().x + 25/2 < wall.getPosition().x + 25) {
        if (player.getPosition().y+25 >= wall.getPosition().y &&
            player.getPosition().y+25 < wall.getPosition().y+accel) {
            // top collision
            p_position.y-=accel;
            player.setPosition(p_position);
            on_the_floor = true;
        }
    }
    return on_the_floor;
}

int gravity(sf::Vector2f position, int accel) {
    position.y += accel;

    return position.y;
}

bool drawAllRegions(sf::RenderWindow& window, sf::RectangleShape& player, sf::RectangleShape& wall,
    sf::RectangleShape& platform, bool on_the_floor, int accel) {
    window.clear(sf::Color(84, 193, 255, 255));

    window.draw(player);

    wall.setPosition(LEVEL_WIDTH-25, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-50, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-75, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-100, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-125, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-150, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-175, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-200, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-225, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-250, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-275, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-300, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-325, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-350, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-375, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-400, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-425, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-450, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-475, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-500, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-525, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-550, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-575, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-600, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-625, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-650, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-675, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-700, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-725, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-750, LEVEL_HEIGHT-25);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    platform.setPosition(LEVEL_WIDTH-600, LEVEL_HEIGHT-50);
    window.draw(platform);

    on_the_floor = playerPlatformCollision(player, platform, on_the_floor, accel);

    platform.setPosition(LEVEL_WIDTH-575, LEVEL_HEIGHT-75);
    window.draw(platform);

    on_the_floor = playerPlatformCollision(player, platform, on_the_floor, accel);

    wall.setPosition(LEVEL_WIDTH-550, LEVEL_HEIGHT-100);
    window.draw(wall);

    on_the_floor = playerWallCollision(player, wall, on_the_floor, accel);

    window.display();

    return on_the_floor;
}

int main()
{
    // window
    sf::RenderWindow window(sf::VideoMode(LEVEL_WIDTH, LEVEL_HEIGHT), "2D Platformer");
    window.setFramerateLimit(60);

    sf::Clock gameClock;

    // player
    sf::RectangleShape player(sf::Vector2f(25, 25));
    player.setFillColor(sf::Color(91, 31, 255, 255));

    player.setPosition(0, LEVEL_HEIGHT-250);

    sf::RectangleShape wall(sf::Vector2f(25, 25));
    wall.setFillColor(sf::Color(0, 0, 0, 255));

    sf::RectangleShape platform(sf::Vector2f(25, 25/2));
    platform.setFillColor(sf::Color(0, 0, 0, 255));

    const float speed = 2.f;
    const int accel = 5;
    bool on_the_floor = false;

    sf::Music music;
    if (!music.openFromFile("assets/music/empty.ogg")) {
        return -1;
    }

    const int volume = 50;
    music.setVolume(volume);

    music.setLoop(true);
    music.play();

#pragma unroll
    while (window.isOpen())
    {
        sf::Event event;
#pragma unroll
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up and on_the_floor == true)
                {
                    // jump
                    player.move(0.f, -accel*10);
                    on_the_floor = false;
                }
                if (event.key.code == sf::Keyboard::Down and on_the_floor == true)
                {
                    // drop down
                    player.move(0.f, accel);
                    on_the_floor = false;
                }
            }
        }

        on_the_floor = movePlayer(player, speed, on_the_floor);

        // Player Boundary
        sf::Vector2f player_position = player_boundary(player.getPosition());
        player.setPosition(player_position);

        // Gravity
        player_position.y = gravity(player.getPosition(), accel);
        player.setPosition(player_position);

        on_the_floor = drawAllRegions(window, player, wall, platform, on_the_floor, accel);
    }

    return 0;
}
