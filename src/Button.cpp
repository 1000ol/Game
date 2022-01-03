#include "Button.h"
#include <SDL_ttf.h>
#include "System.h"
#include <SDL_image.h>

using namespace std;

namespace cwing
{

  Button::Button(int x, int y, int w, int h, std::string txt) : Component(x, y, w, h)
  {
    SDL_Surface *surf = TTF_RenderText_Solid(sys.getFont(), txt.c_str(), {0, 0, 0});
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);

    upIcon = IMG_LoadTexture(sys.getRen(), (resPath + "images/bg.png").c_str());
    downIcon = IMG_LoadTexture(sys.getRen(), (resPath + "images/bg.png").c_str());
  }

  Button::~Button()
  {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(upIcon);
    SDL_DestroyTexture(downIcon);
  }

  Button *Button::getInstance(int x, int y, int w, int h, std::string txt)
  {
    return new Button(x, y, w, h, txt);
  }

  void Button::mouseDown(const SDL_Event &eve)
  {
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
      isDown = true;
  }
  void Button::mouseUp(const SDL_Event &eve)
  {
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
      perform(this);

    isDown = false;
  }
  void Button::draw() const
  {
    if (isDown)
      SDL_RenderCopy(sys.getRen(), downIcon, NULL, &getRect());
    else
      SDL_RenderCopy(sys.getRen(), upIcon, NULL, &getRect());

    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }
}