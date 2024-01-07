#include "../../headers/Managers/ResourceManager.hpp"
#include "../../headers/DataStructures/CustomExceptions.hpp"

using namespace std;
using namespace sf;

ResourceManager::~ResourceManager() {
    for(auto &texture : textures)
        delete &texture;
    textures.clear();

    for(auto &audio : audios)
        delete &audio;
    audios.clear();

    for(auto &font : fonts)
        delete &font;
    fonts.clear();
}

[[maybe_unused]] const Texture & ResourceManager::addTexture(const std::string &name, const string & path) {
    auto textureMapPair = new pair<string, Texture>;
    textureMapPair->first = string(name);
    if(!textureMapPair->second.loadFromFile(path))
        throw FileNotFoundException(path);
    auto insertionResult = textures.emplace(std::move(*textureMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw InsertionFailureException(name);
}

[[maybe_unused]] const SoundBuffer & ResourceManager::addAudio(const string& name, const string & path) {
    auto audioMapPair = new pair<string, SoundBuffer>;
    audioMapPair->first = string(name);
    if(!audioMapPair->second.loadFromFile(path))
        throw FileNotFoundException(path);
    auto insertionResult = audios.emplace(std::move(*audioMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw InsertionFailureException(name);

}

[[maybe_unused]] const Texture & ResourceManager::getTexture(const std::string &name) const {
    auto searchedTextureIterator = textures.find(name);
    if (searchedTextureIterator != textures.end())
        return searchedTextureIterator->second;
    else
        throw TextureNotFoundException(name);
}

[[maybe_unused]] const SoundBuffer & ResourceManager::getAudio(const std::string& name) const {
    auto searchedAudioIterator = audios.find(string(name));
    if(searchedAudioIterator != audios.end())
        return searchedAudioIterator->second;
    else
        throw AudioNotFoundException(name);
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

[[maybe_unused]] const sf::Font & ResourceManager::addFont(const std::string& name, const std::string & path) {
    auto fontMapPair = new pair<string, Font>;
    fontMapPair->first = string(name);
    if(!fontMapPair->second.loadFromFile(path))
        throw FileNotFoundException(path);
    auto insertionResult = fonts.emplace(std::move(*fontMapPair));
    if(insertionResult.second)
        return insertionResult.first->second;
    else
        throw InsertionFailureException(name);
}

[[maybe_unused]] const Font & ResourceManager::getFont(const std::string& name) const {
    auto searchedFontIterator = fonts.find(string(name));
    if (searchedFontIterator != fonts.end())
        return searchedFontIterator->second;
    else
        throw AssetNotFoundException(name);
}