#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "Vec2d.h"
#include "TextureManager.h"
#include <iostream>

/*This class actually is the interface to two other classes, Platform and Player
* Player defines and implements the controllable sprite
* There are only a set number of platforms. Platforms are recycled to new positions above the screen when they go below screen.
* This code was iterated on a lot. Therefore, the design in some places doesn't really make sense. For example, the interface
* should really define a lot more things such as rendering information. There should be a struct storing all relevant physical
* data like velocity, position, acceleration etc. and this should really be stored in a data struct for legibility. 

* This should also have been designed to be flexible enough to provide an interface for Power ups as well.
* What this means is that collision resolution should have been defined here. Therefore, an object would be able to interact
* with another object and change it's own data accordingly. 
*/
enum move_direction {
	left, right, none
};

struct AABB 
{
	Vec2d min;
	Vec2d max;
	AABB(const Vec2d& _min, const Vec2d& _max) : min(_min), max(_max) {}
	AABB() : min(Vec2d()), max(Vec2d()){}
};

struct colour
{
	int r;
	int g;
	int b;
	colour(const int& _r, const int& _g, const int& _b) : r(_r), g(_g), b(_b) {}
	colour() : r(0), g(0), b(0) {}
};

class GameObject
{
public:
	GameObject();
	~GameObject();
	virtual void update(const float &time_step, const bool & drop_animation, const move_direction &) = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
	std::shared_ptr <AABB> hitbox;
protected:
	SDL_Renderer * ren;
	Vec2d pos;
	Vec2d velocity;
	Vec2d acceleration;
	
};

class PlayerObject : public GameObject
{
public:
	PlayerObject(SDL_Renderer* , const Vec2d&, const int &);
	void update( const float &, const bool&, const move_direction &);
	void render();
	void clear();

	int get_velocity_y();
	int get_position_y();

	void set_velocity_y(const int&);
	void set_velocity_x(const int&);
	void set_acceleration(const Vec2d&);
	
private:
	TextureManager * manager;
	SDL_Rect * rect;
	int max_speed_y;
	int SCREEN_WIDTH;

};


class PlatformObject : public GameObject
{
public:
	PlatformObject(SDL_Renderer*, const Vec2d&, const int&, const move_direction &, const int &);
	void update(const float &, const bool &, const move_direction &);
	void render();
	void clear();

	void set_pos(const Vec2d&);
	void set_velocity_y(const int&);
	void increase_speed(const float&);

private:
	TextureManager * manager;
	SDL_Texture * obj_tex;
	SDL_Rect * rect;

	int platform_width;
	move_direction move;
	int SCREEN_WIDTH;

	int speed_x;

};
