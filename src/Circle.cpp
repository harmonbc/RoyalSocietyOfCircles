#include "Circle.h"
#include "Node.h"
#include "Resources.h"

Circle::Circle(Vec2f pos, float radius)
{
	pos_ = pos;
	radius_ = radius;

	color_ = Color8u(255,255,255);
	cur_col_ = COLOR_WHITE;
	frozen_= true;
}
bool Circle::isInCircle(Vec2f click)
{
	int distance = click.distance(pos_);

	if(distance<radius_)
	{
		changeLightColor();
		return true;
	} 
	return false;
}
void Circle::changeLightColor()
{
	switch(cur_col_)
	{
	case COLOR_BLACK:
		cur_col_ = COLOR_WHITE;
		color_ = WHITE;
		break;
	case COLOR_RED:
		cur_col_ = COLOR_ORANGE;
		color_ = ORANGE;
		break;
	case COLOR_ORANGE:
		cur_col_ = COLOR_YELLOW;
		color_ = YELLOW;
		break;
	case COLOR_YELLOW:
		cur_col_ = COLOR_GREEN;
		color_ = GREEN;
		break;
	case COLOR_GREEN:
		cur_col_ = COLOR_BLUE;
		color_ = BLUE;
		break;
	case COLOR_BLUE:
		cur_col_ = COLOR_VIOLET;
		color_ = VIOLET;
		break;
	case COLOR_WHITE:
		cur_col_ = COLOR_RED;
		color_ = RED;
		break;
	default:
		cur_col_ = COLOR_BLACK;
		color_ = BLACK;
		break;
	}

}
float Circle::getRadius()
{
	return radius_;
}
