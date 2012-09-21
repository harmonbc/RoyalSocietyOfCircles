#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"


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
};

void RoyalSocietyOfCirclesApp::setup()
{
	sentinel_ = new Node();
	Circle* c = new Circle(Vec2f(300,400), 60.0f, Color8u(255,0,0));
	(*sentinel_).insertAfter(sentinel_, c);
	Circle* d = new Circle(Vec2f(200,400), 60.0f, Color8u(255,255,0));
	(*sentinel_).insertAfter(sentinel_, d);
}

void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
	console() << event.getPos() << endl;
}

void RoyalSocietyOfCirclesApp::update()
{
	Node* temp = sentinel_->next_node_;
	while(temp!=sentinel_)
	{
		Vec2f orig = (*temp).circle_->pos_;
		orig.x = orig.x+5;
		orig.y = orig.y-5;
		(*temp).circle_->pos_ = orig;
		temp = temp->next_node_;
	}
	temp;
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
	temp;
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
