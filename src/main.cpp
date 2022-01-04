#include <string>
#include <SDL2/SDL.h>

#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"

using namespace game;

// Paths to resources
extern const std::string resPath = "../../resources/";

// OBS!! Ändra till eget content
int value = 0;

// OBS!! Ändra till eget content
class PlayKnapp : public Button
{
public:
	PlayKnapp(Label *lbl) : Button(260, 50, 100, 100, lbl->getText()), label(lbl) {}
	void perform(Button *source)
	{
		value++;
		label->setText(std::to_string(value));
	}

private:
	Label *label;
};

// OBS!! Ändra till eget content
class MinskaKnapp : public Button
{
public:
	MinskaKnapp(Label *lbl) : Button(260, 50, 150, 150, "Minska"), label(lbl) {}
	void perform(Button *source)
	{
		value--;
		label->setText(std::to_string(value));
	}

private:
	Label *label;
};

int main(int argc, char **argv)
{

	// OBS!! Fönstret är 600 bredd 400 i höjd
	Session *ses = sys.getSession();

	// OBS!! Hur får vi bra width+height och koordinatvärden på objekten?
	Label *titel = Label::getInstance(260, 10, 120, 70, "The Game");
	Label *playLbl = Label::getInstance(260, 50, 50, 50, "Play");

	Button *playButton = new PlayKnapp(playLbl);

	ses->add(titel);
	ses->add(playButton);

	/*
ses->add(lbl);
Button *b = new OkaKnapp(lbl);
ses->add(b);
Button *b2 = new MinskaKnapp(lbl);
ses->add(b2);
*/

	ses->run();

	return 0;
}