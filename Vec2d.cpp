#include "Vec2d.h"

Vec2d::Vec2d()
{
	x = 0;
	y = 0;
}

Vec2d::Vec2d(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vec2d::Vec2d(const Vec2d & v)
{
	x = v.get_x();
	y = v.get_y();
}

Vec2d Vec2d::operator=(const Vec2d & v)
{
	x = v.get_x();
	y = v.get_y();
	return Vec2d();
}

Vec2d Vec2d::operator+(const Vec2d & v) const
{
	Vec2d result;
	result.set_x(this->x + v.get_x());
	result.set_y(this->y + v.get_y());
	return result;
}

Vec2d Vec2d::operator+=(const Vec2d & v)
{
	this->set_x(this->x + v.get_x());
	this->set_y(this->y + v.get_y());
	return *this;
}

Vec2d Vec2d::operator-(const Vec2d & v) const
{
	Vec2d result;
	result.set_x(this->x - v.get_x());
	result.set_y(this->y - v.get_y());
	return result;
}

Vec2d Vec2d::operator-=(const Vec2d & v)
{
	this->set_x(this->x - v.get_x());
	this->set_y(this->y - v.get_y());
	return *this;
}

float Vec2d::dotProduct(const Vec2d & v) const
{
	return (x * v.get_x() + y * v.get_x());
}

float Vec2d::crossProduct(const Vec2d & v) const
{
	return (x * v.get_y() - y * v.get_x());
}

Vec2d Vec2d::scalarMultiple(const float &scalar)
{
	Vec2d result(x*scalar, y*scalar);
	return result;
}

float Vec2d::get_x() const
{
	return x;
}

float Vec2d::get_y() const
{
	return y;
}

void Vec2d::set_x(const float & _x)
{
	x = _x;
}

void Vec2d::set_y(const float & _y)
{
	y = _y;
}

void Vec2d::set_vector(const float & _x, const float & _y)
{
	x = _x;
	y = _y;
}

