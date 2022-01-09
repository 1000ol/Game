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

// Konstanta sökvägar till resurser för spelet
const string resPath = "resources/";
const string startBgSrc = "images/space.png";
const string gameBgSrc = "images/space.png";
const string fontSrc = "fonts/AllerDisplay.ttf";
const string playerSrc = "images/blackHole.png";
const string exitBtnSrc = "images/exit.png";
const string exitBtnClickedSrc = "images/exitClicked.png";
const string rightBtnSrc = "images/right.png";
const string rightBtnClickedSrc = "images/rightClicked.png";
const string leftBtnSrc = "images/left.png";
const string leftBtnClickedSrc = "images/leftClicked.png";
const string targetImages[] = {"images/astronaut.png", "images/alien.png", "images/asteroid.png", "images/bubblyPlanet.png", "images/purplePlanet.png", "images/redPlanet.png", "images/rocket.png", "images/rocketTwo.png", "images/ufo.png"};


// Konstanta variabler för spelet
const SDL_Color rgb = {240, 255, 255};
const int winWidth = 1200;
const int winHeight = 700;
const int fps = 80;
const int performance = 1000;
const int maxAmountTargets = 3;
const int smallBtnWidth = 50;
const int smallBtnHeight = 50;
const int mediumBtnWidth = 75;
const int mediumBtnHeight = 75;
const int scoreLblWidth = 85;
const int scoreLblHeight = 35;
const int playerWidth = 200;
const int playerHeight = 200;
const int playerMinX = winWidth*0.05 + mediumBtnWidth;
const int playerMaxX = winWidth*0.9 - playerWidth;

// Variabler för spelet
int tickCount = 0;
int scoreValue = 0;
string score = "Score: " + to_string(scoreValue);
bool gameRendered = false;

// Deklarerade funktioner
void initiateGameScreen();
void initiate();
int main();

class LeftButton : public Button
{
public:
	
	static shared_ptr<LeftButton>getInstance() 
	{
		return make_shared<LeftButton>();
	}
	// Måste implementera klickfunktionen
	// getPlayer()->moveLeft()

	LeftButton() : Button(winWidth*0.05, winHeight*0.8, mediumBtnWidth, mediumBtnHeight, (resPath +leftBtnSrc).c_str(), (resPath +leftBtnClickedSrc).c_str()) {}
};

class RightButton : public Button
{
public:
	
	static shared_ptr<RightButton>getInstance() {
		return make_shared<RightButton>();
	}
	// Måste implementera klickfunktionen
	// getPlayer()->moveRight()
	
	RightButton() : Button(winWidth*0.9, winHeight*0.8, mediumBtnWidth, mediumBtnHeight, 
	(resPath + rightBtnSrc).c_str(), (resPath + rightBtnClickedSrc).c_str()) {}
};

class CloseButton : public Button
{
public:
	static shared_ptr<CloseButton>getInstance() {
		return make_shared<CloseButton>();
	}

		CloseButton() : Button(winWidth*0.05, winHeight*0.07, smallBtnWidth, smallBtnHeight, (resPath + exitBtnSrc).c_str(), (resPath + exitBtnClickedSrc).c_str()) {}
	void perform(shared_ptr<Button> source)
	{	
		gameRendered = false;
		// Stäng renderaren
		SDL_DestroyRenderer(sys.getRen());

		// Stäng sessionen och skapa en ny
		sys.getSession()->~Session();
		sys.setSession(new Session());

		// Kör main() på nytt
		main();
	}
};

// Play-knapp som vid tryck startar spelet
class PlayButton : public Button {
public:

static shared_ptr<PlayButton>getInstance(int x, int y, int w, int h, const char* imgSrcUp, const char* imgSrcDown) {
		return make_shared<PlayButton>(x, y, w, h, imgSrcUp, imgSrcDown);
	}
	using Button::Button;

	void perform(shared_ptr<Button> source)
	{
		initiateGameScreen();
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
void initiateGameScreen()
{
	// Tar bort startsidan
	// Stänger ner renderare
	SDL_DestroyRenderer(sys.getRen());

	// Radera alla element från första fönstret
	sys.getSession()->removeAllElements();

	refreshRenderer((resPath + gameBgSrc).c_str());

	shared_ptr<Button> leftButton = LeftButton::getInstance();
	shared_ptr<Button> rightButton = RightButton::getInstance();
	shared_ptr<Button> closeButton = CloseButton::getInstance();
	shared_ptr<Label> scoreLbl = Label::getInstance(winWidth*0.8, winHeight*0.07, scoreLblWidth, scoreLblHeight, score, TTF_OpenFont((resPath + fontSrc).c_str(), 80), rgb);
	shared_ptr<Player> player = Player::getInstance(winWidth*0.3, winHeight*0.65, playerWidth, playerHeight, (resPath + playerSrc).c_str());
	
	sys.getSession()->addElement(leftButton);
	sys.getSession()->addElement(rightButton);
	sys.getSession()->addElement(closeButton);
	sys.getSession()->addElement(scoreLbl);
	sys.getSession()->addElement(player);

	gameRendered = true;


}

void addTarget() {
	tickCount++;

	if (gameRendered && sys.getSession()->noOfGameElements() < maxAmountTargets && tickCount % 953 == 1)
	{
		// Slumpa x-koordinaten
		int x = (int)winWidth*0.2 + (rand() % (int)((winWidth*0.65) - (winWidth*0.2 + 1)) - 100);

		// Slumpa target
		int i = rand() % 9;
		// Kontrollutskrift
		cout << i << " " << resPath + targetImages[i] << endl;

		shared_ptr<Target> target = Target::getInstance(x, 0, 100, 100, (resPath + targetImages[i]).c_str());
		sys.getSession()->addGameElement(target);
	}
} 

// Startskärmen
void initiate(const char* gameName, int lblWidth, int lblHeight, int pointSize, int playBtnWidth, int playBtnHght, std::string btnUpSrc, std::string btnDownSrc)
{
	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, 0));

	// Skapar en renderare
	refreshRenderer((resPath + startBgSrc).c_str());

	// Se om det är rätt version uppe
	shared_ptr<Label> versionLbl = Label::getInstance(1100, 670, 75, 25, "Version 1.2", TTF_OpenFont((resPath + fontSrc).c_str(), 100), rgb);
	
	shared_ptr<Label> title = Label::getInstance(winWidth/3, winHeight/7, lblWidth, lblHeight, gameName, TTF_OpenFont((resPath + fontSrc).c_str(), pointSize), rgb);
	shared_ptr<Button> playButton = PlayButton::getInstance((winWidth*0.4), (winHeight*0.6), playBtnWidth, playBtnHght, (resPath + btnUpSrc).c_str(), (resPath + btnDownSrc).c_str());

	sys.getSession()->addElement(versionLbl);
	sys.getSession()->addElement(title);
	//Playbutton msåte vara sist här för att for-loopen i Session.run() ska funka. Går detta att ordna på annat sätt?
	sys.getSession()->addElement(playButton);
}

int main()
{
	initiate("The Game", 380, 120, 350, 200, 100, "images/startUp.png", "images/startUpClicked.png");

	sys.getSession()->run();

	return 0;
}