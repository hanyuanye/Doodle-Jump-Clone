#include "GameObject.h"

const int BUNNY_MAX_SPEED_Y = 700;
const int BUNNY_SPEED_X = 500;
const Vec2d BUNNY_ACCELERATION(0, 1000);

const int BUNNY_WIDTH = 100;
const int BUNNY_HEIGHT = 100;

const int BUNNY_HITBOX_WIDTH_START = 25;
const int BUNNY_HITBOX_WIDTH_END = 75;
const int BUNNY_HITBOX_HEIGHT = 10;

const int PLATFORM_HEIGHT = 20;
const int PLATFORM_HITBOX_HEIGHT = 10;
const int SCENE_VELOCITY_ANIMATION = 400;

const colour BUNNY_COLOUR(255, 255, 255);

const colour PLATFORM_COLOUR(255, 255, 255);

const int PLATFORM_SPEED_INITIAL = 200;
const float PLATFORM_SPEED_MULTIPLIER = 0.05;

GameObject::GameObject()
{
}

GameObject::~GameObject()
{

}

PlayerObject::PlayerObject(SDL_Renderer * _ren, const Vec2d & _pos, const int & SCREEN_WIDTH)
{
	ren = _ren;
	pos = _pos;
	acceleration = BUNNY_ACCELERATION;
	Vec2d min(BUNNY_HITBOX_WIDTH_START + pos.get_x(), BUNNY_HEIGHT + pos.get_y() - BUNNY_HITBOX_HEIGHT);
	Vec2d max(BUNNY_HITBOX_WIDTH_END + pos.get_x(), BUNNY_HEIGHT + pos.get_y());
	auto sp1 = std::make_shared<AABB>(min, max);
	hitbox = sp1;

	manager = new TextureManager(ren, "Assets/bunny_sprite.png", BUNNY_COLOUR.r, BUNNY_COLOUR.g, BUNNY_COLOUR.b, BUNNY_WIDTH, BUNNY_HEIGHT);

	max_speed_y = BUNNY_MAX_SPEED_Y;
	this->SCREEN_WIDTH = SCREEN_WIDTH;
}

void PlayerObject::update(const float & time_step, const bool & drop_animation, const move_direction & move)
{
	if (drop_animation) {
		max_speed_y = BUNNY_MAX_SPEED_Y + SCENE_VELOCITY_ANIMATION;
		velocity += Vec2d(0, SCENE_VELOCITY_ANIMATION);
	}
	else {
		max_speed_y = BUNNY_MAX_SPEED_Y;
	}
	switch (move) {
	case left:
		velocity.set_x(-BUNNY_SPEED_X);
		break;
	case right:
		velocity.set_x(BUNNY_SPEED_X);
		break;
	case none:
		velocity.set_x(0);
		break;
	default:
		break;
	}

	if (velocity.get_y() <= max_speed_y) {
		velocity += acceleration.scalarMultiple(time_step);
	}
	pos += velocity.scalarMultiple(time_step);

	Vec2d min(BUNNY_HITBOX_WIDTH_START + pos.get_x(), BUNNY_HEIGHT + pos.get_y() - BUNNY_HITBOX_HEIGHT);
	Vec2d max(BUNNY_HITBOX_WIDTH_END + pos.get_x(), BUNNY_HEIGHT + pos.get_y());
	hitbox->min = min;
	hitbox->max = max;

	if (drop_animation) {
		velocity -= Vec2d(0, SCENE_VELOCITY_ANIMATION);
	}
}

void PlayerObject::render()
{
	manager->render(pos);
}

void PlayerObject::clear()
{
	delete manager;
}

int PlayerObject::get_velocity_y()
{
	return int(velocity.get_y());
}

int PlayerObject::get_position_y()
{
	return int(pos.get_y());
}

void PlayerObject::set_velocity_y(const int& _y)
{
	velocity.set_y(float(_y));
}

void PlayerObject::set_velocity_x(const int & _x)
{
	velocity.set_x(float(_x));
}

void PlayerObject::set_acceleration(const Vec2d& _acceleration)
{
	acceleration = _acceleration;
}




PlatformObject::PlatformObject(SDL_Renderer* _ren, const Vec2d& _pos, const int& width, const move_direction& _move, const int & SCREEN_WIDTH)
{
	ren = _ren;
	pos = _pos;
	Vec2d min = pos;
	Vec2d max(width + pos.get_x(), PLATFORM_HITBOX_HEIGHT + pos.get_y());
	platform_width = width;
	velocity = Vec2d();
	auto sp1 = std::make_shared<AABB>(min, max);
	hitbox = sp1;

	manager = new TextureManager(ren, "Assets/platform_sprite.png", PLATFORM_COLOUR.r, PLATFORM_COLOUR.g, PLATFORM_COLOUR.b, width, PLATFORM_HEIGHT);
	move = _move;
	this->SCREEN_WIDTH = SCREEN_WIDTH;

	speed_x = PLATFORM_SPEED_INITIAL;
}

void PlatformObject::update(const float &time_step, const bool & drop_animation, const move_direction & )
{
	if (drop_animation) {
		velocity += Vec2d(0, SCENE_VELOCITY_ANIMATION);
	}

	switch (move) {
	case left:
		velocity.set_x(-speed_x);
		break;
	case right:
		velocity.set_x(speed_x);
		break;
	case none:
		velocity.set_x(0);
		break;
	default:
		break;
	}

	pos += velocity.scalarMultiple(time_step);

	if (pos.get_x() < 0) {
		move = right;
	}
	if (pos.get_x() >= SCREEN_WIDTH - platform_width) {
		move = left;
	}
	Vec2d max(platform_width + pos.get_x(), PLATFORM_HITBOX_HEIGHT + pos.get_y());
	hitbox->min = pos;
	hitbox->max = max;

	if (drop_animation) {
		velocity -= Vec2d(0, SCENE_VELOCITY_ANIMATION);
	}
}

void PlatformObject::render()
{
	manager->render(pos);
}

void PlatformObject::clear()
{
	delete manager;
}

void PlatformObject::set_pos(const Vec2d & _pos)
{
	pos = _pos;
}

void PlatformObject::set_velocity_y(const int & _velocity_y)
{
	velocity.set_y(_velocity_y);
}

void PlatformObject::increase_speed(const float &score)
{
	speed_x = PLATFORM_SPEED_INITIAL + score * PLATFORM_SPEED_MULTIPLIER;
}
