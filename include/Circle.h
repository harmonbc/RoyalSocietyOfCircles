/**
*@Author: Brandon Harmon
*@Date: 24 September, 2012
*@Assignment: Putting things on top of other things
*@Summary: Goal for the project is to create lists of objects which can be stacked and drawn from the stack
*@note This file is (c) 2012. It is licensed under the
*CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
*which means you are free to use, share, and remix it as long as you
*give attribution. Commercial uses are allowed.
**/
#pragma once
#include "cinder/gl/gl.h"

using namespace ci;

class Circle
{
public:
	Circle();
	Circle(Vec2f pos, int radius, Color8u c);

	Vec2f pos_;
	int radius_;
	Color8u color_;
	Circle* next_;
	Circle* prev_;
	bool is_hole_;
	void draw(int frameCount);
	void update();
};
	void insertAfter(Circle* insertAfter, Circle* data);
	void insertAfter(Circle* insertAfter, Circle* curNode);
	void insertBefore(Circle* insertBefore, Circle* data);
	void removeNode(Circle* removeThis);
	bool isInCircle(Circle* circ, Vec2f click);