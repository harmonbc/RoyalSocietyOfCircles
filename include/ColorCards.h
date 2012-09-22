#pragma once;
#include "cinder/gl/gl.h";

using namespace ci;
using namespace ci::gl;
class ColorCards
{
public:
	ColorCards();

	ColorCards* next_;
	ColorCards* prev_;
	int upper_left_x;
	int upper_left_y;
	int bottom_right_x;
	int bottom_right_y;
	Color8u color_;
	bool top_;

	void draw();
	void insertAfter(ColorCards* afterThis, int ulx, int uly, int brx, int bry, Color8u color);
	void insertBefore(ColorCards* beforeThis, int ulx, int uly, int brx, int bry, Color8u color);
	void cycleDeck(ColorCards* sentinel);
	void remove(ColorCards* thisCard);
};