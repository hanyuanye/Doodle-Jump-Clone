/* This class defines the main logic for the game.
*  It defines the collision detection routine, collision resolution
*  As well as has information on all objects. It defines what happens
*  when two objects collide.
*
*  It also holds all information on the current state. It keeps
*  a platform at player height which gets updated as the player
*  progresses through the game. Whenever a platform falls below this
*  and below the screen, it gets recycled to a new position above the screen.
*  
*  Collision detection is just a simple AABB detection routine that compares
*  all platforms with the player. This could be optimized but it is unnecessary.
*  Collision resolution only adjusts the velocity of the player. 
*  
*  This class does not define any part of the game that happens outside of the
*  actual physics. For example, once gameover is returned, the Game class will 
*  run it's own gameOver function. If a start screen were to be implemented, it
*  would be implemented in the Game class.
*/
#pragma once
#include <vector>
#include <string>
#include <memory>
#include <time.h>
#include <stdlib.h>
#include "GameObject.h"

extern colour BACKGROUND_COLOUR;
extern const int SCENE_VELOCITY_ANIMATION;

class PhysicsEngine
{
public:
	PhysicsEngine();
	PhysicsEngine(SDL_Renderer * _ren, const float& _time_step, const int& _width, const int& _height);
	~PhysicsEngine();
	void add_object(std::string name, const Vec2d& pos); //Adds an object based on name and position, should have done it based on enum system
	void remove_object(int index); 
	void update();
	void render();

	void collission_detect(); //Collision detection routine involving looping thourhg platform list and checking against player sprite
	bool collision_AABB_AABB(std::shared_ptr<AABB>, std::shared_ptr<AABB>); //Helper method to return if two AABBs are colliding
	void resolve_collision(std::shared_ptr<PlayerObject>, std::shared_ptr<PlatformObject>); 

	move_direction move;
	int score;
	bool gameover;

private:

	int get_rand_platform_width();
	int get_rand_off_screen_height();
	int get_rand_screen_width();

	std::shared_ptr<PlayerObject> player;
	std::vector<std::shared_ptr<PlatformObject>> platform_list; 
	std::shared_ptr<PlatformObject> platform_at_player_height;
	SDL_Renderer * ren;
	float time_step;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;


	bool drop_animation;

};

