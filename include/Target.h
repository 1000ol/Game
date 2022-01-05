#include "GameElement.h"

#ifndef TARGET_H
#define TARGET_H

namespace game
{
  class Target : public GameElement
  {

    static Target *getInstance(int x, int y, int w, int h);

    void tick();
    void draw() const;

    void mouseDown(const SDL_Event &);
    void mouseUp(const SDL_Event &);
    void keyUp(const SDL_Event &);
    void keyDown(const SDL_Event &);

    // Destruktor
    ~Target();

  protected:
    Target(int x, int y, int w, int h);
  };

}
#endif