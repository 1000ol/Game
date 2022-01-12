#include "GameElement.h"

#ifndef PLAYER_H
#define PLAYER_H

using namespace gameEngine;

class Player : public gameEngine::GameElement
{
public:
    static std::shared_ptr<Player>getInstance(int x, int y, int w, int h, int miniX, int maxiX, const char *imgSrc);

    Player(int x, int y, int w, int h, int minX, int maxX, const char *imgSrc);

    void keyDown(const SDL_Event &);

    void moveRight();
    void moveLeft();

private: 
    int minX, maxX;

};

#endif