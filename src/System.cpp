#include "System.h"

#include <iostream>
using namespace std;

namespace gameEngine
{
    // Konstruktor
    System::System()
    {
        // Initerar bibliotek
        SDL_Init(SDL_INIT_EVERYTHING);
        TTF_Init();

        //Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        session = new Session();
    }

    void System::setMusic(const char* musicSrc) {
        music = Mix_LoadWAV(musicSrc);
        Mix_PlayChannel(-1, music, -1);
        
     //   if(!music) {
       //     printf("Mix_LoadWAV: %s\n", Mix_GetError());
            // handle error
       // }
        //Mix_PlayChannel(-1, music, -1);
      //  if(Mix_PlayChannel(-1, music, 0)==-1) {
       //     printf("Mix_PlayChannel: %s\n",Mix_GetError());
            // may be critical error, or maybe just no channels were free.
            // you could allocated another channel in that 
       // }
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
        //Mix_Quit();
        // Stänger av systemet
        SDL_Quit();
        delete session;
    }

    System sys;

}
