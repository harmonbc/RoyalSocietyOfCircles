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
	//By default new circles will be holes and not pegs
	is_hole_ = true;
}
Circle::Circle(Vec2f pos, int radius, Color8u c)
{
	next_=prev_=this;
	pos_ = pos;
	radius_ = radius;
	color_ = c;
	//By default new circles will be holes and not pegs
	is_hole_ = true;
}
void Circle::draw(int frameCount)
{
	if(is_hole_)
	{
		gl::color(Color8u(55,55,55));
		gl::drawSolidCircle(pos_, radius_-3);
	}
	else
	{
		//This layer adds the glowing animation to the lights using transparency
		gl::color(ColorA(color_.r, color_.g, color_.b, .25f));
		gl::drawSolidCircle(pos_, radius_-2+sin(frameCount*.1)*2);

		gl::color(ColorA(color_.r, color_.g, color_.b, .5f));
		gl::drawSolidCircle(pos_, radius_*.75);

		gl::color(color_);
		gl::drawSolidCircle(pos_, radius_*.25);
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
