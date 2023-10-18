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
    std::map<std::string, sf::Sound> audios;
    SceneManager() = default;
    ~SceneManager();
    friend Game;
public:
    void AddSprite(const char* name, const sf::Texture & texture);
    void AddSprite(const char* name, sf::Sprite *spritePtr);
    void AddAudio(const char* name, const sf::SoundBuffer & audio);
    void AddAudio(const char* name, sf::Sound *audioPtr);
    const sf::Sprite & GetSprite(const char* name) const;
    const sf::Sound & GetAudio(const char* name) const;
};

#endif //OOP_SCENEMANAGER_HPP
