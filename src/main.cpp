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
// OBS!! Nu har det blivit en konsitg placering av klasser och funktioner för att de ska kunna hitta varandra

class LeftButton : public Button
{
public:
	LeftButton() : Button(75, 575, 75, 75, (resPath + "images/left.png").c_str(), (resPath + "images/left.png").c_str()) {}

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
	RightButton() : Button(1050, 575, 75, 75, (resPath + "images/right.png").c_str(), (resPath + "images/right.png").c_str()) {}
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
	CloseButton() : Button(50, 50, 50, 50, (resPath + "images/exit.png").c_str(), (resPath + "images/exit.png").c_str()) {}
	void perform(Button *source)
	{
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
	PlayButton() : Button(500, 300, 200, 100, (resPath + "images/startUp.png").c_str(), (resPath + "images/startUp.png").c_str()) {}

	void perform(Button *source)
	{
		renderGame();
	}
};

void refreshRenderer(const char *imgSrc)
{

	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));
	SDL_Surface *sur = IMG_Load(imgSrc);
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sur));
	SDL_FreeSurface(sur);
}

// Initerar spelfönstret efter användaren klickat på PlayButton
void renderGame()
{
	// vill man skapa ny session? - nej?
	// men vi vill rendera nytt fönster? - typ

	// OBS!! Vad händer med alla andra element? Raderas dem?
	// Stänger ner renderare
	SDL_DestroyRenderer(sys.getRen());

	refreshRenderer((resPath + "images/space.png").c_str());

	Button *leftButton = new LeftButton();
	Button *rightButton = new RightButton();
	Button *closeButton = new CloseButton();

	sys.getSession()->addElement(leftButton);
	sys.getSession()->addElement(rightButton);
	sys.getSession()->addElement(closeButton);

	// OBS!! Vill vi ha en X-knapp för att gå tillbaka till startsidan? Onödigt?

	std::string score = "Score: " + std::to_string(scoreValue);
	Label *scoreLbl = Label::getInstance(1020, 50, 85, 35, score, TTF_OpenFont((resPath + "fonts/AllerDisplay.ttf").c_str(), 100), {255, 10, 170});

	sys.getSession()->addElement(scoreLbl);

	Player *player = Player::getInstance(360, 450, 200, 200, (resPath + "images/blackHole.png").c_str());
	sys.getSession()->addElement(player);

	std::string targetImages[] = {"astronaut.png", "alien.png", "asteroid.png", "bubblyPlanet.png", "purplePlanet.png", "redPlanet.png", "rocket.png", "rocketTwo.png", "ufo.png"};

	while (counter < maximumAmount)
	{
		int x = 210 + (std::rand() % (780 - 210 + 1) - 100);

		int i = std::rand() % 9;
		std::cout << i << " " << resPath + targetImages[i] << std::endl;

		Target *target = Target::getInstance(x, 0, 100, 100, (resPath + "images/" + targetImages[i]).c_str());
		sys.getSession()->addElement(target);
		counter++;
		// OBS!! Anropa någon slags delay
	}
}

// Startskärmen
void initiate()
{

	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, 0));

	// Skapar en renderare
	refreshRenderer((resPath + "images/space.png").c_str());

	Label *title = Label::getInstance(425, 100, 350, 150, "The Game", TTF_OpenFont((resPath + "fonts/AllerDisplay.ttf").c_str(), 50), {255, 255, 255});

	Button *playButton = new PlayButton();

	sys.getSession()->addElement(title);
	sys.getSession()->addElement(playButton);
}

int main()
{
	initiate();

	sys.getSession()->run();

	return 0;
}
