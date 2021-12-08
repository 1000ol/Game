#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h> 			
#include <SDL2_image/SDL_image.h> 	
#include <SDL2_mixer/SDL_mixer.h> 	
#include <SDL2_ttf/SDL_ttf.h> 
#include <string>

// Vad gör detta??
namespace cwing {

    class System {

    public:
    // Default-konstruktor
    System();
    // Destruktor
    ~System();
    // Statisk metod för att hämta renderare
    SDL_Renderer* getRen() const;
    // Statisk metod för att hämta font
    TTF_Font* getFont() const;
    private:
    SDL_Window* win;
    SDL_Renderer* ren;
    TTF_Font* font;
    Mix_Chunk* musik;

    };

extern System sys;
}

extern std::string resPath;

#endif