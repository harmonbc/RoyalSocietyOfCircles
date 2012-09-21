#include "Circle.h"
#include "Node.h"
#include "Resources.h"

Circle::Circle(Vec2f pos, float radius)
{
	pos_ = pos;
	radius_ = radius;

	traveling_ = true;
	cur_pos_ = Vec2f(0,0);
	color_ = Color8u(255,255,255);
	cur_col_ = COLOR_WHITE;
}
bool Circle::isInCircle(Vec2f click)
{
	int distance = click.distance(pos_);

	if(distance<radius_)
	{
		return true;
	} 
	return false;
}
void Circle::update()
{
	if(traveling_)
	{
		if(cur_pos_.x!=pos_.x)
		cur_pos_.x += pos_.x/50;
		if(cur_pos_.y!=pos_.y)
		cur_pos_.y += pos_.y/50;

		if(cur_pos_.distance(pos_)<10)
		cur_pos_ = pos_;
	}
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
