#include "Node.h"

Node::Node()
{
	next_node_ = prev_node_ = this;
	circle_ = NULL;
}
void Node::insertAfter(Node* insertAfter, Circle* data)
{
}
void Node::insertBefore(Node* insertBefore, Circle* data)
{
}
void Node::draw()
{
	gl::color(circle_->color_);

	gl::drawStrokedCircle(circle_
}