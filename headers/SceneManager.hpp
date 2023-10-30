#ifndef OOP_SCENEMANAGER_HPP
#define OOP_SCENEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>

class Game;

class SceneManager {
private:
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, sf::Sound> sounds;
    SceneManager() = default;
    ~SceneManager();
    friend Game;
public:
    sf::Sprite & addSprite(const char* name, const sf::Texture & texture);
    sf::Sprite & addSprite(const char* name, sf::Sprite * spritePtr);
    sf::Sound & addSound(const char* name, const sf::SoundBuffer & audio);
    sf::Sound & addSound(const char* name, sf::Sound * soundPtr);
    sf::Sprite & getSpriteReference(const char* name);
    sf::Sound & getSoundReference(const char* name);
    friend std::ostream& operator<< (std::ostream & os, const SceneManager & sceneManager) noexcept;
};

#endif //OOP_SCENEMANAGER_HPP
