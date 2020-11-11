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
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH+475), -14.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 555), GUI_HEIGHT-6.5) //Margen derecho, margen inferior
	};
	glm::vec2 geoMoney[2] = {
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 480), 18.f), //Margen izquierdo, margen superior
			glm::vec2(float(GUI_ABILITY_IMG_WIDTH + 550), GUI_HEIGHT - 230) //Margen derecho, margen inferior
	};
	mainTextureQuad = TexturedQuad::createTexturedQuad(geomGUI, texCoords, texProgram);
	mainTexture.loadFromFile("images/gui.png", TEXTURE_PIXEL_FORMAT_RGBA);
	abilityTexQuad = TexturedQuad::createTexturedQuad(geoMoney, texCoords, texProgram);
	abilityTexture.loadFromFile("images/bbrick2.png", TEXTURE_PIXEL_FORMAT_RGBA);

	if (!scoreText.init("fonts/OpenSans-Bold.ttf")) {
		OutputDebugStringW(L"Error FT");
	}
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

	//Ability
	abilityTexQuad->render(abilityTexture);
	//Texts
	int vp[4];
	glGetIntegerv(GL_VIEWPORT, vp);
	//char s[256];
	//sprintf(s, "VP[1]=%d, VP[2]=%d, VP[3]=%d, VP[4]=%d", vp[0], vp[1], vp[2], vp[3]); // 0,0,480,640
	//OutputDebugStringA((LPCSTR)s);
	int screen_height = vp[3] - vp[1];
	int screen_width = vp[2] - vp[0];
	int gui_height = screen_height;
	int hab_size = 15;
	scoreText.render("Score: 99999", glm::vec2(screen_width * 0.2f, screen_height - gui_height / 2 + hab_size / 2), hab_size, glm::vec4(0, 0, 0, 1));

}


void GUI::setLifes(int lifes) {
	lifesAct = lifes;
}

void GUI::setScore(int score) {
	scoreAct = score;
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