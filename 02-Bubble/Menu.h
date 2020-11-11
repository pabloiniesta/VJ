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
	void activateNewRecord(int score);

	void setInstructions(bool value) { bInstructions = value; }


private:
	void initShaders();

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

	int lastScore;
	bool bCredits; //Go to credits screen
	bool bInstructions; //Go to instructions scree
	bool bGameOver; //Go to game over screen
	bool bWin;
	Text testText;
};