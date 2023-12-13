#ifndef OOP_SCENEMANAGER_HPP
#define OOP_SCENEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>

class Game;

class SceneManager {
private:
    std::map<std::string, sf::Sprite> sprites; /// sprites are background items
    std::map<std::string, sf::Shape*> shapePointers; /// shapes are positioned and scaled better, will be drawn over sprites
    std::map<std::string, sf::Sound> sounds;
    SceneManager() = default;
    ~SceneManager();
    friend Game;
public:
    sf::Sprite & addSprite(const std::string & name, const sf::Texture & texture);
    sf::Sprite & addSprite(const std::string & name, sf::Sprite * spritePtr);

    sf::Shape & addShape(const std::string & name, sf::Shape * shapePtr);

    sf::Sound & addSound(const std::string& name, const sf::SoundBuffer & audio);
    sf::Sound & addSound(const std::string& name, sf::Sound * soundPtr);

    sf::Sprite & getSpriteReference(const std::string& name);
    sf::Sound & getSoundReference(const std::string& name);
    sf::Shape & getShapeReference(const std::string& name);
    friend std::ostream& operator<< (std::ostream & os, const SceneManager & sceneManager) noexcept;
};

#endif //OOP_SCENEMANAGER_HPP