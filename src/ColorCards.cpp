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
void ColorCards::cycleDeck(ColorCards* sentinel)
{
	ColorCards* temp = sentinel -> next_;
	sentinel -> next_ = temp -> next_;

	temp ->next_ = temp -> prev_;
	temp ->next_ = sentinel;

	sentinel -> prev_ -> next_ = temp;
	sentinel -> prev_ = temp;
}