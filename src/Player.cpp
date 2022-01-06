#include "Player.h"
#include "System.h"
#include <iostream>

namespace game
{
    Player *Player::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        return new Player(x, y, w, h, imgSrc);
    }

    // Konstruktor
    Player::Player(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
    
    void Player::draw() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }

    void Player::moveRight(){
        rect.x += 20;
        std::cout << rect.x << std::endl;
        
    }

    void Player::moveLeft(){
        rect.x -= 20;
        std::cout << rect.x << std::endl;

    }

    Player::~Player() {
        SDL_DestroyTexture(texture);
    }
    
}