
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
#pragma once
#include "Circle.h"

class Node{
public:
	Node();

	Node* next_node_;
	Node* prev_node_;
	Circle* circle_;


	void draw(int frameCount);
	void update();
};
	void insertAfter(Node* insertAfter, Circle* data);
	void insertAfter(Node* insertAfter, Node* curNode);
	void insertBefore(Node* insertBefore, Circle* data);
	void removeNode(Node* nodeToRemove);