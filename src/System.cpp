#include "System.h"
#include "Session.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <string>

using namespace std;

namespace game
{
    // Konstruktor
    System::System()
    {
        // Initerar SDL-biblioteket
        SDL_Init(SDL_INIT_EVERYTHING);
        // Skapar ett fönster
        // OBS!! Hur gör man den i flexibel storlek?
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 600, 400, 0);
        // Skapar en renderare
        ren = SDL_CreateRenderer(win, -1, 0);
        string resPath = "../../resources/";

        SDL_Surface *sur = IMG_Load((resPath + "images/space.jpg").c_str());

        tex = SDL_CreateTextureFromSurface(ren, sur);
        SDL_FreeSurface(sur);

        // Initerar Font
        TTF_Init();

        font = TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50);

        // Initerar ljud
        /*
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        musik = Mix_LoadWAV((resPath + "sounds/bgMusic.wav").c_str());
        Mix_PlayChannel(-1, musik, -1);
*/
        session = new Session();
    }

    // Destruktor - städar bort vid stängning av programmet
    System::~System()
    {
        // OBS!! I vilken ordning bör dessa ske?
        // Stänger av font;
        TTF_CloseFont(font);
        TTF_Quit();
        // Stänger ner fönster
        SDL_DestroyWindow(win);
        // Stänger ner renderare
        SDL_DestroyRenderer(ren);
        // Stänger av ljud
        //  Mix_Quit();
        // Stänger av systemet
        SDL_Quit();

        // OBS!! Släng Session
    }

    SDL_Renderer *System::getRen() const
    {
        return ren;
    }

    TTF_Font *System::getFont() const
    {
        return font;
    }

    Session *System::getSession()
    {
        return session;
    }

    SDL_Texture *System::getTex() const
    {
        return tex;
    }

    // OBS!! Behövs denna här? Varför?
    System sys;

}
