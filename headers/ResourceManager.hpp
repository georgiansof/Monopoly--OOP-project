#ifndef OOP_RESOURCEMANAGER_HPP
#define OOP_RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <map>
#include <string>

class Game;

class ResourceManager {
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> audios;
    ResourceManager() = default;
    ~ResourceManager();
    friend Game;
public:
    const sf::Texture & addTexture(const char* name, const std::string & path);
    const sf::SoundBuffer & addAudio(const char* name, const std::string & path);
    const sf::Texture & addTexture(const char* name, const char* path);
    const sf::SoundBuffer & addAudio(const char* name, const char* path);
    const sf::Texture & getTexture(const char* name) const;
    const sf::SoundBuffer & getAudio(const char* name) const;
    friend std::ostream& operator<< (std::ostream& os, const ResourceManager & resourceManager) noexcept;
};

#endif //OOP_RESOURCEMANAGER_HPP
