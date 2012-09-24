/**
*@Author: Brandon Harmon
*@Date: 24 September, 2012
*@Assignment: Putting things on top of other things
*@Summary: Goal for the project is to create lists of objects which can be stacked and drawn from the stack
*@note This file is (c) 2012. It is licensed under the
*CC BY 3.0 license (http://creativecommons.org/licenses/by/3.0/),
*which means you are free to use, share, and remix it as long as you
*give attribution. Commercial uses are allowed.
**/
#pragma once;
#include "cinder/gl/gl.h";

using namespace ci;
using namespace ci::gl;

/**
*Color cards are used to specify the current color that will appear when the lights are added to the board
*color cards are organized in a circular doubly linked list.
**/
class ColorCards
{
public:
	//Constructor
	ColorCards();
	//Pointer to the next and previous cards
	ColorCards* next_;
	ColorCards* prev_;
	//X,Y coordinates of the upper left and bottom right rectangle points.
	int upper_left_x;
	int upper_left_y;
	int bottom_right_x;
	int bottom_right_y;
	//Color of the card
	Color8u color_;

	//Cards are stacked as in a deck style, satisfies Main Goal H(70/70)
	void draw();
	//Will return true if the x,y coordinates provided are within the current card
	bool isInside(Vec2f click);
};
//Will insert a new card after the current card. This will create a new card of
//the specified color in front of the first argument
void insertAfter(ColorCards* afterThis,Color8u color);
//This will insert the second argument after the first argument inside the list
void insertAfter(ColorCards* afterThis, ColorCards* thisCard);
//This will create a new color card before the first argument in the list.
void insertBefore(ColorCards* beforeThis, Color8u color);
//User alters list through input, Satisfies Main Goal C(50/70)
void cycleDeck(ColorCards* sentinel);
//User can reverse list with keyboard input, Satisfies Main Goal E(60/70)
void reverseList(ColorCards* sentinel);
//This will remove a card and delete it from memory.
void remove(ColorCards* thisCard);