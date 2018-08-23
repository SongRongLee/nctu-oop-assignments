//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_MonteCarlo.h"
#include <iostream>
#include <iomanip>
using namespace std;

#define MAX_SAMPLES 1000000
#define inside(x,y)(sqrt(x*x+y*y)<=mRadius)

MONTE_CARLO_SYSTEM::MONTE_CARLO_SYSTEM( )
{
	cout.precision(8);
	srand(time(NULL));
	//
	mRadius = 5.0f;
	mNumSamples = MAX_SAMPLES;
	cout << "Hi" << endl;
	computeSamples( );
}

void MONTE_CARLO_SYSTEM::askForInput( )
{
	//
	//Show the system name
	//Ask to input the radius of the circle
	//Ask to input the number of sample points
	//Call computeSamples( ) to compute the sample points and pi
	//
	cout << "This is a Monte Carlo Simulation." << endl;
	cout << "Please input the radius of the circle:" << endl;
	cin >> mRadius;
	cout << "Please input the number of samples [1,1000000]:" << endl;
	cin >> mNumSamples;
	mX.clear();
	mY.clear();
	computeSamples();
}

void MONTE_CARLO_SYSTEM::computeSamples( )
{
	//
	//Compute the coordinates of the sample points.
	//There are mNumSamples samples.
	//Compute pi which is equal to:
	// 4*(number of samples inside the circle / total samples)
	//
	int samplesInside = 0;
	for (int i = 0; i < mNumSamples; i++)
	{
		mX.push_back((rand() / (double)(RAND_MAX)) * 2 * mRadius - mRadius);
		mY.push_back((rand() / (double)(RAND_MAX)) * 2 * mRadius - mRadius);
		if (inside(mX[i], mY[i]))
		{
			samplesInside++;
		}
	}
	if (samplesInside != 0)
	{
		cout <<showpoint<< "PI:" << 4*(double)samplesInside / mNumSamples << endl;
	}
}



double MONTE_CARLO_SYSTEM::getRadius( ) const
{
	//Return the radius of the circle
	return mRadius;
}

int MONTE_CARLO_SYSTEM::getNumSamples( ) const
{
	//Return the number of sample points
	return mNumSamples;
}

bool MONTE_CARLO_SYSTEM::getSample(int sampleIndex, float &x, float &y) const
{
	//
	//Return the sample coordinates in (x, y).
	//Return the boolean value indicating whether the sample lying inside the circle.
	//
	bool flgInside = false;
	x = mX[sampleIndex];
	y = mY[sampleIndex];
	if (inside(x, y))flgInside = true;
	return flgInside;
}
