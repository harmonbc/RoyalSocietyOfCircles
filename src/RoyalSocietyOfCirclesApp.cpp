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
	//Used by Cinder
	void			setup();
	void			mouseDown( MouseEvent event );	
	void			update();
	void			draw();
	void			prepareSettings(Settings* settings);
	void			keyDown(KeyEvent event);
private:
	//Lists
	Node*			sentinel_;
	Hole*			sentinel_hole_;
	ColorCards*		sentinel_card_;

	//Actions from mouse/keboard methods
	void			editBoard(MouseEvent event);
	void			checkCards(MouseEvent event);
	void			bringToFront(MouseEvent event);
	void			removeLight(MouseEvent event);
	void			clearAllNodes();

	//Assist Setup/Actions methods
	void			addCards();
	Node*			getTopNode(MouseEvent event);
	void			drawHoles();
	void			setCurrentColor();
	Color8u			returnColor(LightColors c);
	Color8u			returnColor(int c);

	//Help Menu
	void			render();
	gl::Texture		mTextTexture;
	Vec2f			mSize;
	Font			mFont;
};

#define RED			Color8u(255,0,0);
#define YELLOW		Color8u(255,255,0);
#define GREEN		Color8u(0,255,0);
#define BLUE		Color8u(0,0,255);
#define VIOLET		Color8u(255,0,255);
#define WHITE		Color8u(255,255,255);

static const int	kAppWidth=800;
static const int	kAppHeight=600;
static const int	kBottomBuffer=150;
static const float	kCircleRadius= 8;
static const int	kCircleDistance= 20;
static const int	kTextureSize=1024;
static const int 	kMaxCardWidth = (kAppWidth/LAST);
static const int	kCardBuffer = 5;

static	Color8u		cur_color_;
static int			frame_count_;
static bool			help_screen;
static bool			cards_have_changed_;

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

	gl::enableAlphaBlending();
	drawHoles();
	addCards();
	setCurrentColor();

	mFont = Font( "Times New Roman", 20 );
	mSize = Vec2f( kAppWidth, 100 );
	render();
	cards_have_changed_ = true;

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
		insertBefore(sentinel_card_, returnColor(i));
	}
	cards_have_changed_ = true;
}
/**
*Code primarily taken from Cinder example
**/
void RoyalSocietyOfCirclesApp::render()
{
	string txt = "LITE BRITE:\nLeft Click inside of a grey circle to add a light";
	txt+="\nSelect color either by left clicking on a card or pressing 'n' to cycle through cards\n";
	txt+="\nRemove light by right clicking it";
	txt+="\nc=Clears all lights from the board";
	txt+="\nn=Cycle through colors";
	txt+="\nr=Reverse the list of colors";
	txt+="\n?=Toggle Help Screen\n";
	TextBox tbox = TextBox().alignment( TextBox::RIGHT ).font( mFont ).size( Vec2i( mSize.x, TextBox::GROW ) ).text( txt );
	tbox.setColor( Color8u(0,0,0) );
	tbox.setBackgroundColor( Color8u(255,255,255) );
	Vec2i sz = tbox.measure();
	mTextTexture = gl::Texture( tbox.render() );
}

/**Listens for Actions**/
void RoyalSocietyOfCirclesApp::keyDown(KeyEvent event)
{
	if(event.getChar() == 'c') clearAllNodes();
	else if(event.getChar() == '?') help_screen = !(help_screen); 
	else if(event.getChar() == 'n')
	{
		cycleDeck(sentinel_card_);
		setCurrentColor();
		cards_have_changed_ = true;
	}
	else if(event.getChar() == 'r')
	{
		reverseList(sentinel_card_); 
		cards_have_changed_ = true;
	}
}
void RoyalSocietyOfCirclesApp::mouseDown( MouseEvent event )
{
	if(event.isLeft()&&event.getY()<kAppHeight-kBottomBuffer) editBoard(event);
	else if(event.isLeft()) checkCards(event);
	else if(event.isRight()) removeLight(event);
}

