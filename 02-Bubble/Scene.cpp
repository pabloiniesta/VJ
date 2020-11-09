#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 17 //Donde spawnea el player
#define INIT_PLAYER_Y_TILES 24

#define INIT_BALL_X_TILES 17 //Donde spawnea la bola
#define INIT_BALL_Y_TILES 23

#define INITIAL_BALL_VELOCITY 3


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

	

	//cargar ladrillos
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
	if (ball->velBall.y > 0) { // si la bola baja
		// NO TOCAR NADA A PARTIR DE AQUI O MUERTE
		pair<bool, pair<Direction, glm::ivec2>> colision = CheckCollisionBallPlayer(*ball, *player);
		if (colision.first) { //la bola toca al player. si actualizas la velY con un float el juego se muere, solo act velX en funcion de la colision
			GLfloat centerBoard = player->posPlayer.x + player->sizePlayer.x / 2;
			GLfloat distance = (ball->posBall.x + ball->radi) - centerBoard;
			GLfloat percentage = distance / (player->sizePlayer.x / 2);
			GLfloat strength = 1.2f; //solo tocar este num para + o - speed en rebotes
			int oldx = ball->velBall.x;
			/*
			glm::vec2 newVelocity;
			newVelocity.x = INITIAL_BALL_VELOCITY * percentage * strength;
			newVelocity.y = INITIAL_BALL_VELOCITY * percentage * strength;
			newVelocity = glm::normalize(newVelocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
			int x = (int)newVelocity.x;*/
			int x = INITIAL_BALL_VELOCITY * percentage * strength;
			if (x == 0) {
				if (oldx < 0) x = -3;
				else x = 3;
			}
			ball->velBall.x = x;
			ball->velBall.y = -1 * abs(ball->velBall.y);
		}
		
	}

	//mirar colision de ladrillos con bola
	bool choque = false;
	for (int i = 0; i < bricks.size();i++) {
		if (bricks[i].hp > 0) { //si el brick esta vivo
			pair<bool, pair<Direction, glm::ivec2>> colision = CheckCollisionBallObject(*ball, bricks[i]);
			if (colision.first) {
				bricks[i].colision();
				if (choque == false) { //caso colision con doble ladrillo
					if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
					else ball->velBall.y *= -1; //colision vertical
					choque = true;
				}
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



pair<bool, pair<Direction, glm::ivec2>> Scene::CheckCollisionBallObject(Ball& one, Brick& two) // AABB - Circle collision
{
	// Get center point circle first
	glm::vec2 center(one.posBall + 8); //8 radio de bola
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.sizeBrick.x / 2, two.sizeBrick.y / 2); //tamxladrillo tamyladrillo
	glm::vec2 aabb_center(two.posBrick.x + aabb_half_extents.x, two.posBrick.y + aabb_half_extents.y);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;

	if (glm::length(difference) < 8) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
		return make_pair(GL_TRUE,make_pair(VectorDirection(difference), difference));
	else
		return make_pair(GL_FALSE, make_pair(UP, glm::vec2(0,0)));
}

pair<bool, pair<Direction, glm::ivec2>> Scene::CheckCollisionBallPlayer(Ball& one, Player& two) // AABB - Circle collision
{
	// Get center point circle first
	glm::vec2 center(one.posBall + 8); //8 radio de bola
	// Calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.sizePlayer.x / 2, (two.sizePlayer.y / 5) / 2); //tatamaños player
	glm::vec2 aabb_center(two.posPlayer.x + aabb_half_extents.x, two.posPlayer.y + aabb_half_extents.y);
	// Get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// Now retrieve vector between center circle and closest point AABB and check if length < radius
	difference = closest - center;

	if (glm::length(difference) < 8) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
		return make_pair(GL_TRUE, make_pair(VectorDirection(difference), difference));
	else
		return make_pair(GL_FALSE, make_pair(UP, glm::vec2(0, 0)));
}



Direction Scene::VectorDirection(glm::vec2 target)
{
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),    // up
		glm::vec2(1.0f, 0.0f),    // right
		glm::vec2(0.0f, -1.0f),    // down
		glm::vec2(-1.0f, 0.0f)    // left
	};
	GLfloat max = 0.0f;
	GLuint best_match = -1;
	for (GLuint i = 0; i < 4; i++)
	{
		GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max)
		{
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction)best_match;
}