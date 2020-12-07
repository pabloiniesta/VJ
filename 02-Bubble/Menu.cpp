#include "Menu.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"

#include <GL/glut.h>
#include "Game.h"

#include <iostream>
#include <irrKlang.h>
using namespace irrklang;

using namespace std;

Menu::Menu()
{
}

void Menu::init() {
	bEnterPressed = false;
	bCredits = false;
	bInstructions = false;
	bGameOver = false;
	bWin = false;

	//Shader
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Texture quads
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glm::vec2 geomGUI[2] = { glm::vec2(0.f, 0.f), glm::vec2(float(SCREEN_WIDTH), float(SCREEN_HEIGHT)) };



	float posX = float(SCREEN_WIDTH - 200.f);
	float posY = 20.f;
	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	mainTexture.loadFromFile("images/main_menu.png", TEXTURE_PIXEL_FORMAT_RGBA);

	instructionsQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	instruccionsTex.loadFromFile("images/instructions.png", TEXTURE_PIXEL_FORMAT_RGBA);

	creditsQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	creditsTex.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);

	youWinQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	winTex.loadFromFile("images/youwin.png", TEXTURE_PIXEL_FORMAT_RGBA);

	youLoseQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	loseTex.loadFromFile("images/youlose.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	//Money
	glm::vec2 geoMoney1[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH - 40 + 240), 355.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH - 20 + 240), GUI_HEIGHT + 110) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney2[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH - 20 + 240), 355.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 240), GUI_HEIGHT + 110) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney3[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 240), 355.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 20 + 240), GUI_HEIGHT + 110) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney4[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 20 + 240), 355.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 40 + 240), GUI_HEIGHT + 110) //Margen derecho, margen inferior
	};

	moneyTexQuad1 = TexturedQuad::createTexturedQuad(geoMoney1, texCoords, texProgram);
	moneyTexture1.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moneyTexQuad2 = TexturedQuad::createTexturedQuad(geoMoney2, texCoords, texProgram);
	moneyTexture2.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moneyTexQuad3 = TexturedQuad::createTexturedQuad(geoMoney3, texCoords, texProgram);
	moneyTexture3.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	moneyTexQuad4 = TexturedQuad::createTexturedQuad(geoMoney4, texCoords, texProgram);
	moneyTexture4.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//Score
	glm::vec2 geoScore1[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH -40 +240), 290.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH -20+240), GUI_HEIGHT + 45) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore2[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH -20 + 240), 290.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 240), GUI_HEIGHT + 45) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore3[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 240), 290.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH +20 + 240), GUI_HEIGHT + 45) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore4[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 20 + 240), 290.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 40 + 240), GUI_HEIGHT + 45) //Margen derecho, margen inferior
	};
	scoreTexQuad1 = TexturedQuad::createTexturedQuad(geoScore1, texCoords, texProgram);
	scoreTexture1.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad2 = TexturedQuad::createTexturedQuad(geoScore2, texCoords, texProgram);
	scoreTexture2.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad3 = TexturedQuad::createTexturedQuad(geoScore3, texCoords, texProgram);
	scoreTexture3.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad4 = TexturedQuad::createTexturedQuad(geoScore4, texCoords, texProgram);
	scoreTexture4.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//leer numeros del fichero
	cero.loadFromFile("images/cero.png", TEXTURE_PIXEL_FORMAT_RGBA);
	uno.loadFromFile("images/uno.png", TEXTURE_PIXEL_FORMAT_RGBA);
	dos.loadFromFile("images/dos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	tres.loadFromFile("images/tres.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cuatro.loadFromFile("images/cuatro.png", TEXTURE_PIXEL_FORMAT_RGBA);
	cinco.loadFromFile("images/cinco.png", TEXTURE_PIXEL_FORMAT_RGBA);
	seis.loadFromFile("images/seis.png", TEXTURE_PIXEL_FORMAT_RGBA);
	siete.loadFromFile("images/siete.png", TEXTURE_PIXEL_FORMAT_RGBA);
	ocho.loadFromFile("images/ocho.png", TEXTURE_PIXEL_FORMAT_RGBA);
	nueve.loadFromFile("images/nueve.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
}


void Menu::update(int deltaTime) {

	if (Game::instance().getKey(13) && !bEnterPressed) { //enter key
		Game::instance().playSound("sounds/menu_sel.wav", false);
		bEnterPressed = true;
		if (bInstructions) //If at Instructions screen
			bInstructions = false; //Exit instructions screen
		else if (bCredits) //If at Credits screen
			bCredits = false; //Exit instructions screen
		else if (bGameOver) { //If at Lose screen
			bGameOver = false; //Exit instructions screen
			Game::instance().stopSounds();
			Game::instance().playSound("sounds/menu.mp3", true);
		}
		else if (bWin) { //If at Win screen
			bWin = false; //Exit instructions screen
			Game::instance().stopSounds();
			Game::instance().playSound("sounds/menu.mp3", true);
		}

	}
	else { //Main menu screen
		if (Game::instance().getKey(49)) { //Input 1 - Start
			Game::instance().playSound("sounds/menu_sel.wav", false);
			Game::instance().nextLevel(0, 0 ,0);
		}
		else if (Game::instance().getKey(50)) { //Input 2 - Instructions
			Game::instance().playSound("sounds/menu_sel.wav", false);
			bInstructions = true;
			bEnterPressed = false;
		}
		else if (Game::instance().getKey(51)) { //Input 2 - Instructions
			Game::instance().playSound("sounds/menu_sel.wav", false);
			bCredits = true;
			bEnterPressed = false;
		}
	}	
}

void Menu::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	glm::mat4 modelview;

	//BACKGROUND
	texProgram.setUniformMatrix4f("modelview", modelview);

	mainTextureQuad->render(mainTexture);
	if (bInstructions) {//At instructions screen
		//Render instructions
		instructionsQuad->render(instruccionsTex);
	}
	else if (bCredits) {
		//render records
		creditsQuad->render(creditsTex);
	}
	else if (bGameOver) {
		//render game over
		youLoseQuad->render(loseTex);

		//Score
		
		scoreTexQuad1->render(scoreTexture1);//4
		scoreTexQuad2->render(scoreTexture2);//3
		scoreTexQuad3->render(scoreTexture3);//2
		scoreTexQuad4->render(scoreTexture4);//1
		
	}
	else if (bWin) {
		youWinQuad->render(winTex);

		
		//Money
		moneyTexQuad1->render(moneyTexture1);//4
		moneyTexQuad2->render(moneyTexture2);//3
		moneyTexQuad3->render(moneyTexture3);//2
		moneyTexQuad4->render(moneyTexture4);//1

		//Score
		scoreTexQuad1->render(scoreTexture1);//4
		scoreTexQuad2->render(scoreTexture2);//3
		scoreTexQuad3->render(scoreTexture3);//2
		scoreTexQuad4->render(scoreTexture4);//1
		
	}
	else { //Main menu screen
		mainTextureQuad->render(mainTexture);
	}
}


