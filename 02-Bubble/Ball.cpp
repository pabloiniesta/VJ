#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"



const glm::ivec2 INITIAL_BALL_VELOCITY(3, 3); //vel de bola -> si X pos mov derecha
											   // si Y es pos se va para abajo



void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)//tileMapPos es la x/y dnde spawneará
{

	spritesheet.loadFromFile("images/ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	//asignamos velocidad inicial a la bola
	velBall.x = INITIAL_BALL_VELOCITY.x;
	velBall.y = INITIAL_BALL_VELOCITY.y;
	tileMapDispl = tileMapPos;
	radi = 8;
	isSticky = true;
	sizeBall = glm::ivec2(16, 16);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));

}

void Ball::update(int deltaTime)
{
	sprite->update(deltaTime);
	//calcular movimiento de bola
	if (!isSticky) { //si no esta enganchada al player
		posBall.x += velBall.x;
		if (map->collisionMoveLeft(posBall, glm::ivec2(16, 16))) { //colision por la izq
			posBall.x -= velBall.x; //deshacemos mov
			velBall.x = -velBall.x; //cambiamos de dir
		}
		else if (map->collisionMoveRight(posBall, glm::ivec2(16, 16))) { //colision por la der
			posBall.x -= velBall.x;
			velBall.x = -velBall.x;
		}

		posBall.y += velBall.y;
		if (map->collisionMoveUp(posBall, glm::ivec2(16, 16))) { //colision arriba
			posBall.y -= velBall.y; //deshacemos mov
			velBall.y = -velBall.y; //cambiamos de dir
		}
		else if (map->collisionMoveRight(posBall, glm::ivec2(16, 16))) { //colision por la der
			posBall.y -= velBall.y;
			velBall.y = -velBall.y;
		}
	}
	else { //enganchada al player
		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT)) //mover izq
		{
			posBall.x -= 4;
			if (map->collisionMoveLeft(posBall, glm::ivec2(32, 32)))posBall.x += 4;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))isSticky = false;
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))isSticky = false;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) //mover der
		{
			posBall.x += 4;
			if (map->collisionMoveRight(posBall, glm::ivec2(32, 32)))posBall.x -= 4;
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))isSticky = false;
			if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))isSticky = false;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) isSticky = false;
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) isSticky = false;
		else if (Game::instance().getKey(32))isSticky = false; //le das al space
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}

void Ball::render()
{
	sprite->render();
}

void Ball::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Ball::setPosition(const glm::vec2& pos)
{
	posBall = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));
}


