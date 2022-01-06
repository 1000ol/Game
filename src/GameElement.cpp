#include "GameElement.h"
#include "System.h"

// Behövs dessa tomma konstruktorer/destruktorer här?
namespace game
{

  GameElement *GameElement::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        return new GameElement(x, y, w, h, imgSrc);
    }

    // Konstruktor
    GameElement::GameElement(int x, int y, int w, int h, const char *imgSrc) : Element(x, y, w, h), imageSource(imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    GameElement::~GameElement() {
        SDL_DestroyTexture(texture);
    }

}