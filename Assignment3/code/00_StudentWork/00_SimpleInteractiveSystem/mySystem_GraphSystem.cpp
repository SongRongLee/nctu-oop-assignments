#include <iostream>
#include "mySystem_GraphSystem.h"

using namespace std;

int GRAPH_SYSTEM::getRandInt(int x0, int x1)
{	
	return rand()%(x1-x0+1)+x0;
}

GRAPH_SYSTEM::GRAPH_SYSTEM( )
{
    //
    // Implement your own stuff
    //
	srand(time(NULL));
	node_count = 0;
	edge_count = 0;
    createDefaultGraph();
}

void GRAPH_SYSTEM::reset( )
{

    //
    // Implement your own stuff
    //
	mNodes.clear();
	mEdges.clear();
	node_count = 0;
	edge_count = 0;
    mPassiveSelectedNode = 0;
    mSelectedNode = 0;
}

void GRAPH_SYSTEM::createDefaultGraph( )
{
    reset( );

    int n_0 = addNode( 0.0, 0.0, 0.0 );
    int n_1 = addNode( 5.0, 0.0, 0.0 );
    int n_2 = addNode( 0.0, 0.0, 5.0 );
    addEdge( n_0, n_1 );
    addEdge( n_1, n_2 );
}

void GRAPH_SYSTEM::createNet_Horizontal( int nx, int ny )
{
    reset( );

    float dx = 5.0; // spacing along the x-axis
    float dz = 5.0; // spacing along the y-axis
    //
    // Implement your own stuff
    //
	for (int i = 0; i < ny; i++){
		int pre=-1, cur;
		for (int j = 0; j < nx; j++){
			cur = addNode(j*dx, 0.0, i*dz);
			if (pre != -1){
				addEdge(pre, cur);
			}
			pre = cur;
		}
	}
}

void GRAPH_SYSTEM::createNet_Vertical( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    //
    // Implement your own stuff
    //
	for (int i = 0; i < nx; i++){
		int pre = -1, cur;
		for (int j = 0; j < ny; j++){
			cur = addNode(i*dx, 0.0, j*dz);
			if (pre != -1){
				addEdge(pre, cur);
			}
			pre = cur;
		}
	}
}

void GRAPH_SYSTEM::createRandomGraph( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
	int tempID0=0, tempID1=0;
    //
    // Implement your own stuff
    //
	for (int i = 0; i < ny; i++){
		for (int j = 0; j < nx; j++){
			addNode(j*dx, 0.0, i*dz);
		}
	}
	for (int i = 0; i < 10; i++){		
		while (tempID0 == tempID1 || edgeExist(tempID0,tempID1)){
			tempID0 = getRandInt(0, node_count - 1);
			tempID1 = getRandInt(0, node_count - 1);
		}
		addEdge(tempID0, tempID1);
	}
}

void GRAPH_SYSTEM::createRadialGraph( int nx, int ny )
{
    reset( );

    float dx = 5.0;
    float dz = 5.0;
    //
    // Implement your own stuff
    //
	for (int i = 0; i < ny; i++){
		for (int j = 0; j < nx; j++){
			addNode(j*dx, 0.0, i*dz);
		}
	}
	int center = getRandInt(0, node_count-1);
	for (int i = 0; i < 10; i++){
		int tempID1 = getRandInt(0, node_count - 1);
		while (center == tempID1 || edgeExist(center, tempID1)){
			tempID1 = getRandInt(0, node_count - 1);
		}
		addEdge(center, tempID1);
	}
}
bool GRAPH_SYSTEM::edgeExist(int nodeID0, int nodeID1){
	for (int i = 0; i < edge_count; i++){
		if ((mEdges[i].nodeID[0] == nodeID0&&mEdges[i].nodeID[1] == nodeID1) || (mEdges[i].nodeID[0] == nodeID1&&mEdges[i].nodeID[1] == nodeID0)){
			return true;
		}
	}
	return false;
}
int GRAPH_SYSTEM::addNode( float x, float y, float z, float r )
{
    //
    // Implement your own stuff
    //
	mNodes.push_back(*(new GRAPH_NODE(x, y, z, r, node_count)));
	node_count++;
    return node_count-1;
}

int GRAPH_SYSTEM::addEdge( int nodeID_0, int nodeID_1 )
{
    //
    // Implement your own stuff
    //
	mEdges.push_back(*(new GRAPH_EDGE(nodeID_0, nodeID_1, edge_count)));
	edge_count++;
    return edge_count-1;
}

void GRAPH_SYSTEM::askForInput( )
{
    //
    // Implement your own stuff
    //
	cout << "GRAPH_SYSTEM" << endl;
	cout << "Key usage:" << endl;
	cout << "1: create a default graph" << endl;
	cout << "2: create a graph with 10x10 nodes. Connect the consecutive nodes horizontally" << endl;
	cout << "3: create a graph with 10x10 nodes. Connect the consecutive nodes vertically" << endl;
	cout << "4: create a graph with 10x10 nodes. Create 10 randomly generated edges" << endl;
	cout << "5: create a graph with 10x10 nodes. Create 10 randomly generated edges attached at a random node" << endl;
	cout << "Delete: delete a node and all the edges attached at it" << endl;
	cout << "Spacebar: unselect the selected node" << endl;
	cout << " " << endl;
	cout << "Use the mouse to select nodes and add edges" << endl;
	cout << "Click the left button to select/unselect or create an edge" << endl;
	cout << " " << endl;
	cout << "A selected node is highlighted as red." << endl;

}

