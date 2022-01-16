#include "Session.h"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <string>

#ifndef SYSTEM_H
#define SYSTEM_H

namespace gameEngine
{

    class System
    {

    public:
        // Konstruktor
        System();

        // Set- och getfunktioner 
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

        SDL_Renderer *getRen() const
        {
            return ren;
        }

        Session *getSession()
        {
            return session;
        }

        void setSession(Session *s)
        {
            session = s;
        }

        void setTex(SDL_Texture *tx)
        {
            tex = tx;
        }

        SDL_Texture *getTex() const
        {
            return tex;
        }

        void setSurf(SDL_Surface *s)
        {
            surf = s;
        }

        SDL_Surface *getSurf() const
        {
            return surf;
        }

        void setFont(const char*, int);

        TTF_Font *getFont() const
        {
            return font;
        }

        void setMusic(const char *);

        Mix_Chunk *getMusic() const
        {
            return music;
        }

        // Bestämmer takten
        void setTickInterval(int performance, int fps)
        {
            tickInterval = performance / fps;
        }

        int getTickInterval()
        {
            return tickInterval;
        }

         // Destruktor
        ~System();

    private:
        SDL_Window *win;
        SDL_Renderer *ren;
        TTF_Font *font;
        SDL_Texture *tex;
        SDL_Surface *surf;
        Mix_Chunk *music;
        Session *session;
        int tickInterval;
    };

    // Deklareras som extern så att den kan nås av klasser som inkluderar headerfilen
    extern System sys;

}

#endif