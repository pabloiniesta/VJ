#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 12 //Donde spawnea el player
#define INIT_PLAYER_Y_TILES 20

#define INIT_BALL_X_TILES 12 //Donde spawnea el player
#define INIT_BALL_Y_TILES 15


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initShaders();
	//cargar mapa con sus tiles
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	//cargar player con sus coordenadas de pantalla y atributos
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);

	//cargar bola
	ball = new Ball();
	ball->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
	ball->setTileMap(map);

	for (int i = 0; i < map->brickInfo.size(); i++) { //recorer vec con la info de cada brick para crearlo
		pair<char, pair<int, int> > info = map->brickInfo[i];
		char tipobrick = info.first;
		int posBrickx = info.second.first;
		int posBricky = info.second.second;
		Brick *brick = new Brick();
		brick->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, tipobrick); //creamos el Brick
		brick->setPosition(glm::vec2(posBrickx * map->getTileSize(), posBricky * map->getTileSize())); //le damos su posicion en el mapa
		bricks.push_back(*brick); //lo metemos en el vector de bricks
	}
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	//actualizar player
	player->update(deltaTime);
	//actualizar bola
	ball->update(deltaTime);


	//mirar colision bola con player
	if (ball->velY > 0) { // si la bola baja
		if (touchBallToPlayer(player->posPlayer, ball->posBall, glm::ivec2(16, 16), glm::ivec2(32, 32))) { //miramos si le da al player
			ball->velY *= -1; //si le ha dado cambiamos direccion
		}
	}
	//mirar colision de ladrillos con bola
	for (int i = 0; i < bricks.size();i++) {
		if (bricks[i].hp > 0) { //si el brick esta vivo
			if (touchBallToBrick(bricks[i].posBrick, ball->posBall, glm::ivec2(16, 16), glm::ivec2(32, 16))) {
				bricks[i].colision();
				ball->velY *= -1;
			}
		}
	}

	

}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render(); //pintar mapa
	player->render(); //pintar player
	ball->render(); //pintar bola
	for (int i = 0; i < bricks.size();i++) {
		if(bricks[i].hp > 0) bricks[i].render();
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::touchBallToPlayer(const glm::ivec2& posPlayer, const glm::ivec2& posBall, const glm::ivec2& sizeBall, const glm::ivec2& sizePlayer) const
{
	int ybola, x0bola, x1bola;
	int yplayer, x0player, x1player;


	ybola = posBall.y + sizeBall.y; //cara de abajo de la bola
	x0bola = posBall.x; // Punto x inicial de la bola
	x1bola = posBall.x + sizeBall.x; // Punto x final de la bola

	yplayer = posPlayer.y; //contorno superior del player
	x0player = posPlayer.x; // Punto x inicial del player
	x1player = posPlayer.x + sizePlayer.x; // Punto x final del player

	for (int x = x0bola; x <= x1bola; x++)
	{
		if (ybola >= yplayer && ybola < yplayer+5 && x >= x0player && x <= x1player) return true;
	}
	return false;
}

bool Scene::touchBallToBrick(const glm::ivec2& posBrick, const glm::ivec2& posBall, const glm::ivec2& sizeBall, const glm::ivec2& sizeBrick) const
{
	//colision parte inferior del brick
	int ybola = posBall.y; //parte superior de la bola
	int x0bola = posBall.x; // Punto x inicial de la bola
	int x1bola = posBall.x + sizeBall.x; // Punto x final de la bola

	int ybrick = posBrick.y + sizeBrick.y; //parte inferior brick
	int x0brick = posBrick.x; //punto x inicial brick
	int x1brick = posBrick.x + sizeBrick.x; //punto x final brick
	for (int x = x0bola; x <= x1bola; x++) {
		if (ybola <= ybrick && ybola > ybrick - 5 && x >= x0brick && x <= x1brick) return true; //mirar si cuando la bola sube le da a algun brick
	}
	return false;
}


