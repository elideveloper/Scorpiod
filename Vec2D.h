#pragma once

#include "utility.h"

class Vec2D {
	double x;
	double y;
public:
	Vec2D();
	Vec2D(double x, double y);
	Vec2D(const Vec2D& v);
	Vec2D(double angle);
	Vec2D& operator = (const Vec2D& v);
	bool operator == (const Vec2D& v) const;
	bool operator != (const Vec2D& v) const;
	bool isZero() const;
	double getX() const;
	double getY() const;
	double dot(const Vec2D& v) const;
	double getLength() const;
	double getLengthSquared() const;
	double getAngle() const;
	double getDistance(double x, double y) const;
	double getDistance(const Vec2D& v) const;
	double getDistanceSquare(double x, double y) const;
	double getDistanceSquare(const Vec2D& v) const;
	Vec2D getUnit() const;
	Vec2D getRightPerpend() const;
	Vec2D getLeftPerpend() const;
	Vec2D getReversed() const;
	Vec2D getRotated(double angle) const;
	Vec2D getScaled(double len) const;
	Vec2D add(const Vec2D& v) const;
	Vec2D sub(const Vec2D& v) const;
	Vec2D mul(double val) const;
	void set(double x, double y);
	void set(const Vec2D& v);
	void normalize();
	void rotate(double angle);
	void reverse();
	void scale(double len);

	void print() const;
};