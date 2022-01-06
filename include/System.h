#include "Session.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

#ifndef SYSTEM_H
#define SYSTEM_H

namespace game
{

    class System
    {

    public:
        // Default-konstruktor
        System();
        // Destruktor
        ~System();

        void setWin(SDL_Window *wn)
        {
            win = wn;
        }

        SDL_Window *getWin()
        {
            return win;
        }

        void setRen(SDL_Renderer *rend)
        {
            ren = rend;
        }
        // Statisk metod för att hämta renderare
        SDL_Renderer *getRen() const
        {
            return ren;
        }

        void setFont(TTF_Font *fnt)
        {
            font = fnt;
        }

        void setSession(Session *s) {
            session = s;
        }

        // Statisk metod för att hämta font
        TTF_Font *getFont() const
        {
            return font;
        }

        void setTex(SDL_Texture *tx)
        {
            tex = tx;
        }

        SDL_Texture *getTex() const
        {
            return tex;
        }

        /* Mix_Chunk *getMusic() const
         {
             return music;
         }*/

        Session *getSession()
        {
            return session;
        }

    private:
        SDL_Window *win;
        SDL_Renderer *ren;
        TTF_Font *font;
        SDL_Texture *tex;
        // Mix_Chunk *music;
        Session *session;
    };
    // Deklareras som extern så att den kan nås av klasser som inkluderar headerfilen
    extern System sys;

}
extern const std::string resPath;

#endif