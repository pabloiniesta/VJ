#include "Menu.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Constants.h"

#include <GL/glut.h>
#include "Game.h"

#include <iostream>

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

	if (!testText.init("fonts/OpenSans-Bold.ttf")) {
		OutputDebugStringW(L"Error FT");
	}
}


void Menu::update(int deltaTime) {

	if (Game::instance().getKey(13) && !bEnterPressed) { //enter key
		bEnterPressed = true;
		if (bInstructions) //If at Instructions screen
			bInstructions = false; //Exit instructions screen
		else if (bCredits) //If at Credits screen
			bCredits = false; //Exit instructions screen
		else if (bGameOver) //If at Credits screen
			bGameOver = false; //Exit instructions screen
		else if (bWin) //If at Credits screen
			bWin = false; //Exit instructions screen
	}
	else { //Main menu screen
		if (Game::instance().getKey(49)) { //Input 1 - Start
			Game::instance().nextLevel(0);
		}
		else if (Game::instance().getKey(50)) { //Input 2 - Instructions
			bInstructions = true;
			bEnterPressed = false;
		}
		else if (Game::instance().getKey(51)) { //Input 2 - Instructions
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
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	int screen_height = vp[3] - vp[1];
	int screen_width = vp[2] - vp[0];
	int text_size = min(screen_height / 8, screen_width / 8); //Value that makes the text to fit better on background
	
//    scoreText.render("", glm::vec2(10, text_size), text_size, glm::vec4(1, 1, 1, 1));

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
	}
	else if (bWin) {
		youWinQuad->render(winTex);
		//scoreText.render(std::to_string(lastScore), glm::vec2(280, 260), text_size, glm::vec4(0, 0, 0, 1));
	}
	else { //Main menu screen
		mainTextureQuad->render(mainTexture);
	}
}


void Menu::activateGameOver(int score) {
	bGameOver = true;
	bEnterPressed = false;
	resScore = score;
}

void Menu::activateWin(int score, int money) {
	bWin = true;
	bEnterPressed = false;
	resScore = score;
	resMoney = money;
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