/// global includes
#include <iostream>

/**--------------------------------------------------**/

#include "headers/Game.hpp"

/**--------------------------------------------------**/

Game* Game::instance = nullptr;

using namespace std;

#include <cstring>

class tema {
private:
    int a;
    char *c;
public:
    tema() {
        a = 5;
        c = new char[10];
        strcpy(c, "abcdef");
    }
    tema& operator= (const tema & obj) {
        if(this == &obj)
            return *this;
        this->a = obj.a;
        this->c = new char[10];
        strcpy(c, obj.c);
        return *this;
    }
    tema(const tema & obj) {
        this->a = obj.a;
        this->c = new char[10];
        strcpy(c, obj.c);
    }
    ~tema() {
        delete[] c;
    }
    void setString(const char *str) {
        strcpy(c, str);
    }
    friend ostream& operator<< (ostream& os, const tema& tema) {
        os << tema.c << '\n';
        return os;
    }

};

int main() { /// TOFIX LOCAL DLL ERROR, GITHUB WORKING

    tema a;
    tema b = a;
    a.setString("0bcdef");
    tema c;
    c = a;
    cout << a << b << c;

    Game *game = Game::getInstancePtr();
    ResourceManager *resourceManager = game->getResourceManagerPtr();
    SceneManager *sceneManager = game->getSceneManagerPtr();
    game->initWindow();
    /***************************/
    sceneManager->AddSprite("board", resourceManager->AddTexture("board", "../textures/board.png"));
    game->draw(sceneManager->GetSprite("board"));

    //sceneManager->AddAudio("water", resourceManager->AddSound("water", "../sounds/water.ogg"));
    //sceneManager->GetAudio("water").play();

    cout<<*game;
    cout<<*resourceManager;
    cout<<*sceneManager;
    /***************************/
    game->loop();
    Game::clearInstance();
    return 0;
}
