#include "NumberObject.h"



NumberObject::NumberObject(): NumberObject(0, glm::vec2(0.0)) {}

NumberObject::NumberObject(int num, glm::vec2 loc) {
	pos = loc;
	setNumber(num);
}

NumberObject::~NumberObject() {}

void NumberObject::setNumber(int num) {
	number = num;
}

int NumberObject::getNumber() {
	return number;
}

void NumberObject::setLocation(glm::vec2 loc) {
	pos = loc;
}

void NumberObject::initSprite()
{
	numberSprite.Init("../media/Numbers/", 21, 28, 10);
}

void NumberObject::render() 
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pos), &pos);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(pos), sizeof(number), &number);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Update shaders' input variable
	///////////////////////////	
	glUseProgram(program);

	glBindVertexArray(vao);

	numberSprite.Enable();

	glUniformMatrix4fv(uniforms.mv_matrix, 1, GL_FALSE, &(view * model)[0][0]);
	glUniformMatrix4fv(uniforms.proj_matrix, 1, GL_FALSE, &(projection)[0][0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	numberSprite.Disable();

	glBindVertexArray(0);
	glUseProgram(0);
}