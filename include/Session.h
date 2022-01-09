#include "Element.h"
#include "GameElement.h"

#include <vector>

#ifndef SESSION_H
#define SESSION_H

namespace gameEngine
{

  class Session
  {

  public:
    // Default-konstruktor
    Session();
    void addElement(std::shared_ptr<Element>);
    void addGameElement(std::shared_ptr<GameElement>);
    void removeElement(std::shared_ptr<Element>);
    void removeGameElement(std::shared_ptr<GameElement>);
    void removeAllElements();

    int noOfGameElements();

    void run();
    // Destruktor
    ~Session(){};

  private:
    
    void checkUserInput();
    void updateObjectsState();
    void checkForCollision();
    void handleAddedObjects();
    void handleRemovedObjects();
    void drawObjects();
    void handleDelay();
    
    Uint32 tickInterval;
    Uint32 nextTick;
    bool quit = false;

    // Samling av alla objekt
    std::vector<std::shared_ptr<Element>> allElements;

    // Samling av alla spelobjekt
    std::vector<std::shared_ptr<GameElement>> allGameElements;

    // Samling av alla adderade objekt
    std::vector<std::shared_ptr<Element>> allElementsAdded;

    // Samling av alla raderade objekt
    std::vector<std::shared_ptr<Element>> allElementsRemoved;

     // Samling av alla raderade spelobjekt
    std::vector<std::shared_ptr<GameElement>> allGameElementsRemoved;

  };
}
// OBS!! Inte bra implementering
extern bool gameRendered;
extern const int maximumAmount;
extern void addTarget();

extern const int fps, performance;

#endif