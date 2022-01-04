#include "Component.h"

// Behövs dessa tomma konstruktorer/destruktorer här?
namespace game
{

	Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
	{
	}

	Component::~Component()
	{
	}
}