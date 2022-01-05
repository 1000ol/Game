#include "Session.h"
#include "System.h"

using namespace std;

// Sätter värdet för framesPerSecond
// OBS!! Outsourca??
#define FPS 80

namespace game
{
	// Element-funktioner
	void Session::addElement(Element *e)
	{
		allElements.push_back(e);
	}

	void Session::removeElement(Element *e)
	{
		allElementsRemoved.push_back(e);
	}

	void Session::run()
	{
		// Variabel för körningens tillstånd
		bool quit = false;

		// Bestämmer takten
		// OBS!! Outsourca??
		Uint32 tickInterval = 1000 / FPS;
		while (!quit)
		{
			// För tilläggsnivå C kolla om användargenererad händelse är kortkommando - anropa motsvarande funktion
			Uint32 nextTick = SDL_GetTicks() + tickInterval;
			SDL_Event event;

			// Kollar användargenererade händelser
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_MOUSEBUTTONDOWN:
					for (Element *e : allElements)
						e->mouseDown(event);
					break;
				case SDL_MOUSEBUTTONUP:
					for (Element *e : allElements)
						e->mouseUp(event);
					break;
				case SDL_KEYDOWN:
					for (GameElement *gme : gameElements)
						gme->keyDown(event);
					break;
				case SDL_KEYUP:
					for (GameElement *gme : gameElements)
						gme->keyUp(event);
					break;
				} // Switch-loop
			}		// Inre while-loop

			// OBS!! Uppdatera med tick sen
			// Uppdaterar samtliga objekt
			for (Element *e : allElements)
				e->tick();

			// Kollisionskontroll för objekt
			for (GameElement *gme : gameElements)
			{
				for (GameElement *gmeOther : gameElements)
				{
					if (gme != gmeOther)
					{
						if (gme->getRect().x == gmeOther->getRect().x && gme->getRect().y == gmeOther->getRect().y)
						{
							// Hantering av kollision görs här
						}
					}
				}
			}

			// Lägger till nya objekt
			for (Element *e : allElementsAdded)
				allElements.push_back(e);
			allElementsAdded.clear();

			// Tar bort raderade objekt
			for (Element *e : allElementsRemoved)
			{
				for (vector<Element *>::iterator i = allElementsRemoved.begin();
						 i != allElementsRemoved.end();)
				{
					if (*i == e)
					{
						i = allElements.erase(i);
					}
					else
						i++;
				} // Inre for-loop
			}		// Yttre for-loop
			allElementsRemoved.clear();

			// Ritar ut objekten i det uppdaterade tillståndet
			SDL_RenderClear(sys.getRen());
			SDL_RenderCopy(sys.getRen(), sys.getTex(), NULL, NULL);

			for (Element *e : allElements)
				e->draw();
			SDL_RenderPresent(sys.getRen());

			// Tid kontrolleras och fördröjning framkallas
			int delay = nextTick - SDL_GetTicks();
			if (delay > 0)
				SDL_Delay(delay);
		} // Yttre while
	}

	// OBS!! Destruktor - måste den vara här fast den är tom?
	Session::~Session()
	{
	}
}