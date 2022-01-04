#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>
#include "Session.h"

namespace game
{

    class System
    {

    public:
        // Default-konstruktor
        System();
        // Destruktor
        ~System();
        // Statisk metod för att hämta renderare
        SDL_Renderer *getRen() const;
        // Statisk metod för att hämta font
        TTF_Font *getFont() const;
        Session *getSession();
        SDL_Texture *getTex() const;

    private:
        SDL_Window *win;
        SDL_Renderer *ren;
        TTF_Font *font;
        SDL_Texture *tex;
        // Mix_Chunk *musik;
        Session *session;
    };
    // Deklareras som extern så att den kan nås av klasser som inkluderar headerfilen
    extern System sys;

}
extern const std::string resPath;

#endif