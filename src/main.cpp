#include "Label.h"
#include "System.h"
#include "Button.h"
#include "Element.h"
#include "GameElement.h"

#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <random>

using namespace std;

using namespace gameEngine;

// Konstanta sökvägar till resurser för spelet
const string resPath = "../../resources/";
const string startBgSrc = "images/space.png";
const string gameBgSrc = "images/space.png";
const string fontSrc = "fonts/AllerDisplay.ttf";
const string musicSrc = "sounds/found-in-space.wav";
const string startButton = "images/startUp.png";
const string startButtonClicked = "images/startUpClicked.png";
const string playerSrc = "images/blackHole.png";
const string exitBtnSrc = "images/exit.png";
const string exitBtnClickedSrc = "images/exitClicked.png";
const string targetImages[] = {"images/astronaut.png", "images/alien.png", "images/asteroid.png", "images/bubblyPlanet.png", "images/purplePlanet.png", "images/redPlanet.png", "images/rocket.png", "images/rocketTwo.png", "images/ufo.png"};


// Konstanta variabler för spelet
const char* gameName = "The Void";
const string gamePrompt = "A black hole gets them all! Are you up for the challenge?";
const SDL_Color rgb = {240, 255, 255};
const int winWidth = 1200;
const int winHeight = 700;
const int fps = 80;
const int performance = 1000;
const int smallBtnWidth = 50;
const int smallBtnHeight = 50;
const int mediumBtnWidth = 75;
const int mediumBtnHeight = 75;
const int scoreLblWidth = 85;
const int scoreLblHeight = 35;
const int gameOverLblWidth = 380;
const int gameOverLblHeight = 150;
const int playerWidth = 200;
const int playerHeight = 200;
const int playAreaMinX = winWidth * 0.05 + mediumBtnWidth;
const int playAreaMaxX = winWidth * 0.95 - playerWidth;

// Icke-konstanta variabler för spelet
int targetX = playAreaMinX + (rand() % (playAreaMaxX - playAreaMinX + 1));
int tickCount = 0;
int targetImgIndex = (rand() % (sizeof(targetImages) / sizeof(targetImages[0])));

// Deklarerar klasser så att dessa kan nås i klassdefinitionerna 
class Target;
class Player;


// Deklarerade funktioner
void initiateGameScreen();
int main();

shared_ptr<Player> player;

class Target : public GameElement, public enable_shared_from_this<Target>
{
public:
	static shared_ptr<Target> getInstance() {
		return make_shared<Target>();
	};

// Konstruktor
	Target() : GameElement(targetX, 0, 100, 100, (resPath + targetImages[targetImgIndex]).c_str())
	{
	setAutogenerated();
	SDL_Surface *surf = IMG_Load(getImageSource());
	setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
	SDL_FreeSurface(surf);
	};

	void tick()
	{
		pace++;
		if (pace % 5 == 0)
			setCoordinateY((getRect().y + 7));
		if (hasCollided())
		{	
			SDL_Rect r = getRect();
			setWidth(r.w - 3);
			setHeight(r.h - 3);
			setCoordinateX(r.x + 1.5);
			setCoordinateY(r.y + 8);

			if (r.w == 0 && r.h == 0)
				collide();
		}
	};

	void collide()
	{
		shared_ptr<GameElement> t = dynamic_pointer_cast<GameElement>(shared_from_this());
		sys.getSession()->removeElement(t);
	};

	~Target()
	{
		if (!hasCollided())
		{
			shared_ptr<Label> gameOverLbl = Label::getInstance((winWidth / 3), (winHeight / 4), gameOverLblWidth, gameOverLblHeight, "Game Over", sys.getFont(), rgb);
			sys.getSession()->addElement(gameOverLbl);
		}
	};

	private:
	int pace = 0;
};

class Player : public GameElement
{
public:
	static shared_ptr<Player> getInstance(int x, int y, int w, int h, const char *imgSrc)
	{
	return make_shared<Player>(x, y, w, h, imgSrc);
	};

// Konstruktor
	Player(int x, int y, int w, int h, const char *imgSrc) : GameElement(x, y, w, h, imgSrc)
	{
	setIsUserControlled();
	SDL_Surface *surf = IMG_Load(getImageSource());
	setTexture(SDL_CreateTextureFromSurface(sys.getRen(), surf));
	SDL_FreeSurface(surf);
	};

	void keyDown(const SDL_Event &e)
	{
		int x = getRect().x;
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			if (x < playAreaMinX)
				setCoordinateX(playAreaMinX);
			else
				setCoordinateX(x - 40);
			break;
		case SDLK_RIGHT:
			if (x > playAreaMaxX)
				setCoordinateX(playAreaMaxX);
			else
				setCoordinateX(x + 40);
			break;
		}
	};
	void tick()
	{
		if (hasCollided() && countedCollisions != getCollisions())
			collide();		
	};

	void collide()
	{
		score = getCollisions() * 100;
		countedCollisions = getCollisions();
		targetX = playAreaMinX + (rand() % (playAreaMaxX - playAreaMinX + 1));
		targetImgIndex = (rand() % (sizeof(targetImages) / sizeof(targetImages[0])));
		shared_ptr<Target> newTarget = Target::getInstance();
		sys.getSession()->addElement(newTarget);
	};

	int getScore()
	{
		return score;
	};


	private:
	int score = 0;
	int countedCollisions = 0;
};


