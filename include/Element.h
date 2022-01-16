#include <SDL2/SDL.h>

#ifndef ELEMENT_H
#define ELEMENT_H

namespace gameEngine
{

  class Element
  {

  public:
    // Funktion som är const för att den inte ändrar objektet
    // Ritar ut objektet
    void draw() const;

    // Virtuella funktioner som kan överskuggas i subklasserna
    virtual void mouseDown(const SDL_Event &){};
    virtual void mouseUp(const SDL_Event &){};
    virtual void keyDown(const SDL_Event &){};
    virtual void keyUp(const SDL_Event &){};
    virtual void tick(){};


    // Set- och get-funktioner 
    void setWidth(int width)
    {
      rect.w = width;
    };

    void setHeight(int height)
    {
      rect.h = height;
    };

    void setCoordinateX(int newX)
    {
      rect.x = newX;
    };

    void setCoordinateY(int newY)
    {
      rect.y = newY;
    };

    void setTexture(SDL_Texture *txt)
    {
      texture = txt;
    }

    SDL_Texture *getTexture() const
    {
      return texture;
    }

    void setAutogenerated()
    {
      autogenerated = true;
    }

    bool isAutogenerated()
    {
      return autogenerated;
    }

    // Returnerar rektangelobjektets koordinater för övre vänsterhörn och höjd+bredd  
    // Funktion som är const för att den inte ändrar objektet
    // Returnerar const objekt som inte kan ändras
    const SDL_Rect &getRect() const
    {
      return rect;
    }

    // Destruktor - virtuell så att den kan överskuggas av subklasser - ser till att samtliga objekt raderas säkert
    virtual ~Element();

  protected:
    // Konstruktor som är protected så att subklasser kan använda den
    Element(int x, int y, int w, int h) : rect{x, y, w, h} {};

  private:
    SDL_Texture *texture;
    SDL_Rect rect;
    bool autogenerated = false;

    // Skyddar mot värdesemantik genom att ta bort funktionaliteten för copykonstruktor och tilldelningsoperator
    // Behöver endast ske i en superklass
    // Instantiering via värdesemantik "förbjuds"
    Element(const Element &) = delete;
    // Instantiering via tilldelningsoperator "förbjuds"
    const Element &operator=(const Element &) = delete;
  };
}

#endif