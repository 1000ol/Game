#include "Element.h"

#include <memory>
#include <SDL2_image/SDL_image.h>

#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

namespace gameEngine
{

  class GameElement : public Element
  {

  public:
    static std::shared_ptr<GameElement> getInstance(int x, int y, int w, int h, const char *imgSrc);
    GameElement(int x, int y, int w, int h, const char *imgSrc);    

    // Virtuell funktion som kan definieras av subklasserna
    // Uppdaterar objektets tillstånd
    virtual void tick(){};

  protected:
    
    const char *imageSource;
  };
}

#endif