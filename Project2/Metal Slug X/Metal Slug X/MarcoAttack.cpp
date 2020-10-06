#include "MarcoAttack.h"

float MarcoAttack::KNIFE_ATTACK_GAP_LEFT = 0.015f + 0.003f;
float MarcoAttack::KNIFE_ATTACK_GAP_RIGHT = 0.015f;
float MarcoAttack::BULLET_ATTACK_GAP_X = 0.005f;
float MarcoAttack::BULLET_ATTACK_GAP_Y = 0.3f;
float MarcoAttack::GRENADE_ATTACK_GAP_X = 0.003f;
float MarcoAttack::GRENADE_ATTACK_GAP_Y = 0.25f;
float MarcoAttack::GRENADE_ATTACK_RANGE = 0.013f;

// Constructor
MarcoAttack::MarcoAttack(MAttack t = BULLET, Orientation d = R, float initX = 0.0f, float initY = 0.0f) {
	attack = t;
	orient = d;
	if (t == MAttack::BULLET) {
		if (d == Orientation::L) {
			moveSpeed.x = 0.004f;
			mapLocation.x = initX - 0.0013;
			mapLocation.y = initY + 0.2266;
		}
		else if (d == Orientation::R) {
			moveSpeed.x = 0.004f;
			mapLocation.x = initX + 0.0013;
			mapLocation.y = initY + 0.2266;
		}
		else if (d == Orientation::U) {
			moveSpeed.y = 0.1f;
			mapLocation.x = initX;
			mapLocation.y = initY + 0.45;
		}
		setScreenPosX(mapLocation.x);
		setScreenPosY(mapLocation.y);
	}
	else if (t == MAttack::PINEAPPLE) {
		// Pineapple's movespeed.x define in fly
		moveSpeed.x = 0.0f;
		if (d == Orientation::L) {
			mapLocation.x = initX - 0.0025;
		}
		else if (d == Orientation::R) {
			mapLocation.x = initX + 0.0025;
		}
		mapLocation.y = initY + 0.3812;
	}
	action = Action::FLY;
	setScreenPosX(mapLocation.x);
	setScreenPosY(mapLocation.y);
	serviveTimes = 0;
	canMove = true;
}
// Distructor
MarcoAttack::~MarcoAttack() {}
// Sprite ID counter
bool MarcoAttack::nextFrame() {
	spriteIdx++;
	// Fly
	if (action == Action::FLY) {
		serviveTimes++;
		if (attack == MAttack::BULLET) {
			spriteIdx = 1;
			// Timeout
			if (serviveTimes >= 19) {
				action = Action::EXPLODE;
				initSpriteIndex();
			}
		}
		else if (attack == MAttack::PINEAPPLE) {
			// Timeout
			if (serviveTimes >= 28) {
				action = Action::EXPLODE;
				initSpriteIndex();
			}
		}
	}
	// Explosion
	else if (action == Action::EXPLODE) {
		bool isFinished = false;
		if (attack == MAttack::BULLET) {
			if (spriteIdx >= 11) {
				isFinished = true;
				initSprite();
			}
		}
		else if (attack == MAttack::PINEAPPLE) {
			if (spriteIdx >= 20) {
				isFinished = true;
				initSprite();
			}
		}
		return isFinished;
	}
	return false;
}
// Initial sprite picture
void MarcoAttack::initSprite() {
	// Bullet
	if (attack == MAttack::BULLET) {
		if (orient == Orientation::L) 
		{
			bulletFlyLeftSprite.Init("../media/Attack/Bullet/Fly/Left/", 48, 100, 2);
		}
		else if (orient == Orientation::R) 
		{
			bulletFlyRightSprite.Init("../media/Attack/Bullet/Fly/Right/", 48, 100, 2);
		}
		else if (orient == Orientation::U) 
		{
			bulletFlyUpSprite.Init("../media/Attack/Bullet/Fly/Up/", 48, 100, 2);
		}
		// Explosion
		bulletExplosionSprite.Init("../media/Attack/Bullet/Explosion/", 48, 100, 11);
	}
	// Pineapple
	else if (attack == MAttack::PINEAPPLE)
	{
		if (orient == Orientation::L) 
		{
			pineappleFlyLeftSprite.Init("../media/Attack/Pineapple/Fly/Left/", 48, 100, 28);
		}
		else if (orient == Orientation::R) 
		{
			pineappleFlyRightSprite.Init("../media/Attack/Pineapple/Fly/Right/", 48, 100, 28);
		}
		// Explosion
		pineappleExplosionSprite.Init("../media/Attack/Pineapple/Explosion/", 48, 100, 20);
	}
}

