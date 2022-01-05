#include "Element.h"

// Behövs dessa tomma konstruktorer/destruktorer här?
namespace game
{

  Element::Element(int x, int y, int w, int h) : rect{x, y, w, h}
  {
  }

  Element::~Element()
  {
  }
}