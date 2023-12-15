//
// Created by je_gi on 2023-11-16.
//

#ifndef OOP_CUSTOMEXCEPTIONS_HPP
#define OOP_CUSTOMEXCEPTIONS_HPP

#include <exception>
#include <cstring>
#include <string>
#include "../../constants.hpp"
#include <typeinfo>

class PlayerCountException : public std::exception {
    std::string lastInsertedName;
public:
    PlayerCountException() = default;
    explicit PlayerCountException(std::string lastInsName) : lastInsertedName(std::move(lastInsName)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = "Cannot add one more player, max 8!\n";
        if(!lastInsertedName.empty())
            ret += std::string(" Insertion of player \"") + lastInsertedName + std::string("\" and after will be ignored !\n");

        return ret.c_str();
    }
};

class FatalException : public std::exception {
private:
    const int exit_code;
public:
    FatalException() = delete;
    explicit FatalException(int exit_code) : exit_code(exit_code) {}
    [[nodiscard]] int getExitCode() const noexcept {return exit_code;}
};

class NameTakenException : public FatalException {
public:
    explicit NameTakenException(int exit_code = NAME_TAKEN_ERROR_CODE) : FatalException(exit_code) {}
    [[nodiscard]] const char* what() const noexcept override {
        return "Someone already connected with this name!\n";
    }
};

class ConnectionTimedOutException : public FatalException {
public:
    explicit ConnectionTimedOutException(int exit_code = CONNECTION_TIMED_OUT_ERROR_CODE) : FatalException(exit_code) {}
    [[nodiscard]] const char* what() const noexcept override {
        return "Server did not respond. You might be trying to connect to a port that was already occupied !\n";
    }
};

class SwitchCaseNotCovered : public FatalException {
public:
    explicit SwitchCaseNotCovered(int exit_code = SWITCH_CASE_NOT_COVERED_ERROR_CODE) : FatalException(exit_code) {}
    [[nodiscard]] const char* what() const noexcept override {
        return "Encountered a fatal uncovered switch case.\n";
    }
};

class IndexOutOfBounds : public FatalException {
    int index;
    std::string arrayType;
public:
    IndexOutOfBounds(int index, std::string arrayType) : FatalException(INDEX_OUT_OF_BOUNDS_ERROR_CODE), index(index), arrayType(std::move(arrayType)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Index ") + std::to_string(index) + std::string("out of bounds in array of instances of ") + arrayType;
        return ret.c_str();
    }
};

class FileNotFoundException : public FatalException {
private:
    std::string path;
public:
    FileNotFoundException() = delete;
    explicit FileNotFoundException(const char* path) : FatalException(FILE_MISS_ERROR_CODE), path(path) {}
    explicit FileNotFoundException(std::string path) : FatalException(FILE_MISS_ERROR_CODE), path(std::move(path)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("File at ") + path + std::string(" not found or inaccesible !");
        return ret.c_str();
    }
};

class InsertionFailureException : public FatalException {
private:
    std::string name;
public:
    InsertionFailureException() = delete;
    explicit InsertionFailureException(std::string name) : FatalException(INSERTION_FAILURE_ERROR_CODE), name(std::move(name)) {}
    explicit InsertionFailureException(const char* name) : FatalException(INSERTION_FAILURE_ERROR_CODE), name(name) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Insertion of ") + std::string(name) + std::string(" did not take place.");
        return ret.c_str();
    }
};

class AssetNotFoundException : public FatalException {
protected:
    std::string assetName;
public:
    AssetNotFoundException() = delete;
    explicit AssetNotFoundException(const char *assetName, int error_code = ASSET_MISS_ERROR_CODE) : FatalException(error_code), assetName(assetName) {}
    explicit AssetNotFoundException(std::string assetName, int error_code = ASSET_MISS_ERROR_CODE) : FatalException(error_code), assetName(std::move(assetName)) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Asset with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
    }

};

class TextureNotFoundException : public AssetNotFoundException {
public:
    TextureNotFoundException() = delete;
    explicit TextureNotFoundException(const char *textureName) : AssetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    explicit TextureNotFoundException(const std::string & textureName) : AssetNotFoundException(textureName, TEXTURE_MISS_ERROR_CODE) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Texture with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
    }
};

class AudioNotFoundException : public AssetNotFoundException {
public:
    AudioNotFoundException() = delete;
    explicit AudioNotFoundException(const char *audioName) : AssetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    explicit AudioNotFoundException(const std::string & audioName) : AssetNotFoundException(audioName, AUDIO_MISS_ERROR_CODE) {}
    [[nodiscard]] const char* what() const noexcept override {
        static std::string ret = std::string("Audio with name ") + assetName + std::string(" not found during getter call.");
        return ret.c_str();
    }
};

class SceneAddFailureException : public FatalException {
public:
    enum Type {SPRITE, SOUND, SHAPE, GENERIC};
private:
    Type type;
    std::string objectName;
public:
    SceneAddFailureException() = delete;
    explicit SceneAddFailureException(std::string objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : FatalException(error_code), type(type), objectName(std::move(objectName)) {}
    explicit SceneAddFailureException(const char* objectName, Type type = GENERIC, int error_code = SCENE_ADD_FAIL_ERROR_CODE)
        : FatalException(error_code), type(type), objectName(objectName) {}

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

class SceneObjectNotFoundException : public FatalException {
public:
    enum Type {SPRITE, SOUND, SHAPE, GENERIC};
private:
    Type type;
    std::string objectName;
public:
    SceneObjectNotFoundException() = delete;
    explicit SceneObjectNotFoundException(std::string objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : FatalException(error_code), type(type), objectName(std::move(objectName)) {}
    explicit SceneObjectNotFoundException(const char* objectName, Type type = GENERIC, int error_code = SCENE_OBJECT_MISS_ERROR_CODE)
            : FatalException(error_code), type(type), objectName(objectName) {}

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

class InsufficientTilesException : public FatalException {
    int tilesSuccess;
public:
    InsufficientTilesException() = delete;
    explicit InsufficientTilesException(int tilesSuccess) : FatalException(INSUFFICIENT_TILES_ERROR_CODE), tilesSuccess(tilesSuccess) {}
    [[nodiscard]] const char * what() const noexcept override {
        static std::string ret = std::string("Not enough tiles managed to be registered! Successfully registered ") + std::to_string(tilesSuccess) + std::string(" !");
        return ret.c_str();
    }
};
#endif //OOP_CUSTOMEXCEPTIONS_HPP
