#include "Element.h"
#include "System.h"
#include <iostream>

namespace gameEngine
{

  void Element::draw() const
  {
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

   Element::~Element()
  {
    SDL_DestroyTexture(texture);
  }
}