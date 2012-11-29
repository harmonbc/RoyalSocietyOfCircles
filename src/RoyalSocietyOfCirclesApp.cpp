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
#include "Circle.h"
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
	Circle*			sentinel_; 
	ColorCards*		sentinel_card_;

	//Actions from mouse/keboard methods
	void			editBoard(MouseEvent event);
	void			checkCards(MouseEvent event);
	void			bringToFront(MouseEvent event);
	void			removeLight(MouseEvent event);
	void			clearAllNodes();
	void            drawCards();

	//Assist Setup/Actions methods
	void			addCards();
	Circle*			getTopNode(MouseEvent event);
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
//Defines the colors used in the glowing pegs.
#define RED			Color8u(255,0,0)
#define YELLOW		Color8u(255,255,0)
#define GREEN		Color8u(0,255,0)
#define BLUE		Color8u(0,0,255)
#define VIOLET		Color8u(255,0,255)
#define WHITE		Color8u(255,255,255)
#define BLACK		Color8u(0,0,0)

static const int	kAppWidth=800;
static const int	kAppHeight=600;
//This will be the area where the cards are hel
static const int	kBottomBuffer=150;
static const float	kCircleRadius= 8;
static const int	kCircleDistance= (kCircleRadius*2)+2;
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
	sentinel_ = new Circle();
	sentinel_card_ = new ColorCards();
	help_screen = true;

	gl::enableAlphaBlending();
	drawHoles();
	addCards();
	setCurrentColor();

	mFont = Font( "Sans", 30 );
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
					//Check for boarders
					if((!even&&x+(kCircleRadius*2)+5<kAppWidth)||(even&&(x+(kCircleDistance/2)<kAppWidth-5)))
					{
						//All odd rows will be offset by 1/2 the regular distance
						Circle* c = new Circle(Vec2f((even) ? x : (x+(kCircleDistance/2)),y),kCircleRadius, WHITE);
						insertAfter(sentinel_, c);
					}
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
*Displays a message on start up that explaines controls. Satisfies Main Goal B(50/70)
**/
void RoyalSocietyOfCirclesApp::render()
{
	string txt = "WELCOME TO LITE BRITE!\nLeft Click inside of a grey circle to add a light";
	txt+="\nSelect color either by left clicking on a card or pressing 'n' to cycle through cards\n";
	txt+="\nRemove light by right clicking it";
	txt+="\nc = Clears all lights from the board";
	txt+="\nn = Cycle through colors";
	txt+="\nr = Reverse the list of colors";
	txt+="\n? = Toggle Help Screen\n";
	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( mFont ).size( Vec2i( mSize.x, TextBox::GROW ) ).text( txt );
	tbox.setColor( BLUE );
	tbox.setBackgroundColor( Color8u( 105, 105, 105 ) );
	Vec2i sz = tbox.measure();
	mTextTexture = gl::Texture( tbox.render() );
}
/**Listens for Actions**/
void RoyalSocietyOfCirclesApp::keyDown(KeyEvent event)
{
	if(event.getCode() == event.KEY_c) clearAllNodes();
	else if(event.getChar() == '?') help_screen = !(help_screen); 
	else if(event.getCode() == event.KEY_n) //changed to get code instead of the character
	{
		cycleDeck(sentinel_card_);
		setCurrentColor();
		cards_have_changed_ = true;
	}
	else if(event.getCode() == event.KEY_r)
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
	Circle* curNode = sentinel_->next_;
	while(curNode!=sentinel_)
	{
		curNode ->is_hole_ = true;
		curNode = curNode->next_;
	}
}


void RoyalSocietyOfCirclesApp::checkCards(MouseEvent event)
{
	ColorCards* temp2 = sentinel_card_->next_;

	Vec2f pos = Vec2f(event.getX(),event.getY());
	while(temp2!=sentinel_card_)
	{
		if((*temp2).isInside(pos))
		{
			remove(temp2);
			cur_color_ = temp2 ->color_;
			insertAfter(sentinel_card_, temp2);
			cards_have_changed_ = true;
			break;
		}
		temp2 = temp2 -> next_;
	}
}
void RoyalSocietyOfCirclesApp::removeLight(MouseEvent event)
{
	Circle* temp = sentinel_ -> next_;

	Vec2f click = Vec2f(event.getX(),event.getY());
	while(temp!=sentinel_)
	{
		if(isInCircle(temp, click))
		{
			temp ->is_hole_ = true;
			break;
		}
		temp = temp ->next_;
	}

}

void RoyalSocietyOfCirclesApp::editBoard(MouseEvent event)
{
	Circle* circ = sentinel_->next_;
	int x = event.getX();
	int y = event.getY();
	while(circ!=sentinel_)
	{
		if(isInCircle(circ, Vec2f(x, y)))
		{
			circ -> color_ = cur_color_;
			circ ->is_hole_ = false;
			break;
		}
		circ = circ -> next_;
	}
	ColorCards* temp2 = sentinel_card_ -> next_;

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

//Added to clean up the draw method a little - Raquel
void RoyalSocietyOfCirclesApp::drawCards(){

ColorCards* temp3 = sentinel_card_ ->prev_;

	int pos = 0;
	while(temp3!=sentinel_card_)
	{
		//Update cards if user has changed the order
		if(cards_have_changed_)
		{
			int xPosLeft = ((LAST-pos)*kCardBuffer);
			int yBuffer = (kCardBuffer*((LAST-pos)+1));

			temp3 -> upper_left_x = xPosLeft;
			temp3 -> upper_left_y = (kAppHeight-kBottomBuffer)+yBuffer;
			temp3 -> bottom_right_x = xPosLeft+kMaxCardWidth-kCardBuffer;
			temp3 -> bottom_right_y = (temp3 -> upper_left_y)+100;
		}

		(*temp3).draw();
		temp3 = temp3 -> prev_;
		pos++;
	}

	
	cards_have_changed_ = false;

}

void RoyalSocietyOfCirclesApp::update()
{
}

void RoyalSocietyOfCirclesApp::draw()
{
	gl::clear(Color8u( 105, 105, 105 ));
	Rectf rect(5,5, kAppWidth-5, kAppHeight-kBottomBuffer);

	gl::color(BLACK);
	gl::drawSolidRect(rect);

	Circle* temp = sentinel_->prev_;
	//Draw all circles(holes/pegs)
	while(temp!=sentinel_)
	{
		(*temp).draw(frame_count_);
		temp = temp->prev_;
	}

	//Draws all cards
	drawCards();

	frame_count_++;

	if (help_screen)
	{
		gl::color(WHITE);
		gl::draw(mTextTexture);
	}
}

CINDER_APP_BASIC( RoyalSocietyOfCirclesApp, RendererGl )
