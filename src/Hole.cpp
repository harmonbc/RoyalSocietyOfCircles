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
	ci::gl::drawSolidCircle(pos_, radius_);
}