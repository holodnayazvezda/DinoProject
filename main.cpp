#include <SFML/Graphics.hpp>
#include <iostream>

int getStep(int y) {
    if (y > 410) {
        return 3;
    } else if (y > 340) {
        return 2;
    } else {
        return 1 ;
    }
}

int main()
{
    sf::RenderWindow window(
            sf::VideoMode(1200, 800),
            "Dino");
    window.setFramerateLimit(300);
    sf::RectangleShape rectangleShape;
    rectangleShape.setSize(sf::Vector2f(1200, 250));
    rectangleShape.setPosition(0, 550);
    rectangleShape.setFillColor(sf::Color(70, 70, 70));
    // текст
    sf::Text text;
    sf::Font font;
    font.loadFromFile("C:/Users/holod/CLionProjects/DinoProject/bin/fonts/arial.ttf");
    text.setFont(font);
    text.setString("0");
    text.setCharacterSize(35);
    text.setFillColor(sf::Color(70, 70, 70));
    text.setPosition(sf::Vector2f(1000, 25));
    // об
    sf::Texture baseTexture;
    if (!baseTexture.loadFromFile("C:/Users/holod/CLionProjects/DinoProject/bin/images/sprite.png")) {
        return -1;
    }
    sf::Sprite baseDinoSprite(baseTexture);
    baseDinoSprite.setTextureRect(sf::IntRect(1335, 0, 90, 95));
    baseDinoSprite.setPosition(150, 550-95);
    // финальный спрайт
    sf::Sprite endDinoSprite(baseTexture);
    endDinoSprite.setTextureRect(sf::IntRect(1780, 0, 90, 95));
    endDinoSprite.setPosition(150, 550-95);
    // первый бегущий спрайт
    sf::Sprite firstRunningDinoSprite(baseTexture);
    firstRunningDinoSprite.setTextureRect(sf::IntRect(1515, 0, 90, 95));
    firstRunningDinoSprite.setPosition(150, 550-95);
    // второй бегущий спрайт
    sf::Sprite secondRunningDinoSprite(baseTexture);
    secondRunningDinoSprite.setTextureRect(sf::IntRect(1603, 0, 90, 95));
    secondRunningDinoSprite.setPosition(150, 550-95);
    // спрайты кактуса
    sf::Sprite mediumCactusSprite(baseTexture);
    mediumCactusSprite.setTextureRect(sf::IntRect(448, 0, 34, 70));
    mediumCactusSprite.setPosition(1300, 550-70);
    sf::Sprite bigCactusSprite(baseTexture);
    bigCactusSprite.setTextureRect(sf::IntRect(653, 3, 49, 96));
    bigCactusSprite.setPosition(1300, 550-96);
    sf::Sprite manyCactusSprite(baseTexture);
    manyCactusSprite.setTextureRect(sf::IntRect(802, 3, 149, 96));
    manyCactusSprite.setPosition(1300, 550-96);
    // массив движущихся кактусов
    std::vector<sf::Sprite> movingCactuses = {mediumCactusSprite, bigCactusSprite, manyCactusSprite};
    // массив бегущих дракончиков
    std::vector<sf::Sprite> runningDinos = {firstRunningDinoSprite, secondRunningDinoSprite};
    // часы для ходьбы динозаврика
    sf::Clock steppingClock;
    // часы для счетчика отчков
    sf::Clock scoresClock;
    // часы для кактуса
    sf::Clock cactusClock;
    // счетчик количества шагов (т.е. количество смен спрайта бегущего динозаврика)
    int amountOfChanges = 0;
    // счетчик количества очков (1 секунда = 10 очков, пока без усокрения)
    int score = 0;
    // переменные для физики прыжка динозаврика
    bool onJump = false;
    bool onDown = false;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !onJump && !onDown) {
                sf::Vector2 dinoPos = baseDinoSprite.getPosition();
                if (!onJump) {
                    onJump = true;
                    // baseDinoSprite.setPosition(150, 455);
                }
            }
        }
        if (scoresClock.getElapsedTime().asSeconds() >= 0.1) {
            score ++;
            text.setString(std::to_string(score));
            scoresClock.restart();
        }
        if (onJump) {
            window.clear(sf::Color::White);
            window.draw(rectangleShape);
            sf::Vector2 dinoPos = baseDinoSprite.getPosition();
            if (dinoPos.y <= 320) {
                onJump = false;
                onDown = true;
            } else {
                dinoPos.y -= getStep(dinoPos.y);
            }
            baseDinoSprite.setPosition(dinoPos);
            window.draw(baseDinoSprite);
            window.draw(text);
            if (cactusClock.getElapsedTime().asSeconds() >= 0.0033) {
                sf::Vector2 mediumCactusPosition = mediumCactusSprite.getPosition();
                if (mediumCactusPosition.x < - 150) {
                    mediumCactusSprite.setPosition(1300, mediumCactusPosition.y);
                } else {
                    mediumCactusSprite.setPosition(mediumCactusPosition.x - 4, mediumCactusPosition.y);
                }
                window.draw(mediumCactusSprite);
                std::cout << mediumCactusPosition.x << " " << mediumCactusPosition.y << "\n";
                cactusClock.restart();
            } else {
                window.draw(mediumCactusSprite);
            }
            window.display();
        } else if (onDown) {
            window.clear(sf::Color::White);
            window.draw(rectangleShape);
            sf::Vector2 dinoPos = baseDinoSprite.getPosition();
            if (dinoPos.y >= 455) {
                onDown = false;
                dinoPos.y = 455;
            } else {
                dinoPos.y += getStep(dinoPos.y);
            }
            baseDinoSprite.setPosition(dinoPos);
            window.draw(baseDinoSprite);
            window.draw(text);
            if (cactusClock.getElapsedTime().asSeconds() >= 0.0033) {
                sf::Vector2 mediumCactusPosition = mediumCactusSprite.getPosition();
                if (mediumCactusPosition.x < - 150) {
                    mediumCactusSprite.setPosition(1300, mediumCactusPosition.y);
                } else {
                    mediumCactusSprite.setPosition(mediumCactusPosition.x - 4, mediumCactusPosition.y);
                }
                window.draw(mediumCactusSprite);
                std::cout << mediumCactusPosition.x << " " << mediumCactusPosition.y << "\n";
                cactusClock.restart();
            } else {
                window.draw(mediumCactusSprite);
            }
            window.display();
        } else {
            if (steppingClock.getElapsedTime().asSeconds() >= 0.09) {
                amountOfChanges ++;
                window.clear(sf::Color::White);
                window.draw(rectangleShape);
                if (amountOfChanges % 2 == 0) {
                    window.draw(firstRunningDinoSprite);
                } else {
                    window.draw(secondRunningDinoSprite);
                }
                window.draw(text);
                if (cactusClock.getElapsedTime().asSeconds() >= 0.0033) {
                    sf::Vector2 mediumCactusPosition = mediumCactusSprite.getPosition();
                    if (mediumCactusPosition.x < - 150) {
                        mediumCactusSprite.setPosition(1300, mediumCactusPosition.y);
                    } else {
                        mediumCactusSprite.setPosition(mediumCactusPosition.x - 4, mediumCactusPosition.y);
                    }
                    window.draw(mediumCactusSprite);
                    std::cout << mediumCactusPosition.x << " " << mediumCactusPosition.y << "\n";
                    cactusClock.restart();
                } else {
                    window.draw(mediumCactusSprite);
                }
                window.display();
                steppingClock.restart();
            } else {
                window.clear(sf::Color::White);
                window.draw(rectangleShape);
                if (amountOfChanges % 2 == 0) {
                    window.draw(firstRunningDinoSprite);
                } else {
                    window.draw(secondRunningDinoSprite);
                }
                window.draw(text);
                if (cactusClock.getElapsedTime().asSeconds() >= 0.0033) {
                    sf::Vector2 mediumCactusPosition = mediumCactusSprite.getPosition();
                    if (mediumCactusPosition.x < - 150) {
                        mediumCactusSprite.setPosition(1300, mediumCactusPosition.y);
                    } else {
                        mediumCactusSprite.setPosition(mediumCactusPosition.x - 4, mediumCactusPosition.y);
                    }
                    window.draw(mediumCactusSprite);
                    std::cout << mediumCactusPosition.x << " " << mediumCactusPosition.y << "\n";
                    cactusClock.restart();
                } else {
                    window.draw(mediumCactusSprite);
                }
                window.display();
            }
        }
    }
    return 0;
}
