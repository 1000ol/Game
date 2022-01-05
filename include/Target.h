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

    //vill vi kunna anropa en set()-funktion för att öka y vid varje tick?
    void increasePosY();

    // Destruktor
    ~Target();

    protected:
    Target(int x, int y, int w, int h);
  };

}
#endif