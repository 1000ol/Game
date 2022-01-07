#include "Session.h"
#include "System.h"
#include "Player.h"
#include "Button.h"

#include <iostream>
#include <memory>

using namespace std;

namespace gameEngine
{

Session::Session() {
	// Bestämmer takten
	tickInterval = performance / fps;

	// För tilläggsnivå C kolla om användargenererad händelse är kortkommando - anropa motsvarande funktion
	nextTick = SDL_GetTicks() + tickInterval;
}

// Element-funktioner
void Session::addElement(shared_ptr<Element> e)
{
	allElements.push_back(e);
}

void Session::removeElement(shared_ptr<Element> e)
{
	allElementsRemoved.push_back(e);
}

void Session::removeAllElements() {
	for (shared_ptr<Element> e : allElements) 
		allElementsRemoved.push_back(e);
 handleRemovedObjects();
}

void Session::checkUserInput() {
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
			for (shared_ptr<Element> e : allElements)
				if (shared_ptr<Button> b = dynamic_pointer_cast<Button>(e))
					b->mouseDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			for (shared_ptr<Element> e : allElements) {
				if (shared_ptr<Button> b = dynamic_pointer_cast<Button>(e)) {
					b->mouseUp(event);
				}
			}
				
					
			break;
		case SDL_KEYDOWN:
			for (shared_ptr<Element> e : allElements)
			{
				if (shared_ptr<Player> player = dynamic_pointer_cast<Player>(e))
				{
					switch (event.key.keysym.sym)
					{
					case SDLK_LEFT:
						player->moveLeft();
						break;
					case SDLK_RIGHT:
						player->moveRight();

						break;
					}
				}
			}
		case SDL_KEYUP:
			// for (Element *e : allElements) {
			// if (Player* player = dynamic_cast<Player*>(e))
			//}
			break;
			// OBS!! case mouseRight och mouseLeft
		}	// Switch
	}	// Inre while-loop
}

void Session::updateObjectsState() {
	// OBS!! Uppdatera med tick sen

	// Uppdaterar samtliga objekt
	for (shared_ptr<Element> e : allElements)
		if (shared_ptr<GameElement> gme = dynamic_pointer_cast<GameElement>(e))
			gme->tick();
}

void Session::checkForCollision() {
	/*
	// Kollisionskontroll för objekt
	for (Element *e : allElements)
	{
		if (Player *p = dynamic_cast<Player *>(e))
		{
			for (Elements *eOther : allElements)
			{
				if (Target *t = dynamic_cast<Target *>(eOther))
				{
					if (p->getRect().x == t->getRect().x && p->getRect().y == t->getRect().y)
					{
						std::cout << "KOLLISION" << std ::endl; // Hantering av kollision görs här
					}
				}
			}
		}
	}
	*/

}

void Session::handleAddedObjects() {
	// Lägger till nya objekt
	for (shared_ptr<Element> e : allElementsAdded)
		allElements.push_back(e);
	allElementsAdded.clear();
}


void Session::handleRemovedObjects() {

// Tar bort raderade objekt
for (shared_ptr<Element> e : allElementsRemoved)
{
	for (vector<shared_ptr<Element>>::iterator i = allElements.begin(); i != allElements.end();)
	{
		if (*i == e)
		{
			i = allElements.erase(i);
		}
		else
			i++;
	} // Inre for-loop
}	// Yttre for-loop
allElementsRemoved.clear();
}

void Session::drawObjects() {
	// Ritar ut objekten i det uppdaterade tillståndet
	SDL_RenderClear(sys.getRen());
	SDL_RenderCopy(sys.getRen(), sys.getTex(), NULL, NULL);

	for (shared_ptr<Element> e : allElements)
		e->draw();
	SDL_RenderPresent(sys.getRen());
}

void Session::handleDelay() {
	// Tid kontrolleras och fördröjning framkallas
	int delay = nextTick - SDL_GetTicks();
	if (delay > 0)
		SDL_Delay(delay);
}

	void Session::run()
	{
		while (!quit)
		{
			checkUserInput();
			updateObjectsState();
			checkForCollision();

			handleAddedObjects();
			handleRemovedObjects();
			drawObjects();
			handleDelay(); 
		}
	}

}