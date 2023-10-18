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
    std::map<std::string, sf::SoundBuffer> sounds;
    ResourceManager() = default;
    ~ResourceManager();
    friend Game;
public:
    void AddTexture(const char* name, const std::string & path);
    void AddSound(const char* name, const std::string & path);
    const sf::Texture & getTexture(const char* name) const;
    const sf::SoundBuffer & getSound(const char* name) const;
};

#endif //OOP_RESOURCEMANAGER_HPP
