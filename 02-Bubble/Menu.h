#pragma once

#include "TexturedQuad.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Text.h"


class Menu
{
public:
	Menu();
	~Menu() {}

	void init();
	void update(int deltaTime);
	void render();
	void activateWin(int score, int money);
	void activateGameOver(int score);
	void setInstructions(bool value) { bInstructions = value; }
	void calcularTexScore(int score);
	void calcularTexMoney(int money);


private:
	void initShaders();
	Texture asignarnum(int num);

private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	int index;
	int numOptions;
	bool bUpPressed, bDownPressed, bEnterPressed;
	int resMoney, resScore;


	TexturedQuad* instructionsQuad; //Instructions Background
	Texture instruccionsTex;

	TexturedQuad* creditsQuad; //Credits Background
	Texture creditsTex;

	TexturedQuad* youLoseQuad; //Game over Background
	Texture loseTex;

	TexturedQuad* youWinQuad; //Game over Background
	Texture winTex;

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


	int lastScore;
	bool bCredits; //Go to credits screen
	bool bInstructions; //Go to instructions scree
	bool bGameOver; //Go to game over screen
	bool bWin;
	Text testText;
};