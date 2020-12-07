#pragma once

#include "TexturedQuad.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Text.h"

class GUI
{
public:
	GUI();
	~GUI() {}

	void init();
	bool update(int deltaTime);
	void render();

	void actualizarGui(int money, int score, int vidas, int stage, int level);


private:
	void initShaders();
	Texture asignarnum( int num);
private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	int mHeight;
	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	//Money
	TexturedQuad* moneyTexQuad1;
	Texture moneyTexture1;
	TexturedQuad* moneyTexQuad2;
	Texture moneyTexture2;
	TexturedQuad* moneyTexQuad3;
	Texture moneyTexture3;
	TexturedQuad* moneyTexQuad4;
	Texture moneyTexture4;

	//Score
	TexturedQuad* scoreTexQuad1;
	Texture scoreTexture1;
	TexturedQuad* scoreTexQuad2;
	Texture scoreTexture2;
	TexturedQuad* scoreTexQuad3;
	Texture scoreTexture3;
	TexturedQuad* scoreTexQuad4;
	Texture scoreTexture4;

	//Vidas
	TexturedQuad* vidasTexQuad;
	Texture vidasTexture;

	//Level
	TexturedQuad* levelTexQuad;
	Texture levelTexture;

	//Stage
	TexturedQuad* stageTexQuad;
	Texture stageTexture;

	//texturas de numeros
	Texture cero;
	Texture uno;
	Texture dos;
	Texture tres;
	Texture cuatro;
	Texture cinco;
	Texture seis;
	Texture siete;
	Texture ocho;
	Texture nueve;

};
