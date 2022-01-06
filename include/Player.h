#include "GameElement.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#ifndef PLAYER_H
#define PLAYER_H

namespace game 
{
    class Player : public GameElement 
    {
    public:
        static Player *getInstance(int x, int y, int w, int h, const char *imgSrc);

        void tick(){};
        void draw() const;

        /*
        void mouseDown(const SDL_Event &) {};
        void mouseUp(const SDL_Event &){};
        */
        void moveRight();
        void moveLeft();

        void perform(Player *){};

        // Destruktor
        ~Player();

    protected:
        Player(int x, int y, int w, int h, const char *imgSrc);

    }; 
   
}


#endif

