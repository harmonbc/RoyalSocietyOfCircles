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

//Circluar doubly linked list Satisfies A (30/70)
ColorCards::ColorCards()
{
	next_ = prev_ = this;
}

void ColorCards::draw()
{
	gl::color(color_);
	Rectf rect(upper_left_x, upper_left_y, bottom_right_x, bottom_right_y);
	gl::drawSolidRect(rect);
}

void insertAfter(ColorCards* afterThis, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> color_ = color;

	temp -> next_ = afterThis ->next_;
	temp -> prev_ = afterThis;

	temp -> next_ -> prev_ = temp;
	temp -> prev_ -> next_ = temp;
}

void insertAfter(ColorCards* afterThis, ColorCards* thisCard)
{
	afterThis -> next_ -> prev_ = thisCard;

	thisCard -> next_ = afterThis -> next_;
	thisCard -> prev_ = afterThis;

	afterThis -> next_ = thisCard;
}

void insertBefore(ColorCards* beforeThis, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> color_ = color;

	temp -> next_ = beforeThis;
	temp -> prev_ = beforeThis -> prev_;

	temp -> prev_ -> next_ = temp;
	temp -> next_ -> prev_ = temp;

}
void reverseList(ColorCards* sentinel)
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
void cycleDeck(ColorCards* sentinel)
{
	ColorCards* temp = sentinel -> next_;
	sentinel -> next_ = temp -> next_;
	sentinel -> next_ -> prev_ = sentinel;

	temp -> prev_ = sentinel -> prev_;
	temp -> next_ = sentinel;

	sentinel -> prev_ = temp;

	temp -> prev_ -> next_ = temp;
}

void remove(ColorCards* removeThis)
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

