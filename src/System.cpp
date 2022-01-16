#include "System.h"

using namespace std;

namespace gameEngine
{
    // Konstruktor
    System::System()
    {
        // Initerar bibliotek
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();

        // Initierar musiken
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);

        // Skapar nytt Session-objekt
        session = new Session();
    }

    void System::setFont(const char* fontSrc, int pointSize) {
        font = TTF_OpenFont(fontSrc, pointSize);
    }

    void System::setMusic(const char *musicSrc)
    {
        music = Mix_LoadWAV(musicSrc);
        Mix_PlayChannel(-1, music, -1);
    }

    // Destruktor - städar bort vid stängning av programmet
    System::~System()
    {
        // Stänger av ljud
        Mix_Quit();
        // Stänger av font;
        TTF_CloseFont(font);
        TTF_Quit();
        // Stänger ner renderare
        SDL_DestroyRenderer(ren);
        // Stänger ner fönster
        SDL_DestroyWindow(win);
        // Stänger av systemet
        SDL_Quit();
        delete session;
    }

    System sys;

}
