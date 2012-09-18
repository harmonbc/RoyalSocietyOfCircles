#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RoyalSocietyOfCirclesApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void RoyalSocietyOfCirclesApp::setup()
{
}

void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
}

void RoyalSocietyOfCirclesApp::update()
{
}

void RoyalSocietyOfCirclesApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
