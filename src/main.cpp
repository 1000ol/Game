#include <iostream>
#include <string>

// Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// Bifogas endast för test av SDL installation! 

#include <SDL.h> 			//<SDL2/SDL.h>
#include <SDL_image.h> 		//<SDL2_image/SDL_image.h>
#include <SDL_mixer.h> 		//<SDL2_mixer/SDL_mixer.h>
#include <SDL_ttf.h> 		//<SDL2_ttf/SDL_ttf.h>

//#define FPS 60


int main(int argc, char* argv[]) {

	// Paths to resources
	std::string imagePath = "../../images/";
	std::string fontPath = "../../fonts/";
	std::string soundPath = "../../sounds/";

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}
	
	SDL_Window* window 		= SDL_CreateWindow("Window", 100, 100, 800, 600, 0);
	SDL_Renderer* renderer 	= SDL_CreateRenderer(window, -1, 0);

	SDL_Surface* bg_sur = IMG_Load( (imagePath + "bg.jpg").c_str() );

	SDL_Texture* bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
	SDL_FreeSurface(bg_sur);

	std::cout << "Avsluta programmet genom \"quit\" från fönstrets meny eller genom att stänga fönstret!" << std::endl;

	// Loop till dess att programmet avslutas!
	bool running = true;
	while (running) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	// Städa innan programmet avslutas!

	SDL_DestroyTexture(bg_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	
	return EXIT_SUCCESS;
}