#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"


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
	void keyDown(KeyEvent event);
private:
	Node* sentinel_;
	void editBoard(MouseEvent event);
	void bringToFront(MouseEvent event);
	void removeLight(MouseEvent event);
	Node* getTopNode(MouseEvent event);
	void clearAllNodes();
	void help();
	void blastColors();
	gl::Texture master_texture_font_;
};

static const int kAppWidth=800;
static const int kAppHeight=600;
static const float kCircleRadius= 8;
static const int kCircleDistance= 12;
static const int kTextureSize=1024;
static int frame_count_;
static bool help_screen;
static bool twinkle;

void RoyalSocietyOfCirclesApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void RoyalSocietyOfCirclesApp::setup()
{
	sentinel_ = new Node();
	help_screen = true;
	twinkle = false;
	frame_count_ = 0;
	help();
	gl::enableAlphaBlending();
}
void RoyalSocietyOfCirclesApp::keyDown(KeyEvent event)
{
	if(event.getChar() == '1') clearAllNodes();
	if(event.getChar() == '?') help_screen = !(help_screen);
	if(event.getChar() == 'e') blastColors();
	if(event.getChar() == 's') twinkle = !(twinkle);
}
void RoyalSocietyOfCirclesApp::clearAllNodes()
{
	Node* curNode = sentinel_->next_node_;
	Node* temp = sentinel_->next_node_;
	while(curNode!=sentinel_)
	{
		temp = curNode ->next_node_;
		(*curNode).removeNode(curNode);
		curNode = temp;
	}
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
void RoyalSocietyOfCirclesApp::blastColors()
{
	for(int y = 1; y < kAppHeight; y++)
	{
		if(y%20 == 0)
		{
			for(int x = 1; x < kAppWidth; x++)
			{
				if(x%20 ==0)
				{
					Circle* c = new Circle(Vec2f(x, y), kCircleRadius);
					(*sentinel_).insertAfter(sentinel_, c);
				}

			}
		}
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
void RoyalSocietyOfCirclesApp::help(){
	Font master_font_ = Font("Helvetica",15);
	string txt = "APPLE BANNANA YUM";
	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font(master_font_).size( Vec2f( 1024, 1024) ).text( txt );
	tbox.setColor( Color( 1.0f, 0.65f, 0.35f ) );
	tbox.setBackgroundColor( ColorA( 0.5, 0, 0, 1 ) );
	Vec2i sz = tbox.measure();
	console() << "Height: " << sz.y << endl;
	master_texture_font_ = gl::Texture( tbox.render() );
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
		if(twinkle&&rand()%3==0) (*c).changeLightColor();
		(*temp).draw(frame_count_);
		temp = temp->prev_node_;
	}
	frame_count_++;
	console() << frame_count_++ << endl;
	if (help_screen)
		gl::draw(master_texture_font_);
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