/**Performs user actions**/
void RoyalSocietyOfCirclesApp::clearAllNodes()
{
	Node* curNode = sentinel_->next_node_;
	Node* temp = sentinel_->next_node_;
	while(curNode!=sentinel_)
	{
		temp = curNode ->next_node_;
		removeNode(curNode);
		curNode = temp;
	}
}
void RoyalSocietyOfCirclesApp::checkCards(MouseEvent event)
{
	ColorCards* temp2 = sentinel_card_->next_;
	while(temp2!=sentinel_card_)
	{
		if((*temp2).isInside(Vec2f(event.getX(), event.getY())))
		{
			remove(temp2);
			insertAfter(sentinel_card_, temp2);
			cards_have_changed_ = true;
			break;
		}
		temp2 = temp2 -> next_;
	}
}
void RoyalSocietyOfCirclesApp::removeLight(MouseEvent event)
{
	Node* highestInside = getTopNode(event);
	if(highestInside!=NULL)
	{
		removeNode(highestInside);
		delete highestInside;
	}
}

void RoyalSocietyOfCirclesApp::editBoard(MouseEvent event)
{
	Hole* temp = sentinel_hole_->next_;
	while(temp!=sentinel_hole_)
	{
		if((*temp).isInsideHole(Vec2f(event.getX(), event.getY())))
		{
			Circle* c = new Circle(Vec2f((*temp).pos_.x,(*temp).pos_.y), kCircleRadius, sentinel_card_->next_->color_);
			insertAfter(sentinel_, c);
			break;
		}
		temp = temp -> next_;
	}
	ColorCards* temp2 = sentinel_card_ -> next_;

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
		isInside = isInCircle(circ, curClick);

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
	case COLOR_YELLOW: return YELLOW; break;
	case COLOR_GREEN: return GREEN; break;
	case COLOR_BLUE: return BLUE; break;
	case COLOR_VIOLET: return VIOLET; break;
	case COLOR_WHITE: return WHITE; break;
	default: return WHITE; break;
	}
}

Color8u RoyalSocietyOfCirclesApp::returnColor(int c)
{
	switch(c)
	{
	case COLOR_RED: return RED; break;
	case COLOR_YELLOW: return YELLOW; break;
	case COLOR_GREEN: return GREEN; break;
	case COLOR_BLUE: return BLUE; break;
	case COLOR_VIOLET: return VIOLET; break;
	case COLOR_WHITE: return WHITE; break;
	default: return WHITE; break;
	}
}

void RoyalSocietyOfCirclesApp::setCurrentColor()
{
	cur_color_ = sentinel_card_ -> next_ -> color_;
}


void RoyalSocietyOfCirclesApp::update()
{
}

void RoyalSocietyOfCirclesApp::draw()
{
	// clear out the window with black
	gl::clear(Color( 0, 0, 0 ));

	Node* temp = sentinel_->prev_node_;
	Hole* temp2 = sentinel_hole_->prev_;
	ColorCards* temp3 = sentinel_card_ ->next_;

	while(temp2 != sentinel_hole_)
	{
		(*temp2).draw();
		temp2 = temp2->prev_;
	}

	temp2 = NULL;
	while(temp!=sentinel_)
	{
		(*temp).draw(frame_count_);
		temp = temp->prev_node_;
	}

	temp = NULL;

	int pos = 0;

	while(temp3!=sentinel_card_)
	{

		if(cards_have_changed_)
		{
			console() << "Has Changed "<< pos << endl;
			int xPos = kMaxCardWidth*pos;
			int yBuffer = (kCardBuffer*(pos+1));

			temp3 -> upper_left_x = xPos+kCardBuffer;
			temp3 -> upper_left_y = kAppHeight-kBottomBuffer+yBuffer;
			temp3 -> bottom_right_x = xPos+kMaxCardWidth-kCardBuffer;
			temp3 -> bottom_right_y = kAppHeight-yBuffer;
		}

		(*temp3).draw();
		temp3 = temp3 -> next_;
		pos++;
	}

	cards_have_changed_ = false;
	frame_count_++;

	if (help_screen)
	{
		gl::color(Color8u(255,255,255));
		gl::draw(mTextTexture);
	}
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
