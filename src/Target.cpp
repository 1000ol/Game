#include "Target.h"
#include "System.h"

namespace game
{

    Target *Target::getInstance(int x, int y, int w, int h, const char *imgSrc)
    {
        return new Target(x, y, w, h, imgSrc);
    }
 // Konstruktor
    Target::Target(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
    {
        SDL_Surface *surf = IMG_Load(imageSource);
        texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
        SDL_FreeSurface(surf);
    }
    
	void Target::tick() {
		//counter++;
		if (rect.y >= 600) {
            sys.getSession()->removeElement(this);
           // delete this;
        }
		else
			rect.y+= 10;
	}
	
    void Target::draw() const {
        SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
    }


	Target::~Target() {
        SDL_DestroyTexture(texture);
    }
}