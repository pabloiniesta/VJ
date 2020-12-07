#include "Brick.h"

void Brick::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, char typebrick)
{
	if (typebrick == 'r') { //ladrillo rojo, 1hp, 10 puntos
		spritesheet.loadFromFile("images/redbrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 10;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'r';
		sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'g') { //ladrillo verde, 2hp, 20 puntos
		spritesheet.loadFromFile("images/greenbrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 2;
		points = 20;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'g';
		sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'b') { //ladrillo azul, 3hp, 30 puntos
		spritesheet.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 3;
		points = 30;
		sizeBrick = glm::ivec2(32, 16);
		tipo = 'b';
		sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'k') { //Llave, 1hp, 0 puntos
		spritesheet.loadFromFile("images/key.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(32, 32);
		tipo = 'k';
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'A') { //Puerta A, 1hp, 0 puntos
		spritesheet.loadFromFile("images/metal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(16, 16);
		tipo = 'A';
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'B') { //Puerta B, 1hp, 0 puntos
		spritesheet.loadFromFile("images/metal.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(16, 16);
		tipo = 'B';
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'c') { //coin, 1hp, 100 dineros
		spritesheet.loadFromFile("images/coin.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 10;
		sizeBrick = glm::ivec2(32, 32);
		tipo = 'c';
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'd') { //diamond, 1hp, 200 dineros
		spritesheet.loadFromFile("images/diamond.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 20;
		sizeBrick = glm::ivec2(32, 32);
		tipo = 'd';
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'x') { //el atm, 1hp, cambia puntos a dineros
		spritesheet.loadFromFile("images/atm.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(32, 32);
		tipo = 'x';
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 't') { //timbre, 1hp, activa al malo
		spritesheet.loadFromFile("images/alarm.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(32, 32);
		tipo = 't';
		sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == '?') { //sorpresa, 1hp
		spritesheet.loadFromFile("images/interrogante.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 0;
		sizeBrick = glm::ivec2(16, 16);
		tipo = '?';
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
	else if (typebrick == 'm') { //moneda que cae, 1hp
		spritesheet.loadFromFile("images/centavo.png", TEXTURE_PIXEL_FORMAT_RGBA);
		hp = 1;
		points = 5;
		sizeBrick = glm::ivec2(16, 16);
		tipo = 'm';
		sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	}
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

void Brick::makegold(ShaderProgram& shaderProgram) {
	spritesheet.loadFromFile("images/goldbrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
	hp = 1;
	points = 10;
	tipo = 'o';
}

void Brick::breakbrick(ShaderProgram& shaderProgram)
{
	if (tipo == 'g') {
		spritesheet.loadFromFile("images/greenbrickbreak1.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
		sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
	}
	else if (tipo == 'b') {
		if (hp == 2) {
			spritesheet.loadFromFile("images/bluebrickbreak1.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
		}
		if (hp == 1){
			spritesheet.loadFromFile("images/bluebrickbreak2.png", TEXTURE_PIXEL_FORMAT_RGBA);
			sprite = Sprite::createSprite(glm::ivec2(32, 16), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBrick.x), float(tileMapDispl.y + posBrick.y)));
		}
	}
}
