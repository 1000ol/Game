#include "Label.h"
#include "System.h"

#include <iostream>

using namespace std;

// Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
std::shared_ptr<Label> Label::getInstance(int x, int y, int w, int h, string txt, TTF_Font *fnt, SDL_Color clr)
{
  return std::make_shared<Label>(x, y, w, h, txt, fnt, clr);
}

// Konstruktor
Label::Label(int x, int y, int w, int h,
             string txt, TTF_Font *fnt, SDL_Color clr) : UIElement(x, y, w, h), text(txt), font(fnt), color(clr)
{
  // Sätter font, storlek, färg för label
  SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
  setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
  SDL_FreeSurface(surf);
}

void Label::setText(string newText)
{
  text = newText;
  SDL_Surface *surf = TTF_RenderText_Solid(font, text.c_str(), color);
  setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
  SDL_FreeSurface(surf);
}

Label::~Label()
{
  std::cout << "Label::~Label() " << std ::endl;
}