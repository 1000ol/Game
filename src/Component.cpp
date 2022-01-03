#include "Component.h"

using namespace std;

namespace cwing
{

	Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
	{
	}

	Component::~Component()
	{
	}
}