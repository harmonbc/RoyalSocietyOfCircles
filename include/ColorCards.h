#pragma once;
#include "cinder/gl/gl.h";

using namespace ci;
using namespace ci::gl;
class ColorCards
{
	ColorCards();

	ColorCards* next_;
	ColorCards* prev_;
	Vec2f pos_;
	Color8u color_;

	void darw();
	void insertAfter(ColorCards* afterThis, Vec2f pos, Color8u color);
	void insertBefore(ColorCards* beforeThis, Vec2f pos, Color8u color);
	void cycleDeck();
};