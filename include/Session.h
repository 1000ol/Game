#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include <vector>

namespace cwing {
  
  class Session {

  public:
    void add(Component*);
    void remove(Component*);
    void run();
    // Destruktor
    ~Session();
  private:
  std::vector<Component*> components;
  std::vector<Component*> added, removed;

  };
}

#endif