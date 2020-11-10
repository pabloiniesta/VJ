#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// enemigo. persigue al jugador y no se va hasta que lo mata



class Enemy
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram); //tilemappos la X y Y donde hara spawn
	void render();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);


	glm::ivec2 posEnemy;
	glm::ivec2 sizeEnemy;

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;

};


#endif // enemy
