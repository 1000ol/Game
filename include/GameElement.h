#include "Element.h"
#include <SDL2_image/SDL_image.h>

#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

namespace game
{

  class GameElement : public Element
  {

  public:
    static GameElement *getInstance(int x, int y, int w, int h, const char *imgSrc);
   // class LeftButton och class RightButton kontrollerar musevent
    

      void tick(){};
      void draw() const {};
    // Funktioner som hanterar användargenererade händelser (input)
    virtual void keyUp(const SDL_Event &){};
    virtual void keyDown(const SDL_Event &){};
  
    // Destruktor
    ~GameElement();

  protected:
    GameElement(int x, int y, int w, int h, const char* imgSrc);
    const char *imageSource;
    SDL_Texture* texture;


  };
}

#endif