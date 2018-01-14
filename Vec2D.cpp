#include "Vec2D.h"

#include <math.h>

#ifdef DEBUG_MODE
#include <iostream>
#endif

Vec2D::Vec2D() : x(0.0), y(0.0)
{}

Vec2D::Vec2D(double x, double y) : x(x), y(y) 
{}

Vec2D::Vec2D(const Vec2D& v) : x(v.x), y(v.y) 
{}

Vec2D::Vec2D(double angle)
{
	this->x = cos(angle);
	this->y = sin(angle);
}

Vec2D& Vec2D::operator = (const Vec2D& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

bool Vec2D::operator == (const Vec2D& v) const
{
	return fabs(x - v.x) < EPS && fabs(y - v.y) < EPS;
}

bool Vec2D::operator != (const Vec2D& v) const
{
	return fabs(x - v.x) >= EPS || fabs(y - v.y) >= EPS;
}

bool Vec2D::isZero() const
{
	return fabs(x) < EPS && fabs(y) < EPS;
}

double Vec2D::getX() const
{
	return this->x;
}

double Vec2D::getY() const
{
	return this->y;
}

double Vec2D::dot(const Vec2D& v) const
{
	if (this->isZero() || v.isZero()) return 0.0;
	return x * v.x + y * v.y;
}

double Vec2D::getLength() const
{
	if (this->isZero()) return 0.0;
	return sqrt(x * x + y * y);
}

double Vec2D::getLengthSquared() const
{
	if (this->isZero()) return 0.0;
	return x * x + y * y;
}

double Vec2D::getAngle() const
{
	if (this->isZero()) return 0.0;
	return atan2(y, x);
}

double Vec2D::getDistance(double x, double y) const
{
	return sqrt((x - this->x)*(x - this->x) + (y - this->y)*(y - this->y));
}

double Vec2D::getDistance(const Vec2D& v) const
{
	return sqrt((v.x - this->x)*(v.x - this->x) + (v.y - this->y)*(v.y - this->y));
}

double Vec2D::getDistanceSquare(double x, double y) const
{
	return (x - this->x)*(x - this->x) + (y - this->y)*(y - this->y);
}

double Vec2D::getDistanceSquare(const Vec2D& v) const
{
	return (v.x - this->x)*(v.x - this->x) + (v.y - this->y)*(v.y - this->y);
}

Vec2D Vec2D::getUnit() const
{
	if (this->isZero()) return Vec2D();
	double l = this->getLength();
	if (fabs(l - 1.0) >= EPS) {
		return Vec2D(this->x / l, this->y / l);
	}
	return Vec2D(*this);
}

Vec2D Vec2D::getRightPerpend() const
{
	if (this->isZero()) return Vec2D();
	return Vec2D(-this->y, this->x);
}

Vec2D Vec2D::getLeftPerpend() const
{
	if (this->isZero()) return Vec2D();
	return Vec2D(this->y, -this->x);
}

Vec2D Vec2D::getReversed() const
{
	if (this->isZero()) return Vec2D();
	return Vec2D(-this->x, -this->y);
}

Vec2D Vec2D::getRotated(double angle) const
{
	if (this->isZero()) return Vec2D();
	double sinVal = sin(angle);
	double cosVal = cos(angle);
	return Vec2D(x * cosVal - y * sinVal, x * sinVal + y * cosVal);
}

Vec2D Vec2D::getScaled(double len) const
{
	if (this->isZero()) return Vec2D();
	double angle = this->getAngle();
	return Vec2D(len * cos(angle), len * sin(angle));
}

Vec2D Vec2D::add(const Vec2D& v) const
{
	return Vec2D(this->x + v.x, this->y + v.y);
}

Vec2D Vec2D::sub(const Vec2D& v) const
{
	return Vec2D(this->x - v.x, this->y - v.y);
}

Vec2D Vec2D::mul(double val) const
{
	if (this->isZero()) return Vec2D();
	return Vec2D(this->x * val, this->y * val);
}

void Vec2D::set(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Vec2D::set(const Vec2D& v)
{
	this->x = v.x;
	this->y = v.y;
}

void Vec2D::normalize()
{
	if (this->isZero()) return;
	double l = this->getLength();
	if (fabs(l - 1.0) >= EPS) {
		this->x /= l;
		this->y /= l;
	}
}

void Vec2D::rotate(double angle)
{
	if (this->isZero()) return;
	double sinVal = sin(angle);
	double cosVal = cos(angle);
	double xNew = x * cosVal - y * sinVal;
	this->y = x * sinVal + y * cosVal;
	this->x = xNew;
}

void Vec2D::reverse()
{
	if (this->isZero()) return;
	this->x = -this->x;
	this->y = -this->y;
}

void Vec2D::scale(double len)
{
	if (this->isZero()) return;
	double l = this->getLength();
	this->x *= len / l;
	this->y *= len / l;
}

void Vec2D::print() const
{
#ifdef DEBUG_MODE
	std::cout << "x: " << this->x << "	y: " << this->y << std::endl;
#endif
}
