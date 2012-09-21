#pragma once
#include "cinder/gl/gl.h"

using namespace ci;

class Circle
{
public:
	Circle(Vec2f pos, float radius, Color8u c);
	Vec2f pos_;
	float radius_;
	Color8u color_;

	void isInCircle(Vec2f click);
	float getRadius();
};
	