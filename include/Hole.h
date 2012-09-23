**
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
#include "cinder/gl/gl.h";

class Hole{
public:
	Hole();

	ci::Vec2f pos_;
	float radius_;
	Hole* next_;
	Hole* prev_;

	void draw();
	void insertAfter(Hole* afterThis, ci::Vec2f pos, float radius);
	void insertBefore(Hole* beforeThis, ci::Vec2f pos, float radius);
	bool isInsideHole(ci::Vec2f event);
};