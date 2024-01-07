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
    [[maybe_unused]] sf::Sprite & addSprite(const std::string & name, const sf::Texture & texture);
    [[maybe_unused]] sf::Sprite & addSprite(const std::string & name, const sf::Sprite * spritePtr);

    [[maybe_unused]] sf::Shape & addShape(const std::string & name, sf::Shape * shapePtr);

    [[maybe_unused]] sf::Sound & addSound(const std::string& name, const sf::SoundBuffer & audio);
    [[maybe_unused]] sf::Sound & addSound(const std::string& name, sf::Sound * soundPtr);

    [[maybe_unused]] sf::Sprite & getSpriteReference(const std::string& name);
    [[maybe_unused]] sf::Sound & getSoundReference(const std::string& name);
    [[maybe_unused]] sf::Shape & getShapeReference(const std::string& name);
    friend std::ostream& operator<< (std::ostream & os, const SceneManager & sceneManager) noexcept;
};

#endif //OOP_SCENEMANAGER_HPP
