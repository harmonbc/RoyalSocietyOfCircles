#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include "Hole.h"
#include "ColorCards.h"
#include "cinder/Text.h"
#include "cinder/gl/Texture.h"

#define RED Color8u(255,0,0);
#define ORANGE Color8u(255,127,0);
#define YELLOW Color8u(255,255,0);
#define GREEN Color8u(0,255,0);
#define BLUE Color8u(0,0,255);
#define VIOLET Color8u(255,0,255);
#define WHITE Color8u(255,255,255);
#define GRAY Color8u(211,211,211);

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
	Hole* sentinel_hole_;
	ColorCards* sentinel_card_;
	void editBoard(MouseEvent event);
	void bringToFront(MouseEvent event);
	void removeLight(MouseEvent event);
	Node* getTopNode(MouseEvent event);
	void clearAllNodes();
	void help();
	void drawHoles();
	gl::Texture master_texture_font_;
};

static const int kAppWidth=800;
static const int kAppHeight=600;
static const float kCircleRadius= 8;
static const int kCircleDistance= 20;
static const int kTextureSize=1024;
static Color8u currentColor = WHITE;
static int frame_count_;
static bool help_screen;

void RoyalSocietyOfCirclesApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void RoyalSocietyOfCirclesApp::setup()
{
	sentinel_ = new Node();
	sentinel_hole_ = new Hole();
	help_screen = false;
	frame_count_ = 0;
	help();
	gl::enableAlphaBlending();
	drawHoles();
}
void RoyalSocietyOfCirclesApp::drawHoles()
{
		bool even = true;
	for(int y = 1; y < kAppHeight-150; y++)
	{
		if(y%kCircleDistance==0)
		{
			for(int x = 1 ; x < kAppWidth; x++){
				if(x%kCircleDistance==0)
				{
					(*sentinel_hole_).insertAfter(sentinel_hole_, Vec2f((even) ? x : x+(kCircleDistance/2),y), kCircleRadius);
				}
			}
			even = !(even);
		}
	}

}
void RoyalSocietyOfCirclesApp::keyDown(KeyEvent event)
{
	if(event.getChar() == '1') clearAllNodes();
	if(event.getChar() == '?') help_screen = !(help_screen);
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
	if(event.isRight()) removeLight(event);
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
void RoyalSocietyOfCirclesApp::editBoard(MouseEvent event)
{
	Hole* temp = sentinel_hole_->next_;
	Hole* highest= NULL;
	while(temp!=sentinel_hole_)
	{
		if((*temp).isInsideHole(Vec2f(event.getX(), event.getY())))
		{
			Circle* c = new Circle(Vec2f((*temp).pos_.x,(*temp).pos_.y), kCircleRadius, currentColor);
			(*sentinel_).insertAfter(sentinel_, c);
			break;
		}
		temp = temp -> next_;
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
	string txt = "WELCOME TO LIGHT BRIGHT!";
	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font(master_font_).size( Vec2f( 1024, 1024) ).text( txt );
	tbox.setColor(Color8u(0, 0, 0) );
	tbox.setBackgroundColor( Color8u( 255, 255, 255) );
	Vec2i sz = tbox.measure();
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
	Hole* temp2 = sentinel_hole_->prev_;
	while(temp2 != sentinel_hole_)
	{
		(*temp2).draw();
		temp2 = temp2->prev_;
	}
	while(temp!=sentinel_)
	{
		Circle* c = temp->circle_;
		(*c).update();
		(*temp).draw(frame_count_);
		temp = temp->prev_node_;
	}
	frame_count_++;
	console() << frame_count_++ << endl;
	if (help_screen)
		gl::draw(master_texture_font_);
	Rectf rect(200, 200, 200+50, 200+60);
	gl::drawSolidRect(rect);
	
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
