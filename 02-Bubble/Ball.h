#ifndef _BALL_INCLUDE
#define _BALL_INCLUDE


#include "Sprite.h"
#include "TileMap.h"

class Ball
{
public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram); //tilemappos la X y Y donde hara spawn
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
 
	int velX, velY;
	glm::ivec2 posBall;

private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};







#endif // _BALL_INCLUDE