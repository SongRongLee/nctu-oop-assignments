//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_GalaxySystem.h"
#include <iostream>

using namespace std;

namespace {
    double getRandDouble( double L, double U ) {
        return L + (U-L)*rand( )/(double) RAND_MAX;
    }
	double dist(double x1, double y1, double x2, double y2){
		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}
};

GALAXY_SYSTEM::GALAXY_SYSTEM( )
{
	
    mTimeStep = 0.0015; 
    mMaxV = 100.0;
    mNumOfObjs = 100;
    mNumLargeObjs = 2;
    mMinR = 0.5;            //minimum radius of objects
    mMaxR = 3.0;            //maximum radius of objects
    mSpaceSize = 300.0;
    mG = 5.0;               //gravitational constant
	mX.reserve(mNumOfObjs);
	mY.reserve(mNumOfObjs);
	mR.reserve(mNumOfObjs);
	mMass.reserve(mNumOfObjs);
	mVx.reserve(mNumOfObjs);
	mVy.reserve(mNumOfObjs);
	mFx.reserve(mNumOfObjs);
	mFy.reserve(mNumOfObjs);	
	mAlive.reserve(mNumOfObjs);
	srand(time(NULL));
    generateObjects( );
}

/*
Generate randomly the positions,  
velocities and radii of the objects.

Also, if the objects are large, 
set their masses to be a large number.

The mass of an  object depends on the object's radius.

The position of an object is inside 
[-halfSpaceSize, halfSpaceSize]x[-halfSpaceSize, halfSpaceSize].

The velocity of an object is inside
[-100.0, 100]x[-100.0, 100].

Initialize the alive flag of each object.
the alive flag indicates whether the object is alive or not.
If the object is not alive, ignore it in all the calculations.

If there's only one large object,
set its position to the origin
and set its velocity to zero.

*/
void GALAXY_SYSTEM::generateObjects( )
{
    //Fill in here
    for (int i = 0; i < mNumLargeObjs; i++)
	{
		if (mNumLargeObjs == 1)
		{
			mX[i] = 0;
			mY[i] = 0;
		}
		else
		{
			mX[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
			mY[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		}
		mVx[i] = 0;
		mVy[i] = 0;
		mR[i] = mMaxR * 2;
		mMass[i] = mMaxR*mMaxR * 1000;		
		mAlive[i] = true;
	}
	for (int i = mNumLargeObjs; i < mNumOfObjs; i++)
	{
		mX[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mY[i] = getRandDouble(-mSpaceSize / 2, mSpaceSize / 2);
		mVx[i] = getRandDouble(-100, 100);
		mVy[i] = getRandDouble(-100, 100);
		mR[i] = getRandDouble(mMinR, mMaxR);
		mMass[i] = mR[i]*mR[i];
		mAlive[i] = true;
	}
}

/*
Handle the key events.
*/
bool GALAXY_SYSTEM::handleKeyPressedEvent( int key )
{
    bool flgHandled = false;
	switch (key)
	{
	case '1':
		mNumLargeObjs = 1;
		flgHandled = true;
		generateObjects();
		break;
	case '2':
		mNumLargeObjs = 2;
		flgHandled = true;
		generateObjects();
		break;
	case '3':
		mNumLargeObjs = 3;
		flgHandled = true;
		generateObjects();
		break;
	default:
		break;
	}	
    return flgHandled;
}

/*
Generate the objects.
Call generateObjects( ).
*/
void GALAXY_SYSTEM::reset( )
{
    generateObjects( );
}

/*
Show the system title.
Show the key usage.
*/
void GALAXY_SYSTEM::askForInput( )
{
    cout << "GALAXY_SYSTEM::askForInput" << endl;
	cout << "Key usage:" << endl;
	cout << "1: one large object" << endl; 
	cout << "2: two large object" << endl; 
	cout << "3: three large object" << endl; 
	cout << "r: reset" << endl;
}

/*
Return the number of objects
return mNumOfObjs
*/
int GALAXY_SYSTEM::getNumOfObjs( ) const
{
    return mNumOfObjs;
}

/*
Get the object information based on the object index.
(x,y) = position
r = radius
Return the alive flag.
*/
bool GALAXY_SYSTEM::getObjInfo( int objIndex, double &x, double &y, double &r ) const
{
    x = mX[objIndex];
	y = mY[objIndex];
    r = mR[objIndex];
    return mAlive[objIndex];
}

/*
Merge the objects if they overlap with each other.
Modify the velocities of the objects after merging
based on the conservation of momentum.
Set the alive flags of the objects accordingly.

Pseudo-code

For each pair of the objects
  if they do not overlap continue
  If they overlap
    do
      turn off the alive flag of the object with smaller radius
      compute the new velocity of the larger object
*/
void GALAXY_SYSTEM::mergeObjects( )
{
	for (int i = 0; i < mNumOfObjs; i++) 
	{
		if (!mAlive[i]) continue;
		for (int j = i + 1; j < mNumOfObjs; j++) 
		{
			if (!mAlive[j]) continue;
			if (dist(mX[i], mY[i], mX[j], mY[j]) < mR[i] + mR[j])
			{
				int larger=(mR[i]>mR[j]?i:j);
				int smaller = (larger == j ? i : j);
				mAlive[smaller] = false;
				
				mVx[larger] = (mVx[i] * mMass[i] + mVx[j] * mMass[j]) / (mMass[i] + mMass[j]);
				mVy[larger] = (mVy[i] * mMass[i] + mVy[j] * mMass[j]) / (mMass[i] + mMass[j]);
				mMass[larger] += mMass[smaller];
			}
		}
	}
}

/*
Update the position of the objects
Steps:
1. compute the forces exerting on each object
2. compute the velocity of each object
3. compute the position of each object

Constraints:
The component of a velocity must be inside [-mMaxV, mMaxV].

The component of a position must be inside [-halfSpaceSize, halfSpaceSize].
Warp the position if it's outside of the range.
Consider a position (x,y).
If x > halfSpaceSize, set x = -halfSpaceSize;


*/
void GALAXY_SYSTEM::update( ) 
{
    mergeObjects( ); // merge objects first if they overlap with each other
    
    //
    //Fill in here
    //compute forces exerting on objects
    //compute velocities of objects
    //compute positions of objects
    //make sure the objects inside the space
	for (int i = 0; i < mNumOfObjs; i++)
	{
		mFx[i] = 0;
		mFy[i] = 0;
	}
    for (int i = 0; i < mNumOfObjs; i++)
	{
		if (!mAlive[i]) continue;
		for (int j = i + 1; j < mNumOfObjs; j++)
		{
			if (!mAlive[j]) continue;
			double d = dist(mX[i], mY[i], mX[j], mY[j]);
			//Force
			double nx = (mX[i] - mX[j]) / d; //normalize along the x-axis
			double ny = (mY[i] - mY[j]) / d; //normalize along the y-axis

			double mij = mMass[i]*mMass[j];

			mFx[i] -= mij*mG*nx / ((mX[i] - mX[j])*(mX[i] - mX[j]) + (mY[i] - mY[j])*(mY[i] - mY[j])); 	//notice the negative sign	
			mFy[i] -= mij*mG*ny / ((mX[i] - mX[j])*(mX[i] - mX[j]) + (mY[i] - mY[j])*(mY[i] - mY[j]));	//notice the negative sign

			mFx[j] += mij*mG*nx / ((mX[i] - mX[j])*(mX[i] - mX[j]) + (mY[i] - mY[j])*(mY[i] - mY[j]));	//notice the positive sign
			mFy[j] += mij*mG*ny / ((mX[i] - mX[j])*(mX[i] - mX[j]) + (mY[i] - mY[j])*(mY[i] - mY[j]));  //notice the positive sign
		}
	}
	for (int i = 0; i < mNumOfObjs; i++)
	{
		if (!mAlive[i]) continue;
		//Velocity
		mVx[i] = mVx[i] + mFx[i] / mMass[i] * mTimeStep;
		mVy[i] = mVy[i] + mFy[i] / mMass[i] * mTimeStep;
		if (fabs(mVx[i]) > mMaxV)mVx[i] = (mVx[i] > 0 ? mMaxV : -mMaxV);
		if (fabs(mVy[i]) > mMaxV)mVy[i] = (mVy[i] > 0 ? mMaxV : -mMaxV);
	}
	for (int i = 0; i < mNumOfObjs; i++)
	{
		if (!mAlive[i]) continue;
		//Position
		mX[i] = mX[i] + mVx[i] * mTimeStep;
		mY[i] = mY[i] + mVy[i] * mTimeStep;
		if (mX[i]>mSpaceSize / 2)
		{
			mX[i] = -mSpaceSize / 2;
		}
		else if (mX[i] < -mSpaceSize / 2)
		{
			mX[i] = mSpaceSize / 2;
		}
		if (mY[i]>mSpaceSize / 2)
		{
			mY[i] = -mSpaceSize / 2;
		}
		else if (mY[i] < -mSpaceSize / 2)
		{
			mY[i] = mSpaceSize / 2;
		}
	}
}