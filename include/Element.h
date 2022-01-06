#include <SDL2/SDL.h>

#ifndef ELEMENT_H
#define ELEMENT_H

namespace game
{

  class Element
  {

  public:
        // Abstrakt funktion som måste definieras av subklasserna
    // Funktion som är const för att den inte ändrar objektet
    // Ritar ut objektet
    virtual void draw() const = 0;

    virtual void mouseDown(const SDL_Event &){};
    virtual void mouseUp(const SDL_Event &){};

    // Returnerar rektangelobjektets koordinater för övre vänsterhörn och höjd+bredd
    // Funktion som är const för att den inte ändrar objektet
    // Returnerar const objekt som inte kan ändras
    const SDL_Rect &getRect() const
    {
      return rect;
    }

    // Destruktor - virtual så att den kan överskuggas av subklasser
    virtual ~Element(){};

  protected:
    // Konstruktor som är protected så att subklasser kan använda den
    Element(int x, int y, int w, int h) : rect{x, y, w, h} {};
    SDL_Rect rect;

  private:
    // Skyddar mot värdesemantik genom att ta bort funktionaliteten för copykonstruktor och tilldelningsoperator
    // Instantiering via värdesemantik "förbjuds"
    Element(const Element &) = delete;
    // Instantiering via tilldelningsoperator "förbjuds"
    const Element &operator=(const Element &) = delete;
  };
}

#endif