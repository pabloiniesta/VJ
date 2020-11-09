#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void show_menu();
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
	vector<Brick> bricks;
	float cameraYPos;


	pair<bool, pair<Direction, glm::ivec2>> CheckCollisionBallObject(Ball& one, Brick& two); //mirar colision bola con objeto
	pair<bool, pair<Direction, glm::ivec2>> CheckCollisionBallPlayer(Ball& one, Player& two);//params-> colision?, Direction para dir colision, ivec2 = dist entre los 2

																								
	Direction VectorDirection(glm::vec2 target);
};


#endif // _SCENE_INCLUDE

