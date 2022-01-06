#include "Element.h"
#include "GameElement.h"

#include <vector>

#ifndef SESSION_H
#define SESSION_H

namespace game
{

  class Session
  {

  public:
    // Default-konstruktor
    Session(){};
    void addElement(Element *);
    void removeElement(Element *);
    void run();
    // Destruktor
    ~Session();

  private:
    // Samling av alla objekt
    std::vector<Element *> allElements;

    // Samling av alla adderade objekt
    std::vector<Element *> allElementsAdded;

    // Samling av alla raderade objekt
    std::vector<Element *> allElementsRemoved;

  };
}

#endif