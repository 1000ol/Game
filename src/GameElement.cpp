#include "GameElement.h"
#include "System.h"
#include <iostream>

namespace gameEngine
{

    std::shared_ptr<GameElement> GameElement::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        // Allokerar minne dynamiskt
        return std::make_shared<GameElement>(x, y, w, h, imgSrc);
    }

    // Konstruktor
    GameElement::GameElement(int x, int y, int w, int h, const char *imgSrc) : Element(x, y, w, h), imageSource(imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
        SDL_FreeSurface(surf);
    }

    GameElement::~GameElement()
    {
        std::cout << "GameElement::~GameElement()" << std::endl;
    }

}