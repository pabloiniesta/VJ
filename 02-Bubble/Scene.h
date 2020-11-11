#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "Enemy.h"


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
	Scene() {}


	static Scene& instance()
	{
		static Scene S;

		return S;
	}

	void init(int lvl);
	void update(int deltaTime);
	void render();

private:
	void initShaders();

private:
	TileMap *map; //el mapa de tiles
	Player *player; //el player
	Ball *ball;  //la bola
	Enemy *enemy;  //el malo
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	vector<Brick> bricks;
	float cameraYPos;
	int stage;
	int door;
	int vidas;
	int puntuacion;
	int dinero;
	int loot;
	bool enemigoActivo;
	bool random;
	bool gold;


	pair<bool, pair<Direction, glm::ivec2>> CheckCollisionBallObject(Ball& one, Brick& two); //mirar colision bola con objeto
	pair<bool, pair<Direction, glm::ivec2>> CheckCollisionBallPlayer(Ball& one, Player& two);//params-> colision?, Direction para dir colision, ivec2 = dist entre los 2
	bool CheckCollisionEnemyPlayer(Enemy& one, Player& two);
																
	
	Direction VectorDirection(glm::vec2 target);
};


#endif // _SCENE_INCLUDE

