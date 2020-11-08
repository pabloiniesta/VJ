#include "Brick.h"

void Brick::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, char typebrick)
{
	if (typebrick == 'r') { //ladrillo rojo, 1hp, 10 puntos
		spritesheet.loadFromFile("images/redbrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 10;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'r';
	}
	else if (typebrick == 'g') { //ladrillo verde, 2hp, 20 puntos
		spritesheet.loadFromFile("images/greenbrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 2;
		points = 20;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'g';
	}
	else if (typebrick == 'b') { //ladrillo azul, 3hp, 30 puntos
		spritesheet.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 3;
		points = 30;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'b';
	}
	sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
}

void Brick::update(int deltaTime)
{
}

void Brick::render()
{
	sprite->render();
}


void Brick::colision()
{
	this->hp -= 1;
}

void Brick::setPosition(const glm::vec2& pos)
{
	posBrick = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
}

