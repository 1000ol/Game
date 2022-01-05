#include "Element.h"

#ifndef UIELEMENT_H
#define UIELEMENT_H

namespace game
{

  class UIElement : public Element
  {

  public:
    // Destruktor - virtual så att den kan överskuggas av subklasser
    virtual ~UIElement();

  protected:
    using Element::Element;
  };
}

#endif