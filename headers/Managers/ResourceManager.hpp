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
    std::map<std::string, sf::Font> fonts;
    ResourceManager() = default;
    ~ResourceManager();
    friend Game;
public:
    [[maybe_unused]] const sf::Texture & addTexture(const std::string &name, const std::string & path);
    [[maybe_unused]] const sf::SoundBuffer & addAudio(const std::string& name, const std::string & path);
    [[maybe_unused]] const sf::Font & addFont(const std::string& name, const std::string & path);

    [[maybe_unused]] [[nodiscard]] const sf::Texture & getTexture(const std::string& name) const;
    [[maybe_unused]] [[nodiscard]] const sf::SoundBuffer & getAudio(const std::string& name) const;
    [[maybe_unused]] [[nodiscard]] const sf::Font & getFont(const std::string& name) const;
    friend std::ostream& operator<< (std::ostream& os, const ResourceManager & resourceManager) noexcept;
};

#endif //OOP_RESOURCEMANAGER_HPP
