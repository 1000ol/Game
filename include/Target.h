#include "GameElement.h"

#ifndef TARGET_H
#define TARGET_H

namespace game
{
  class Target : public GameElement
  {
    public:
    static Target *getInstance(int x, int y, int w, int h, const char* imgSrc);

    void tick();
    void draw() const;

    // Destruktor
    ~Target();

    protected:
    Target(int x, int y, int w, int h, const char* imgSrc);

    private:
    SDL_Texture *texture;
  };
}
extern int counter;
#endif