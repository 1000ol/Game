#include <iostream>
#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"
#include <string>

// Alla dessa SDL inkluderingsfiler används inte i detta testprogram.
// Bifogas endast för test av SDL installation!

#include <SDL.h>			 //<SDL2/SDL.h>
#include <SDL_image.h> //<SDL2_image/SDL_image.h>
#include <SDL_mixer.h> //<SDL2_mixer/SDL_mixer.h>
#include <SDL_ttf.h>	 //<SDL2_ttf/SDL_ttf.h>

//#define FPS 60

using namespace std;
using namespace cwing;

// Paths to resources
std::string resPath = "../../resources/";

int value = 0;

class OkaKnapp : public Button
{
public:
	OkaKnapp(Label *lbl) : Button(100, 100, 150, 70, "Oka"), label(lbl) {}
	void perform(Button *source)
	{
		value++;
		label->setText(to_string(value));
	}

private:
	Label *label;
};

class MinskaKnapp : public Button
{
public:
	MinskaKnapp(Label *lbl) : Button(400, 100, 150, 70, "Minska"), label(lbl) {}
	void perform(Button *source)
	{
		value--;
		label->setText(to_string(value));
	}

private:
	Label *label;
};

int main(int argc, char **argv)
{
	Session ses;
	Label *lbl = Label::getInstance(270, 100, 100, 70, "0");
	ses.add(lbl);

	Button *b = new OkaKnapp(lbl);
	ses.add(b);
	Button *b2 = new MinskaKnapp(lbl);
	ses.add(b2);

	ses.run();

	return 0;
}