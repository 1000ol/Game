#include "System.h"
#include <iostream>
using namespace std;

namespace game
{
    // Konstruktor
    System::System()
    {
        // Initerar bibliotek
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();

        // Skapar ett fönster
        win = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, 600, 400, 0);
        // Skapar en renderare
        ren = SDL_CreateRenderer(win, -1, 0);

        // OBS!! Det här vill vi kunna ta bort
        string resPath = "../../resources/";

        SDL_Surface *sur = IMG_Load((resPath + "images/space.jpg").c_str());

        tex = SDL_CreateTextureFromSurface(ren, sur);
        SDL_FreeSurface(sur);
        /*
        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        music = Mix_LoadWAV((resPath + "sounds/bgMusic.wav").c_str());
        Mix_PlayChannel(-1, music, -1);
        */
        session = new Session();
    }

    // Destruktor - städar bort vid stängning av programmet
    System::~System()
    {
        // Göras i omvänd ordning till hur vi initierat
        // Stänger av font;
        TTF_CloseFont(font);
        TTF_Quit();
        // Stänger ner fönster
        SDL_DestroyWindow(win);
        // Stänger ner renderare
        SDL_DestroyRenderer(ren);
        // Stänger av ljud
        Mix_Quit();
        // Stänger av systemet
        SDL_Quit();
        delete session;
    }

    System sys;

}
