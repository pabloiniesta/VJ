#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


enum PlayerAnims
{
	MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT, STAND
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) //tileMapPos es la x/y dnde spawneará
{
	spritesheet.loadFromFile("images/pala.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(5);
	
		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.25f));
	
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25, 0.25f));

		sprite->setAnimationSpeed(STAND, 8);
		sprite->addKeyframe(STAND, glm::vec2(0.f, 0.f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sizePlayer = glm::ivec2(32, 32);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) //mover izq
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 4;
	    if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 4;
			sprite->changeAnimation(STAND);
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) //izq + arriba
		{
			posPlayer.y -= 4;
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.y += 4;
			}
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) //izq + abajo
		{
			posPlayer.y += 4;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.y -= 4;
			}
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) //mover der
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 4;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 4;
			sprite->changeAnimation(STAND);
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_UP)) //der + arriba
		{
			posPlayer.y -= 4;
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.y += 4;
			}
		}
		if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) //der + abajo
		{
			posPlayer.y += 4;
			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.y -= 4;
			}
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP)) //mover arriba
	{
		if (sprite->animation() != MOVE_UP)
			sprite->changeAnimation(MOVE_UP);
		posPlayer.y -= 4;
		if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y += 4;
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)) //mover abajo
	{	
		if (sprite->animation() != MOVE_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		posPlayer.y += 4;
		if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.y -= 4;
		}
	}
	else
	{
		sprite->changeAnimation(STAND);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

