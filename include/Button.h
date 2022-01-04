#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace game
{
  // Button subklass till Component
  class Button : public Component
  {
  public:
    static Button *getInstance(int x, int y, int w, int h, std::string txt);
    void mouseDown(const SDL_Event &);
    void mouseUp(const SDL_Event &);
    // void keyUp(const SDL_Event &);
    // void keyDown(const SDL_Event &);

    // virtual void tick();
    void draw() const;
    // OBS!! När använder vi denna???
    virtual void perform(Button *source) {}

    // Destruktor
    ~Button();

  protected:
    Button(int x, int y, int w, int h, std::string txt);

  private:
    // OBS!! Privat eller protected konstruktor?
    // Button(int x, int y, int w, int h, std::string txt);
    std::string text;

    // OBS!! Byta ut mot vårt content
    SDL_Texture *texture;
    SDL_Texture *upIcon, *downIcon;
    bool isDown = false;
  };

}

#endif