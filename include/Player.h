#include "GameElement.h"

#ifndef PLAYER_H
#define PLAYER_H

namespace game 
{
    class Player : public GameElement {
    
        static Player *getInstance(int x, int y, int w, int h);

        void tick();
        void draw() const;

        void mouseDown(const SDL_Event &);
        void mouseUp(const SDL_Event &);
        void keyUp(const SDL_Event &);
        void keyDown(const SDL_Event &);

        // Destruktor
        ~Player();

        protected:
        Player(int x, int y, int w, int h);
    }; 
   
}

#endif

