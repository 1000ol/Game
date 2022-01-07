#include "Label.h"
#include "Session.h"
#include "Button.h"
#include "System.h"
#include "Player.h"
#include "Target.h"
#include "Element.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

using namespace std;

using namespace gameEngine;

// Paths to resources
const std::string resPath = "../../resources/";
int scoreValue = 0;
const int maximumAmount = 5;
int counter = 0;
int fps = 80;
int performance = 1000;

void renderGame();
void initiate();
int main();
// OBS!! Nu har det blivit en konsitg placering av klasser och funktioner för att de ska kunna hitta varandra

class LeftButton : public Button
{
public:
	
	static shared_ptr<LeftButton>getInstance() 
	{
		return make_shared<LeftButton>();
	}

	LeftButton() : Button(75, 575, 75, 75, (resPath + "images/left.png").c_str(), (resPath + "images/leftClicked.png").c_str()) {}
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
	
	static shared_ptr<RightButton>getInstance() 
	{
		return make_shared<RightButton>();
	}

	RightButton() : Button(1050, 575, 75, 75, (resPath + "images/right.png").c_str(), (resPath + "images/rightClicked.png").c_str()) {}
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
	static shared_ptr<CloseButton>getInstance() {
		return make_shared<CloseButton>();
	}

		CloseButton() : Button(50, 50, 50, 50, (resPath + "images/exit.png").c_str(), (resPath + "images/exitClicked.png").c_str()) {}
	void perform(shared_ptr<Button> source)
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

static shared_ptr<PlayButton>getInstance() {
		return make_shared<PlayButton>();
	}

		PlayButton() : Button(500, 300, 200, 100, (resPath + "images/startUp.png").c_str(), (resPath + "images/startUpClicked.png").c_str()) {}

	void perform(shared_ptr<Button> source)
	{

		std::cout << "Initierar renderGame()" << std::endl;
		renderGame();
		std::cout << "Tillbaka i perform(), funktionen avslutas" << std::endl;

		//Problemet med bad access i Session är att vi raderar objektet när vi är inne i en av objektets funktioner
		//vi kommer alltså inte ut
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
	std::cout << "I början av renderGame()" << std::endl;
	// OBS!! Vad händer med alla andra element? Raderas dem?
	// Stänger ner renderare
	SDL_DestroyRenderer(sys.getRen());

	// Radera alla element från första fönstret
	sys.getSession()->removeAllElements();

	refreshRenderer((resPath + "images/space.png").c_str());

	shared_ptr<Button> leftButton = LeftButton::getInstance();
	shared_ptr<Button> rightButton = RightButton::getInstance();
	shared_ptr<Button> closeButton = CloseButton::getInstance();

	sys.getSession()->addElement(leftButton);
	sys.getSession()->addElement(rightButton);
	sys.getSession()->addElement(closeButton);

	// OBS!! Vill vi ha en X-knapp för att gå tillbaka till startsidan? Onödigt?

	std::string score = "Score: " + std::to_string(scoreValue);
	shared_ptr<Label> scoreLbl = Label::getInstance(1020, 50, 85, 35, score, TTF_OpenFont((resPath + "fonts/AllerDisplay.ttf").c_str(), 100), {255, 10, 170});

	sys.getSession()->addElement(scoreLbl);

	shared_ptr<Player> player = Player::getInstance(360, 450, 200, 200, (resPath + "images/blackHole.png").c_str());
	sys.getSession()->addElement(player);

	std::string targetImages[] = {"astronaut.png", "alien.png", "asteroid.png", "bubblyPlanet.png", "purplePlanet.png", "redPlanet.png", "rocket.png", "rocketTwo.png", "ufo.png"};

	while (counter < maximumAmount)
	{
		int x = 210 + (std::rand() % (780 - 210 + 1) - 100);

		int i = std::rand() % 9;
		std::cout << i << " " << resPath + targetImages[i] << std::endl;

		shared_ptr<Target> target = Target::getInstance(x, 0, 100, 100, (resPath + "images/" + targetImages[i]).c_str());
		sys.getSession()->addElement(target);
		counter++;
		// OBS!! Anropa någon slags delay
	}
	std::cout << "Ingen mer aktivitet i renderGame()" << std::endl;	
}

// Startskärmen
void initiate()
{
	
	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, 0));

	// Skapar en renderare
	refreshRenderer((resPath + "images/space.png").c_str());

	// Se om det är rätt version uppe
	shared_ptr<Label> versionLbl = Label::getInstance(1100, 670, 75, 25, "Version 1.5", TTF_OpenFont((resPath + "fonts/AllerDisplay.ttf").c_str(), 100), {255, 255, 255});
	sys.getSession()->addElement(versionLbl);
	
	shared_ptr<Label> title = Label::getInstance(425, 100, 350, 150, "The Game", TTF_OpenFont((resPath + "fonts/AllerDisplay.ttf").c_str(), 20), {255, 255, 255});

	shared_ptr<Button> playButton = PlayButton::getInstance();

	sys.getSession()->addElement(title);
	//Playbutton msåte vara sist här för att for-loopen i Session.run() ska funka. Går detta att ordna på annat sätt?
	sys.getSession()->addElement(playButton);
}

int main()
{
	initiate();

	sys.getSession()->run();

	return 0;
}
