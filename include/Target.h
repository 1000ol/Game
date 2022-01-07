#include "GameElement.h"

#ifndef TARGET_H
#define TARGET_H

namespace gameEngine
{
  class Target : public GameElement, public std::enable_shared_from_this<Target>
  {
  public:
    static std::shared_ptr<Target> getInstance(int x, int y, int w, int h, const char *imgSrc);
    Target(int x, int y, int w, int h, const char *imgSrc);

    void tick();
  };
}
extern int counter;
#endif
