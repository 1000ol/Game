#include "Player.h"
#include "System.h"
#include <iostream>

namespace gameEngine
{
    // Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
   std::shared_ptr<Player> Player::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        return std::make_shared<Player>(x, y, w, h, imgSrc);
    }

    // Konstruktor
    Player::Player(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
        SDL_FreeSurface(surf);
    }

    void Player::moveRight()
    {
        if (rect.x > playerMaxX)
            rect.x = playerMaxX;
        else
            rect.x += 30;
    }

    void Player::moveLeft()
    {
        if (rect.x < playerMinX)
            rect.x = playerMinX;
        else
            rect.x -= 30;
    }

}