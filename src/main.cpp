#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"
#include "Player.h"
#include "Target.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <random>


using namespace game;

// Paths to resources
const std::string resPath = "../../resources/";
int scoreValue = 0;
const int maximumAmount = 5;
int counter = 0;

void renderGame();
void initiate();
int main();
//OBS!! Nu har det blivit en konsitg placering av klasser och funktioner för att de ska kunna hitta varandra

class LeftButton : public Button
{
public:
	LeftButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(100, 500, 100, 100, lbl, imgSrcUp, imgSrcDown) {}

	/*
	void Button::mouseDown(const SDL_Event &eve)
  	{
		//minska x-koordinaten för Player
	}
	void Button::mouseUp(const SDL_Event &eve)
  	{
		//stå still/inget
	}
	*/
};

class RightButton : public Button
{
public:
	RightButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(780, 500, 100, 100, lbl, imgSrcUp, imgSrcDown) {}
	/*
	void Button::mouseDown(const SDL_Event &eve)
  	{
		//öka x-koordinaten för Player
	}
	void Button::mouseUp(const SDL_Event &eve)
  	{
		//stå still/inget
	}
	*/
};


class CloseButton : public Button
{
public:
	CloseButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(10, 10, 50, 50, lbl, imgSrcUp, imgSrcDown) {}
	void perform(Button* source) {
		// Återställ countern
		counter = 0;

		// Stäng renderaren
		SDL_DestroyRenderer(sys.getRen());

		// Stäng sessionen och skapa en ny
		sys.getSession()->~Session();
		sys.setSession(new Session());

		// Kör main() på nytt
		main();
	}
};


class PlayButton : public Button
{
public:
	PlayButton(Label *lbl, const char *imgSrcUp, const char *imgSrcDown) : Button(420, 350, 180, 80, lbl, imgSrcUp, imgSrcDown) {}

	void perform(Button* source) {
		renderGame();
	}

};

void refreshRenderer(const char* imgSrc) {

	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));
	SDL_Surface *sur = IMG_Load(imgSrc);
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
	SDL_FreeSurface(sur);
}

// Initerar spelfönstret efter användaren klickat på PlayButton
void renderGame() {
	//vill man skapa ny session? - nej?
	//men vi vill rendera nytt fönster? - typ
	
	// OBS!! Vad händer med alla andra element? Raderas dem?
	// Stänger ner renderare
    SDL_DestroyRenderer(sys.getRen());

 	refreshRenderer((resPath + "images/space.png").c_str());

	Label *leftLbl = Label::getInstance(1, 1, 1, 1, "L", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});
	Label *rightLbl = Label::getInstance(1, 1, 1, 1, "R", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});
	Label *closeLbl = Label::getInstance(1, 1, 1, 1, "x", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	Button *leftButton = new LeftButton(leftLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/neonClicked.png").c_str());
	Button *rightButton = new RightButton(rightLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/neonClicked.png").c_str());
	Button *closeButton = new CloseButton(closeLbl, (resPath + "images/neon.png").c_str(), (resPath + "images/neonClicked.png").c_str());

	sys.getSession()->addElement(leftButton);
	sys.getSession()->addElement(rightButton);
	sys.getSession()->addElement(closeButton);

	// OBS!! Vill vi ha en X-knapp för att gå tillbaka till startsidan? Onödigt?

	std::string score = "Score: " + std::to_string(scoreValue);
	Label *scoreLbl = Label::getInstance(820, 10, 85, 35, score, TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	sys.getSession()->addElement(scoreLbl);

	Player *player = Player::getInstance(360, 440, 150, 150, (resPath + "images/hole.png").c_str());
	sys.getSession()->addElement(player);

	while(counter < maximumAmount) {
		int x = 120 + (std::rand() % ( 760 - 120 + 1 ));

		Target *target = Target::getInstance(x, 0, 100, 100, (resPath + "images/bg.png").c_str());
		sys.getSession()->addElement(target);
		counter++;
		// OBS!! Anropa någon slags delay
	}
}

// Startskärmen
void initiate() {

	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, 0));

	// Skapar en renderare
	refreshRenderer((resPath + "images/space.png").c_str());

	// OBS!! Hur får vi bra width+height och koordinatvärden på objekten?
	Label *title = Label::getInstance(360, 80, 300, 150, "The Game", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 50), {255, 10, 170});
	Label *playLbl = Label::getInstance(500, 150, 1, 1, "Play", TTF_OpenFont((resPath + "fonts/Arial.ttf").c_str(), 100), {255, 10, 170});

	Button *playButton = new PlayButton(playLbl, (resPath + "images/neonPlay.png").c_str(), (resPath + "images/neonPlayClicked.png").c_str());

	sys.getSession()->addElement(title);
	sys.getSession()->addElement(playButton);

}

int main()
{
	initiate();

	sys.getSession()->run();

	return 0;
}

