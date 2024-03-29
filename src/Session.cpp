#include "Session.h"
#include "System.h"

#include <iostream>
#include <memory>

using namespace std;

namespace gameEngine
{

	// Konstruktor som sätter 
	Session::Session()
	{
		nextTick = SDL_GetTicks() + sys.getTickInterval();
	}

	// Förbereder för att lägga till element
	void Session::addElement(shared_ptr<Element> e)
	{
		allElementsAdded.push_back(e);
	}

	// Förbereder för att ta bort element
	void Session::removeElement(shared_ptr<Element> e)
	{
		allElementsRemoved.push_back(e);
	}

	// Förbereder för att ta bort ALLA element
	void Session::removeAllElements()
	{
		for (shared_ptr<Element> e : allElements)
			allElementsRemoved.push_back(e);
	}

	// Kontrollerar användargenererade händelser och anropar objektens metoder för dessa kommandon
	void Session::checkUserInput()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (shared_ptr<Element> e : allElements)
					e->mouseDown(event);
				break;
			case SDL_MOUSEBUTTONUP:
				for (shared_ptr<Element> e : allElements)
					e->mouseUp(event);
				break;
			case SDL_KEYDOWN:
				for (shared_ptr<Element> e : allElements)
					e->keyDown(event);
				break;
			case SDL_KEYUP:
				for (shared_ptr<Element> e : allElements)
					e->keyUp(event);
				break;
			}
		}
	}

	// Uppdaterar samtliga objekt
	void Session::updateObjectsState()
	{
		for (shared_ptr<Element> e : allElements)
			e->tick();
	}

	// Kontrollerar spelobjektens uppdaterade x-och ykoordinater och tar bort objekt som hamnat utanför skärmen
	void Session::checkObjectsState()
	{
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0, &dm);
		int w = dm.w;
		int h = dm.h;
		for (shared_ptr<Element> e : allElements)
		{
			if (shared_ptr<GameElement> g = dynamic_pointer_cast<GameElement>(e))
			{
				SDL_Rect rect = g->getRect();
				int x = rect.x;
				int y = rect.y;
				if (x > w || x < 0 || y > h || y < 0)
					removeElement(g);
			}
		}
	}

	// Kollisionskontroll för objekt
	void Session::checkForCollision()
	{
		for (size_t i = 0; i < allElements.size(); i++)
		{
			if (shared_ptr<GameElement> g = dynamic_pointer_cast<GameElement>(allElements.at(i)))
			{
				for (size_t j = i; j < allElements.size(); j++)
				{
					if (shared_ptr<GameElement> gOther = dynamic_pointer_cast<GameElement>(allElements.at(j)))
					{
						const SDL_Rect *gRect = &g->getRect();
						const SDL_Rect *gOtherRect = &gOther->getRect();
						if (g != gOther && SDL_HasIntersection(gRect, gOtherRect) == SDL_TRUE && !(g->hasCollided() && gOther->hasCollided()))
						{
							gOther->setHasCollided(true);
							g->setHasCollided(true);
						}
					}
				}
			}
		}
	}

	// Lägger till nya objekt
	void Session::handleAddedObjects()
	{
		for (shared_ptr<Element> e : allElementsAdded)
			allElements.push_back(e);
		allElementsAdded.clear();
	}

	// Tar bort raderade objekt
	void Session::handleRemovedObjects()
	{
		for (shared_ptr<Element> e : allElementsRemoved)
		{
			for (vector<shared_ptr<Element>>::iterator i = allElements.begin(); i != allElements.end();)
			{
				if (*i == e)
					i = allElements.erase(i);
				else
					i++;
			}
		}
		allElementsRemoved.clear();
	}

	// Ritar ut objekten i det uppdaterade tillståndet
	void Session::drawObjects()
	{
		SDL_RenderClear(sys.getRen());
		SDL_RenderCopy(sys.getRen(), sys.getTex(), NULL, NULL);

		for (shared_ptr<Element> e : allElements)
			e->draw();
		SDL_RenderPresent(sys.getRen());
	}

	// Tid kontrolleras och fördröjning framkallas
	void Session::handleDelay()
	{
		int delay = nextTick - SDL_GetTicks();
		if (delay > 0)
			SDL_Delay(delay);
	}

	void Session::run()
	{
		while (!quit)
		{
			checkUserInput();
			checkObjectsState();
			updateObjectsState();
			checkForCollision();
			handleAddedObjects();
			handleRemovedObjects();
			drawObjects();
			handleDelay();
		}
	}
}