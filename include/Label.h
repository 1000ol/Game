#include "UIElement.h"

#include <string>
#include <SDL2_ttf/SDL_ttf.h>

#ifndef LABEL_H
#define LABEL_H

namespace gameEngine
{

  // Subklass till UIElement
  class Label : public UIElement
  {
  public:
    // Skyddar mot värdesemantik genom att returnera pekare till det instantierade objektet
    static std::shared_ptr<Label> getInstance(int x, int y, int w, int h, std::string txt, TTF_Font *fnt, SDL_Color clr);

    Label(int x, int y, int w, int h, std::string txt, TTF_Font *fnt, SDL_Color clr);

    std::string getText() const
    {
      return text;
    }

    void setText(std::string newText);

    TTF_Font *getFont() const
    {
      return font;
    }

    SDL_Color getColor() const
    {
      return color;
    }

  private:
    std::string text;
    TTF_Font *font;
    SDL_Color color;
  };

}

#endif