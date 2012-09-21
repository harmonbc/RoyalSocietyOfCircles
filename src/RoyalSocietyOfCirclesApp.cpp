#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include <time.h>


using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyOfCirclesApp : public AppBasic {
public:
	Node* sentinel_;
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepareSettings(Settings* settings);
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
}

void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
	Node* temp = sentinel_->next_node_;
	Vec2f curClick = Vec2f(event.getX(), event.getY());
	bool changedColor = false;

	while(temp!=sentinel_)
	{
		Circle* circ = temp->circle_;
		changedColor = (*circ).isInCircle(curClick);
		temp = temp->next_node_;
	}
	if(!changedColor)
	{
		Circle* c = new Circle(curClick, kCircleRadius);
		(*sentinel_).insertAfter(sentinel_, c);
	}
}

void RoyalSocietyOfCirclesApp::update()
{
	Node* temp = sentinel_->next_node_;
	/*while(temp!=sentinel_)
	{
		Vec2f orig = (*temp).circle_->pos_;
		orig.x = orig.x+5;
		orig.y = orig.y-5;
		(*temp).circle_->pos_ = orig;
		temp = temp->next_node_;
	}*/
}

void RoyalSocietyOfCirclesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
	Node* temp = sentinel_->next_node_;
	while(temp!=sentinel_)
	{
		(*temp).draw();
		temp = temp->next_node_;
	}
	frame_count_++;
	console() << frame_count_++ << endl;
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
