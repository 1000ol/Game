#include "Target.h"
#include "System.h"

namespace gameEngine
{

    // Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
    std::shared_ptr<Target>Target::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        return std::make_shared<Target>(x, y, w, h, imgSrc);
    }
    // Konstruktor
    Target::Target(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
        SDL_FreeSurface(surf);
    }

    void Target::tick()
    {
        pace++;
        if (getRect().y >= 600)
        {
            sys.getSession()->removeElement(shared_from_this());
            sys.getSession()->removeGameElement(shared_from_this());
        }
        else if (pace % 10 == 0) {
            int newY = getRect().y + 5;
            setCoordinateY(newY);
        }
           
    }

    bool Target::hasCollided(){
      return collided;
    }

    void Target::setCollided(bool collision) {
        collided = collision;
    }
    
}