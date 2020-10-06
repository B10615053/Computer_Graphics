#pragma once
#include "Object.h"
#include <string>
#include <iostream>

#define MAX_KEY_NUM			256
#define INIT_MAP_LOC_X		(-0.036f)
#define INIT_MAP_LOC_Y		(-0.8f)
#define TEX_SIZE_WIDTH		(0.17f)
#define BLINK_TIME			70

//static std::string stateSymbols[] = {
//	"Idle", "Walk", "Stop", "Jump", "Fall", "JumpForward", "Redirect", "Knife" ,"Gun", "Grenade", "Up", "GunUp" , "IdleUp"
//};
enum State {
	IDLE,
	WALK,
	STOP,
	JUMP,
	FALL,
	JUMP_FORWARD,
	REDIRECT,
	KNIFE,
	GUN,
	GRENADE,
	UP,
	GUNUP,
	IDLEUP,
	DEATH_WHICH_ATTACK_FROM_LEFT,
	DEATH_WHICH_ATTACK_FROM_RIGHT,
	VICTORY
};
enum Direction {
	LEFT, RIGHT
};

class Marco: public Object
{
public:
	bool atCentre;

	Marco();
	~Marco();
	void setKeyboard(int, bool);
	bool getKeyboard(int);

	void reborn();

	int getSpriteId(void);

	void idleLeftTest(void);
	// Left
	void LtoR(void);
	void idleLeft(void);
	void stopLeft(void);
	void walkLeft(float);
	void upLeft(void);
	void idleUpLeft(void);
	void downLeft(void);
	void jumpLeft(void);
	void fallLeft(void);
	void knifeLeft(void);
	void shootLeft(void);
	void shootUpLeft(void);
	void grenadeLeft(void);
	void deathLeft(void);
	void victoryLeft(glm::vec2);

	// Right
	void RtoL(void);
	void idleRight(void);
	void stopRight(void);
	void walkRight(float);
	void upRight(void);
	void idleUpRight(void);
	void downRight(void);
	void jumpRight(void);
	void fallRight(void);
	void knifeRight(void);
	void shootRight(void);
	void shootUpRight(void);
	void grenadeRight(void);
	void deathRight(void);
	void victoryRight(glm::vec2);

	State state;
	Direction direction;
	int blinkingCounter;
	glm::vec3 dotLightScreenPos3D;
	bool isDieing;
	bool isDead;
	bool noDamageStatus;

private:
	void initSprite(void);

	Sprite2D idleLeftTestSprite;
	// Left
	Sprite2D LtoRSprite;
	Sprite2D idleLeftSprite;
	Sprite2D stopLeftSprite;
	Sprite2D walkLeftSprite;
	Sprite2D upLeftSprite;
	Sprite2D idleUpLeftSprite;
	Sprite2D downLeftSprite;
	Sprite2D jumpLeftSprite;
	Sprite2D fallLeftSprite;
	Sprite2D knifeLeftSprite;
	Sprite2D shootLeftSprite;
	Sprite2D shootUpLeftSprite;
	Sprite2D grenadeLeftSprite;
	Sprite2D deathLeftSprite;
	Sprite2D victoryLeftSprite;

	// Right
	Sprite2D RtoLSprite;
	Sprite2D idleRightSprite;
	Sprite2D stopRightSprite;
	Sprite2D walkRightSprite;
	Sprite2D upRightSprite;
	Sprite2D idleUpRightSprite;
	Sprite2D downRightSprite;
	Sprite2D jumpRightSprite;
	Sprite2D fallRightSprite;
	Sprite2D knifeRightSprite;
	Sprite2D shootRightSprite;
	Sprite2D shootUpRightSprite;
	Sprite2D grenadeRightSprite;
	Sprite2D deathRightSprite;
	Sprite2D victoryRightSprite;

	bool keyboardState[MAX_KEY_NUM];
	GLint blinkingLocation;
	GLint dotLightScreenPos3DLocation;
};