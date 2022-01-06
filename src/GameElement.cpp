#include "GameElement.h"
#include "System.h"

// Behövs dessa tomma konstruktorer/destruktorer här?
namespace game
{
    // Konstruktor
    GameElement::GameElement(int x, int y, int w, int h, const char *imgSrc) : Element(x, y, w, h), imageSource(imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }

    GameElement::~GameElement()
    {
        SDL_DestroyTexture(texture);
    }

}