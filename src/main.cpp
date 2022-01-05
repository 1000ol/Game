#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"

#include <string>
#include <SDL2/SDL.h>

using namespace game;

// Paths to resources
const std::string resPath = "../../resources/";

class PlayButton : public Button
{
public:
	PlayButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(230, 150, 200, 150, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
		SDL_Surface *sur = IMG_Load((resPath + "images/bg.jpg").c_str());
		sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
		SDL_FreeSurface(sur);
		// här ska playButton försvinna
	}
};

class LeftButton : public Button
{
public:
	LeftButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(260, 50, 100, 100, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
	}
};

class RightButton : public Button
{
public:
	RightButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(260, 50, 100, 100, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
	}
};

int main(int argc, char **argv)
{

	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0));

	// Skapar en renderare
	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));

	SDL_Surface *sur = IMG_Load((resPath + "images/space.jpg").c_str());
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
	SDL_FreeSurface(sur);

	Session *ses = sys.getSession();

	// OBS!! Hur får vi bra width+height och koordinatvärden på objekten?
	Label *title = Label::getInstance(260, 10, 120, 70, "The Game", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50), {255, 10, 170});
	Label *playLbl = Label::getInstance(230, 150, 50, 50, "Play", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50), {255, 10, 170});

	Button *playButton = new PlayButton(playLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/steel.jpg").c_str());

	ses->addElement(title);
	ses->addElement(playButton);

	ses->run();

	return 0;
}