#include "Circle.h"
#include "Node.h"
#include "Resources.h"

Circle::Circle(Vec2f pos, float radius, Color8u c)
{
	pos_ = pos;
	radius_ = radius;

	traveling_ = true;
	cur_pos_ = Vec2f(0,0);
	color_ = c;
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
	else
	{
		cur_pos_ = pos_;
	}
}
float Circle::getRadius()
{
	return radius_;
}
