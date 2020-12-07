#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <string>
#include <iostream>
#include "Texture.h"
#include "Constants.h"
#include "Scene.h"
#include <irrKlang.h>

using namespace std;
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();

void Game::playSound(const char*path, bool loop) {
	SoundEngine->play2D(path, loop);
}

void Game::stopSounds() {
	SoundEngine->stopAllSounds();
}



void Game::init()
{
	bPlay = true;
	state = 1;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	setMenuState();
	MainMenu.init();
	Scene::instance().init(1);
	gui.init();
	SoundEngine->play2D("sounds/menu.mp3", true);
	scoretotal = 0;
	moneytotal = 0;
}

void Game::setMenuState() {
	levelAct = MENU_LVL;
	scoreAct = 0;
	lifesAct = 3; //Init number of lifes
	//mSound->playMusic("sounds/menu.wav");
}
void Game::actualizarGui(int money, int score, int vidas, int stage) {
	gui.actualizarGui(money, score, vidas, stage, levelAct);
}
bool Game::update(int deltaTime) {
	if (levelAct == MENU_LVL) {  //Main menu
		MainMenu.update(deltaTime);
	}
	else {
		Scene::instance().update(deltaTime);
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (levelAct == MENU_LVL) { //Main menu
		MainMenu.render();
	}
	else if(levelAct == 1){
		Scene::instance().render();
		gui.render();
	}
	else if (levelAct == 2) {
		Scene::instance().render();
		gui.render();
	}
	else if (levelAct == 3) {
		Scene::instance().render();
		gui.render();
	}
}

int Game::getlevelAct() {
	return levelAct;
}

void Game::nextLevel(int lvl, int score, int money) {
	scoretotal += score;
	moneytotal += money;
	if (lvl == 0) {
		++levelAct; //Go to next level
		if (levelAct == 1) {//Num of total levels+1
			SoundEngine->stopAllSounds();
			SoundEngine->play2D("sounds/background.mp3", true);
			OutputDebugStringW(L"LEVEL1");
			Scene::instance().init(1);
		}
		else if (levelAct == 2) {
			OutputDebugStringW(L"LEVEL2");
			Scene::instance().init(2);
		}
		else if (levelAct == 3) {
			OutputDebugStringW(L"LEVEL3");
			Scene::instance().init(3);
		}
	}
}

void Game::winScreen() {
	setMenuState();
	MainMenu.activateWin(scoretotal,moneytotal);
	scoretotal = 0;
	moneytotal = 0;
}

void Game::loseScreen(int score) {
	scoretotal += score;
	setMenuState();
	MainMenu.activateGameOver(scoretotal);
	scoretotal = 0;
	moneytotal = 0;
}


void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}






