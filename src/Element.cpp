#include "Element.h"
#include "System.h"

namespace gameEngine
{

  void Element::draw() const {
    SDL_RenderCopy(sys.getRen(), texture, NULL, &getRect());
  }

  void Element::setWidth(int width) {
    rect.w = width;
  }

  void Element::setHeight(int height) {
    rect.h = height;
  }

  void Element::setCoordinateX(int newX) {
    rect.x = newX;
  }
  void Element::setCoordinateY(int newY) {
    rect.y = newY;
  }

  Element::~Element() {
    SDL_DestroyTexture(texture);
  }
}