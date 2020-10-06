#pragma once
#include "Object.h"
#include <string>
#include <vector>

static std::string enemyType[] = {
	"Dally", "Gun", "Knife"
};
enum Arms {
	DALLY = 0, PISTOL, SABER
};
static Arms armsList[3] = { Arms::DALLY, Arms::PISTOL, Arms::SABER };
enum Death {
	STAB = 0, SHOT, BOMB
};
enum Side {
	LSIDE = 0, RSIDE
};
enum EnemyState {
	E_IDLE, E_WALK, E_ATTACK
};

// Range: 0.0 - 0.925
static float mapLocationList[] = {
	0.050, 0.105, 0.152, 0.382, 0.727, 0.255, 0.413, 0.436, 0.086, 0.835,
	0.233, 0.274, 0.867, 0.177, 0.762, 0.754, 0.820, 0.299, 0.589, 0.666
};
// sorted: 
// 0.013, 0.086, 0.105, 0.152, 0.177, 0.233, 0.255, 0.274, 0.299, 0.382, 0.413, 0.436, 0.589, 0.666, 0.727, 0.754, 0.762, 0.820, 0.835, 0.867

class Enemy : public Object {
public:
	static int enemyNum;

	// Born
	Enemy();
	Enemy(Arms, Side, float, float, float);

	// Death
	~Enemy();
	
	void setScreenPosX(float);
	float getMapLocationX();
	void killed(Death);

	int getSpriteId(void);

	// Left
	void dallyLeft(void);
	void pistolLeft(void);
	void saberLeft(void);
	void restLeft(void);
	void walkLeft(float);
	void deathLeft();

	// Right
	void dallyRight(void);
	void pistolRight(void);
	void saberRight(void);
	void restRight(void);
	void walkRight(float);
	void deathRight();

	Arms type;
	Side side;
	Death deathType;
	EnemyState state;

	int running = 0;
	int step = 0;
	bool isDieing;
private:
	void initSprite(void);

	// Left
	Sprite2D dallyLeftSprite;
	Sprite2D pistolLeftSprite;
	Sprite2D saberLeftSprite;
	Sprite2D restLeftSprite;
	Sprite2D walkLeftSprite;
	Sprite2D deathKnifeLeftSprite;
	Sprite2D deathGunLeftSprite;
	Sprite2D deathGrenadeLeftSprite;

	// Right
	Sprite2D dallyRightSprite;
	Sprite2D pistolRightSprite;
	Sprite2D saberRightSprite;
	Sprite2D restRightSprite;
	Sprite2D walkRightSprite;
	Sprite2D deathKnifeRightSprite;
	Sprite2D deathGunRightSprite;
	Sprite2D deathGrenadeRightSprite;
};