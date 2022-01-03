#include "Session.h"
#include "System.h"
#include <SDL2/SDL.h>

using namespace std;

#define FPS 80

namespace cwing {

    void Session::add(Component* comp) {
		components.push_back(comp);
	}

    void Session::remove(Component* comp) {
        removed.push_back(comp);
    }

	void Session::run() {
	bool quit = false;

	// Bestämmer takten
	Uint32 tickInterval = 1000 / FPS;
	while (!quit) {
		// För tilläggsnivå C kolla om användargenererad händelse är kortkommando - anropa motsvarande funktion
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		// Kollar användargenererade händelser i form 
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: quit = true; break;
			case SDL_MOUSEBUTTONDOWN:
				for (Component* comp : components)
					comp->mouseDown(event);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Component* comp : components)
					comp->mouseUp(event);
				break;
			// Ska vi även ha musrörelser här?
			case SDL_KEYDOWN:
				for (Component* comp : components)
					comp->keyDown(event);
				break;
			case SDL_KEYUP:
				for (Component* comp : components)
					comp->keyUp(event);
				break;
			} // Switch
		} // Inre while

		// Uppdaterar samtliga objekt
		for (Component* comp : components)
			comp->tick();

		// Kollisionskontroll för objekt
		for (Component* comp : components) {
			for (Component* compOther : components) {
				if (comp != compOther) {
					if (comp->getRect().x == compOther->getRect().x && comp->getRect().y == compOther->getRect().y) {
						// Hantering av kollision görs här

					}
				}
			}
		}

		// Lägger till nya objekt
		for (Component* comp : added)
			components.push_back(comp);
		added.clear();

		// Tar bort raderade objekt
		for (Component* comp : removed) {
			for (vector<Component*>::iterator i = components.begin();
				i != components.end();) {
				if (*i == comp) {
					i = components.erase(i);
				}
				else
					i++;
			} // Inre for-loop
		} // Yttre for-loop
		removed.clear();

		// Ritar ut objekten i det uppdaterade tillståndet 
		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		SDL_RenderClear(sys.getRen());
		for (Component* comp : components)
			comp->draw();
		SDL_RenderPresent(sys.getRen());

		// Tid kontrolleras och fördröjning framkallas
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	} // Yttre while
}
    

    // Destruktor - måste den vara här fast den är tom? 
    Session::~Session() {

    }
}