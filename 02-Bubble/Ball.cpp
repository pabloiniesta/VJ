#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Ball.h"
#include "Game.h"


#define RADI 12.5f
const glm::ivec2 INITIAL_BALL_VELOCITY(3, 3); //vel de bola -> si X pos mov derecha
											   // si Y es pos se va para abajo



void Ball::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)//tileMapPos es la x/y dnde spawneará
{
	
	spritesheet.loadFromFile("images/ball.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	//asignamos velocidad inicial a la bola
	velX = INITIAL_BALL_VELOCITY.x;
	velY = INITIAL_BALL_VELOCITY.y;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBall.x), float(tileMapDispl.y + posBall.y)));

}

void Ball::update(int deltaTime)
{
	sprite->update(deltaTime);
	//calcular movimiento de bola
	posBall.x += velX;
	if (map->collisionMoveLeft(posBall, glm::ivec2(16, 16))){ //colision por la izq
		posBall.x -= velX; //deshacemos mov
		velX = -velX; //cambiamos de dir
	}
	else if (map->collisionMoveRight(posBall, glm::ivec2(16, 16))) { //colision por la der
		posBall.x -= velX;
		velX = -velX;
	}
	
	posBall.y += velY;
	if (map->collisionMoveUp(posBall, glm::ivec2(16, 16))) { //colision arriba
		posBall.y -= velY; //deshacemos mov
		velY = -velY; //cambiamos de dir
	}
	else if (map->collisionMoveRight(posBall, glm::ivec2(16, 16))) { //colision por la der
		posBall.y -= velY;
		velY = -velY;
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