void Menu::activateGameOver(int score) {
	Game::instance().stopSounds();
	Game::instance().playSound("sounds/lose.wav", false);
	bGameOver = true;
	bEnterPressed = false;
	//calcularTexScore(score);
	scoreTexture4 = asignarnum(score % 10);
	scoreTexture3 = asignarnum((score / 10) % 10);
	scoreTexture2 = asignarnum((score / 100) % 10);
	scoreTexture1 = asignarnum((score / 1000) % 10);
}

void Menu::activateWin(int score, int money) {
	Game::instance().stopSounds();
	Game::instance().playSound("sounds/win.wav", false);
	bWin = true;
	bEnterPressed = false;
	//calcularTexScore(score); 
	scoreTexture4 = asignarnum(money % 10);      //los nombres de las texturas estan cambiados lul
	scoreTexture3 = asignarnum((money / 10) % 10);
	scoreTexture2 = asignarnum((money / 100) % 10);
	scoreTexture1 = asignarnum((money / 1000) % 10);
	//calcularTexMoney(money);
	moneyTexture4 = asignarnum(score % 10);
	moneyTexture3 = asignarnum((score / 10) % 10);
	moneyTexture2 = asignarnum((score / 100) % 10);
	moneyTexture1 = asignarnum((score / 1000) % 10);
}


void Menu::initShaders() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

Texture Menu::asignarnum(int num)
{
	if (num == 0) return cero;
	else if (num == 1) return uno;
	else if (num == 2) return dos;
	else if (num == 3) return tres;
	else if (num == 4) return cuatro;
	else if (num == 5) return cinco;
	else if (num == 6) return seis;
	else if (num == 7) return siete;
	else if (num == 8) return ocho;
	else if (num == 9) return nueve;
}