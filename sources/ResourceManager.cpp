#include "../headers/ResourceManager.hpp"

using namespace std;
using namespace sf;

void ResourceManager::AddTexture(const char* name, const string & path) {
    auto textureMapPair = new pair<string, Texture>;
    textureMapPair->first = string(name);
    if(!textureMapPair->second.loadFromFile(path))
        throw std::runtime_error(string("File at ") + path + string(" not found or nonaccessible !"));
    textures.emplace(std::move(*textureMapPair));
}

void ResourceManager::AddSound(const char* name, const string & path) {
    auto soundMapPair = new pair<string, SoundBuffer>;
    soundMapPair->first = string(name);
    if(!soundMapPair->second.loadFromFile(path))
        throw std::runtime_error(string("File at ") + path + " not found or nonaccessible !");
    sounds.emplace(std::move(*soundMapPair));
}

const Texture & ResourceManager::getTexture(const char* name) const {
    auto searchedTextureIterator = textures.find(string(name));
    if (searchedTextureIterator != textures.end())
        return searchedTextureIterator->second;
    else
        throw std::runtime_error(string("Texture #") + string(name) + string("# not found during getter call"));
}

const SoundBuffer & ResourceManager::getSound(const char* name) const {
    auto searchedSoundIterator = sounds.find(string(name));
    if(searchedSoundIterator != sounds.end())
        return searchedSoundIterator->second;
    else
        throw std::runtime_error(string("Sound #") + string(name) + string("# not found during getter call"));
}

ResourceManager::~ResourceManager() {
    for(auto &texture : textures)
        delete &texture;
    textures.clear();

    for(auto &sound : sounds)
        delete &sound;
    sounds.clear();
}