#include "UIElement.h"
#include "Label.h"

#include <SDL2_image/SDL_image.h>

#ifndef BUTTON_H
#define BUTTON_H

namespace game
{
  // Button subklass till UIElement
  class Button : public UIElement
  {
  public:
    static Button *getInstance(int x, int y, int w, int h, Label *lbl, const char *imgSrcUp, const char *imgSrcDown);

    void tick(){};

    void draw() const;

    void mouseDown(const SDL_Event &);
    void mouseUp(const SDL_Event &);

    virtual void perform(Button *){};

    // Destruktor
    ~Button();

  protected:
    Button(int x, int y, int w, int h, Label *lbl, const char *imgSrcUp, const char *imgSrcDown);

  private:
    Label *label;
    SDL_Texture *texture;
    const char *imageSourceUp, *imageSourceDown;
    SDL_Texture *imageMouseUp, *imageMouseDown;
    bool isDown = false;
  };

}

#endif