#include "GameElement.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#ifndef PLAYER_H
#define PLAYER_H

namespace gameEngine
{
    class Player : public GameElement
    {
    public:
        static std::shared_ptr<Player>getInstance(int x, int y, int w, int h, const char *imgSrc);

        Player(int x, int y, int w, int h, const char *imgSrc);

        void tick(){};

        void moveRight();
        void moveLeft();

    };

}

extern const int playerMinX, playerMaxX;

#endif