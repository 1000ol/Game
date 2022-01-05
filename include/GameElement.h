#include "Element.h"

#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

namespace game
{

  class GameElement : public Element
  {

  public:
    // Funktioner som hanterar användargenererade händelser (input)
    virtual void keyUp(const SDL_Event &) = 0;
    virtual void keyDown(const SDL_Event &) = 0;

    // Destruktor - virtual så att den kan överskuggas av subklasser
    virtual ~GameElement();

  protected:
    using Element::Element;
  };
}

#endif