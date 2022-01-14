#include "UIElement.h"
#include <iostream>

namespace gameEngine
{

  UIElement::~UIElement()
  {
    std::cout << "UIElement::~UIElement()" << std::endl;
  }

}