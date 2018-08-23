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



void MY_SYSTEM_APP::askForInput( )
{
	switch( mSystemType ) {
		case SYSTEM_TYPE_MONTE_CARLO_CIRCLE:
			mMonteCarloSystem.askForInput( );
			break;
		case SYSTEM_TYPE_QUADRATIC_FUNCTION:
			mQuadraticFunction.askForInput( );
			break;
		case SYSTEM_TYPE_CUBIC_FUNCTION:
			mCubicFunction.askForInput( );
			break;
		case SYSTEM_TYPE_STUDENT_RECORD_MANAGER:
			mStudentRecordManager.askForInput( );
			break;
	}
}

bool MY_SYSTEM_APP::specialFunc(int key, int x, int y)
{
	//cout << "special key:" << key << endl;

	switch( key ) {
	case GLUT_KEY_F1:
		mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE;
		cout << "mSystemType = SYSTEM_TYPE_MONTE_CARLO_CIRCLE" << endl;
		break;
	case GLUT_KEY_F2:
		mSystemType = SYSTEM_TYPE_QUADRATIC_FUNCTION;
		cout << "mSystemType = SYSTEM_TYPE_QUADRATIC_FUNCTION" << endl;

		break;
	case GLUT_KEY_F3:
		mSystemType = SYSTEM_TYPE_CUBIC_FUNCTION;
		cout << "mSystemType = SYSTEM_TYPE_CUBIC_FUNCTION" << endl;

		break;
case GLUT_KEY_F4:
		mSystemType = SYSTEM_TYPE_STUDENT_RECORD_MANAGER;
		cout << "mSystemType = SYSTEM_TYPE_STUDENT_RECORD_MANAGER" << endl;

		break;
	}
	return true;
}

bool MY_SYSTEM_APP::handleKeyEvent( unsigned char key )
{
	bool flgHandled = false;
	switch ( key ) {
		case 's':
		case 'S':
			showStudentInfo( );
			break;
		case 'i':
		case 'I':
			askForInput( );
			break;
		case 'g':
		case 'G':
			mFlgShow_Grid = !mFlgShow_Grid;
			break;
	}
	return flgHandled;
}

bool MY_SYSTEM_APP::mouseMotionFunc( int mx, int my )
{
	static vector3 color( 1.0, 0.0, 0.0 );
	if ( mMouseButton == GLUT_LEFT_BUTTON ) {
		//cout << "mouseMotionFunc GLUT_LEFT_BUTTON" << endl;
		float x, y, z;
		mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

		float rf = (rand()%1000)/1000.0f*0.5f;
		color += vector3(0.1f, 0.07f, 0.11f*rf);
		//clickAt( (int) x, (int) z, color );

	} else {
		//if ( mPickedObj == 0 ) {
		return FREE_CANVAS_2D::mouseMotionFunc( mx, my );
		//}
	}

	//cout << "here 5" << endl;

	//float x, y, z;
	//mCamera->getCoordinates( x, y, z, mx, my );
	//cout << "Set Position XZ:" << x << "\t" << z << endl;
	return true;
}

bool MY_SYSTEM_APP::mouseFunc( int button, int state, int mx, int my )
{
	//cout << "button:" << button << endl;
	//if ( mPickedObj == 0 || button == GLUT_MIDDLE_BUTTON ) {
	//if ( button == 3 || button == 4 ) {

	float x, y, z;
	mCamera->getCoordinates( x, y, z, (float) mx, (float) my );

	vector3 color( 1.0, 0.0, 0.0 );
	mMouseButton = button;
	if ( button == GLUT_LEFT_BUTTON ) {
		//clickAt( (int) x, (int) z, color );
	} else {
		return FREE_CANVAS_2D::mouseFunc( button, state, mx, my );
	}
	return true;
}


bool MY_SYSTEM_APP::passiveMouseFunc( int mx, int my )
{
	float x, y, z;
	mCamera->getCoordinates( x, y, z, (float) mx, (float) my );
	return true;
}