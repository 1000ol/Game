#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"

namespace game
{

  class Session
  {

  public:
    // Default-konstruktor
    Session();
    void add(Component *);
    void remove(Component *);
    void run();
    // Destruktor
    ~Session();

  private:
    // Samling av alla komponentobjekt
    std::vector<Component *> components;
    // Samlingar av tillagda och radera objekt
    std::vector<Component *> added, removed;
  };
}

#endif