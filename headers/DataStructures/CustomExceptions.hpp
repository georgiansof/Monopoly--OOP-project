//
// Created by je_gi on 2023-11-16.
//

#ifndef OOP_CUSTOMEXCEPTIONS_HPP
#define OOP_CUSTOMEXCEPTIONS_HPP

#include <exception>
#include <cstring>
#include <string>
#include "../../constants.hpp"

class playerCountException : public std::exception {
    std::string lastInsertedName;
public:
    playerCountException() = default;
    explicit playerCountException(std::string lastInsName) : lastInsertedName(std::move(lastInsName)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = "Cannot add one more player, max 8!\n";
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
    explicit fatalException(int exit_code) : exit_code(exit_code) {}
    [[nodiscard]] int getExitCode() const noexcept {return exit_code;}
};

class fileNotFoundException : public fatalException {
private:
    std::string path;
public:
    fileNotFoundException() = delete;
    explicit fileNotFoundException(const char* path) : fatalException(FILE_MISS_ERROR_CODE), path(path) {}
    explicit fileNotFoundException(std::string path) : fatalException(FILE_MISS_ERROR_CODE), path(std::move(path)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("File at ") + path + std::string(" not found or inaccesible !");
        return ret.c_str();
    }
};

class insertionFailureException : public fatalException {
private:
    std::string name;
public:
    insertionFailureException() = delete;
    explicit insertionFailureException(std::string name) : fatalException(INSERTION_FAILURE_ERROR_CODE), name(std::move(name)) {}
    explicit insertionFailureException(const char* name) : fatalException(INSERTION_FAILURE_ERROR_CODE), name(name) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Insertion of ") + std::string(name) + std::string(" did not take place.");
        return ret.c_str();
    }
};

class assetNotFoundException : public fatalException {
protected:
    std::string assetName;
public:
    assetNotFoundException() = delete;
    explicit assetNotFoundException(const char *assetName, int error_code = ASSET_MISS_ERROR_CODE) : fatalException(error_code), assetName(assetName) {}
    explicit assetNotFoundException(std::string assetName, int error_code = ASSET_MISS_ERROR_CODE) : fatalException(error_code), assetName(std::move(assetName)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Asset with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
    }

};

class textureNotFoundException : public assetNotFoundException {
public:
    textureNotFoundException() = delete;
    explicit textureNotFoundException(const char *textureName) : assetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    explicit textureNotFoundException(const std::string & textureName) : assetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Texture with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
    }
};

class audioNotFoundException : public assetNotFoundException {
public:
    audioNotFoundException() = delete;
    explicit audioNotFoundException(const char *audioName) : assetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    explicit audioNotFoundException(const std::string & audioName) : assetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Audio with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
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
    explicit sceneAddFailureException(std::string objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : fatalException(error_code), type(type), objectName(std::move(objectName)) {}
    explicit sceneAddFailureException(const char* objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : fatalException(error_code), type(type), objectName(objectName) {}

    [[nodiscard]] const char* what() const noexcept override {
        static std::string exception_message;
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
    explicit sceneObjectNotFoundException(std::string objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : fatalException(error_code), type(type), objectName(std::move(objectName)) {}
    explicit sceneObjectNotFoundException(const char* objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : fatalException(error_code), type(type), objectName(objectName) {}

    [[nodiscard]] const char* what() const noexcept override {
        static std::string exception_message;
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
    explicit insufficientTilesException(int tilesSuccess) : fatalException(INSUFFICIENT_TILES_ERROR_CODE), tilesSuccess(tilesSuccess) {}
    [[nodiscard]] const char * what() const noexcept override {
        static std::string ret = std::string("Not enough tiles managed to be registered! Successfully registered ") + std::to_string(tilesSuccess) + std::string(" !");
        return ret.c_str();
    }
};
#endif //OOP_CUSTOMEXCEPTIONS_HPP
