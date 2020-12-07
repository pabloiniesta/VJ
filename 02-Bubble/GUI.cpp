#include "GUI.h"
#include "Constants.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <GL/glut.h>
#include <string>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
using namespace std;


GUI::GUI()
{
}


void GUI::init() {
	//Shader
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	//Texture quads
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	glm::vec2 geomGUI[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH+ 470), -14.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 560), GUI_HEIGHT-6.5) //Margen derecho, margen inferior
	};
	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	mainTexture.loadFromFile("images/gui.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//Money
	glm::vec2 geoMoney1[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 475), 18.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 495), GUI_HEIGHT - 230) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney2[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 495), 18.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 515), GUI_HEIGHT - 230) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney3[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 515), 18.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 535), GUI_HEIGHT - 230) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney4[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 535), 18.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 555), GUI_HEIGHT - 230) //Margen derecho, margen inferior
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
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 475), 75.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 495), GUI_HEIGHT - 175) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore2[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 495), 75.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 515), GUI_HEIGHT - 175) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore3[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 515), 75.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 535), GUI_HEIGHT - 175) //Margen derecho, margen inferior
	};
	glm::vec2 geoScore4[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 535), 75.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 555), GUI_HEIGHT - 175) //Margen derecho, margen inferior
	};
	scoreTexQuad1 = TexturedQuad::createTexturedQuad(geoScore1, texCoords, texProgram);
	scoreTexture1.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad2 = TexturedQuad::createTexturedQuad(geoScore2, texCoords, texProgram);
	scoreTexture2.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad3 = TexturedQuad::createTexturedQuad(geoScore3, texCoords, texProgram);
	scoreTexture3.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	scoreTexQuad4 = TexturedQuad::createTexturedQuad(geoScore4, texCoords, texProgram);
	scoreTexture4.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//Vidas
	glm::vec2 geoVidas[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 505), 130.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 525), GUI_HEIGHT - 120) //Margen derecho, margen inferior
	};
	vidasTexQuad = TexturedQuad::createTexturedQuad(geoVidas, texCoords, texProgram);
	vidasTexture.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	
	//Level
	glm::vec2 geoLevel[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 505), 180.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 525), GUI_HEIGHT - 70) //Margen derecho, margen inferior
	};
	levelTexQuad = TexturedQuad::createTexturedQuad(geoLevel, texCoords, texProgram);
	levelTexture.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);

	//Stage
	glm::vec2 geoStage[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 505), 230.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 525), GUI_HEIGHT - 20) //Margen derecho, margen inferior
	};
	stageTexQuad = TexturedQuad::createTexturedQuad(geoStage, texCoords, texProgram);
	stageTexture.loadFromFile("images/bluebrick.png", TEXTURE_PIXEL_FORMAT_RGBA);
	

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

void GUI::actualizarGui(int money, int score, int vidas, int stage, int level) {
	
	//asignar money
	moneyTexture4 = asignarnum(money % 10);
	moneyTexture3 = asignarnum((money / 10) % 10);
	moneyTexture2 = asignarnum((money / 100) % 10);
	moneyTexture1 = asignarnum((money / 1000) % 10);

	//asignar puntuacion
	scoreTexture4 = asignarnum(score % 10);
	scoreTexture3 = asignarnum((score / 10) % 10);
	scoreTexture2 = asignarnum((score / 100) % 10);
	scoreTexture1 = asignarnum((score / 1000) % 10);
	
	//asignar vidas
	vidasTexture = asignarnum(vidas);

	//asignar stage
	stageTexture = asignarnum(stage);

	//asignar level
	levelTexture = asignarnum(level);
}


void GUI::render() {
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f); //Color uniform transform
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	glm::mat4 modelview;

	//BACKGROUND
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, SCREEN_HEIGHT - GUI_HEIGHT, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	mainTextureQuad->render(mainTexture);

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

	//Vidas
	vidasTexQuad->render(vidasTexture);

	//Level
	levelTexQuad->render(levelTexture);

	//Stage
	stageTexQuad->render(stageTexture);
}



void GUI::initShaders() {
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

Texture GUI::asignarnum(int num)
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
