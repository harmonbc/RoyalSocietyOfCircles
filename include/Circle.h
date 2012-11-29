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

/**
*Circle is an object that can either represent a hole in the board or a light. This is so the frame rate is
*consistant throughout play. If circle is set to is_hole_ it will display as a gray circle, otherwise it will
*glow with the specified circle.
**/

#include "cinder/gl/gl.h"

using namespace ci;

class Circle
{
public:
	//Overloaded constructor, used in creation of the sentinel
	Circle();
	//Doubly Linked List Satisfies main goal A(30/70)
	Circle(Vec2f pos, int radius, Color8u c);
	//Position of the circle
	Vec2f pos_;
	//Size of the circle
	int radius_;
	//Color used if is_hole_ is disabled
	Color8u color_;
	//Pointer to next Circle
	Circle* next_;
	//Pointer to prev Circle
	Circle* prev_;
	//Boolean controlling if this object will represent a hole or a peg
	bool is_hole_;
	//Uses transparency to make it appear that the lights are glowing satisfies Main Goal G
	//Use this as credit if the deck stack of color cards is not as interesting as expected.
	void draw(int frameCount);
};
//Will insert the circle object after the first argument.
void insertAfter(Circle* insertAfter, Circle* data);
//Will insert the new circle object data before the first argment.
void insertBefore(Circle* insertBefore, Circle* data);
//Not used but will remove the node from the list and delete it from memory.
void removeNode(Circle* removeThis);
//Will return true if the x&y coordinates are within the circle
bool isInCircle(Circle* circ, Vec2f click);