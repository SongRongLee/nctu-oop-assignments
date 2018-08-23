#include "mySystem_2048.h"
#include <iostream>
#include<cmath>
using namespace std;

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
}
int MY_2048::getRandInt(int x0, int x1)
{
	return rand() % (x1 - x0 + 1) + x0;
}

void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

//
// copy the board of m to this object
//
void MY_2048::copy( const BASE_SYSTEM *m )
{
    //
    // Implement your own stuff
    //
	const MY_2048* temp_system = dynamic_cast<const MY_2048*>(m);
	if (temp_system!=NULL){
		for (int i = 0; i < mNX; i++){
			for (int j = 0; j < mNZ; j++){
				this->mBoard[j][i]=temp_system->mBoard[j][i];
			}
		}
	}
}


void MY_2048::reset( )
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            mBoard[ j ][ i ] = 0;
			mTmpBoard[j][i] = 0;
        }
    }
    //mNumFreeCells = mNX * mNZ;
    mEvent = 0;
}

void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "MY_2048" << endl;
	cout << "Key usage:" << endl;
	cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
	cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
	cout << "3: generate randomly the numbers for all the cells" << endl;
	cout << "r: clear all the cells" << endl;
	cout << " " << endl;
	cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;
}

//
// Generate a new number (2 or 4) randomly.
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
	int ok = 0;
	for (int j = 0; j < mNZ; ++j) {
		for (int i = 0; i < mNX; ++i) {
			if (mBoard[j][i] == 0){
				ok = 1;
				break;
			}
		}
	}
	if (ok == 0)return;
	int xcoord = getRandInt(0, mNX-1), ycoord=getRandInt(0,mNZ-1);
	while (mBoard[ycoord][xcoord] != 0){
		xcoord = getRandInt(0, mNX - 1);
		ycoord = getRandInt(0, mNZ - 1);
	}
	mBoard[ycoord][xcoord] = getRandInt(1, 2) * 2;
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    //
	for (int i = 0; i < mNZ-1; i++){
		for (int j = 0; j < mNX; j++){
			int  row = i+1;
			while (row < mNZ && mBoard[row][j] == 0){
				row++;
			}
			if (row != mNZ && mBoard[i][j] == mBoard[row][j]){
				mBoard[i][j] *= 2;
				mBoard[row][j] = 0;
			}
		}
	}
	
	for (int i = 0; i < mNX; i++){
		int count = 0;
		for (int j = 0; j < mNZ; j++){
			if (mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[count][i];
			mBoard[count][i] = mBoard[j][i];
			mBoard[j][i] = temp;
			count++;
		}
	}
}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
	for (int i = mNZ - 1; i > 0; i--){
		for (int j = 0; j < mNX; j++){
			int  row = i - 1;
			while (row >= 0 && mBoard[row][j] == 0){
				row--;
			}
			if (row >= 0 && mBoard[i][j] == mBoard[row][j]){
				mBoard[i][j] *= 2;
				mBoard[row][j] = 0;
			}
		}
	}
	for (int i = 0; i < mNX; i++){
		int count = 0;
		for (int j = mNZ-1; j >= 0; j--){
			if (mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[mNZ-count-1][i];
			mBoard[mNZ - count-1][i] = mBoard[j][i];
			mBoard[j][i] = temp;
			count++;
		}
	}

}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNX-1; j++){
		for (int i = 0; i < mNZ; i++){		
			int  col = j + 1;
			while (col < mNX && mBoard[i][col] == 0){
				col++;
			}
			if (col != mNX && mBoard[i][j] == mBoard[i][col]){
				mBoard[i][j] *= 2;
				mBoard[i][col] = 0;
			}
		}
	}
	
	for (int j = 0; j < mNZ; j++){	
		int count = 0;
		for (int i = 0; i < mNX; i++){
			if (mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[j][count];
			mBoard[j][count] = mBoard[j][i];
			mBoard[j][i] = temp;
			count++;
		}
	}
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
	for (int j = mNX-1; j > 0; j--){
		for (int i = 0; i < mNZ; i++){
			int  col = j - 1;
			while (col >= 0 && mBoard[i][col] == 0){
				col--;
			}
			if (col >= 0 && mBoard[i][j] == mBoard[i][col]){
				mBoard[i][j] *= 2;
				mBoard[i][col] = 0;
			}
		}
	}

	for (int j = 0; j < mNZ; j++){
		int count = 0;
		for (int i = mNX-1; i >= 0; i--){
			if (mBoard[j][i] == 0)continue;
			int temp;
			temp = mBoard[j][mNX-count-1];
			mBoard[j][mNX - count - 1] = mBoard[j][i];
			mBoard[j][i] = temp;
			count++;
		}
	}
}

void MY_2048::generateNumbers_All_2to4( )
{
    reset( );
	
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
		for (int i = 0; i < mNX; ++i) {
			mBoard[j][i] = getRandInt(1,2)*2;
		}
	}
}

void MY_2048::generateNumbers_All_2to8( )
{
    reset( );
	
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
		for (int i = 0; i < mNX; ++i) {
			mBoard[j][i] = (int)pow(2,getRandInt(1, 3));
		}
	}
}

void MY_2048::generateNumbers_All( )
{
    reset( );
    //
    // Implement your own stuff
    //
	for (int j = 0; j < mNZ; ++j) {
		for (int i = 0; i < mNX; ++i) {
			mBoard[j][i] = (int)pow(2, getRandInt(1, 11));
		}
	}
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        generateNumbers_All_2to4( );
        break;
    case '2':
        generateNumbers_All_2to8( );
        break;
    case '3':
        generateNumbers_All( );
        break;
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }
    //
    // Implement your own stuff
    //
	if (flgDone == true){
		generateNumber();
	}
}
