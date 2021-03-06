#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "Scene.h"
#include "Texture.h"
#include "Menu.h"
#include "GUI.h"


#define SCREEN_WIDTH 640 //640
#define SCREEN_HEIGHT 480 //480


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void playSound(const char * path, bool loop);

	void stopSounds();
	void actualizarGui(int money, int score, int vidas, int stage);
	void init();
	void setMenuState();
	bool update(int deltaTime);
	void render();
	int getlevelAct();
	void nextLevel(int lvl, int score, int money);
	void winScreen();
	void loseScreen(int score);
	void state_handler(int prev_state, int fut_state);
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	void newaction(int act);
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;                       // Continue to play game?
	bool keys[256], specialKeys[256]; // Store key states so that 
	                                  // we can have access at any time
	int state;						  // 1 = menu, 2 = instructions, 3 = credits, 4 = play
	Menu MainMenu;
	GUI gui;
	int levelAct;
	int scoreAct;
	int lifesAct;
	int scoretotal;
	int moneytotal;
};


#endif // _GAME_INCLUDE


