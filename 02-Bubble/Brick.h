#ifndef _BRICK_INCLUDE
#define _BRICK_INCLUDE


#include "Sprite.h"



class Brick
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, char typebrick); //tilemappos la X y Y donde hara spawn
	void update(int deltaTime);
	void render();
	
	void colision();
	void setPosition(const glm::vec2& pos);

	glm::ivec2 posBrick;
	int hp;
	int points;
	
	

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;

};

#endif // _BRICK_INCLUDE
