#include "Session.h"
#include "System.h"
#include "Player.h"
#include "Button.h"
#include "Target.h"
#include "Element.h"

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

void Session::addGameElement(shared_ptr<GameElement> gme)
{
	allGameElements.push_back(gme);
	allElements.push_back(gme);
}

int Session::noOfGameElements() {
	return allGameElements.size();
}

void Session::removeElement(shared_ptr<Element> e)
{
	allElementsRemoved.push_back(e);
}

void Session::removeGameElement(shared_ptr<GameElement> gme) {
	allGameElementsRemoved.push_back(gme);
	allElementsRemoved.push_back(gme);
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
	
	// Kollisionskontroll för objekt
	
	for (shared_ptr<Element> e : allElements)
	{
		if (shared_ptr<Player> p = dynamic_pointer_cast<Player>(e))
		{
			for (shared_ptr<Element> eOther : allElements)
			{
				if (shared_ptr<Target> t = dynamic_pointer_cast<Target>(eOther))
				{
					int playerMinX = p->getRect().x; 
					int playerMaxX = playerMinX + p->getRect().w;
					int targetMiddleX = t->getRect().x + (t->getRect().w/2);

					int y = p->getRect().y + (p->getRect().h*0.9);
					int targetY = t->getRect().y + t->getRect().h;
					int playerY = y % 5 == 0 ? y : y - (y % 5);

					//körs även om target inte har rätt koordinater
					/*
					if (playerMinX < targetMiddleX && targetMiddleX < playerMaxX && (targetY + 10) == (playerY - 10)) {
						SDL_Rect r = t->getRect();
						int h = r.h;
						int w = r.w;
						//int x = r.x;
						t->setHeight(h-5);
						t->setWidth(w-5);
						//t->setCoordinateX(x+2.5);
					}
					*/
					//blir ingen kollision när vi ändrar om rect
					if (!(t->hasCollided()) && playerMinX < targetMiddleX < playerMaxX && targetY == playerY)
					{
						t->setCollided(true);
						std::cout << "KOLLISION:" << "playerMinX: " << playerMinX << ", playerMaxX: " << playerMaxX << ", targetMiddleX: " << targetMiddleX << ", playerY :" << playerY << ", targetY: " << targetY << std ::endl; // Hantering av kollision görs här
						removeGameElement(t);
						scoreValue += 1000;
						scoreLbl->setText("Score: " + to_string(scoreValue));
					}
				}
			}
		}
	}
	
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

	for (shared_ptr<GameElement> gme : allGameElementsRemoved) {
		for (vector<shared_ptr<GameElement>>::iterator i = allGameElements.begin(); i != allGameElements.end();)
		{
			if (*i == gme)
			{		
				i = allGameElements.erase(i);
				std::cout << "One removed, status: " << noOfGameElements() << endl;
			}
			else
				i++;
		} // Inre for-loop
	} // Yttre for-loop
	allGameElementsRemoved.clear();
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
			// OBS!! Tagen från main
			addTarget();
			updateObjectsState();
			checkForCollision();
			handleAddedObjects();
			handleRemovedObjects();
			drawObjects();
			handleDelay(); 
		}
	}

}