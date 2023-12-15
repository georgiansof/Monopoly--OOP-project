//
// Created by je_gi on 2023-11-04.
//

#ifndef OOP_CONSTANTS_HPP
#define OOP_CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Globals {
    static sf::Font *defaultFont;
    static bool capsLock;
    static bool repeatKeyPressed;
public:
    static void setDefaultFont(const sf::Font *font) {
        defaultFont = const_cast<sf::Font*> (font);
    }
    static const sf::Font& getDefaultFont() {
        return *defaultFont;
    }
    static void switchCaps() {
        capsLock = !capsLock;
    }
    static bool isCapsLockPressed() {
        return capsLock;
    }
    static bool doesKeyPressedRepeat() {
        return repeatKeyPressed;
    }
    static void nullFunction() {}
};

#define BOARD_TILES_NUMBER 40
#define PLAYER_START_MONEY 1500

#define PROPERTY_BROWN 56,10,34
#define PROPERTY_LIGHT_BLUE 125,163,214
#define PROPERTY_PINK 228,28,104
#define PROPERTY_ORANGE 238,120,31
#define PROPERTY_RED 227,39,32
#define PROPERTY_YELLOW 253,229,0
#define PROPERTY_GREEN 6,154,89
#define PROPERTY_DARK_BLUE 19,69,143

#define AUDIO_MISS_ERROR_CODE (-3)
#define TEXTURE_MISS_ERROR_CODE (-2)
#define ASSET_MISS_ERROR_CODE (-6)
#define FILE_MISS_ERROR_CODE (-4)
#define INSERTION_FAILURE_ERROR_CODE (-5)
#define UNHANDLED_ERROR_CODE (-1)
#define SCENE_ADD_FAIL_ERROR_CODE (-7)
#define SCENE_OBJECT_MISS_ERROR_CODE (-8)
#define INSUFFICIENT_TILES_ERROR_CODE (-9)
#define INDEX_OUT_OF_BOUNDS_ERROR_CODE (-10)
#define SWITCH_CASE_NOT_COVERED_ERROR_CODE (-11)

#define DICE_SIZE_X 0.1
#define DICE_SIZE_Y 0.1
#define DICE1_POSITION_X 0.2
#define DICE1_POSITION_Y 0.65
#define DICE_GAP (DICE_SIZE_X + DICE_SIZE_X * 0.25)

#define DICE_SIZE sf::Vector2f(DICE_SIZE_X,DICE_SIZE_Y)
#define DICE1_POSITION sf::Vector2f(DICE1_POSITION_X, DICE1_POSITION_Y)
#define DICE2_POSITION sf::Vector2f(DICE1_POSITION_X + DICE_GAP, DICE1_POSITION_Y)

#define MONEY_FROM_START 200

#define OUTLINE_THICKNESS_DEFAULT 3.0f
#define FONTSIZE_DEFAULT 15

#define COLOR_PURPLE 75, 0, 110
#define COLOR_ORANGE 255, 165, 0

#define BACKSPACE_ASCII 8

#define DYNAMIC_PORT_RANGE_MIN 49152
#define DYNAMIC_PORT_RANGE_MAX 65535

#define ERROR_SHOWTIME 5.0f

#endif //OOP_CONSTANTS_HPP
