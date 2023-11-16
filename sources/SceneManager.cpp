#include "../headers/SceneManager.hpp"
#include "../headers/CustomExceptions.hpp"

using namespace std;
using namespace sf;

typedef sceneAddFailureException _safe;
typedef sceneObjectNotFoundException _sonf;

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
        throw sceneAddFailureException(name, _safe::SPRITE);
}

sf::Sprite & SceneManager::addSprite(const std::string & name, sf::Sprite * spritePtr) {

    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = name;
    pairPtr->second = *spritePtr;
    auto insertionResult = sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw sceneAddFailureException(name, _safe::SPRITE);
}

sf::Sprite & SceneManager::addSprite(const char* name, Sprite * const spritePtr) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = *spritePtr;
    auto insertionResult =sprites.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw sceneAddFailureException(name, _safe::SPRITE);
}

sf::Sound & SceneManager::addSound(const char* name, const SoundBuffer & audio) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second.setBuffer(audio);
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw sceneAddFailureException(name, _safe::SOUND);
}

sf::Sound & SceneManager::addSound(const char* name, Sound * const soundPtr) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = *soundPtr;
    auto insertionResult = sounds.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw sceneAddFailureException(name, _safe::SOUND);
}

Sprite & SceneManager::getSpriteReference(const char* name) {
    string nameString(name);
    auto foundPair = sprites.find(nameString);
    if(foundPair != sprites.end())
        return foundPair->second;
    else
        throw sceneObjectNotFoundException(name, _sonf::SPRITE);
}

Sound & SceneManager::getSoundReference(const char* name) {
    string nameString(name);
    auto foundPair = sounds.find(nameString);
    if(foundPair != sounds.end())
        return foundPair->second;
    else
        throw sceneObjectNotFoundException(name, _sonf::SOUND);
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

sf::Shape & SceneManager::addShape(const char* name, sf::Shape * shapePtr) {
    return this->addShape(string(name), shapePtr);
}
sf::Shape & SceneManager::addShape(const std::string & name, sf::Shape * shapePtr) {
    auto pairPtr = new pair<string, Shape*>;
    pairPtr->first = name;
    pairPtr->second = shapePtr;
    auto insertionResult = shapePointers.emplace(std::move(*pairPtr));
    if(insertionResult.second)
        return *insertionResult.first->second;
    else
        throw sceneAddFailureException(name, _safe::SHAPE);
}

sf::Shape & SceneManager::getShapeReference(const char* name) {
    string nameString(name);
    auto foundPair = shapePointers.find(nameString);
    if(foundPair != shapePointers.end())
        return *foundPair->second;
    else
        throw sceneObjectNotFoundException(name, _sonf::SHAPE);
}