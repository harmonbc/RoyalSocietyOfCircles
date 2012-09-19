#pragma once
#include "cinder/gl/gl.h"

using namespace ci;

class Circle
{
public:
	Circle(Vec2f pos, int radius, Color8u c);
	Vec2f pos_;
	int radius_;
	Color8u color_;
};
void draw();
void update();