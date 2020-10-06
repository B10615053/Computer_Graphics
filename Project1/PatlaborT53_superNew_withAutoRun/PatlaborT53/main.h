#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
//#include <cmath>

// Include .h
// OpenGL
#include "vgl.h"
// Shader
#include "LoadShaders.h"
// Object
#include "objloader.hpp"
// Cube
#include "CubemapShader.h"
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#define PARTSNUM 14
#define BODY 0
#define HEAD 1
#define LEFTUPPERARM 2
#define LEFTLOWERARM 3
#define LEFTHAND 4
#define RIGHTUPPERARM 5
#define RIGHTLOWERARM 6
#define RIGHTHAND 7
#define LEFTTHIGH 8
#define LEFTSHANK 9
#define LEFTFOOT 10
#define RIGHTTHIGH 11
#define RIGHTSHANK 12
#define RIGHTFOOT 13

void updateModels();

void dumpInformation(void);
GLuint M_KaID;
GLuint M_KdID;
GLuint M_KsID;
void init();

void ChangeSize(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);
void Mouse(int button, int state, int x, int y);
void motion(int x, int y);
void menuEvents(int option);
void ModeMenuEvents(int option);
void SceneMenuEvents(int option);
void ActionMenuEvents(int option);
void ShaderMenuEvents(int option);
#define DOR(angle) (angle * 3.1415/180);
void display();

void idle(int dummy);
void autoRun(int eventNo);

mat4 translate(float x, float y, float z);
mat4 scale(float x, float y, float z);
mat4 rotate(float angle, float x, float y, float z);

void Obj2Buffer();
void load2Buffer(const char* obj, int);

void resetObj(int);
void atEase(int);
void salute(int);
void walk(int);
void run(int);
void squats(int);
void jump(int);
void petanque(int);
void lose(int);
void breakingKS(int);
void breakingICE(int);
void lockingWT(int);
void lockingSH(int);

bool isFrame;
int frameCounter;
int winWidth, winHeight;
int lookDistance;

GLuint pointSpriteProgID;
GLuint VAO;
GLuint VBO;
GLuint uVBO;
GLuint nVBO;
GLuint mVBO;
GLuint UBO;
GLuint VBOs[PARTSNUM];
GLuint uVBOs[PARTSNUM];
GLuint nVBOs[PARTSNUM];
GLuint program;
int shaderNo;
int sceneNo;

struct Angle
{
	float X = 0.0, // Angle of X
		Y = 0.0, // Angle of Y
		Z = 0.0; // Angle of Z
};
Angle modelAngle[PARTSNUM];
float bodyPosition[3] = { 0, 0, 0 };
/*
float angles[PARTSNUM];
float angle = 0.0;
float position = 0.0;
*/
float eyeAngley = 0.0;
float eyedistance = 20.0;
float size = 1;
GLfloat movex, movey;
GLint MatricesIdx;
GLuint ModelID;

GLint partLocation;

ShaderInfo shaderList[][3] = {
	// Normal
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material0.fp" },
	{ GL_NONE, NULL } },
	// Purple
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material1.fp" }, 
	{ GL_NONE, NULL } },
	// Transparent
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material2.fp" },
	{ GL_NONE, NULL } },
	// Gray scale
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material3.fp" },
	{ GL_NONE, NULL } },
	// Colorful
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material4.fp" }, 
	{ GL_NONE, NULL } },
	// Complement
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material5.fp" },
	{ GL_NONE, NULL } },
	// Black and white
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material6.fp" },
	{ GL_NONE, NULL } },
	// Ghost
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material7.fp" },
	{ GL_NONE, NULL } },
	// Black dots
	{ { GL_VERTEX_SHADER, "DSPhong_Material.vp" },
	{ GL_FRAGMENT_SHADER, "DSPhong_Material8.fp" },
	{ GL_NONE, NULL } },
};

typedef struct {
	string right,
		left,
		down,
		top,
		front,
		back;
} Cube;

Cube cubeFilesName[][6] = {
	// Hangar
	{ "../Cubemap/Hangar/right.png",
	"../Cubemap/Hangar/left.png",
	"../Cubemap/Hangar/down.png", 
	"../Cubemap/Hangar/top.png",
	"../Cubemap/Hangar/front.png",
	"../Cubemap/Hangar/back.png" },
	// Sea
	{  "../Cubemap/ThickCloudsWater/right.png",
	"../Cubemap/ThickCloudsWater/left.png",
	"../Cubemap/ThickCloudsWater/down.png",
	"../Cubemap/ThickCloudsWater/top.png",
	"../Cubemap/ThickCloudsWater/front.png",
	"../Cubemap/ThickCloudsWater/back.png" }
};

int vertices_size[PARTSNUM];
int uvs_size[PARTSNUM];
int normals_size[PARTSNUM];
int materialCount[PARTSNUM];

std::vector<std::string> mtls[PARTSNUM];//use material
std::vector<unsigned int> triangleFaces[PARTSNUM];//face count
map<string, vec3> KDs;//mtl-name&Kd
map<string, vec3> KSs;//mtl-name&Ks

mat4 Projection;
mat4 View;
mat4 Model;

// Model matrix
mat4 models[PARTSNUM];
// Rotate matrix
mat4 rotation[PARTSNUM];
// Translate matrix
mat4 translation[PARTSNUM];
// Action number
#define ATTENTION		0
#define ATEASE		1
#define SALUTE		2
#define WALK		3
#define RUN			4
#define SQUATS		5
#define JUMP		6
#define PETANQUE	7
#define LOSE		8
#define BREAKINGKS		9
#define BREAKINGICE		10
#define LOCKINGTWIRL	11
#define LOCHINGSCOOBA	12

int lastAction = 0;
int action;

int mouseX, mouseY;

int interval = 100;
int autoRunInterval = 3000;
bool prepared4AutoRun = false;
bool stopAutoRun = false;

CubemapShader cubemapShader;