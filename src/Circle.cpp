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

#include "Circle.h"
#include "Node.h"

Circle::Circle(Vec2f pos, int radius, Color8u c)
{
	pos_ = pos;
	radius_ = radius;
	color_ = c;
}

bool isInCircle(Circle* circ, Vec2f click)
{
	int distance = click.distance(circ->pos_);
	if(distance<circ->radius_)
	{
		return true;
	} 
	return false;
}
