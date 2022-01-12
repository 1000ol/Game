#include "Player.h"
#include "System.h"


    // Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
    std::shared_ptr<Player>Player::getInstance(int x, int y, int w, int h, int minX, int maxX, const char *imgSrc)
    {
        return std::make_shared<Player>(x, y, w, h, minX, maxX, imgSrc);
    }

    // Konstruktor
    Player::Player(int x, int y, int w, int h, int miniX, int maxiX, const char *imgSrc) : GameElement(x, y, w, h, imgSrc), minX(miniX), maxX(maxiX)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
        SDL_FreeSurface(surf);
    }

    void Player::keyDown(const SDL_Event & e) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
                moveLeft();
                break;
            case SDLK_RIGHT:
                moveRight();
                break;
        }
    }

    void Player::moveRight() {
        int x = getRect().x;
        if (x > maxX)
            setCoordinateX(maxX);
        else
            setCoordinateX(x+30);
    }

    void Player::moveLeft() {
        int x = getRect().x;
        if (x < minX)
            setCoordinateX(minX);
        else
            setCoordinateX(x-30);
    }

