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
        if (rect.y >= 600)
        {
            sys.getSession()->removeElement(shared_from_this());
            counter--;
        }
        else if (pace % 10 == 0)
            rect.y+=2;
    }

}