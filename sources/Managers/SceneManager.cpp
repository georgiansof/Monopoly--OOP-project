#include "../../headers/Managers/SceneManager.hpp"
#include "../../headers/DataStructures/CustomExceptions.hpp"

using namespace std;
using namespace sf;

typedef SceneAddFailureException _safe;
typedef SceneObjectNotFoundException _sonf;

SceneManager::~SceneManager() {
    for(auto &sprite : sprites)
        delete &sprite;
    sprites.clear();
    for(auto &soundElement : sounds)
        delete &soundElement;
    sounds.clear();
    for(auto &shapePair : shapePointers)
        delete shapePair.second;
    shapePointers.clear();
}

sf::Sprite & SceneManager::addSprite(const string& name, const Texture & texture) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second.setTexture(texture);
    auto insertionResult =sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw SceneAddFailureException(name, _safe::SPRITE);
}

sf::Sprite & SceneManager::addSprite(const std::string & name, sf::Sprite * spritePtr) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = name;
    pairPtr->second = *spritePtr;
    auto insertionResult = sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw SceneAddFailureException(name, _safe::SPRITE);
}

sf::Sound & SceneManager::addSound(const string& name, const SoundBuffer & audio) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second.setBuffer(audio);
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw SceneAddFailureException(name, _safe::SOUND);
}

sf::Sound & SceneManager::addSound(const string& name, Sound * const soundPtr) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = *soundPtr;
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw SceneAddFailureException(name, _safe::SOUND);
}

Sprite & SceneManager::getSpriteReference(const string& name) {
    auto foundPair = sprites.find(name);
    if(foundPair != sprites.end())
        return foundPair->second;
    else
        throw SceneObjectNotFoundException(name, _sonf::SPRITE);
}

Sound & SceneManager::getSoundReference(const string& name) {
    auto foundPair = sounds.find(name);
    if(foundPair != sounds.end())
        return foundPair->second;
    else
        throw SceneObjectNotFoundException(name, _sonf::SOUND);
}

ostream& operator<< (ostream & os, const SceneManager & sceneManager) noexcept {
    os << "*** Scene Manager:\n";
    os << "Sprites:\n";
    for(auto& sprite : sceneManager.sprites)
        os << ' ' << sprite.first << '\n';
    os <<"-- \n";

    os << "Shapes:\n";
    for(auto& shape : sceneManager.shapePointers)
        os << ' ' << shape.first << '\n';
    os <<"-- \n";

    os << "\nSounds:\n";
    for(auto & sound : sceneManager.sounds)
        os << ' ' << sound.first << '\n';
    os << " -- \n";

    os << '\n';
    return os;
}

sf::Shape & SceneManager::addShape(const std::string & name, sf::Shape * shapePtr) {
    auto insertionResult = shapePointers.emplace(name,shapePtr);
    if(insertionResult.second)
        return *insertionResult.first->second;
    else
        throw SceneAddFailureException(name, _safe::SHAPE);
}

sf::Shape & SceneManager::getShapeReference(const string& name) {
    auto foundPair = shapePointers.find(name);
    if(foundPair != shapePointers.end())
        return *foundPair->second;
    else
        throw SceneObjectNotFoundException(name, _sonf::SHAPE);
}