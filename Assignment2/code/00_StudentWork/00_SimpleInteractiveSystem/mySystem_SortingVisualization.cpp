//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_SortingVisualization.h"
#include <iostream>

using namespace std;

SORTING_VISUALIZATION::SORTING_VISUALIZATION( )
{
    mNumElements = 20;
    mMinValue = 1;
    mMaxValue = 30;
    reset( );
}

/*
Generate randomly the elements between mMinValue and mMaxValue.
The total number of elements is mNumElements.
*/
void SORTING_VISUALIZATION::reset( )
{
	mCurrentIndex = 0;
	mMaxNonHandledElementIndex = mNumElements;
	mNumbers.clear();
	for (int i = 0; i < mNumElements; i++)
	{
		mNumbers.push_back(rand() % (mMaxValue - mMinValue + 1) + mMinValue);
	}
}

/*
Show the system title.
Ask to input the range [mMinValue, mMaxValue] of the elements.
Ask to input the number of elements.
Generate the elements.
*/
void SORTING_VISUALIZATION::askForInput( )
{
    cout << "//////////////////////////////" << endl;
    cout << "SORTING_VISUALIZATION" << endl;
	cout << "The range of elements is [1, 30]:" << endl;	
	do{
		cout << "Input minValue and maxValue:" << endl;
		cin >> mMinValue;
		cin >> mMaxValue;
	} while (mMinValue<1 || mMaxValue>30 || mMinValue > mMaxValue);	
	do{
		cout << "Input the number of elements [1, 50]:" << endl;
		cin >> mNumElements;
	} while (mNumElements<1 || mNumElements>50);
	cout << "//////////////////////////////" << endl;
	cout << "Press SPACEBAR to visualize the process..." << endl;
	cout << "//////////////////////////////" << endl;
	reset();
}

/*
Two elements whose
indices are (index) and (index+1).

Swap these two elements if their order is incorrect.
*/
void SORTING_VISUALIZATION::checkAndSwapTwoElements( int index )
{
	if (mNumbers[index] > mNumbers[index + 1]){
		int temp = mNumbers[index];
		mNumbers[index] = mNumbers[index + 1];
		mNumbers[index + 1] = temp;
	}
}

/*
Perform one swap step for two elements.
The first element is indicated by mCurrentIndex.
*/
void SORTING_VISUALIZATION::processOneSwapStep( )
{
	if (mCurrentIndex != mMaxNonHandledElementIndex-2)
	{
		checkAndSwapTwoElements(mCurrentIndex);
		mCurrentIndex++;
	}
	else if (mMaxNonHandledElementIndex!=0)
	{
		checkAndSwapTwoElements(mCurrentIndex);
		mMaxNonHandledElementIndex--;
		mCurrentIndex = 0;
	}
}

/*
Return the current element that will be processed.
*/
int SORTING_VISUALIZATION::getCurrentElementIndex( ) const
{
    return mCurrentIndex;
}

/*
Return the index of the last non-handled element.

mMaxNonHandledElementIndex
*/
int SORTING_VISUALIZATION::getMaxNonHandledElementIndex( ) const
{
    return mMaxNonHandledElementIndex;
}

/*
Return the number of elements.
*/
int SORTING_VISUALIZATION::getNumOfElements( ) const
{
    //Return the number of elements
    return mNumElements;
}

/*
Return the element whose index is elementIndex.
*/
int SORTING_VISUALIZATION::getElement( int elementIndex ) const
{
    return mNumbers[elementIndex];
}