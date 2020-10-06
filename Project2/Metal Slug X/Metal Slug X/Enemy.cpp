#include "Enemy.h"

int Enemy::enemyNum = 0;

// Constructor
Enemy::Enemy() {
	type = Arms::DALLY;
	side = Side::RSIDE;
	pos = glm::vec2(0.0, -0.8);
	isDieing = false;
}

Enemy::Enemy(Arms t = DALLY, Side d = RSIDE, float InitX = 0.0, float InitY = -0.8, float sceneLocX = 0.0)
{
	spriteIdx = 0;

	type = t;
	side = d;

	pos = glm::vec2(InitX, InitY);
	mapLocation.x = mapLocationList[enemyNum];
	setHeight();

	enemyNum++;
	if (enemyNum >= (sizeof(mapLocationList) / sizeof(float)))
		enemyNum = (sizeof(mapLocationList) / sizeof(float)) - 1;

	moveSpeed = glm::vec2(0.0005f, 0.0f);
	step = -1;

	isDieing = false;
}
// Distructor
Enemy::~Enemy()
{
}

void Enemy::setScreenPosX(float mapPosX) {
	Object::setScreenPosX(mapPosX);

	float dis_has_dir = mapLocation.x - mapPosX;
	if (dis_has_dir < 0)
		side = Side::LSIDE;
	else
		side = Side::RSIDE;
}

float Enemy::getMapLocationX() {
	return mapLocation.x;
}

void Enemy::killed(Death death_type) {
	isDieing = true;
	deathType = death_type;
	initSpriteIndex();
}

int Enemy::getSpriteId() {
	return spriteIdx;
}

// Initial Sprite
void Enemy::initSprite() {
	// LEFT
	// The categories of arms
	// Dilly-Dally
	if (type == Arms::DALLY) 
	{
		dallyLeftSprite.Init("../media/Enemy/Dally/Left/", 76, 55, 28);
	}
	// Gun
	else if (type == Arms::PISTOL) 
	{
		pistolLeftSprite.Init("../media/Enemy/Gun/Left/", 76, 55, 12);
	}
	// Knife
	else if (type == Arms::SABER) 
	{
		saberLeftSprite.Init("../media/Enemy/Knife/Left/", 76, 55, 23);
	}
	// Rest
	restLeftSprite.Init("../media/Enemy/Rest/Left/", 76, 55, 7);
	// Walk
	walkLeftSprite.Init("../media/Enemy/Walk/Left/", 76, 55, 12);
	// Death reason
	// Grenade
	deathGrenadeLeftSprite.Init("../media/Enemy/Death/Left/Grenade/", 76, 55, 10);
	// Gun
	deathGunLeftSprite.Init("../media/Enemy/Death/Left/Gun/", 76, 55, 15);
	// Knife
	deathKnifeLeftSprite.Init("../media/Enemy/Death/Left/Knife/", 76, 55, 16);

	// RIGHT
	// The categories of arms
	// Dilly-Dally
	if (type == Arms::DALLY)
	{
		dallyRightSprite.Init("../media/Enemy/Dally/Right/", 76, 55, 28);
	}
	// Gun
	else if (type == Arms::PISTOL) 
	{
		pistolRightSprite.Init("../media/Enemy/Gun/Right/", 76, 55, 12);
	}
	// Knife
	else if (type == Arms::SABER) 
	{
		saberRightSprite.Init("../media/Enemy/Knife/Right/", 76, 55, 23);
	}
	// Rest
	restRightSprite.Init("../media/Enemy/Rest/Right/", 76, 55, 7);
	// Walk
	walkRightSprite.Init("../media/Enemy/Walk/Right/", 76, 55, 12);
	// Death reason
	// Grenade
	deathGrenadeRightSprite.Init("../media/Enemy/Death/Right/Grenade/", 76, 55, 10);
	// Gun
	deathGunRightSprite.Init("../media/Enemy/Death/Right/Gun/", 76, 55, 15);
	// Knife
	deathKnifeRightSprite.Init("../media/Enemy/Death/Right/Knife/", 76, 55, 16);
}

// LEFT
// Dilly-Dally function
void Enemy::dallyLeft()
{
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	dallyLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	dallyLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun function
void Enemy::pistolLeft() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	pistolLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	pistolLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Knife function
void Enemy::saberLeft() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	saberLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	saberLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Rest function
void Enemy::restLeft() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	restLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	restLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Walk function
void Enemy::walkLeft(float sceneLocX) {
	mapLocation.x += moveSpeed.x;
	setScreenPosX(sceneLocX);
	setHeight();
	
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	walkLeftSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	walkLeftSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Death function
void Enemy::deathLeft()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	if (deathType == Death::BOMB) {
		deathGrenadeLeftSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathGrenadeLeftSprite.Disable();
	}
	else if (deathType == Death::SHOT) {
		deathGunLeftSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathGunLeftSprite.Disable();
	}
	else if (deathType == Death::STAB) {
		deathKnifeLeftSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathKnifeLeftSprite.Disable();
	}

	glBindVertexArray(0);
	glUseProgram(0);
}

// RIGHT
// Dilly-Dally function
void Enemy::dallyRight() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	dallyRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	dallyRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Gun function
void Enemy::pistolRight() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	pistolRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	pistolRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Knife function
void Enemy::saberRight() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	saberRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	saberRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Rest function
void Enemy::restRight() {
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	restRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	restRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Walk function
void Enemy::walkRight(float sceneLocX) {
	mapLocation.x -= moveSpeed.x;
	setScreenPosX(sceneLocX);
	setHeight();
	
	int currentSprite = spriteIdx / 2;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(currentSprite), &currentSprite);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	walkRightSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	walkRightSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}
// Death function
void Enemy::deathRight() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(spriteIdx), &spriteIdx);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	if (deathType == Death::BOMB) {
		deathGrenadeRightSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathGrenadeRightSprite.Disable();
	}
	else if (deathType == Death::SHOT) {
		deathGunRightSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathGunRightSprite.Disable();
	}
	else if (deathType == Death::STAB) {
		deathKnifeRightSprite.Enable();

		glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
		glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		deathKnifeRightSprite.Disable();
	}

	glBindVertexArray(0);
	glUseProgram(0);
}