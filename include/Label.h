#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace game
{

  class Label : public Component
  {
  public:
    // Skyddar mot värdesemantik genom att returnera pekare till det instantierade objektet 
    static Label *getInstance(int x, int y, int w, int h, std::string txt);

    // virtual void tick();
    void draw() const;

    std::string getText() const {
        return text;
    }

    void setText(std::string newText);

    // Destruktor
    ~Label();

  protected:
     Label(int x, int y, int w, int h, std::string txt);

  private:
    // OBS!! Privat eller protected konstruktor?
    //Label(int x, int y, int w, int h, std::string txt);
    std::string text;
    SDL_Texture *texture;
  };

}
#endif