class CloseButton : public Button
{
public:
	static shared_ptr<CloseButton> getInstance()
	{
		return make_shared<CloseButton>();
	};

		// Konstruktor
	CloseButton() : Button(winWidth * 0.05, winHeight * 0.07, smallBtnWidth, smallBtnHeight, (resPath + exitBtnSrc).c_str(), (resPath + exitBtnClickedSrc).c_str()) {};
	
	void perform(shared_ptr<Button> source)
	{
		// Stäng renderaren
		SDL_DestroyRenderer(sys.getRen());

		// Stäng sessionen och skapa en ny, alla element raderas
		sys.getSession()->~Session();
		sys.setSession(new Session());

		// Kör main() på nytt
		main();
	};

};

// Play-knapp som vid tryck startar spelet
class PlayButton : public Button
{
public:
	static shared_ptr<PlayButton> getInstance(int x, int y, int w, int h, const char *imgSrcUp, const char *imgSrcDown)
	{
		return make_shared<PlayButton>(x, y, w, h, imgSrcUp, imgSrcDown);
	};

		// Eftersom klassens konstruktor inte kräver ytterligare parameterargument utöver sin superklass så använder det superklassens konstruktor genom följande anrop
	using Button::Button;


	void perform(shared_ptr<Button> source)
	{
		initiateGameScreen();
	};


};

class ScoreLabel : public Label
{
public:
	static shared_ptr<ScoreLabel> getInstance(int x, int y, int w, int h, TTF_Font *fnt, SDL_Color clr)
	{
		return make_shared<ScoreLabel>(x, y, w, h, fnt, clr);
	};

	// Konstruktor
	ScoreLabel(int x, int y, int w, int h, TTF_Font *fnt, SDL_Color clr) : Label(x, y, w, h, "Score:      ", fnt, clr) {};

	void tick()
	{
		setText("Score: " + to_string(player->getScore()));
	};

};

void refreshRenderer(const char *imgSrc)
{
	sys.setRen(SDL_CreateRenderer(sys.getWin(), -1, 0));
	sys.setSurf(IMG_Load(imgSrc));
	sys.setTex(SDL_CreateTextureFromSurface(sys.getRen(), sys.getSurf()));
	SDL_FreeSurface(sys.getSurf());
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

	shared_ptr<Button> closeButton = CloseButton::getInstance();
	shared_ptr<Label> scoreLbl = ScoreLabel::getInstance(winWidth * 0.85, winHeight * 0.07, scoreLblWidth, scoreLblHeight, sys.getFont(), rgb);
	player = Player::getInstance(winWidth * 0.3, winHeight * 0.65, playerWidth, playerHeight, (resPath + playerSrc).c_str());
	shared_ptr<Target> target = Target::getInstance();

	sys.getSession()->addElement(closeButton);
	sys.getSession()->addElement(scoreLbl);
	sys.getSession()->addElement(player);
	sys.getSession()->addElement(target);

}

// Initierar startfönstret för spelet
void initiate(const char *gameName, int lblWidth, int lblHeight, int pointSize, int playBtnWidth, int playBtnHght, string btnUpSrc, string btnDownSrc)
{
	// Skapar ett fönster
	sys.setWin(SDL_CreateWindow(gameName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winWidth, winHeight, 0));

	sys.setTickInterval(performance, fps);

	sys.setMusic((resPath + musicSrc).c_str());

	sys.setFont((resPath + fontSrc).c_str(), pointSize);

	// Skapar en renderare
	refreshRenderer((resPath + startBgSrc).c_str());

	shared_ptr<Label> title = Label::getInstance(winWidth / 3, winHeight / 7, lblWidth, lblHeight, gameName, sys.getFont(), rgb);
	shared_ptr<Label> instruction = Label::getInstance(winWidth * 0.18, winHeight / 3, 800, lblHeight/3, gamePrompt, sys.getFont(), rgb);

	shared_ptr<Button> playButton = PlayButton::getInstance((winWidth * 0.42), (winHeight * 0.6), playBtnWidth, playBtnHght, (resPath + btnUpSrc).c_str(), (resPath + btnDownSrc).c_str());

	sys.getSession()->addElement(title);
	sys.getSession()->addElement(instruction);
	sys.getSession()->addElement(playButton);
}

int main()
{
	initiate(gameName, 380, 120, 350, 200, 100, startButton, startButtonClicked);

	sys.getSession()->run();

	return 0;
}