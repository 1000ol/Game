/*#include "Player.h"
#include "System.h"

#include <iostream>

// Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
std::shared_ptr<Player> Player::getInstance(int x, int y, int w, int h, const char *imgSrc)
{
    return std::make_shared<Player>(x, y, w, h, imgSrc);
}

// Konstruktor
Player::Player(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
{
    setIsUserControlled();
    SDL_Surface *surf = IMG_Load(getImageSource());
    setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
    SDL_FreeSurface(surf);
}

void Player::tick()
{
}

void Player::keyDown(const SDL_Event &e)
{
    switch (e.key.keysym.sym)
    {
    case SDLK_LEFT:
        moveLeft();
        break;
    case SDLK_RIGHT:
        moveRight();
        break;
    }
}

void Player::moveRight()
{
    int x = getRect().x;
    if (x > playerMaxX)
        setCoordinateX(playerMaxX);
    else
        setCoordinateX(x + 30);
}

void Player::moveLeft()
{
    int x = getRect().x;
    if (x < playerMinX)
        setCoordinateX(playerMinX);
    else
        setCoordinateX(x - 30);
}

Player::~Player()
{
    std::cout << "Player::~Player()" << std::endl;
}
*/