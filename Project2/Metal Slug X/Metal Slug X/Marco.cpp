#pragma warning(disable:4996)
#include "Marco.h"
// Constructor
Marco::Marco() {
	mapLocation = glm::vec2(INIT_MAP_LOC_X, INIT_MAP_LOC_Y);
	setScreenPosX(0.0f);
	setScreenPosY(INIT_MAP_LOC_Y);

	reborn();
}
// Distructor
Marco::~Marco() {}
// Set keyboard table
void Marco::setKeyboard(int key, bool state) 
{
	keyboardState[key] = state;
}
// Get keyboard function
bool Marco::getKeyboard(int key)
{
	if (key < 0)
		key = 0;

	if (key >= MAX_KEY_NUM)
		key = MAX_KEY_NUM - 1;

	return keyboardState[key];
}
// Reborn function
void Marco::reborn() {
	for (int k = 0; k < MAX_KEY_NUM; k++)
		keyboardState[k] = false;
	spriteIdx = 0;
	// Initial action
	state = State::IDLE;
	// Initial direction
	direction = Direction::RIGHT;
	// Initial moving speed
	moveSpeed.x = 0.0015f;
	moveSpeed.y = 0.1f;

	mapLocation.y = INIT_MAP_LOC_Y;
	setHeight();

	canMove = true;
	atCentre = false;
	isDieing = isDead = false;
	noDamageStatus = true;

	blinkingCounter = 0;
}
// Get sprite ID
int Marco::getSpriteId() 
{
	return spriteIdx;
}

// Initial sprite picture
void Marco::initSprite() 
{
	blinkingLocation = glGetUniformLocation(program, "blinkingcounter");
	dotLightScreenPos3DLocation = glGetUniformLocation(program, "pos3d");

	// Initial LEFT
	// Initial Left to Right
	LtoRSprite.Init("../media/Marco/Left/LtoR/", 76, 55, 4);
	// Initial idle left
	idleLeftSprite.Init("../media/Marco/Left/Idle/", 76, 55, 1);
	// Initial stop left
	stopLeftSprite.Init("../media/Marco/Left/Stop/", 76, 55, 8);
	// Initial walk left
	walkLeftSprite.Init("../media/Marco/Left/Walk/", 76, 55, 13);
	// Initial up left
	upLeftSprite.Init("../media/Marco/Left/Up/", 76, 55, 5);
	// Initial idle up left
	idleUpLeftSprite.Init("../media/Marco/Left/IdleUp/", 76, 55, 1);
	// Initial down left
	downLeftSprite.Init("../media/Marco/Left/Down/", 76, 55, 5);
	// Initial jump left
	jumpLeftSprite.Init("../media/Marco/Left/Jump/", 76, 55, 9);
	// Initial fall left
	fallLeftSprite.Init("../media/Marco/Left/Fall/", 76, 55, 9);
	// Initial knife left
	knifeLeftSprite.Init("../media/Marco/Left/Knife/", 76, 55, 8);
	// Initial gun left
	shootLeftSprite.Init("../media/Marco/Left/Shoot/", 76, 55, 12);
	// Initial gun up left
	shootUpLeftSprite.Init("../media/Marco/Left/UpShoot/", 76, 55, 12);
	// Initial grenade left
	grenadeLeftSprite.Init("../media/Marco/Left/Grenade/", 76, 55, 7);
	// Initial death left
	deathLeftSprite.Init("../media/Marco/Left/Death/", 76, 55, 10);
	// Initial victory left
	victoryLeftSprite.Init("../media/Marco/Left/Victory/", 76, 55, 7);
	
	// Initial RIGHT
	// Initial Right to Left
	RtoLSprite.Init("../media/Marco/Right/RtoL/", 76, 55, 4);
	// Initial idle right
	idleRightSprite.Init("../media/Marco/Right/Idle/", 76, 55, 1);
	// Initial stop right
	stopRightSprite.Init("../media/Marco/Right/Stop/", 76, 55, 8);
	// Initial walk right
	walkRightSprite.Init("../media/Marco/Right/Walk/", 76, 55, 13);
	// Initial up right
	upRightSprite.Init("../media/Marco/Right/Up/", 76, 55, 5);
	// Initial idle up right
	idleUpRightSprite.Init("../media/Marco/Right/IdleUp/", 76, 55, 1);
	// Initial down right
	downRightSprite.Init("../media/Marco/Right/Down/", 76, 55, 5);
	// Initial jump right
	jumpRightSprite.Init("../media/Marco/Right/Jump/", 76, 55, 9);
	// Initial fall right
	fallRightSprite.Init("../media/Marco/Right/Fall/", 76, 55, 9);
	// Initial knife right
	knifeRightSprite.Init("../media/Marco/Right/Knife/", 76, 55, 8);
	// Initial gun right
	shootRightSprite.Init("../media/Marco/Right/Shoot/", 76, 55, 12);
	// Initial gun up right
	shootUpRightSprite.Init("../media/Marco/Right/UpShoot/", 76, 55, 12);
	// Initial grenade right
	grenadeRightSprite.Init("../media/Marco/Right/Grenade/", 76, 55, 7);
	// Initial death right
	deathRightSprite.Init("../media/Marco/Right/Death/", 76, 55, 10);
	// Initial victory right
	victoryRightSprite.Init("../media/Marco/Right/Victory/", 76, 55, 7);
}

