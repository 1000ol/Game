#include "Button.h"
#include "System.h"

using namespace std;

namespace game
{

  Button *Button::getInstance(int x, int y, int w, int h, Label *lbl, const char *imgSrcUp, const char *imgSrcDown)
  {
    return new Button(x, y, w, h, lbl, imgSrcUp, imgSrcDown);
  };

  // Konstruktor
  Button::Button(int x, int y, int w, int h, Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : UIElement(x, y, w, h), label(lbl), imageSourceUp(imgSrcUp), imageSourceDown(imgSrcDown)
  {
    SDL_Surface *surf = TTF_RenderText_Solid(label->getFont(), label->getText().c_str(), label->getColor());
    texture = SDL_CreateTextureFromSurface(sys.getRen(), surf);
    SDL_FreeSurface(surf);

    imageMouseUp = IMG_LoadTexture(sys.getRen(), imageSourceUp);
    imageMouseDown = IMG_LoadTexture(sys.getRen(), imageSourceDown);
  }

  // Hanterar när musknapp trycks ner
  void Button::mouseDown(const SDL_Event &eve)
  {
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
      isDown = true;
  }

  // Hanterar när musknapp släpps upp
  void Button::mouseUp(const SDL_Event &eve)
  {
    SDL_Point p = {eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
        perform(this);
    isDown = false;
  }

  // Ritar ut objektet
  void Button::draw() const
  {
    if (isDown) {
      SDL_RenderCopy(sys.getRen(), imageMouseDown, NULL, &getRect());
    }
    else
      SDL_RenderCopy(sys.getRen(), imageMouseUp, NULL, &getRect());
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

  // Destruktor
  Button::~Button()
  {
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(imageMouseUp);
    SDL_DestroyTexture(imageMouseDown);
  }

}