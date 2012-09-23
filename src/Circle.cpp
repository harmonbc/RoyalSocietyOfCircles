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
Circle::Circle()
{
	next_=prev_=this;
	is_hole_ = false;
}
Circle::Circle(Vec2f pos, int radius, Color8u c)
{
	next_=prev_=this;
	pos_ = pos;
	radius_ = radius;
	color_ = c;
	is_hole_ = false;
}
void Circle::draw(int frameCount)
{
	if(is_hole_)
	{
		gl::color(Color8u(111,111,111));
		gl::drawSolidCircle(pos_, radius_);
	}
	else
	{
		gl::color(ColorA(color_.r, color_.g, color_.b, .25f));
		gl::drawSolidCircle(pos_, radius_-5+sin(frameCount/2.0)*4);
		gl::color(color_);
		gl::drawSolidCircle(pos_, radius_/2);
	}
}
void insertAfter(Circle* insertAfter, Circle* data)
{
	data->next_ = insertAfter->next_;
	data->prev_ = insertAfter;

	insertAfter->next_ = data;
	data->next_->prev_ = data;
}

void insertBefore(Circle* insertBefore, Circle* data)
{
	data->next_ = insertBefore;
	data->prev_ = insertBefore->prev_;

	insertBefore->prev_ = data;
	data->prev_->next_= data;
}

void removeNode(Circle* nodeToRemove)
{
	nodeToRemove->prev_->next_ = nodeToRemove->next_;
	nodeToRemove->prev_->prev_ = nodeToRemove->prev_;
	delete nodeToRemove;
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
