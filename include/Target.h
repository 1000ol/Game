#include "GameElement.h"

#ifndef TARGET_H
#define TARGET_H

using namespace gameEngine;

class Target : public gameEngine::GameElement, public std::enable_shared_from_this<Target>
{
public:
  static std::shared_ptr<Target> getInstance(int x, int y, int w, int h, const char *imgSrc);
  Target(int x, int y, int w, int h, const char *imgSrc);

  void tick();

  void collide();

private:
  int pace = 0;
};

#endif
