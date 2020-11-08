#pragma once

#include "TexturedQuad.h"
#include "ShaderProgram.h"
#include "Texture.h"

class GUI
{
public:
	GUI();
	~GUI() {}

	void init();
	void render();

	void addScore(int scoreToAdd) { scoreAct += scoreToAdd; }

	void setPlayerEnergy(int energy);
	void setLifes(int lifes); //TODO: Set lifes
	void setScore(int score);

private:
	void initShaders();
private:
	ShaderProgram texProgram;
	glm::mat4 projection;

	int mHeight;
	TexturedQuad* mainTextureQuad; //GUI Background
	Texture mainTexture;

	//ability
	TexturedQuad* abilityTexQuad;
	Texture abilityTexture;

	//score
	unsigned int scoreAct;

	//Energy
	TexturedQuad* energyQuad;
	Texture energyTexture;
	int energyAct;

	//Lifes
	TexturedQuad* lifesQuad;
	Texture lifesIndicatorTexture;
	int lifesAct;

};
