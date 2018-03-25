#include "Constants.h"

enum move_direction {
	left, right, none
};

struct AABB
{
	Vec2d min;
	Vec2d max;
	AABB(const Vec2d& _min, const Vec2d& _max) : min(_min), max(_max) {}
	AABB() : min(Vec2d()), max(Vec2d()) {}
};

struct colour
{
	int r;
	int g;
	int b;
	colour(const int& _r, const int& _g, const int& _b) : r(_r), g(_g), b(_b) {}
	colour() : r(0), g(0), b(0) {}
};

int BUNNY_MAX_SPEED_Y = 700;
int BUNNY_SPEED_X = 500;
Vec2d BUNNY_ACCELERATION(0, 900);
int BUNNY_WIDTH = 100;
int BUNNY_HEIGHT = 100;
int PLATFORM_HEIGHT = 20;
int SCENE_VELOCITY_ANIMATION = 400;
int PLATFORM_SPEED_X = 100;
int BUNNY_JUMP_VELOCITY = -700;
int PLATFORM_MAX_WIDTH = 200;
int PLATFORM_MIN_WIDTH = 150;
int PLATFORM_HEIGHT_OFF_SCREEN = 500;
int PLATFORM_ADD_EVERY_HEIGHT = 250;
float SCENE_HEIGHT_MAXIMUM = 2.0;
int NUMBER_OF_PLATFORMS = 10;
int PLATFORM_HIGHEST_STABLE_HEIGHT = 700;
int BUNNY_HITBOX_WIDTH_START = 25;
int BUNNY_HITBOX_WIDTH_END = 75;
int BUNNY_HITBOX_HEIGHT = 10;
int PLATFORM_HITBOX_HEIGHT = 10;
int PLATFORM_SPEED_INITIAL = 200;
float PLATFORM_SPEED_MULTIPLIER = 0.05;