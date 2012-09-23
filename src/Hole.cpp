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

/**
*This file is used to identify the holes on the Lite Brite board where the pegs can be placed. The list
*is circular never empty
**/

#include "Hole.h";
#include "cinder/gl/gl.h";

Hole::Hole()
{
	next_ = prev_ = this;
}

void Hole::insertAfter(Hole* afterThis, ci::Vec2f pos, float radius)
{
	Hole* temp = new Hole();
	temp ->pos_ = pos;
	temp ->radius_ = radius;

	temp -> next_ = afterThis -> next_;
	temp -> prev_ = afterThis;

	temp -> next_->prev_ = temp;
	temp -> prev_->next_ = temp;
}

void Hole::insertBefore(Hole* beforeThis, ci::Vec2f pos, float radius)
{
	Hole* temp = new Hole();
	temp ->pos_ = pos;
	temp ->radius_ = radius;

	temp -> next_ = beforeThis;
	temp -> prev_ = beforeThis -> prev_;

	temp -> next_ -> prev_ = temp;
	temp -> prev_ -> next_ = temp;
}
bool Hole::isInsideHole(ci::Vec2f click)
{
	int distance = click.distance(pos_);

	if(distance<radius_)
	{
		return true;
	} 
	return false;

}

void Hole::draw()
{
	ci::gl::color(ci::Color8u(90,90,90));
	ci::gl::drawStrokedCircle(pos_, radius_);
}