#include <SDL_ttf.h>
#include <SDL_image.h>

#include "Button.h"
#include "System.h"

using namespace std;

namespace game
{

  Button *Button::getInstance(int x, int y, int w, int h, std::string txt)
  {
    return new Button(x, y, w, h, txt);
  };

  // Konstruktor
  Button::Button(int x, int y, int w, int h, std::string txt) : Component(x, y, w, h)
  {
    // OBS!! Font funkar inte???!
    SDL_Surface *surf = TTF_RenderText_Solid(TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50), txt.c_str(), {239, 100, 170});
    // OBS!! Hur interagerar texture och surface??
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);

    // OBS!! Bytas ut mot vårt content
    upIcon = IMG_LoadTexture(sys.getRen(), (resPath + "images/neon.png").c_str());
    downIcon = IMG_LoadTexture(sys.getRen(), (resPath + "images/explosion.jpg").c_str());
  }

  // Hanterar när musknapp trycks ner
  void Button::mouseDown(const SDL_Event &eve)
  {
    // OBS!! Byta ut mot eget content
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
      isDown = true;
  }

  // Hanterar när musknapp släpps
  void Button::mouseUp(const SDL_Event &eve)
  {
    // OBS!! Byta ut mot eget content
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
      perform(this);
    isDown = false;
  }

  // Ritar ut objektet
  void Button::draw() const
  {
    // OBS!! Byta ut mot eget content
    if (isDown)
      SDL_RenderCopy(sys.getRen(), downIcon, NULL, &getRect());
    else
      SDL_RenderCopy(sys.getRen(), upIcon, NULL, &getRect());
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

  // Destruktor
  Button::~Button()
  {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(upIcon);
    SDL_DestroyTexture(downIcon);
  }

}