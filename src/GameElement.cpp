#include "GameElement.h"
#include "System.h"

namespace gameEngine
{

    std::shared_ptr<GameElement> GameElement::getInstance(int x, int y, int w, int h, const char *imgSrc) {
        return std::make_shared<GameElement>(x,y,w,h,imgSrc);
    }

    // Konstruktor
    GameElement::GameElement(int x, int y, int w, int h, const char *imgSrc) : Element(x, y, w, h), imageSource(imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
        SDL_FreeSurface(surf);
    }

    bool GameElement::isInsideWindow() {
        int w = sys.getSurf()->w;
        int h = sys.getSurf()->h;
       // SDL_Rect* r = const_cast<SDL_Rect*>(&getRect());
        //return (SDL_GetDisplayBounds(SDL_GetWindowDisplayIndex(sys.getWin()), r) == 0);
        int minX = getRect().x;
        int maxX = minX + getRect().w;
        int minY = getRect().y;
        int maxY = getRect().h;
        return (minX >= 0 && maxX <= w && minY >= 0 && maxY <= h);
    }


}