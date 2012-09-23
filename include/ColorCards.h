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
#pragma once;
#include "cinder/gl/gl.h";

using namespace ci;
using namespace ci::gl;
class ColorCards
{
public:
	ColorCards();

	ColorCards* next_;
	ColorCards* prev_;
	int upper_left_x;
	int upper_left_y;
	int bottom_right_x;
	int bottom_right_y;
	Color8u color_;
	bool top_;

	void draw();
	bool isInside(Vec2f click);
};
	void insertAfter(ColorCards* afterThis,Color8u color);
	void insertAfter(ColorCards* afterThis, ColorCards* thisCard);
	void insertBefore(ColorCards* beforeThis, Color8u color);
	void cycleDeck(ColorCards* sentinel);
	void reverseList(ColorCards* sentinel);
	void remove(ColorCards* thisCard);