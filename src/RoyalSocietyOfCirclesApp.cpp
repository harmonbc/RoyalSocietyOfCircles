#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include <time.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyOfCirclesApp : public AppBasic {
public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
private:
	Node* sentinel_;
	void editBoard(MouseEvent event);
	void bringToFront(MouseEvent event);
	void removeLight(MouseEvent event);
	Node* getTopNode(MouseEvent event);
};

static const int kAppWidth=800;
static const int kAppHeight=600;
static const float kCircleRadius= 10;
static const int kCircleDistance= 25;
static const int kTextureSize=1024;
static int frame_count_;

void RoyalSocietyOfCirclesApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void RoyalSocietyOfCirclesApp::setup()
{
	sentinel_ = new Node();
	frame_count_ = 0;
	gl::enableAlphaBlending();
}

void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
	if(event.isLeft()) editBoard(event);
	if(event.isRight()) bringToFront(event);
	if(event.isMiddle()) removeLight(event);
}
void RoyalSocietyOfCirclesApp::removeLight(MouseEvent event)
{
		Node* highestInside = getTopNode(event);
		if(highestInside!=NULL)
		{
			(*highestInside).removeNode(highestInside);
			delete highestInside;
		}
}
void RoyalSocietyOfCirclesApp::bringToFront(MouseEvent event)
{
	Node* highestInside = getTopNode(event);
	if(highestInside!=NULL)
	{
		(*highestInside).removeNode(highestInside);
		(*highestInside).insertAfter(sentinel_, highestInside);
	}
}
void RoyalSocietyOfCirclesApp::editBoard(MouseEvent event)
{
	Node* highestInside = getTopNode(event);
	if(highestInside==NULL)
	{
		Circle* c = new Circle(Vec2f(event.getX(), event.getY()), kCircleRadius);
		(*sentinel_).insertAfter(sentinel_, c);
	}
	else
	{
		Circle* circ = highestInside->circle_;
		(*circ).changeLightColor();
	}
}
Node* RoyalSocietyOfCirclesApp::getTopNode(MouseEvent event)
{
	Node* temp = sentinel_->prev_node_;
	Node* highestInside = NULL;
	Vec2f curClick = Vec2f(event.getX(), event.getY());
	bool isInside = false;
	Circle* circ = NULL;
	while(temp!=sentinel_)
	{
		circ = temp->circle_;
		isInside = (*circ).isInCircle(curClick);
		if(isInside)
		{
			highestInside = temp;
		}
		temp = temp->prev_node_;
	}
	return highestInside;
}

void RoyalSocietyOfCirclesApp::update()
{
}

void RoyalSocietyOfCirclesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	Node* temp = sentinel_->prev_node_;
	while(temp!=sentinel_)
	{
		Circle* c = temp->circle_;
		(*c).update();
		(*temp).draw(frame_count_);
		temp = temp->prev_node_;
	}
	frame_count_++;
	console() << frame_count_++ << endl;
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
