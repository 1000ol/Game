#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL2/SDL.h>

namespace cwing
{

  class Component
  {

  public:
    // destruktor
    virtual ~Component();

    // funktioner som hanterar användargenererade händelser (input)
    virtual void mouseDown(const SDL_Event &) {}
    virtual void mouseUp(const SDL_Event &) {}
    virtual void keyUp(const SDL_Event &) {}
    virtual void keyDown(const SDL_Event &) {}

    // uppdaterar objektets tillstånd
    virtual void tick() = 0;

    // ritar ut objektet
    // funktioner som är const för att de inte ändrar objekten.
    virtual void draw() const = 0;

    const SDL_Rect &getRect() const
    {
      return rect;
    }

  protected:
    // Konstruktor
    Component(int x, int y, int w, int h);

  private:
    SDL_Rect rect;

    // Skyddar mot värdesemantik???
    // Instantiering via värdesemantik "förbjuds"
    Component(const Component &) = delete;
    // Instantiering via tilldelningsoperator "förbjuds"
    const Component &operator=(const Component &) = delete;
  };
}

#endif