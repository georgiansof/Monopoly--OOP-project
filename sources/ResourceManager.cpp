#include "../headers/ResourceManager.hpp"

using namespace std;
using namespace sf;

ResourceManager::~ResourceManager() {
    for(auto &texture : textures)
        delete &texture;
    textures.clear();

    for(auto &sound : sounds)
        delete &sound;
    sounds.clear();
}

const Texture & ResourceManager::AddTexture(const char* name, const char* path) {
    return this->AddTexture(name, string(path));
}

/*const SoundBuffer & ResourceManager::AddSound(const char* name, const char* path) {
    return this->AddSound(name, string(path));
}*/

const Texture & ResourceManager::AddTexture(const char* name, const string & path) {
    auto textureMapPair = new pair<string, Texture>;
    textureMapPair->first = string(name);
    if(!textureMapPair->second.loadFromFile(path))
        throw std::runtime_error(string("Fatal error: File at ") + path + string(" not found or nonaccessible !"));
    auto insertionResult = textures.emplace(std::move(*textureMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Insertion of " + string(path) + " did not take place.");
}

/*const SoundBuffer & ResourceManager::AddSound(const char* name, const string & path) {
    auto soundMapPair = new pair<string, SoundBuffer>;
    soundMapPair->first = string(name);
    if(!soundMapPair->second.loadFromFile(path))
        throw std::runtime_error(string("Fatal error: File at ") + path + " not found or nonaccessible !");
    auto insertionResult = sounds.emplace(std::move(*soundMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw std::runtime_error("Fatal error: Insertion of " + string(path) + " did not take place.");

}*/

const Texture & ResourceManager::getTexture(const char* name) const {
    auto searchedTextureIterator = textures.find(string(name));
    if (searchedTextureIterator != textures.end())
        return searchedTextureIterator->second;
    else
        throw std::runtime_error(string("Texture #") + string(name) + string("# not found during getter call"));
}

/*const SoundBuffer & ResourceManager::getSound(const char* name) const {
    auto searchedSoundIterator = sounds.find(string(name));
    if(searchedSoundIterator != sounds.end())
        return searchedSoundIterator->second;
    else
        throw std::runtime_error(string("Sound #") + string(name) + string("# not found during getter call"));
}*/

ostream& operator<< (ostream & os, const ResourceManager & resourceManager) {
    os << "*** Resource Manager:\n";
    os << "Textures:\n";
    for(auto& texture : resourceManager.textures)
        os << ' ' << texture.first << '\n';
    os <<"-- \n";

    os << "\nSounds:\n";
    for(auto & sound : resourceManager.sounds)
        os << ' ' << sound.first << '\n';
    os << " -- \n";

    os << '\n';
    return os;
}