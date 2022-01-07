#include <SDL2/SDL.h>

#ifndef ELEMENT_H
#define ELEMENT_H

namespace gameEngine
{

  class Element
  {

  public:
    // Rent virtuell funktion som måste definieras av subklasserna
    // Funktion som är const för att den inte ändrar objektet
    // Ritar ut objektet
    void draw() const;


    virtual void mouseDown(const SDL_Event &){};
    virtual void mouseUp(const SDL_Event &){};

    // Returnerar rektangelobjektets koordinater för övre vänsterhörn och höjd+bredd
    // Funktion som är const för att den inte ändrar objektet
    // Returnerar const objekt som inte kan ändras
    const SDL_Rect &getRect() const
    {
      return rect;
    }

    void setTexture(SDL_Texture *txt) {
      texture = txt;
    }

    SDL_Texture &getTexture() const
    {
      SDL_Texture *txt = const_cast<SDL_Texture*>(texture);
      return *txt;
    }

    // Destruktor - virtuell så att den kan överskuggas av subklasser - ser till att samtliga objekt raderas säkert
    virtual ~Element();

  protected:
    // Konstruktor som är protected så att subklasser kan använda den
    Element(int x, int y, int w, int h) : rect{x, y, w, h} {};
    // Medlem som är protected så att subklasser kan ändra dess koordinater
    SDL_Rect rect;


  private:
    SDL_Texture *texture;
    // Skyddar mot värdesemantik genom att ta bort funktionaliteten för copykonstruktor och tilldelningsoperator
    // Behöver endast ske i en superklass
    // Instantiering via värdesemantik "förbjuds"
    Element(const Element &) = delete;
    // Instantiering via tilldelningsoperator "förbjuds"
    const Element &operator=(const Element &) = delete;
  };
}

#endif