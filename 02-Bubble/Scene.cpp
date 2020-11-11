#include "Scene.h"
#include "Game.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 9 //Donde spawnea el player
#define INIT_PLAYER_Y_TILES 67

#define INIT_BALL_X_TILES 9 //Donde spawnea la bola
#define INIT_BALL_Y_TILES 66

#define INITIAL_BALL_VELOCITY 3

bool god; //godmode
bool skip; //sltar pantalla
bool next_level; //saltar nivelaz


void Scene::init(int lvl) 
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	initShaders();
	
	//cargar mapa con sus tiles
	if (lvl == 1) {
		map = TileMap::createTileMap("levels/level02.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
	else if (lvl == 2) {
		map = TileMap::createTileMap("levels/level03.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}
	else if (lvl == 3) {
		map = TileMap::createTileMap("levels/level04.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	}

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

	//cargar malo
	enemy = new Enemy();
	enemy->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	enemy->setPosition(glm::vec2(0 * map->getTileSize(), 0 * map->getTileSize()));
	enemy->setTileMap(map);
	

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

	cameraYPos = SCREEN_HEIGHT+223;
	projection = glm::ortho(20.f, float(SCREEN_WIDTH -150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos+80);
	currentTime = 0.0f;
	stage = 1;
	door = 1;
	vidas = 2;
	loot = 0;
	god = false;
	skip = false;
	next_level = false;
	for (int i = 0; i < bricks.size();i++) { //contar loot
		if (bricks[i].tipo == 'd' || bricks[i].tipo == 'c')loot = loot + 1;
	}
	enemigoActivo = false;
}

/*void keyUp(unsigned char key, int x, int y) { //controla las releases de las teclas
	if (key == 'a') {
		if (!god)god = true;
		else god = false;
	}
	if (key == 's') {
		if (!skip)skip = true;
	}
	if (key == 'd') {
		if (!next_level) next_level = true;
	}
}*/


void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	//actualizar player
	player->update(deltaTime);
	//actualizar bola
	ball->update(deltaTime);

	/*
	if (Game::instance().getKey(55)) { //MOVE UP
		cameraYPos = cameraYPos+300 - (SCREEN_WIDTH - 1) / 2;
		for(int i=0;i<1;i++){
			projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
		}
	}
	if (Game::instance().getKey(56)) {//MOVE DOWN
		cameraYPos = cameraYPos + 350 - (SCREEN_WIDTH - 1) / 2;
		for (int i = 0;i < 1;i++) {
			projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
		}
	}
	if (Game::instance().getKey(57)) {//RESET CAM
		cameraYPos = SCREEN_HEIGHT-8;
		for (int i = 0;i < 1;i++) {
			projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
		}
	}*/

	if (Game::instance().getKey(52)) { //4 -> saltar pantalla
		if (Game::instance().getKey(52)) {
			Game::instance().keyReleased(52);
		}
		if (Game::instance().getKey(52)) {
			Game::instance().keyReleased(52);
		}
		skip = true;
	}
	if (Game::instance().getKey(53)) { // 5 -> god mode
		if (Game::instance().getKey(53)) {
			Game::instance().keyReleased(53);
		}
		if (Game::instance().getKey(53)) {
			Game::instance().keyReleased(53);
		}
		if (god) god = false;
			else god = true;
	}
	//saltar de pantalla
	if (skip) {
		ball->isSticky = true;
		if (stage == 1) { //primer stage
			cameraYPos = SCREEN_HEIGHT - 175;
			stage = 2;
			player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 24) * map->getTileSize()));
			ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), (INIT_BALL_Y_TILES - 24) * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		else if(stage == 2) {
			cameraYPos = SCREEN_HEIGHT - 550;
			stage = 3;
			player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 48) * map->getTileSize()));
			ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), (INIT_BALL_Y_TILES - 48) * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		else if (stage == 3) {
			cameraYPos = SCREEN_HEIGHT + 223;
			stage = 1;
			player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
			ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		skip = false;
	}

	//control de camara dependiendo de la stage y bola
	if (stage == 1) { //primer stage
		if (ball->posBall.y / map->getTileSize() == 47 && ball->velBall.y < 0) { //sube stage 2
			cameraYPos = SCREEN_HEIGHT - 175;
			stage = 2;
			int posplayerx = (player->posPlayer.x / map->getTileSize());
			int posplayery = (player->posPlayer.y / map->getTileSize()) - 23; //subir player
			player->setPosition(glm::vec2(posplayerx * map->getTileSize(), posplayery * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		if (player->posPlayer.y / map->getTileSize() == 48) player->posPlayer.y += 4; //player no puede salir de la habitacion
	}
	else if (stage == 2) { //segundo stage
		if (ball->posBall.y / map->getTileSize() == 23 && ball->velBall.y < 0) { //sube hacia stage 3
			cameraYPos = SCREEN_HEIGHT - 550;
			stage = 3;
			int posplayerx = (player->posPlayer.x / map->getTileSize());
			int posplayery = (player->posPlayer.y / map->getTileSize()) - 24; //subir player
			player->setPosition(glm::vec2(posplayerx * map->getTileSize(), posplayery * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		if (ball->posBall.y / map->getTileSize() == 48 && ball->velBall.y > 0) { //baja a stage 1 
			cameraYPos = SCREEN_HEIGHT + 223;
			stage = 1;
			int posplayerx = (player->posPlayer.x / map->getTileSize());
			int posplayery = (player->posPlayer.y / map->getTileSize()) + 24; //bajar player
			player->setPosition(glm::vec2(posplayerx * map->getTileSize(), posplayery * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		if (player->posPlayer.y / map->getTileSize() == 24) player->posPlayer.y += 4; //player no puede salir de la habitacion
		if ((player->posPlayer.y + player->sizePlayer.y) / map->getTileSize() == 48) player->posPlayer.y -= 4; //player no puede salir de la habitacion
	}
	else {
		if (ball->posBall.y / map->getTileSize() == 24 && ball->velBall.y > 0) { //sube hacia stage 3
			cameraYPos = SCREEN_HEIGHT - 175;
			stage = 2;
			int posplayerx = (player->posPlayer.x / map->getTileSize());
			int posplayery = (player->posPlayer.y / map->getTileSize()) + 24; //bajar player
			player->setPosition(glm::vec2(posplayerx * map->getTileSize(), posplayery * map->getTileSize()));
			for (int i = 0;i < 1;i++) {
				projection = glm::ortho(20.f, float(SCREEN_WIDTH - 150), float(cameraYPos + SCREEN_HEIGHT), cameraYPos + 80);
			}
		}
		if ((player->posPlayer.y + player->sizePlayer.y) / map->getTileSize() == 24) player->posPlayer.y -= 4; //player no puede salir de la habitacion


	}

	//mirar colision enemigo con player y mover enemigo
	if (enemigoActivo) {
		if (enemy->posEnemy.x < player->posPlayer.x) enemy->moveRight();
		if (enemy->posEnemy.x > player->posPlayer.x) enemy->moveLeft();
		if (enemy->posEnemy.y < player->posPlayer.y) enemy->moveDown();
		if (enemy->posEnemy.y > player->posPlayer.y) enemy->moveUp();

		if (CheckCollisionEnemyPlayer(*enemy, *player)) { //si el enemigo te toca
			enemigoActivo = false;
			if(!god)--vidas;
			enemy->setPosition(glm::vec2(0 * map->getTileSize(), 0 * map->getTileSize())); //reset enemigo
			ball->isSticky = true;
			if (stage == 1) {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
				ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
			}
			else if (stage == 2) {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES-24) * map->getTileSize()));
				ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), (INIT_BALL_Y_TILES-24) * map->getTileSize()));
			}
			else if (stage == 3) {
				player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), (INIT_PLAYER_Y_TILES - 48) * map->getTileSize()));
				ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), (INIT_BALL_Y_TILES - 48) * map->getTileSize()));
			}
		}
	}

	//mirar si la bola se ha caido por el hueco
	if ((ball->posBall.y + ball->sizeBall.y) / map->getTileSize() == 71) { //la bola toca el final del mapa, reseteamos ball y player y quitamos vida
		player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
		ball->setPosition(glm::vec2(INIT_BALL_X_TILES * map->getTileSize(), INIT_BALL_Y_TILES * map->getTileSize()));
		ball->isSticky = true;
		if (!god)--vidas;
	}

	//mirar colision bola con player
	if (ball->velBall.y > 0) { // si la bola baja
		// NO TOCAR NADA A PARTIR DE AQUI O MUERTE
		pair<bool, pair<Direction, glm::ivec2>> colision = CheckCollisionBallPlayer(*ball, *player);
		if (colision.first) { //la bola toca al player. si actualizas la velY con un float el juego se muere, solo act velX en funcion de la colision
			if (god) {
				ball->velBall.x = 0;
				ball->velBall.y *= -1;
			}
			else {
				GLfloat centerBoard = player->posPlayer.x + player->sizePlayer.x / 2;
				GLfloat distance = (ball->posBall.x + ball->radi) - centerBoard;
				GLfloat percentage = distance / (player->sizePlayer.x / 2);
				GLfloat strength = 1.2f; //solo tocar este num para + o - speed en rebotes
				int oldx = ball->velBall.x;
				int x = INITIAL_BALL_VELOCITY * percentage * strength;
				if (x == 0) {
					if (oldx < 0) x = -3;
					else x = 3;
				}
				ball->velBall.x = x;
				ball->velBall.y = -1 * abs(ball->velBall.y);
			}
		}
		
	}
	
	//mirar colision de objetos con bola
	bool choque = false;
	for (int i = 0; i < bricks.size();i++) {
		if (bricks[i].hp > 0) { //si el objeto esta vivo
			pair<bool, pair<Direction, glm::ivec2>> colision = CheckCollisionBallObject(*ball, bricks[i]);
			if (colision.first) {
				if (bricks[i].tipo == 'r' || bricks[i].tipo == 'g' || bricks[i].tipo == 'b') { // si son ladrillos
					bricks[i].colision();
					puntuacion += bricks[i].points;
					if (choque == false) { //caso colision con doble ladrillo
						if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
						else ball->velBall.y *= -1; //colision vertical
						choque = true;
					}
				}
				else { //cosas 
					if (bricks[i].tipo == 'k') { //cojer llave
						bricks[i].colision();
						if (door == 1) { //primera llave abre primera puerta
							for (int j = 0; j < bricks.size();j++) {
								if (bricks[j].hp > 0 && bricks[j].tipo == 'A') bricks[j].colision();
							}
						}
						if (door == 3) { //segunda llave abre segunda puerta
							for (int j = 0; j < bricks.size();j++) {
								if (bricks[j].hp > 0 && bricks[j].tipo == 'B') bricks[j].colision();
							}
						}
						if (choque == false) { //caso colision con doble ladrillo
							if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
							else ball->velBall.y *= -1; //colision vertical
							choque = true;
						}
						door = door + 1;
					}
					if (bricks[i].tipo == 'B' || bricks[i].tipo == 'A') { //puerta A o B cerrada
						if (choque == false) { //caso colision con doble ladrillo
							if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
							else ball->velBall.y *= -1; //colision vertical
							choque = true;
						}
					}
					if (bricks[i].tipo == 'd' || bricks[i].tipo == 'c') {//diamante o coin
						bricks[i].colision();
						dinero += bricks[i].points;
						if (choque == false) { //caso colision con doble ladrillo
							if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
							else ball->velBall.y *= -1; //colision vertical
							choque = true;
						}
						loot = loot - 1;
					}
					if (bricks[i].tipo == 'x') { //atm
						bricks[i].colision();
						dinero = dinero + puntuacion;
						puntuacion = 0;
						if (choque == false) { //caso colision con doble ladrillo
							if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
							else ball->velBall.y *= -1; //colision vertical
							choque = true;
						}
					}
					if (bricks[i].tipo == 't') { //timbre o alarma
						if (!enemigoActivo) { //si no esta el malo por ahi lo activamos
							enemigoActivo = true;
						}
						if (choque == false) { //caso colision con doble ladrillo
							if (colision.second.first == LEFT || colision.second.first == RIGHT) ball->velBall.x *= -1; //colision horizontal 
							else ball->velBall.y *= -1; //colision vertical
							choque = true;
						}
					}
				}
			}
			
		}
	}

	//mirar condicion de victoria
	
	if (loot == 0 || Game::instance().getKey(54)){
		if (Game::instance().getKey(54)) {
			Game::instance().keyReleased(54);
		}
		if (Game::instance().getKey(54)) {
			Game::instance().keyReleased(54);
		}
		if (Game::instance().getlevelAct() == 3){
			Game::instance().winScreen(puntuacion, dinero);
		}
		else{
			Game::instance().nextLevel(0);
			char s[256];
			sprintf(s, "%d", Game::instance().getlevelAct()); 
			OutputDebugStringA((LPCSTR)s);
		}
	}

	//mirar condicion de derrota
	if (vidas == 0) {
		Game::instance().loseScreen(puntuacion);
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

	ball->render(); //pintar bola

	for (int i = 0; i < bricks.size();i++) {
		if(bricks[i].hp > 0) bricks[i].render(); //pintar ladrillos y objetos
	}
	if(enemigoActivo)enemy->render();
	player->render(); //pintar player
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
	glm::vec2 aabb_half_extents(two.sizePlayer.x / 2, (two.sizePlayer.y / 5) / 2); //tatama�os player
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

bool Scene::CheckCollisionEnemyPlayer(Enemy &one, Player &two) // AABB - AABB collision
{
	// Collision x-axis?
	bool collisionX = one.posEnemy.x + one.sizeEnemy.x >= two.posPlayer.x &&
		two.posPlayer.x + two.sizePlayer.x >= one.posEnemy.x;
	// Collision y-axis?
	bool collisionY = one.posEnemy.y + one.sizeEnemy.y >= two.posPlayer.y &&
		two.posPlayer.y + two.sizePlayer.y>= one.posEnemy.y;
	// Collision only if on both axes
	return collisionX && collisionY;
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