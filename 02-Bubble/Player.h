#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.



class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram); //tilemappos la X y Y donde hara spawn
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


	glm::ivec2 posPlayer;
	
private:
	glm::ivec2 tileMapDispl;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _PLAYER_INCLUDE


