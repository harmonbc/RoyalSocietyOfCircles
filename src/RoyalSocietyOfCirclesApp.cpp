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

#pragma once
#include "cinder/CinderResources.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Node.h"
#include "Hole.h"
#include "LightColors.h"
#include "ColorCards.h"
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
	//Lists
	Node* sentinel_;
	Hole* sentinel_hole_;
	ColorCards* sentinel_card_;

	//Actions
	void editBoard(MouseEvent event);
	void bringToFront(MouseEvent event);
	void removeLight(MouseEvent event);
	void clearAllNodes();

	//Helpers
	void help();
	void addCards();
	Node* getTopNode(MouseEvent event);
	void drawHoles();
	void setCurrentColor();
	Color8u returnColor(LightColors c);
	Color8u returnColor(int c);
	gl::Texture master_texture_font_;
};

#define RED		Color8u(255,0,0);
#define ORANGE	Color8u(255,127,0);
#define YELLOW	Color8u(255,255,0);
#define GREEN	Color8u(0,255,0);
#define BLUE	Color8u(0,0,255);
#define VIOLET	Color8u(255,0,255);
#define WHITE	Color8u(255,255,255);
#define GRAY	Color8u(211,211,211);



static const int kAppWidth=800;
static const int kAppHeight=600;
static const int kBottomBuffer=150;
static const float kCircleRadius= 8;
static const int kCircleDistance= 20;
static const int kTextureSize=1024;

static Color8u cur_color_;
static int frame_count_;
static bool help_screen;

/**Executes before program starts*/
void RoyalSocietyOfCirclesApp::prepareSettings(Settings* settings)
{
	(*settings).setWindowSize(kAppWidth,kAppHeight);
	(*settings).setResizable(false);
}

void RoyalSocietyOfCirclesApp::setup()
{
	sentinel_ = new Node();
	sentinel_card_ = new ColorCards();
	sentinel_hole_ = new Hole();
	help_screen = false;

	help();
	gl::enableAlphaBlending();
	drawHoles();
	addCards();
	setCurrentColor();

	frame_count_ = 0;
}
/**Helper methods for program start up**/
void RoyalSocietyOfCirclesApp::drawHoles()
{
	bool even = true;
	for(int y = 1; y < kAppHeight-kBottomBuffer; y++)
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
void RoyalSocietyOfCirclesApp::addCards()
{
	int maxCardWidth = (kAppWidth/LAST);
	int cardBuffer = 5;

	for(int i = COLOR_RED; i != LAST ; i++)
	{
		(*sentinel_card_).insertBefore(sentinel_card_, maxCardWidth*i+cardBuffer, kAppHeight-kBottomBuffer+30,
			maxCardWidth*i+maxCardWidth-cardBuffer, kAppHeight-30, returnColor(i));
	}
	console() <<"finished making cards"<<endl;
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

/**Listens for Actions**/
void RoyalSocietyOfCirclesApp::keyDown(KeyEvent event)
{
	if(event.getChar() == '1') clearAllNodes();
	else if(event.getChar() == '?') help_screen = !(help_screen); 
	else if(event.getChar() == 'n')
	{
		(*sentinel_card_).cycleDeck(sentinel_card_);
		setCurrentColor();
	}
	else if(event.getChar() == 'r') (*sentinel_card_).reverseList(sentinel_card_); 
}
void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
	if(event.isLeft()) editBoard(event);
	if(event.isRight()) removeLight(event);
}

/**Performs user actions**/
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
			Circle* c = new Circle(Vec2f((*temp).pos_.x,(*temp).pos_.y), kCircleRadius, sentinel_card_->next_->color_);
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

Color8u RoyalSocietyOfCirclesApp::returnColor(LightColors c)
{
	switch(c)
	{
	case COLOR_RED: return RED; break;
	case COLOR_ORANGE: return ORANGE; break;
	case COLOR_YELLOW: return YELLOW; break;
	case COLOR_GREEN: return GREEN; break;
	case COLOR_BLUE: return BLUE; break;
	case COLOR_VIOLET: return VIOLET; break;
	case COLOR_WHITE: return WHITE; break;
	default: return GRAY; break;
	}
}
void RoyalSocietyOfCirclesApp::setCurrentColor()
{
	cur_color_ = sentinel_card_ -> next_ -> color_;
}
Color8u RoyalSocietyOfCirclesApp::returnColor(int c)
{
	switch(c)
	{
	case COLOR_RED: return RED; break;
	case COLOR_ORANGE: return ORANGE; break;
	case COLOR_YELLOW: return YELLOW; break;
	case COLOR_GREEN: return GREEN; break;
	case COLOR_BLUE: return BLUE; break;
	case COLOR_VIOLET: return VIOLET; break;
	case COLOR_WHITE: return WHITE; break;
	default: return GRAY; break;
	}
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
	ColorCards* temp3 = sentinel_card_ ->next_;
	temp3 -> top_ = true;

	while(temp3!=sentinel_card_)
	{
		(*temp3).draw();
		temp3 = temp3 -> next_;
		temp3 -> top_ = false;
	}

	frame_count_++;
	
	console() << frame_count_++ << endl;
	
	if (help_screen)
		gl::draw(master_texture_font_);
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
