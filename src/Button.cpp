#include "Button.h"
#include "System.h"

#include <iostream>

using namespace std;

// Säkerställer att objekt endast kan instantieras via privat konstruktor och hämtas som pekarobjekt
std::shared_ptr<Button> Button::getInstance(int x, int y, int w, int h, const char *imgSrcUp, const char *imgSrcDown)
{
  return std::make_shared<Button>(x, y, w, h, imgSrcUp, imgSrcDown);
}

// Konstruktor
Button::Button(int x, int y, int w, int h, const char *imgSrcUp, const char *imgSrcDown) : UIElement(x, y, w, h), imageSourceUp(imgSrcUp), imageSourceDown(imgSrcDown)
{
  SDL_Surface *surf = IMG_Load(imageSourceUp);
  setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
  textureUp = getTexture();
  textureDown = IMG_LoadTexture(sys.getRen(), imageSourceDown);
  SDL_FreeSurface(surf);
}

// Hanterar när musknapp trycks ner
void Button::mouseDown(const SDL_Event &eve)
{
  SDL_Point p = {eve.button.x, eve.button.y};
  if (SDL_PointInRect(&p, &getRect()))
    setTexture(textureDown);
}

// Hanterar när musknapp släpps upp
void Button::mouseUp(const SDL_Event &eve)
{
  SDL_Point p = {eve.button.x, eve.button.y};
  if (SDL_PointInRect(&p, &getRect()))
    perform(shared_from_this());
  setTexture(textureUp);
}

// Destruktor
Button::~Button()
{
  std::cout << "Button::~Button()" << std::endl;
  SDL_DestroyTexture(textureUp);
  SDL_DestroyTexture(textureDown);
}
