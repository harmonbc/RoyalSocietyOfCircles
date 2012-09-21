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
void Node::insertBefore(Node* insertBefore, Circle* data)
{
	Node* temp = new Node();

	temp->next_node_ = insertBefore;
	temp->prev_node_ = insertBefore->prev_node_;
	temp->circle_ = data;

	insertBefore->prev_node_ = temp;
	temp->prev_node_->next_node_= temp;
}

void Node::draw()
{
	gl::color(circle_->color_);
	gl::drawSolidCircle(circle_->pos_, circle_->radius_);
}