// Bullet
// Left
void MarcoAttack::bulletFlyLeft(float scenePosX) 
{
	mapLocation.x -= moveSpeed.x;
	setScreenPosX(scenePosX);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	bulletFlyLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	bulletFlyLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Right
void MarcoAttack::bulletFlyRight(float scenePosX) 
{
	mapLocation.x += moveSpeed.x;
	setScreenPosX(scenePosX);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	bulletFlyRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	bulletFlyRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Up
void MarcoAttack::bulletFlyUp(float scenePosX) 
{
	setScreenPosX(scenePosX);
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

	bulletFlyUpSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	bulletFlyUpSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Explosion
void MarcoAttack::bulletExplode(float scenePosX) 
{
	setScreenPosX(scenePosX);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	bulletExplosionSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	bulletExplosionSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}

// Pineapple
// Left
void MarcoAttack::pineappleFlyLeft(float scenePosX) {
	// Move curve
	// High wave start
	if (spriteIdx <= 7) {
		moveSpeed.x = 0.0015f;
		moveSpeed.y = pineappleCurveHighUp[spriteIdx];
	}
	// High wave down
	else if (spriteIdx <= 19) {
		moveSpeed.x = 0.0015f;
		moveSpeed.y = -pineappleCurveHighDown[spriteIdx - 8];
	}
	// Wave trough
	else if (spriteIdx == 20) {
		moveSpeed.x = 0.0f;
		moveSpeed.y = 0.0f;
	}
	// Low wave start
	else if (spriteIdx <= 23) {
		moveSpeed.x = 0.0020f;
		moveSpeed.y = pineappleCurveLowUp[spriteIdx - 21];
	}
	// Low wave down
	else if (spriteIdx <= 26) {
		moveSpeed.x = 0.0020f;
		moveSpeed.y = -pineappleCurveLowDown[spriteIdx - 24];
	}
	else if (spriteIdx == 27) {
		moveSpeed.x = 0.0f;
		moveSpeed.y = 0.0f;
	}
	// Change position
	mapLocation.x -= moveSpeed.x;
	setScreenPosX(scenePosX);
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

	pineappleFlyLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	pineappleFlyLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Right
void MarcoAttack::pineappleFlyRight(float scenePosX) {
	// Move curve
	// High wave start
	if (spriteIdx <= 7) {
		moveSpeed.x = 0.0015f;
		moveSpeed.y = pineappleCurveHighUp[spriteIdx];
	}
	// High wave down
	else if (spriteIdx <= 19) {
		moveSpeed.x = 0.0015f;
		moveSpeed.y = -pineappleCurveHighDown[spriteIdx - 8];
	}
	// Wave trough
	else if (spriteIdx == 20) {
		moveSpeed.x = 0.0f;
		moveSpeed.y = 0.0f;
	}
	// Low wave start
	else if (spriteIdx <= 23) {
		moveSpeed.x = 0.0020f;
		moveSpeed.y = pineappleCurveLowUp[spriteIdx - 21];
	}
	// Low wave down
	else if (spriteIdx <= 26) {
		moveSpeed.x = 0.0020f;
		moveSpeed.y = -pineappleCurveLowDown[spriteIdx - 24];
	}
	else if (spriteIdx == 27) {
		moveSpeed.x = 0.0f;
		moveSpeed.y = 0.0f;
	}
	// Change position
	mapLocation.x += moveSpeed.x;
	setScreenPosX(scenePosX);
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

	pineappleFlyRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	pineappleFlyRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Explosion
void MarcoAttack::pineappleExplode(float scenePosX) {
	setScreenPosX(scenePosX);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	pineappleExplosionSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	pineappleExplosionSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}