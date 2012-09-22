#include "ColorCards.h"

ColorCards::ColorCards()
{
	next_ = prev_ = this;
}

void ColorCards::draw()
{

}

void ColorCards::insertAfter(ColorCards* afterThis, Vec2f pos, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> pos_ = pos;
	temp -> color_ = color;

	temp -> next_ = afterThis ->next_;
	temp -> prev_ = afterThis;

	temp -> next_ -> prev_ = temp;
	temp -> prev_ -> next_ = temp;
}

void ColorCards::insertBefore(ColorCards* beforeThis, Vec2f pos, Color8u color)
{
	ColorCards* temp = new ColorCards();
	temp -> pos_ = pos;
	temp -> color_ = color;

	temp -> next_ = beforeThis;
	temp -> prev_ = beforeThis -> prev_;

	temp -> prev_ -> next_ = temp;
	temp -> next_ -> prev_ = temp;

}
void ColorCards::cycleDeck(ColorCards* sentinel, int noOfCards)
{
	ColorCards* temp = sentinel -> next_;
	sentinel -> next_ = temp -> next_;

	temp ->pos_.x = temp ->pos_.x-noOfCards;
	temp ->pos_.y = temp ->pos_.y+noOfCards;

	temp ->next_ = temp -> prev_;
	temp ->next_ = sentinel;

	sentinel -> prev_ -> next_ = temp;
	sentinel -> prev_ = temp;

	while(temp != sentinel)
	{
		temp ->pos_.x = temp ->pos_.x+1;
		temp ->pos_.y = temp ->pos_.y-1;
		temp = temp -> prev_;
	}
}