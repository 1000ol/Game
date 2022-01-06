#include "Label.h"
#include "System.h"

using namespace std;

namespace game
{

  // Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
  Label *Label::getInstance(int x, int y, int w, int h, string txt, TTF_Font *fnt, SDL_Color clr)
  {
    return new Label(x, y, w, h, txt, fnt, clr);
  }

  // Konstruktor
  Label::Label(int x, int y, int w, int h,
               string txt, TTF_Font *fnt, SDL_Color clr) : UIElement(x, y, w, h), text(txt), font(fnt), color(clr)
  {
    // Sätter font, storlek, färg för label
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
  }

  void Label::draw() const
  {
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

  void Label::setText(string newText)
  {
    text = newText;
    SDL_DestroyTexture(texture);
    SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
  }

  // Destruktor
  Label::~Label()
  {
    SDL_DestroyTexture(texture);
  }

}