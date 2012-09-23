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
#include "ColorCards.h"
#include "cinder\gl\gl.h"

ColorCards::ColorCards()
{
	next_ = prev_ = this;
}

void ColorCards::draw()
{
	gl::color(color_);
	Rectf rect(upper_left_x, (top_) ? upper_left_y-10 : upper_left_y, bottom_right_x, (top_) ? bottom_right_y+10 : bottom_right_y);
	gl::drawSolidRect(rect);
}

void ColorCards::insertAfter(ColorCards* afterThis, int ulx, int uly, int brx, int bry, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> upper_left_x = ulx;
	temp -> upper_left_y = uly;
	temp -> bottom_right_x = brx;
	temp -> bottom_right_y = bry;
	temp -> color_ = color;

	temp -> next_ = afterThis ->next_;
	temp -> prev_ = afterThis;

	temp -> next_ -> prev_ = temp;
	temp -> prev_ -> next_ = temp;
}
void ColorCards::insertAfter(ColorCards* afterThis, ColorCards* thisCard)
{
	afterThis -> next_ -> prev_ = thisCard;

	thisCard -> next_ = afterThis -> next_;
	thisCard -> prev_ = afterThis;

	afterThis -> next_ = thisCard;
}

void ColorCards::insertBefore(ColorCards* beforeThis, int ulx, int uly, int brx, int bry, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> upper_left_x = ulx;
	temp -> upper_left_y = uly;
	temp -> bottom_right_x = brx;
	temp -> bottom_right_y = bry;
	temp -> color_ = color;

	temp -> next_ = beforeThis;
	temp -> prev_ = beforeThis -> prev_;

	temp -> prev_ -> next_ = temp;
	temp -> next_ -> prev_ = temp;

}
void ColorCards::reverseList(ColorCards* sentinel)
{
	ColorCards* temp = sentinel;
	ColorCards* temp2 = NULL;
	do{
		temp2 = temp->next_;
		temp->next_ = temp->prev_;
		temp->prev_ = temp2;
		temp = temp2;
	}while(temp!=sentinel);

}
void ColorCards::cycleDeck(ColorCards* sentinel)
{
	ColorCards* temp = sentinel -> next_;
	sentinel -> next_ = temp -> next_;
	sentinel -> next_ -> prev_ = sentinel;

	temp -> prev_ = sentinel -> prev_;
	temp -> next_ = sentinel;

	sentinel -> prev_ = temp;

	temp -> prev_ -> next_ = temp;
}

void ColorCards::remove(ColorCards* removeThis)
{
	removeThis -> prev_ -> next_ = removeThis -> next_;
	removeThis -> next_ -> prev_ = removeThis -> prev_;
}
bool ColorCards::isInside(Vec2f click)
{
	if(click.x>upper_left_x&&click.x<bottom_right_x&&click.y>upper_left_y&&bottom_right_y)
		return true;
	else
		return false;
}

