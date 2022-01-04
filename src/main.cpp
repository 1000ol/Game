#include <iostream>
#include <string>
#include <SDL.h>			 
#include <SDL_image.h> 
#include <SDL_mixer.h> 
#include <SDL_ttf.h>
#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"


using namespace std;
using namespace game;

// Paths to resources
std::string resPath = "../../resources/";

// OBS!! Ändra till eget content
int value = 10;

// OBS!! Ändra till eget content
class OkaKnapp : public Button
{
public:
	OkaKnapp(Label *lbl) : Button(100, 100, 150, 70, "Oka"), label(lbl) {}
	void perform(Button *source)
	{
		value++;
		label->setText(to_string(value));
		label->draw();
	}

private:
	Label *label;
};

// OBS!! Ändra till eget content
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

	// OBS!! Fönstret är 600 bredd 400 i höjd
	Session ses;

	Label *lbl = Label::getInstance(270, 20, 100, 70, "10");
	ses.add(lbl);
	//Button *b = new OkaKnapp(lbl);
	//ses.add(b);
//	Button *b2 = new MinskaKnapp(lbl);
//	ses.add(b2);
	ses.run();

	return 0;
}