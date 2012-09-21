#include "Circle.h"
#include "Node.h"

Circle::Circle(Vec2f pos, float radius, Color8u c)
{
	pos_ = pos;
	radius_ = radius;
	color_ = c;
}
void Circle::isInCircle(Vec2f click)
{
	int distance = click.distance(pos_);

	if(distance<radius_)
	{
		color_ = Color8u(0,0,255);
	}
}
float Circle::getRadius()
{
	return radius_;
}
