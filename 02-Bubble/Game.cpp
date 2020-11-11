#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include <string>
#include <iostream>
#include "Texture.h"
#include "Constants.h"

using namespace std;

//HOL1
void Game::init()
{
	bPlay = true;
	state = 1;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	levelAct = MENU_LVL;
	setMenuState();
	MainMenu.init();
	scene.init(1);
	gui.init();
}

void Game::setMenuState() {
	levelAct = MENU_LVL;
	scoreAct = 0;
	lifesAct = 3; //Init number of lifes
	//mSoundHelper->playMusic("sounds/menu.wav");
}

bool Game::update(int deltaTime) {
	if (levelAct == MENU_LVL) {  //Main menu

		MainMenu.update(deltaTime);
	}
	else {
		scene.update(deltaTime);
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (levelAct == MENU_LVL) { //Main menu
		MainMenu.render();
	}
	else {
		scene.render();
		gui.render();
	}
}

int Game::getlevelAct() {
	return levelAct;
}

void Game::nextLevel(int lvl) {
	if (lvl == 0) {
		++levelAct; //Go to next level
		if (levelAct == 1) {//Num of total levels+1
			scene.init(1);
		}
		else if (levelAct == 2) {
			scene.init(2);
		}
		else if (levelAct == 3) {
			scene.init(3);
		}
	}
	else if (lvl == 1) {
		levelAct = 1;
		scene.init(1);
	}
	else if (lvl == 2) {
		levelAct = 2;
		scene.init(2);
	}
	else if (lvl == 3) {
		levelAct = 3;
		scene.init(3);
	}
}

void Game::winScreen(int score, int money) {
	setMenuState();
	MainMenu.activateWin(score,money);
}

void Game::loseScreen(int score) {
	setMenuState();
	MainMenu.activateGameOver(score);
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






