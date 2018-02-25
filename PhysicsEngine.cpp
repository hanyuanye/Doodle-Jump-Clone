#include "PhysicsEngine.h"

const int BUNNY_JUMP_VELOCITY = -700;

const int PLATFORM_MAX_WIDTH = 200;
const int PLATFORM_MIN_WIDTH = 150;
const int PLATFORM_HEIGHT_OFF_SCREEN = 150;
const int PLATFORM_ADD_EVERY_HEIGHT = 250;
const float SCENE_HEIGHT_MAXIMUM = 2.0;
const int NUMBER_OF_PLATFORMS = 4;

const int PLATFORM_HIGHEST_STABLE_HEIGHT = 700;

PhysicsEngine::PhysicsEngine()
{
	srand(time(NULL));
}

PhysicsEngine::PhysicsEngine(SDL_Renderer * _ren, const float& _time_step, const int& _width, const int& _height)
{
	srand(time(NULL));
	ren = _ren;
	time_step = _time_step;
	SCREEN_WIDTH = _width;
	SCREEN_HEIGHT = _height;
	move = none;
	add_object("player", Vec2d(100, 100));
	add_object("platform", Vec2d(100, 500));
	int platform_height = 0;
	for (int i = 1; i <= NUMBER_OF_PLATFORMS; i++) {
		platform_height += SCREEN_HEIGHT / NUMBER_OF_PLATFORMS;
		add_object("platform", Vec2d(get_rand_screen_width(), platform_height));
	}
	score = 0;

	gameover = false;
}


PhysicsEngine::~PhysicsEngine()
{
	for (int i = 0; i < platform_list.size(); i++) {
		remove_object(i);
	}
}

void PhysicsEngine::add_object(std::string name, const Vec2d& pos)
{
	if (name == "player") {
		auto sp1 = std::make_shared<PlayerObject>(ren, pos, SCREEN_WIDTH);
		player = sp1;
	}

	if (name == "platform") {
		int width = get_rand_platform_width();
		move_direction platform_rand_move = left;
		auto sp1 = std::make_shared<PlatformObject>(ren, pos, width, platform_rand_move, SCREEN_WIDTH);
		platform_list.push_back(sp1);
	}
}

void PhysicsEngine::remove_object(int index)
{
	platform_list.erase(platform_list.begin() + index);
}

void PhysicsEngine::update()
{
	collission_detect();
	if (platform_at_player_height != NULL) {
		drop_animation = (platform_at_player_height->hitbox->max.get_y() <= PLATFORM_HIGHEST_STABLE_HEIGHT);
	}
	else {
		drop_animation = false;
	}
	for (int i = 0; i < platform_list.size(); i++) {
		platform_list[i]->update(time_step, drop_animation, none);
		if (platform_list[i]->hitbox->max.get_y() > SCREEN_HEIGHT) {
			Vec2d v(get_rand_screen_width(), get_rand_off_screen_height());
			platform_list[i]->set_pos(v);
		}
		platform_list[i]->increase_speed(score);
	}
	player->update(time_step, drop_animation, move);

	if (player->hitbox->max.get_y() > SCREEN_HEIGHT) {
		gameover = true;
	}
}

void PhysicsEngine::render()
{
	SDL_RenderClear(ren);
	for (int i = 0; i < platform_list.size(); i++) {
		platform_list[i]->render();
	}
	player->render();
	SDL_RenderPresent(ren);
}

void PhysicsEngine::collission_detect()
{
	for (int i = 0; i < platform_list.size(); i++) {
		if (collision_AABB_AABB(player->hitbox, platform_list[i]->hitbox) && player->get_velocity_y() > 0) {
			platform_at_player_height = NULL;
			resolve_collision(player, platform_list[i]);
		}
	}
}

bool PhysicsEngine::collision_AABB_AABB(std::shared_ptr<AABB> a, std::shared_ptr<AABB> b)
{
	if (a->max.get_x() > b->min.get_x() &&
		a->min.get_x() < b->max.get_x() &&
		a->max.get_y() > b->min.get_y() &&
		a->min.get_y() < b->max.get_y()) {
		return true;
	}
	return false;
}

void PhysicsEngine::resolve_collision(std::shared_ptr<PlayerObject> player, std::shared_ptr<PlatformObject> platform)
{
	player->set_velocity_y(BUNNY_JUMP_VELOCITY);
	if (platform->hitbox->max.get_y() < PLATFORM_HIGHEST_STABLE_HEIGHT) {
		platform_at_player_height = platform;
		score += PLATFORM_HIGHEST_STABLE_HEIGHT - platform->hitbox->max.get_y();
	}
}

int PhysicsEngine::get_rand_platform_width()
{
	return rand() % (PLATFORM_MAX_WIDTH - PLATFORM_MIN_WIDTH) + PLATFORM_MIN_WIDTH;
}

int PhysicsEngine::get_rand_off_screen_height()
{
	return 0 - rand() % SCREEN_HEIGHT % NUMBER_OF_PLATFORMS;
}

int PhysicsEngine::get_rand_screen_width()
{
	return rand() % (SCREEN_WIDTH - PLATFORM_MAX_WIDTH);
}

