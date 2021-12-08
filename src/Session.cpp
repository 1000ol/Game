#include "Session.h"

using namespace std;

#define FPS 80

namespace cwing {

    void Session::add(Component* c) {
		comps.push_back(c);
	}

    void Session::remove(Component* comp) {
        removed.push_back(comp);
    }

	void Session::run() {
bool quit = false;

	Uint32 tickInterval = 1000 / FPS;
	while (!quit) {
		Uint32 nextTick = SDL_GetTicks() + tickInterval;
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: quit = true; break;
			case SDL_MOUSEBUTTONDOWN:
				for (Component* c : comps)
					c->mouseDown(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Component* c : comps)
					c->mouseUp(event.button.x, event.button.y);
				break;
			} //switch
		} //inre while

		for (Component* c : comps)
			c->tick();

		for (Component* c : added)
			comps.push_back(c);
		added.clear();

		for (Component* c : removed)
			for (vector<Component*>::iterator i = comps.begin();
				i != comps.end();)
				if (*i == c) {
					i = comps.erase(i);
				}
				else
					i++;
		removed.clear();

		SDL_SetRenderDrawColor(sys.ren, 255, 255, 255, 255);
		SDL_RenderClear(sys.ren);
		for (Component* c : comps)
			c->draw();
		SDL_RenderPresent(sys.ren);

		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	} // yttre while
}
    

    //Destruktor
    Session::~Session() {

    }
}