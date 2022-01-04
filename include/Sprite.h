#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

namespace game
{

  class Sprite
  {

  public:
    // Destruktor - virtual så att den kan överskuggas av subklasser
    virtual ~Sprite();

    // Funktioner som hanterar användargenererade händelser (input)
    virtual void mouseDown(const SDL_Event &) {}
    virtual void mouseUp(const SDL_Event &) {}
    virtual void keyUp(const SDL_Event &) {}
    virtual void keyDown(const SDL_Event &) {}

    // Abstrakt funktion som måste definieras av subklasserna
    // Uppdaterar objektets tillstånd
    // virtual void tick() = 0;

    // Abstrakt funktion som måste definieras av subklasserna
    // Funktion som är const för att den inte ändrar objektet
    // Ritar ut objektet
    virtual void draw() const = 0;

    // Returnerar rektangelobjektets koordinater för övre vänsterhörn och höjd+bredd
    // Funktion som är const för att den inte ändrar objektet
    // Returnerar const objekt som inte kan ändras
    const SDL_Rect &getRect() const
    {
      return rect;
    }

  protected:
    // Konstruktor
    Sprite(int x, int y, int w, int h);

  private:
    SDL_Rect rect;

    // Skyddar mot värdesemantik genom att ta bort funktionaliteten för copykonstruktor och tilldelningsoperator
    // Instantiering via värdesemantik "förbjuds"
    Sprite(const Sprite &) = delete;
    // Instantiering via tilldelningsoperator "förbjuds"
    const Sprite &operator=(const Sprite &) = delete;
  };
}

#endif