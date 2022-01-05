#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"

#include <string>
#include <SDL2/SDL.h>

using namespace game;

// Paths to resources
const std::string resPath = "../../resources/";
int scoreValue = 0;

//OBS!! Nu har det blivit en konsitg placering av klasser och funktioner för att de ska kunna hitta varandra

class LeftButton : public Button
{
public:
	LeftButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(100, 500, 100, 100, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
	}
};

class RightButton : public Button
{
public:
	RightButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(780, 500, 100, 100, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
	}
};

void renderGame() {
	//vill man skapa ny session? - nej?
	//men vi vill rendera nytt fönster? - typ
	
	//OBS!! Vad händer med alla andra element? Raderas dem?
	// Stänger ner renderare
    SDL_DestroyRenderer(sys.getRen());
	// Skapar en renderare
	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));

	//OBS!! Duplicering av kod
	SDL_Surface *sur = IMG_Load((resPath + "images/space.jpg").c_str());
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
	SDL_FreeSurface(sur);

	Label *leftLbl = Label::getInstance(1, 1, 1, 1, "L", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});
	Label *rightLbl = Label::getInstance(1, 1, 1, 1, "R", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	Button *leftButton = new LeftButton(leftLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/neonClicked.png").c_str());
	Button *rightButton = new RightButton(rightLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/neonClicked.png").c_str());

	sys.getSession()->addElement(leftButton);
	sys.getSession()->addElement(rightButton);

	//OBS!! Vill vi ha en X-knapp för att gå tillbaka till startsidan? Onödigt?

	std::string score = "Score: " + std::to_string(scoreValue);
	Label *scoreLbl = Label::getInstance(820, 10, 85, 35, score, TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	sys.getSession()->addElement(scoreLbl);
}

class PlayButton : public Button
{
public:
	PlayButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(420, 350, 180, 80, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button *source)
	{
		/*
		SDL_Surface *sur = IMG_Load((resPath + "images/bg.jpg").c_str());
		sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
		SDL_FreeSurface(sur);
		// här ska playButton försvinna
		*/
		renderGame();
	}
};

void initiate() {
	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0));

	// Skapar en renderare
	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));

	SDL_Surface *sur = IMG_Load((resPath + "images/space.jpg").c_str());
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
	SDL_FreeSurface(sur);

	// OBS!! Hur får vi bra width+height och koordinatvärden på objekten?
	Label *title = Label::getInstance(360, 80, 300, 150, "The Game", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50), {255, 10, 170});
	Label *playLbl = Label::getInstance(500, 150, 1, 1, "Play", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	Button *playButton = new PlayButton(playLbl, (resPath + "images/neonPlay.png").c_str(), (resPath + "images/neonPlayClicked.png").c_str());

	sys.getSession()->addElement(title);
	sys.getSession()->addElement(playButton);
}

int main(int argc, char **argv)
{
	initiate();

	sys.getSession()->run();

	return 0;
}

