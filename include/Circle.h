#pragma once
#include "cinder/gl/gl.h"
#define RED Color8u(255,0,0);
#define ORANGE Color8u(255,127,0);
#define YELLOW Color8u(255,255,0);
#define GREEN Color8u(0,255,0);
#define BLUE Color8u(0,0,255);
#define VIOLET Color8u(255,0,255);
#define WHITE Color8u(255,255,255);

using namespace ci;

class Circle
{
public:
	Circle(Vec2f pos, float radius);
	Vec2f pos_;
	float radius_;
	Color8u color_;
	bool traveling_;
	Vec2f cur_pos_;
	void update();
	bool isInCircle(Vec2f click);
	void changeLightColor();
	float getRadius();

	static enum LightColor
	{
		COLOR_RED,
		COLOR_ORANGE,
		COLOR_YELLOW,
		COLOR_GREEN,
		COLOR_BLUE,
		COLOR_VIOLET,
		COLOR_WHITE,
	};
	LightColor cur_col_;
};