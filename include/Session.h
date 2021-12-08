#ifndef SESSION_H
#define SESSION_H

#include "Component.h"
#include <vector>

class Session {

public:
  void add(Component* c);
  void remove(Component* c);
  void run();
private:
std::vector<Component*> components;
std::vector<Component*> added, removed;

};

#endif