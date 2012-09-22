#pragma once
#include "cinder/gl/gl.h";

class Hole{
public:
	Hole();

	ci::Vec2f pos_;
	float radius_;
	Hole* next_;
	Hole* prev_;

	void draw();
	void insertAfter(Hole* afterThis, ci::Vec2f pos, float radius);
	void insertBefore(Hole* beforeThis, ci::Vec2f pos, float radius);
	bool isInsideHole(ci::Vec2f event);
};