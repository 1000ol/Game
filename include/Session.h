#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include <vector>

namespace game {
  
  class Session {

  public:
    void add(Component*);
    void remove(Component*);
    void run();
    // Destruktor
    ~Session();
  private:
  // Samling av alla komponentobjekt
  std::vector<Component*> components;
  // Samlingar av tillagda och radera objekt 
  std::vector<Component*> added, removed;

  };
}

#endif