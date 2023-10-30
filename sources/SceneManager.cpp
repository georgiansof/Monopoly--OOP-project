#include "../headers/SceneManager.hpp"

using namespace std;
using namespace sf;

SceneManager::~SceneManager() {
    for(auto &sprite : sprites)
        delete &sprite;
    sprites.clear();
    for(auto &soundElement : sounds)
        delete &soundElement;
    sounds.clear();
}

sf::Sprite & SceneManager::addSprite(const char* name, const Texture & texture) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second.setTexture(texture);
    auto insertionResult =sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Scene adding of sprite " + string(name) + " did not take place.");
}

sf::Sprite & SceneManager::addSprite(const char* name, Sprite * const spritePtr) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = *spritePtr;
    auto insertionResult =sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Scene adding of sprite " + string(name) + " did not take place.");
}

sf::Sound & SceneManager::addSound(const char* name, const SoundBuffer & audio) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second.setBuffer(audio);
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Scene adding of sound " + string(name) + " did not take place.");
}

sf::Sound & SceneManager::addSound(const char* name, Sound * const soundPtr) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = *soundPtr;
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Scene adding of sound " + string(name) + " did not take place.");
}

Sprite & SceneManager::getSpriteReference(const char* name) {
    string nameString(name);
    auto foundPair = sprites.find(nameString);
    if(foundPair != sprites.end())
        return foundPair->second;
    else
        throw std::runtime_error(string("Sprite ") + nameString + string(" not found!"));
}

Sound & SceneManager::getSoundReference(const char* name) {
    string nameString(name);
    auto foundPair = sounds.find(nameString);
    if(foundPair != sounds.end())
        return foundPair->second;
    else
        throw std::runtime_error(string("Sound ") + nameString + string (" not found!"));
}

ostream& operator<< (ostream & os, const SceneManager & sceneManager) noexcept {
    os << "*** Scene Manager:\n";
    os << "Sprites:\n";
    for(auto& sprite : sceneManager.sprites)
        os << ' ' << sprite.first << '\n';
    os <<"-- \n";

    os << "\nSounds:\n";
    for(auto & sound : sceneManager.sounds)
        os << ' ' << sound.first << '\n';
    os << " -- \n";

    os << '\n';
    return os;
}