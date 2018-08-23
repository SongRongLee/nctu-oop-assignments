//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SimplePainter.h"
#include <iostream>
#include "myBasicTools.h"
#define inside(x,y)(x<mNX&&x>=0&&y<mNY&&y>=0)
#define colorInside(r,g,b)(r>=0&&r<=1&&g>=0&&g<=1&&b>=0&&b<=1)
using namespace std;
namespace {
};

SIMPLE_PAINTER::SIMPLE_PAINTER()
{
    mMaxBrushSize = 21;
    mBrushSize = 3; 

    mNX = 256; // index from 0 to mNX-1 along the x-axis; number of colmns
    mNY = 256; // index from 0 to mNY-1 along the y-axis; number of rows

    mCanvas = new vector3[mNX*mNY]; // a color bitmap
    mColor = vector3(1.0, 0.0, 0.0); // current color
    mTransparency = 0.25;  // current transparency
    reset( );
}

/*
Randomly generate the colors of the bitmap.
*/
void SIMPLE_PAINTER::reset( )
{
    double v0 = 0.75;
    double v1 = 0.9;
    for ( int i = 0; i < mNY*mNX; ++i ) {
		mCanvas[i] = vector3(getRandDouble(v0, v1), getRandDouble(v0, v1), getRandDouble(v0, v1));
    }
}

/*
Get the canvas dimension.
nx : number of columns
ny : number of rows

nx = mNX;
ny = mNY;
*/
void SIMPLE_PAINTER::getCanvasDimension( int &nx, int &ny ) const
{
   nx = mNX;
   ny = mNY;
}

//Return x + y*nx
int SIMPLE_PAINTER::computeCanvasIndex( int x, int y, int nx, int ny )
{
    return x+y*nx;
}

/*
Get the color at pixel (x,y).
Store it to color.
*/
void SIMPLE_PAINTER::getColorAtPixel( int x, int y, vector3 &color ) const
{
	int index = x+y*mNX;
    color = mCanvas[index];
}

/*
Show system title.
Show key usage.
*/
void SIMPLE_PAINTER::askForInput( )
{
    cout << "SIMPLE_PAINTER::askForInput( )" << endl;
	cout << "Please use keyboard and mouse to control" << endl;
	cout << "1: red color" << endl;
	cout << "2: green color" << endl;
	cout << "3: blue color" << endl;
	cout << ",: decrease brush size" << endl;
	cout << ".: increase brush size" << endl;
}

/*
Return true if the key event is handled.
Return false otherwise.

Make sure that the brush size is not larger than mMaxBrushSize.
*/
bool SIMPLE_PAINTER::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
	switch (key)
	{
	case '1':
		mColor = vector3(1.0, 0.0, 0.0);
		flgHandled = true;
		break;
	case '2':
		mColor = vector3(0.0, 1.0, 0.0);
		flgHandled = true;
		break;
	case '3':
		mColor = vector3(0.0, 0.0, 1.0);
		flgHandled = true;
		break;
	case ',':
		mBrushSize -= 2;
		if (mBrushSize < 0)
		{
			mBrushSize = 0;
		}
		flgHandled = true;
		flgHandled = true;
		break;
	case '.':		
		mBrushSize += 2;
		if (mBrushSize > mMaxBrushSize)
		{
			mBrushSize = mMaxBrushSize;
		}
		break;
	default:
		break;
	}
    return flgHandled;
}

/*
Return the brush size:
Return mBrushSize
*/
int SIMPLE_PAINTER::getBrushSize( ) const
{
    return mBrushSize;
}

/*
Set color:
mColor = color
*/
void SIMPLE_PAINTER::setColor( const vector3 &color )
{
    mColor = color;
}

/*
Set transparency:
mTransparency = v
*/
void SIMPLE_PAINTER::setTransparency( float v ) {
    mTransparency = v;
}

/*
Use the brush to draw. The center is at (x,y).
A disk is defined based on position (x,y) and
brush radius.

The radius of  the disk is set to ~2*mBrushSize.
Steps:

For each pixel in the disk centered at (x,y)
   do
     compute color and transparency
     draw at the pixel
*/
void SIMPLE_PAINTER::clickAt(double x, double y)
{
	vector3 color = mColor;
	int R = 2 * mBrushSize;
	for (int j = -R; j <= R; j++) {
		for (int i = -R; i <= R; i++) {
			double rx = i;
			double ry = j;
			double w = 1.0;	// weight
			double r2 = rx*rx + ry*ry;

			if (r2 > R*R/4.0) continue;    // this pixel is too far. ignore it
			else if (r2 > R*R / 32.0) {    // pixel is a bit far but not too far
				double k = R*R / 32.0 - r2;
				double d = 0.003;		   // magic number
				w = pow(2.718281828, d*k); // use the guassian function to compute weight w
			}
			else {
				w = 1.0; // pixel is near to the center (x,y). Set weight to a high value; here it's one.
			}
			//
			drawAt(x + i, y + j, w*color, w*mTransparency);
		}
	}

}

/*
Draw one pxiel at (x,y) with color and weight w.
If (x,y) is not inside the canvas return.

Make sure that the color component is inside [0,1].

new color = current_color*(1.0-w*w) + w*w*color;
*/
void SIMPLE_PAINTER::drawAt(int x, int y, const vector3 &color, double w )
{
	if (inside(x, y) && colorInside(color.r, color.g, color.b)){
		//colorFit(color);
		mCanvas[computeCanvasIndex(x, y, mNX, mNY)] = mCanvas[computeCanvasIndex(x, y, mNX, mNY)]*(1.0-w*w)+w*w*color;
	}
	return;
}
