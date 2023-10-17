#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game {
private:
    static Game* instance;
    sf::RenderWindow window;
    Game();
    ~Game() = default;
public:
    static Game & getInstance() ;
    static void clearInstance();
    void init();
    void loop();
};

#endif //OOP_GAME_H
