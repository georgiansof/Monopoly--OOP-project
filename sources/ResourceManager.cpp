#include "../headers/ResourceManager.hpp"
#include "../headers/CustomExceptions.hpp"

using namespace std;
using namespace sf;

ResourceManager::~ResourceManager() {
    for(auto &texture : textures)
        delete &texture;
    textures.clear();

    for(auto &audio : audios)
        delete &audio;
    audios.clear();
}

const Texture & ResourceManager::addTexture(const char* name, const char* path) {
    return this->addTexture(name, string(path));
}

const SoundBuffer & ResourceManager::addAudio(const char* name, const char* path) {
    return this->addAudio(name, string(path));
}

const Texture & ResourceManager::addTexture(const char* name, const string & path) {
    auto textureMapPair = new pair<string, Texture>;
    textureMapPair->first = string(name);
    if(!textureMapPair->second.loadFromFile(path))
        throw fileNotFoundException(path);
    auto insertionResult = textures.emplace(std::move(*textureMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw insertionFailureException(name);
}

const SoundBuffer & ResourceManager::addAudio(const char* name, const string & path) {
    auto audioMapPair = new pair<string, SoundBuffer>;
    audioMapPair->first = string(name);
    if(!audioMapPair->second.loadFromFile(path))
        throw fileNotFoundException(path);
    auto insertionResult = audios.emplace(std::move(*audioMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw insertionFailureException(name);

}

const Texture & ResourceManager::getTexture(const char* name) const {
    auto searchedTextureIterator = textures.find(string(name));
    if (searchedTextureIterator != textures.end())
        return searchedTextureIterator->second;
    else
        throw textureNotFoundException(name);
}

const SoundBuffer & ResourceManager::getAudio(const char* name) const {
    auto searchedAudioIterator = audios.find(string(name));
    if(searchedAudioIterator != audios.end())
        return searchedAudioIterator->second;
    else
        throw audioNotFoundException(name);
}

ostream& operator<< (ostream & os, const ResourceManager & resourceManager) noexcept {
    os << "*** Resource Manager:\n";
    os << "Textures:\n";
    for(auto& texture : resourceManager.textures)
        os << ' ' << texture.first << '\n';
    os <<"-- \n";

    os << "\nAudios:\n";
    for(auto & audio : resourceManager.audios)
        os << ' ' << audio.first << '\n';
    os << " -- \n";

    os << '\n';
    return os;
}