#pragma once
#include <vector>

class Vec2d
{
private:
	float x;
	float y;

public:
	Vec2d();
	Vec2d(float _x, float _y);
	Vec2d(const Vec2d& v);

	Vec2d operator=(const Vec2d&);
	Vec2d operator+(const Vec2d&) const;
	Vec2d operator+=(const Vec2d&);
	Vec2d operator-(const Vec2d&) const;
	Vec2d operator-=(const Vec2d&);

	float dotProduct(const Vec2d&) const;
	float crossProduct(const Vec2d&) const;
	Vec2d scalarMultiple(const float&);

	float get_x() const;
	float get_y() const;

	void set_x(const float &_x);
	void set_y(const float &_y);
	void set_vector(const float  &_x, const float  &_y);


};