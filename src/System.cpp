#include "System.h"

using namespace std;

namespace cwing
{
    // Konstruktor
    System::System()
    {
        // Initerar SDL-biblioteket??
        SDL_Init(SDL_INIT_EVERYTHING);
        // Skapar ett fönster
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 600, 400, 0);
        // Skapar en renderare
        ren = SDL_CreateRenderer(win, -1, 0);

        // Initerar TTF-biblioteket?
        TTF_Init();
        // Initerar font
        font = TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 36);
        /*
          // Initerar ljud
          Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
          musik = Mix_LoadWAV((resPath + "sounds/bgMusic.wav").c_str());
          Mix_PlayChannel(-1, musik, -1);
          */
    }

    // Destruktor
    System::~System()
    {

        // Stänger ner ...
        //  SDL_DestroyTexture(bg_tex);
        // Stänger ner fönster
        SDL_DestroyWindow(win);
        // Stänger ner renderare
        SDL_DestroyRenderer(ren);
        // Stänger av font;
        TTF_CloseFont(font);
        TTF_Quit();
        // Stänger av ljud
        //  Mix_Quit();
        // Stänger av systemet
        SDL_Quit();
    }

    SDL_Renderer *System::getRen() const
    {
        return ren;
    }

    TTF_Font *System::getFont() const
    {
        return font;
    }

    System sys;
}
