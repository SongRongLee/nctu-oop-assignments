//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//
#include "mySystemApp.h"

using namespace std;

void MY_SYSTEM_APP::showStudentInfo( ) const
{
	cout << "*******************************" << endl;
	cout << "Student ID:0410023\t" << endl;
	cout << "Student Name:§õªQ¿Ä\t" << endl;
	cout << "Student Email:hub12345@ymail.com\t" << endl;
	cout << "*******************************" << endl;
}

MY_SYSTEM_APP::MY_SYSTEM_APP( )
{
	mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
}

void MY_SYSTEM_APP::initApp( )
{
	mFlgShow_Grid = true;
}

void MY_SYSTEM_APP::update( )
{

}




