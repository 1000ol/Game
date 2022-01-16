#include "Element.h"
#include "UIElement.h"
#include "GameElement.h"

#include <vector>

#ifndef SESSION_H
#define SESSION_H

namespace gameEngine
{

  class Session
  {

  public:
    
    // Konstruktor
    Session();

    // Funktioner för elementen
    void addElement(std::shared_ptr<Element>);
    void removeElement(std::shared_ptr<Element>);
    void removeAllElements();

    // Funktion som kör programmet genom anrop till de privata funktionerna
    void run();
    
    // Destruktor
    ~Session(){};

  private:
    void checkUserInput();
    void checkObjectsState();
    void updateObjectsState();
    void checkForCollision();
    void handleAddedObjects();
    void handleRemovedObjects();
    void drawObjects();
    void handleDelay();

    Uint32 nextTick;
    bool quit = false;
    int tickCount = 0;

    // Samtliga vektorer för elementen 

    // Samling av alla objekt
    std::vector<std::shared_ptr<Element>> allElements;

    // Samling av alla adderade objekt
    std::vector<std::shared_ptr<Element>> allElementsAdded;

    // Samling av alla raderade objekt
    std::vector<std::shared_ptr<Element>> allElementsRemoved;

  };
}

#endif