#include "Element.h"

#include <memory>
#include <SDL2_image/SDL_image.h>

#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

namespace gameEngine
{

  class GameElement : public Element
  {

  public:
    // Funktion som instantierar nytt objekt genom anrop till konstruktorn och returnerar en pekare till objektet. 
    static std::shared_ptr<GameElement> getInstance(int x, int y, int w, int h, const char *imgSrc);
    
    // Virtuell funktion som kan definieras av subklasserna
    // Uppdaterar objektets tillstånd

    virtual void collide(){};

    void setImageSource(const char *imgSrc)
    {
      imageSource = imgSrc;
    }

    const char *getImageSource()
    {
      return imageSource;
    }

    void setIsUserControlled()
    {
      userControlled = true;
    };

    bool isUserControlled()
    {
      return userControlled;
    };

    void setHasCollided(bool c)
    {
      collided = c;
      if (collided)
        collisions++;
    }

    bool hasCollided()
    {
      return collided;
    }

    int getCollisions()
    {
      return collisions;
    }

    ~GameElement(){};

    // Konstruktor protected så att den nås av subklasserna men inte av tillämpningsprogrammeraren
    GameElement(int x, int y, int w, int h, const char *imgSrc);



  private:
    const char *imageSource;
    bool userControlled;
    bool collided;
    int collisions = 0;
  };
}

#endif