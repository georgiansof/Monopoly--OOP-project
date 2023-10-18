#include "../headers/SceneManager.hpp"

using namespace std;
using namespace sf;

void SceneManager::AddSprite(const char* name, const Texture & texture) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = Sprite(texture);
    sprites.emplace(std::move(*pairPtr));
}

void SceneManager::AddSprite(const char* name, Sprite *spritePtr) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = *spritePtr;
    sprites.emplace(std::move(*pairPtr));
}

void SceneManager::AddAudio(const char* name, const SoundBuffer & audio) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = Sound(audio);
    audios.emplace(std::move(*pairPtr));
}

void SceneManager::AddAudio(const char* name, Sound *audioPtr) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = *audioPtr;
    audios.emplace(std::move(*pairPtr));
}

const Sprite & SceneManager::GetSprite(const char* name) const {
    string nameString(name);
    auto foundPair = sprites.find(nameString);
    if(foundPair != sprites.end())
        return foundPair->second;
    else
        throw(string("Sprite ") + nameString + string(" not found!"));
}

const Sound & SceneManager::GetAudio(const char* name) const {
    string nameString(name);
    auto foundPair = audios.find(nameString);
    if(foundPair != audios.end())
        return foundPair->second;
    else
        throw(string("Audio ") + nameString + string (" not found!"));
}

SceneManager::~SceneManager() {
    for(auto &sprite : sprites)
        delete &sprite;

    for(auto &audioElement : audios)
        delete &audioElement;
}