//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#ifndef __MY_CUBIC_FUNCTION_H_
#define __MY_CUBIC_FUNCTION_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;
class CUBIC_FUNCTION
{
protected:
	// ax^3 + bx^2 + cx +d 
	double a, b, c, d;
	double x0, x1;
	int mNumSamples;
public:
	CUBIC_FUNCTION( );
	void askForInput( );
	void getRangeOfX( double &x0, double &x1 ) const;
	int getNumOfSamples( ) const;
	double getValue( double x ) const;

};
#endif