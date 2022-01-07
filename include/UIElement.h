#include "Element.h"

#include <memory>

#ifndef UIELEMENT_H
#define UIELEMENT_H

namespace gameEngine
{

  class UIElement : public Element
  {

  protected:
    // Använder sig av superklassens konstruktor då den inte har några ytterligare argument 
    using Element::Element;
  };
}

#endif