// LEFT
// Left turn to Right
void Marco::LtoR() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	LtoRSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	LtoRSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Idle Left
void Marco::idleLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	idleLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	idleLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Stop Left
void Marco::stopLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	stopLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	stopLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Walk Left
void Marco::walkLeft(float sceneLocX) 
{
	setScreenPosX(sceneLocX);

	atCentre = (fabs(pos.x - 0.0f) <= moveSpeed.x);

	if ((fabs(pos.x - 0.0f) > moveSpeed.x || atCentre) && pos.x > -1.0 && canMove)
	{
		if (pos.x < -1.0 + (TEX_SIZE_WIDTH / 2.0f))
			pos.x = -1.0 + (TEX_SIZE_WIDTH / 2.0f);
	}
	
	mapLocation.x -= moveSpeed.x;
	setScreenPosX(sceneLocX);
	setHeight();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	walkLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	walkLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Up Left
void Marco::upLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	upLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	upLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Up idle Left
void Marco::idleUpLeft() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	idleUpLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	idleUpLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Down Left
void Marco::downLeft() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	downLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	downLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Jump Left
void Marco::jumpLeft()
{
	if (spriteIdx < 5)
		mapLocation.y += moveSpeed.y;
	setScreenPosY(mapLocation.y);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	jumpLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	jumpLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Fall Left
void Marco::fallLeft()
{
	if (spriteIdx > 3)
		mapLocation.y -= moveSpeed.y;
	setScreenPosY(mapLocation.y);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	fallLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	fallLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Knife Left
void Marco::knifeLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	knifeLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	knifeLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun Left
void Marco::shootLeft() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	shootLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shootLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun Up Left
void Marco::shootUpLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	shootUpLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shootUpLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Grenade Left
void Marco::grenadeLeft() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	grenadeLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	grenadeLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// death left
void Marco::deathLeft() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	deathLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	deathLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// victory left
void Marco::victoryLeft(glm::vec2 screenPos) {
	pos = screenPos;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	victoryLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	victoryLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}

// RIGHT
// Right turn to Left
void Marco::RtoL() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	RtoLSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	RtoLSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Idle Right
void Marco::idleRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	idleRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	idleRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Stop Right
void Marco::stopRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	stopRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	stopRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Walk Right
void Marco::walkRight(float sceneLocX) 
{
	setScreenPosX(sceneLocX);

	atCentre = (fabs(pos.x - 0.0f) <= moveSpeed.x);

	if ((fabs(pos.x - 0.0f) > moveSpeed.x || atCentre) && pos.x < 1.0 && canMove) {
		//if (pos.x < -1.0 + (TEX_SIZE_WIDTH / 2.0f))
		//	pos.x = -1.0 + (TEX_SIZE_WIDTH / 2.0f);
	}

	mapLocation.x += moveSpeed.x;
	setScreenPosX(sceneLocX);
	setHeight();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	walkRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	walkRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Up Right
void Marco::upRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	upRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	upRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Up idle Right
void Marco::idleUpRight() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	idleUpRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	idleUpRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Down Right
void Marco::downRight() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	downRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	downRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Jump Right
void Marco::jumpRight() {
	if (spriteIdx < 5)
		mapLocation.y += moveSpeed.y;
	setScreenPosY(mapLocation.y);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	jumpRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	jumpRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Jump Right
void Marco::fallRight() {
	if (spriteIdx > 3)
		mapLocation.y -= moveSpeed.y;
	setScreenPosY(mapLocation.y);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	fallRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	fallRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Knife Left
void Marco::knifeRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	knifeRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	knifeRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun Right
void Marco::shootRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	shootRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shootRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun Up Right
void Marco::shootUpRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	shootUpRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shootUpRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Grenade Right
void Marco::grenadeRight() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	grenadeRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	grenadeRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// death right
void Marco::deathRight()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	deathRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	deathRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// victory right
void Marco::victoryRight(glm::vec2 screenPos) {
	pos = screenPos;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	victoryRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glUniform1f(blinkingLocation, (float)blinkingCounter);
	glUniform3fv(dotLightScreenPos3DLocation, 1, &dotLightScreenPos3D[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	victoryRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}