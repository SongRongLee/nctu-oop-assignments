//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystem_StudentRecordManager.h"
#include <iostream>
#include <algorithm>
using namespace std;

STUDENT_RECORD_MANAGER::STUDENT_RECORD_MANAGER( )
{
	mNumStudents = 0;
}

void STUDENT_RECORD_MANAGER::askForInput( )
{
	//Show the system title
	//Ask to input the number of students
	//Ask to input the score of each student
	//Show the average
	//Show the standard deviation
	//Show the scores in an ascending order
	//
	mScore.clear();
	mSortedScore.clear();
	cout << "STUDENT_RECORD_MANAGER" << endl;
	cout << "Input the number of students:" << endl;
	cin >> mNumStudents;
	cout << "Input the scores:" << endl;
	for (int i = 0; i < mNumStudents; i++)
	{
		int tempScore;
		cin >> tempScore;
		mScore.push_back(tempScore);
	}
	cout << "Average:" << computeAverage() << endl;
	cout << "Standard Deviation:" << computeStandardDeviation() << endl;
	sortScores();
	showSortedScores();
}

double STUDENT_RECORD_MANAGER::computeAverage( )
{
	//Compute the average
	double sum=0;
	for (int i = 0; i < mNumStudents; i++)
	{
		sum += mScore[i];
	}
	mAverageScore = sum / mNumStudents;
	return mAverageScore;
}

double STUDENT_RECORD_MANAGER::computeStandardDeviation( )
{
	//Compute the standard deviation
	double quadraticSum = 0;
	for (int i = 0; i < mNumStudents; i++)
	{
		quadraticSum += (mScore[i] - mAverageScore)*(mScore[i] - mAverageScore);
	}
	mStandardDeviation = sqrt(quadraticSum / mNumStudents);
	return mStandardDeviation;
}

void STUDENT_RECORD_MANAGER::sortScores( )
{
	//Sorting in an ascending order
	mSortedScore = mScore;
	sort(mSortedScore.begin(), mSortedScore.end());
}

void STUDENT_RECORD_MANAGER::showSortedScores( ) const
{
	//Show the scores in an ascending order
	cout << "Sorted Scores:" << endl;
	for (int i = 0; i < mNumStudents; i++)
	{
		cout << mSortedScore[i] << endl;
	}
}

int STUDENT_RECORD_MANAGER::getNumOfStudentsInScoreInterval(int s0, int s1) const
{
	//
	//Return the number of students whose score is inside the interval [s0, s1]. 
	//s0 and s1 are included.
	// 
	int num = 0;
	for (int i = 0; i < mNumStudents; i++)
	{
		if (mScore[i] >= s0&&mScore[i] <= s1)
		{
			num++;
		}
	}
	return num;
}
