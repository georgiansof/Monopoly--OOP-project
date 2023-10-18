#include "../headers/SceneManager.hpp"

using namespace std;
using namespace sf;

SceneManager::~SceneManager() {
    for(auto &sprite : sprites)
        delete &sprite;

    for(auto &audioElement : audios)
        delete &audioElement;
}

void SceneManager::AddSprite(const char* name, const Texture & texture) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = Sprite(texture); /// TOFIX
    sprites.emplace(std::move(*pairPtr));
}

/*void SceneManager::AddSprite(const char* name, Sprite * const spritePtr) {
    auto pairPtr = new pair<string, Sprite>;
    pairPtr->first = string(name);
    pairPtr->second = *spritePtr;
    sprites.emplace(std::move(*pairPtr));
}*/

/*void SceneManager::AddAudio(const char* name, const SoundBuffer & audio) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = Sound(audio); /// TOFIX
    audios.emplace(std::move(*pairPtr));
}

void SceneManager::AddAudio(const char* name, Sound * const audioPtr) {
    auto pairPtr = new pair<string, Sound>;
    pairPtr->first = string(name);
    pairPtr->second = *audioPtr;
    audios.emplace(std::move(*pairPtr));
}*/

const Sprite & SceneManager::GetSprite(const char* name) const {
    string nameString(name);
    auto foundPair = sprites.find(nameString);
    if(foundPair != sprites.end())
        return foundPair->second;
    else
        throw std::runtime_error(string("Sprite ") + nameString + string(" not found!"));
}

/*Sound & SceneManager::GetAudio(const char* name) {
    string nameString(name);
    auto foundPair = audios.find(nameString);
    if(foundPair != audios.end())
        return foundPair->second;
    else
        throw std::runtime_error(string("Audio ") + nameString + string (" not found!"));
}*/

ostream& operator<< (ostream & os, const SceneManager & sceneManager) {
    os << "*** Scene Manager:\n";
    os << "Sprites:\n";
    for(auto& sprite : sceneManager.sprites)
        os << ' ' << sprite.first << '\n';
    os <<"-- \n";

    os << "\nAudios:\n";
    for(auto & audio : sceneManager.audios)
        os << ' ' << audio.first << '\n';
    os << " -- \n";

    os << '\n';
    return os;
}