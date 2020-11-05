#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map; //el mapa de tiles
	Player *player; //el player
	Ball *ball;  //la bola
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;

	bool touchBallToPlayer(const glm::ivec2& posPlayer, const glm::ivec2& posBall, const glm::ivec2& sizeBall, const glm::ivec2& sizePlayer) const;

};


#endif // _SCENE_INCLUDE

