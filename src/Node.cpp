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

#include "Node.h"
#include "Circle.h"

Node::Node()
{
	next_node_ = prev_node_ = this;
	circle_ = NULL;
}

void Node::insertAfter(Node* insertAfter, Circle* data)
{
	Node* temp = new Node();

	temp->next_node_ = insertAfter->next_node_;
	temp->prev_node_ = insertAfter;
	temp->circle_ = data;

	insertAfter->next_node_ = temp;
	temp->next_node_->prev_node_ = temp;
}

void Node::insertAfter(Node* insertAfter, Node* curNode)
{

	curNode->next_node_ = insertAfter->next_node_;
	curNode->prev_node_ = insertAfter;

	insertAfter->next_node_ = curNode;
	curNode->next_node_->prev_node_ = curNode;
}

void Node::insertBefore(Node* insertBefore, Circle* data)
{
	Node* temp = new Node();

	temp->next_node_ = insertBefore;
	temp->prev_node_ = insertBefore->prev_node_;
	temp->circle_ = data;
	insertBefore->prev_node_ = temp;
	temp->prev_node_->next_node_= temp;
}

void Node::removeNode(Node* nodeToRemove)
{
	nodeToRemove->prev_node_->next_node_ = nodeToRemove->next_node_;
	nodeToRemove->next_node_->prev_node_ = nodeToRemove->prev_node_;
	delete nodeToRemove -> circle_;
	delete nodeToRemove;
}

void Node::draw(int frameCount)
{
	Color8u temp = circle_->color_;
	gl::color(ColorA(temp.r, temp.g, temp.b, .25f));
	gl::drawSolidCircle(circle_->pos_, circle_->radius_-5+frameCount%5);
	gl::color(temp);
	gl::drawSolidCircle(circle_->pos_, circle_->radius_/2);
}