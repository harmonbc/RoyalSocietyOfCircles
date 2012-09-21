#pragma once
#include "Circle.h"

class Node{
public:
	Node();

	Node* next_node_;
	Node* prev_node_;
	Circle* circle_;

	void insertAfter(Node* insertAfter, Circle* data);
	void insertAfter(Node* insertAfter, Node* curNode);
	void insertBefore(Node* insertBefore, Circle* data);
	void draw(int frameCount);
	void update();
	void removeNode(Node* nodeToRemove);
};