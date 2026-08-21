#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float x, float y, float width, float height, float speed)
        : shape(sf::Vector2f(width, height)), speed(speed) {
        shape.setPosition(sf::Vector2f(x, y));
    }

    void move(float direction, float deltaTime, float windowHeight) {
        shape.move(sf::Vector2f(0.0f, direction * speed * deltaTime));

        if (shape.getPosition().y < 0.0f) {
            shape.setPosition(sf::Vector2f(shape.getPosition().x, 0.0f));
        }

        if (shape.getPosition().y + shape.getSize().y > windowHeight) {
            shape.setPosition(sf::Vector2f(
                shape.getPosition().x,
                windowHeight - shape.getSize().y
            ));
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

private:
    sf::RectangleShape shape;
    float speed;
};

class Ball {
public:
    Ball(float x, float y, float radius, float speedX, float speedY)
        : shape(radius), velocity(speedX, speedY) {
        shape.setPosition(sf::Vector2f(x, y));
    }

    void update(float deltaTime) {
        shape.move(velocity * deltaTime);
    }

    void bounceVertical() {
        velocity.y = -velocity.y;
    }

    void bounceHorizontal() {
        velocity.x = -velocity.x;
    }

    void reset(float x, float y, float speedX, float speedY) {
        shape.setPosition(sf::Vector2f(x, y));
        velocity = sf::Vector2f(speedX, speedY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }

    sf::Vector2f getVelocity() const {
        return velocity;
    }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

int main() {
    constexpr unsigned int WINDOW_WIDTH = 800;
    constexpr unsigned int WINDOW_HEIGHT = 600;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Pong - C++"
    );

    window.setFramerateLimit(60);

    Paddle player(
        30.0f,
        WINDOW_HEIGHT / 2.0f - 50.0f,
        20.0f,
        100.0f,
        400.0f
    );

    Paddle enemy(
        WINDOW_WIDTH - 50.0f,
        WINDOW_HEIGHT / 2.0f - 50.0f,
        20.0f,
        100.0f,
        350.0f
    );

    Ball ball(
        WINDOW_WIDTH / 2.0f - 10.0f,
        WINDOW_HEIGHT / 2.0f - 10.0f,
        10.0f,
        300.0f,
        200.0f
    );

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float playerDirection = 0.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            playerDirection = -1.0f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            playerDirection = 1.0f;
        }

        player.move(playerDirection, deltaTime, WINDOW_HEIGHT);

        float enemyDirection = 0.0f;

        float ballY = ball.getBounds().position.y;
        float enemyY = enemy.getBounds().position.y;
        float enemyCenter = enemyY + enemy.getBounds().size.y / 2.0f;

        if (ballY < enemyCenter) {
            enemyDirection = -1.0f;
        } else if (ballY > enemyCenter) {
            enemyDirection = 1.0f;
        }

        enemy.move(enemyDirection, deltaTime, WINDOW_HEIGHT);

        ball.update(deltaTime);

        sf::FloatRect ballBounds = ball.getBounds();

        if (ballBounds.position.y <= 0.0f ||
            ballBounds.position.y + ballBounds.size.y >= WINDOW_HEIGHT) {
            ball.bounceVertical();
        }

        if (ballBounds.findIntersection(player.getBounds()) ||
            ballBounds.findIntersection(enemy.getBounds())) {
            ball.bounceHorizontal();
        }

        ballBounds = ball.getBounds();

        if (ballBounds.position.x < 0.0f) {
            ball.reset(
                WINDOW_WIDTH / 2.0f - 10.0f,
                WINDOW_HEIGHT / 2.0f - 10.0f,
                300.0f,
                200.0f
            );
        }

        if (ballBounds.position.x + ballBounds.size.x > WINDOW_WIDTH) {
            ball.reset(
                WINDOW_WIDTH / 2.0f - 10.0f,
                WINDOW_HEIGHT / 2.0f - 10.0f,
                -300.0f,
                -200.0f
            );
        }

        window.clear();

        player.draw(window);
        enemy.draw(window);
        ball.draw(window);

        window.display();
    }

    return 0;
}
