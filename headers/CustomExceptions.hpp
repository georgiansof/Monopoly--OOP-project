//
// Created by je_gi on 2023-11-16.
//

#ifndef OOP_CUSTOMEXCEPTIONS_HPP
#define OOP_CUSTOMEXCEPTIONS_HPP

#include <exception>
#include <cstring>
#include <string>
#include "../constants.hpp"

class playerCountException : public std::exception {
    std::string lastInsertedName;
public:
    playerCountException() = default;
    playerCountException(std::string lastInsName) : lastInsertedName(lastInsName) {}
    const char* what() const noexcept override {
        std::string ret = "Cannot add one more player, max 8!\n";
        if(!lastInsertedName.empty())
            ret += std::string(" Insertion of player \"") + lastInsertedName + std::string("\" and after will be ignored !\n");
        return ret.c_str();
    }
};

class fatalException : public std::exception {
private:
    const int exit_code;
public:
    fatalException() = delete;
    fatalException(int exit_code) : exit_code(exit_code) {}
    int getExitCode() const noexcept {return exit_code;}
};

class fileNotFoundException : public fatalException {
private:
    std::string path;
public:
    fileNotFoundException() = delete;
    fileNotFoundException(const char* path) : fatalException(FILE_MISS_ERROR_CODE), path(path) {}
    fileNotFoundException(const std::string &path) : fatalException(FILE_MISS_ERROR_CODE), path(path) {}
    const char* what() const noexcept override {
        return (std::string("File at ") + path + std::string(" not found or inaccesible !")).c_str();
    }
};

class insertionFailureException : public fatalException {
private:
    std::string name;
public:
    insertionFailureException() = delete;
    insertionFailureException(std::string name) : fatalException(INSERTION_FAILURE_ERROR_CODE), name(name) {}
    insertionFailureException(const char* name) : fatalException(INSERTION_FAILURE_ERROR_CODE), name(name) {}
    const char* what() const noexcept override {
        return (std::string("Insertion of ") + std::string(name) + std::string(" did not take place.")).c_str();
    }
};

class assetNotFoundException : public fatalException {
protected:
    std::string assetName;
public:
    assetNotFoundException() = delete;
    assetNotFoundException(const char *assetName, int error_code = ASSET_MISS_ERROR_CODE) : fatalException(error_code), assetName(assetName) {}
    assetNotFoundException(const std::string &assetName, int error_code = ASSET_MISS_ERROR_CODE) : fatalException(error_code), assetName(assetName) {}
    const char* what() const noexcept override {
        return (std::string("Asset with name ") + assetName + std::string(" not found during getter call.")).c_str();
    }

};

class textureNotFoundException : public assetNotFoundException {
public:
    textureNotFoundException() = delete;
    textureNotFoundException(const char *textureName) : assetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    textureNotFoundException(const std::string & textureName) : assetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    const char* what() const noexcept override {
        return (std::string("Texture with name ") + assetName + std::string(" not found during getter call.")).c_str();
    }
};

class audioNotFoundException : public assetNotFoundException {
public:
    audioNotFoundException() = delete;
    audioNotFoundException(const char *audioName) : assetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    audioNotFoundException(const std::string & audioName) : assetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    const char* what() const noexcept override {
        return (std::string("Audio with name ") + assetName + std::string(" not found during getter call.")).c_str();
    }
};

class sceneAddFailureException : public fatalException {
public:
    enum Type {SPRITE, SOUND, SHAPE, GENERIC};
private:
    Type type;
    std::string objectName;
public:
    sceneAddFailureException() = delete;
    sceneAddFailureException(std::string objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : fatalException(error_code), type(type), objectName(objectName) {}
    sceneAddFailureException(const char* objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : fatalException(error_code), type(type), objectName(objectName) {}

    const char* what() const noexcept override {
        std::string exception_message;
        switch(type) {
            case SPRITE:
                exception_message = "Sprite";
                break;
            case SOUND:
                exception_message = "Sound";
                break;
            case SHAPE:
                exception_message = "Shape";
                break;
            default:
                exception_message = "Scene object ";
        }
        exception_message += std::string(" with name ") + objectName + std::string("failed Scene Manager insertion");
        return exception_message.c_str();
    }
};

class sceneObjectNotFoundException : public fatalException {
public:
    enum Type {SPRITE, SOUND, SHAPE, GENERIC};
private:
    Type type;
    std::string objectName;
public:
    sceneObjectNotFoundException() = delete;
    sceneObjectNotFoundException(std::string objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : fatalException(error_code), type(type), objectName(objectName) {}
    sceneObjectNotFoundException(const char* objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : fatalException(error_code), type(type), objectName(objectName) {}

    const char* what() const noexcept override {
        std::string exception_message;
        switch(type) {
            case SPRITE:
                exception_message = "Sprite";
                break;
            case SOUND:
                exception_message = "Sound";
                break;
            case SHAPE:
                exception_message = "Shape";
                break;
            default:
                exception_message = "Scene object ";
        }
        exception_message += std::string(" with name ") + objectName + std::string("not found during getter call.");
        return exception_message.c_str();
    }
};

class insufficientTilesException : public fatalException {
    int tilesSuccess;
public:
    insufficientTilesException() = delete;
    insufficientTilesException(int tilesSuccess) : fatalException(INSUFFICIENT_TILES_ERROR_CODE), tilesSuccess(tilesSuccess) {}
    const char * what() const noexcept override {
        return (std::string("Not enough tiles managed to be registered! Successfully registered ") + std::to_string(tilesSuccess) + std::string(" !")).c_str();
    }
};
#endif //OOP_CUSTOMEXCEPTIONS_HPP
