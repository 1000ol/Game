#include "UIElement.h"

#include <SDL2_image/SDL_image.h>

#ifndef BUTTON_H
#define BUTTON_H

namespace gameEngine
{
  // Button subklass till UIElement
  class Button : public UIElement, public std::enable_shared_from_this<Button>
  {
  public:
    static std::shared_ptr <Button> getInstance(int x, int y, int w, int h, const char *imgSrcUp, 
    const char *imgSrcDown);

    Button(int x, int y, int w, int h, const char *imgSrcUp, const char *imgSrcDown);


    void mouseDown(const SDL_Event &);
    void mouseUp(const SDL_Event &);

    virtual void perform(std::shared_ptr<Button>){};

    // Destruktor
    ~Button();

  private:
    SDL_Texture *textureUp, *textureDown;
    const char *imageSourceUp, *imageSourceDown;
  };

}

#endif