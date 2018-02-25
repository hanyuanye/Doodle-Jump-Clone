#pragma once
#include "Vec2d.h"

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

const int BUNNY_MAX_SPEED_Y = 700;
const int BUNNY_SPEED_X = 500;
const Vec2d BUNNY_ACCELERATION(0, 900);

const int BUNNY_WIDTH = 100;
const int BUNNY_HEIGHT = 100;

const int PLATFORM_HEIGHT = 20;
const int SCENE_VELOCITY_ANIMATION = 400;

const colour BUNNY_COLOUR(255, 255, 255);

const colour PLATFORM_COLOUR(255, 255, 255);

const int PLATFORM_SPEED_X = 100;

const int BUNNY_JUMP_VELOCITY = -700;

const int PLATFORM_MAX_WIDTH = 200;
const int PLATFORM_MIN_WIDTH = 150;
const int PLATFORM_HEIGHT_OFF_SCREEN = 500;
const int PLATFORM_ADD_EVERY_HEIGHT = 250;
const float SCENE_HEIGHT_MAXIMUM = 2.0;
const int NUMBER_OF_PLATFORMS = 10;

const int PLATFORM_HIGHEST_STABLE_HEIGHT = 700;
