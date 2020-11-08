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
	setMenuState();
	MainMenu.init();
}

void Game::setMenuState() {
	levelAct = MENU_LVL;
	//scoreAct = 0;
	//playerLifes = 3; //Init number of lifes
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
	}
}

void Game::nextLevel() {
	//++levelAct; //Go to next level
	levelAct = 1;
	if (levelAct == 1) {//Num of total levels+1
		scene.init();
	}
	else {
		OutputDebugStringW(L"ELSE");
	}
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