// Find the nearest node to the given position (x, y, z).
// Note that we work in x-z plane only. y should be set to 0.
// The squared distance of the node and the given position should be stored in cur_distance2.
//
//
GRAPH_NODE *GRAPH_SYSTEM::findNearestNode( double x, double z, double &cur_distance2 ) const
{
    GRAPH_NODE *n = 0;
    //
    // Implement your own stuff
    //
    cur_distance2 = -1.0;
    for ( int i = 0; i < node_count; ++i ) {
		const GRAPH_NODE *cn = &mNodes[i];
		double dx = cn->p.x - x;
		double dz = cn->p.z - z;
		double d2 = dx*dx + dz*dz;
		if ( cur_distance2 < 0.0 || d2 < cur_distance2 ) {
		cur_distance2 = d2;
		n = (GRAPH_NODE *)cn;
		}
    }
    return n;
}

void GRAPH_SYSTEM::clickAt(double x, double z)
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) {
        mSelectedNode = 0;
        return;
    }
    //
    // A nearest node may not be touched by the mouse cursor.
    // Thus we need their distance to check.
    //
    if ( cur_d2 > n->r*n->r ) {
        mSelectedNode = 0;
        return;

    }
    if ( mSelectedNode == n ) {
        mSelectedNode = 0;
        return;
    }
    if ( mSelectedNode != 0 ) {
        addEdge( mSelectedNode->id, n->id );
        mSelectedNode = 0;
        return;
    }
    mSelectedNode = n;
}

void GRAPH_SYSTEM::deleteNode( int nodeID ) {
    //
    // Implement your own stuff
    //
	int i=0;
	while (i < mEdges.size()){
		if (mEdges[i].nodeID[0] == nodeID || mEdges[i].nodeID[1] == nodeID){
			mEdges.erase(mEdges.begin() + i);
			edge_count--;
		}
		else{
			i++;
		}
	}
	for (int i = 0; i < mNodes.size(); i++){
		if (mNodes[i].id == nodeID){
			mNodes.erase(mNodes.begin() + i);
			node_count--;
			break;
		}
	}
}

void GRAPH_SYSTEM::deleteSelectedNode(  ) {
    if ( mSelectedNode == 0 ) return;
    deleteNode( mSelectedNode->id );
    //
    // Implement your own stuff
    //
    // for examples,
    // delete edges attached at the node
    //
    //	
    mSelectedNode = 0;
    mPassiveSelectedNode = 0;
}

bool GRAPH_SYSTEM::isSelectedNode( ) const
{
    return mSelectedNode != 0;
}

void GRAPH_SYSTEM::getInfoOfSelectedPoint( double &r, vector3 &p ) const
{
    if ( isSelectedNode( ) == false ) return;
    r = mSelectedNode->r;
    p = mSelectedNode->p;

}

void GRAPH_SYSTEM::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 127: // delete
        deleteSelectedNode( );
        break;
    case '1':
        createDefaultGraph( );
        mSelectedNode = 0;
        break;
    case '2':
        createNet_Horizontal(10, 10);
        mSelectedNode = 0;

        break;
    case '3':
        createNet_Vertical(10, 10);
        mSelectedNode = 0;

        break;
    case '4':
        createRandomGraph(10, 10);
        mSelectedNode = 0;

        break;
    case '5':
        createRadialGraph(10, 10);
        mSelectedNode = 0;

        break;
    case ' ':
        mSelectedNode = 0;
        break;
    }
}

void GRAPH_SYSTEM::handlePassiveMouseEvent( double x, double z )
{
    double cur_d2;
    GRAPH_NODE *n = findNearestNode( x, z, cur_d2 );
    if ( n == 0 ) return;
    if ( cur_d2 > n->r*n->r ) {
        mPassiveSelectedNode = 0;
        return;
    }
    mPassiveSelectedNode = n;
}

int GRAPH_SYSTEM::getNumOfNodes( ) const
{
    //
    // Implement your own stuff
    //
    return node_count;
}

void GRAPH_SYSTEM::getNodeInfo( int nodeIndex, double &r, vector3 &p ) const
{
    //
    // Implement your own stuff
    //
	r = mNodes[nodeIndex].r;
	p = mNodes[nodeIndex].p;
}

int GRAPH_SYSTEM::getNumOfEdges( ) const
{
    //
    // Implement your own stuff
    //
    return edge_count; 
}

vector3 GRAPH_SYSTEM::getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const
{
    //
    // Implement your own stuff
    //
	int nodeID = mEdges[edgeIndex].nodeID[nodeIndex];
	for (int i = 0; i < mNodes.size(); i++){
		if (mNodes[i].id == nodeID){
			return mNodes[i].p;
		}
	}
}
