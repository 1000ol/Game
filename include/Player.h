/*#include "GameElement.h"

#ifndef PLAYER_H
#define PLAYER_H

using namespace gameEngine;

class Player : public gameEngine::GameElement
{
public:
    static std::shared_ptr<Player> getInstance(int x, int y, int w, int h, const char *imgSrc);

    Player(int x, int y, int w, int h, const char *imgSrc);

    void tick();

    void keyDown(const SDL_Event &);

    void moveRight();
    void moveLeft();

    ~Player();

    void increaseRemovedTargets()
    {
        targetsRemoved++;
    };

    int getTargetsRemoved()
    {
        return targetsRemoved;
    }

private:
    int targetsRemoved = 0;
};

extern const int playerMinX, playerMaxX;

#endif
*/
/*
class Player : public gameEngine::GameElement
{
public:
    static std::shared_ptr<Player> getInstance(int x, int y, int w, int h, const char *imgSrc){
        return std::make_shared<Player>(x, y, w, h, imgSrc);
    };

    Player(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc){
        setIsUserControlled();
    SDL_Surface *surf = IMG_Load(getImageSource());
    setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
    SDL_FreeSurface(surf);
    }

    void keyDown(const SDL_Event &){
        switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        moveLeft();
        break;
    case SDLK_RIGHT:
        moveRight();
        break;
    }
    };

    void moveRight() {
        int x = getRect().x;
    if (x > playerMaxX)
        setCoordinateX(playerMaxX);
    else
        setCoordinateX(x + 30);
    }
    void moveLeft() {
            int x = getRect().x;
    if (x < playerMinX)
        setCoordinateX(playerMinX);
    else
        setCoordinateX(x - 30);
    };

    void increaseRemovedTargets()
    {
        targetsRemoved++;
    };

    int getTargetsRemoved()
    {
        return targetsRemoved;
    }

private:
    int targetsRemoved = 0;
};

extern const int playerMinX, playerMaxX;

#endif


*/