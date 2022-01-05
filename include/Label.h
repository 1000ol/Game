#include "UIElement.h"

#include <string>
#include <SDL2_ttf/SDL_ttf.h>

#ifndef LABEL_H
#define LABEL_H

namespace game
{

  // Subklass till UIElement
  class Label : public UIElement
  {
  public:
    // Skyddar mot värdesemantik genom att returnera pekare till det instantierade objektet
    static Label *getInstance(int x, int y, int w, int h, std::string txt, TTF_Font *fnt, SDL_Color clr);

    // OBS!! Vill vi verkligen ha kvar denna funktion?
    void tick();
    void draw() const;

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

    // Destruktor
    ~Label();

  private:
    Label(int x, int y, int w, int h, std::string txt, TTF_Font *fnt, SDL_Color clr);
    std::string text;
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture *texture;
  };

}

#endif