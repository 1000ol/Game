#include "Label.h"
#include <SDL_ttf.h>
#include "System.h"
#include <iostream>
#include <string>

using namespace std;

namespace game
{

  Label* Label::getInstance(int x, int y, int w, int h, std::string txt) {
    return new Label(x, y, w, h, txt);
  }

  // Konstruktor
  Label::Label(int x, int y, int w, int h,
               std::string txt) : Component(x, y, w, h), text(txt)
  {
    // OBS!! Font funkar inte?? Varför kan vi inte hämta fonten med sys.getFont() här???
    SDL_Surface *surf = TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 36), text.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
  }

  void Label::draw() const
  {
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

  void Label::setText(std::string newText)
  {
    text = newText;
    SDL_DestroyTexture(texture);
    // OBS!! Font funkar inte??
    SDL_Surface *surf = TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 36),
                                             text.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);
  }
  
  // Destruktor
  Label::~Label()
  {
    SDL_DestroyTexture(texture);
  }

}