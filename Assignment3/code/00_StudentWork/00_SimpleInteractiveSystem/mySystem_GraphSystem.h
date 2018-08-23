//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//

#ifndef __MY_GRAPH_SYSTEM_H_
#define __MY_GRAPH_SYSTEM_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
#include "graph_basics.h"

using std::vector;

//#define GRAPH_MAX_NUM_NODES 10000
//#define GRAPH_MAX_NUM_EDGES 10000



class GRAPH_SYSTEM : public BASE_SYSTEM {

protected:
    /*
    void drawNodes( ) const;
    void drawEdges( ) const;
    void drawSelectedNode( ) const;
    */
    //
    void drawNodes_Indirect( ) const;
    void drawEdges_Indirect( ) const;
    void drawSelectedNode_Indirect( ) const;

    GRAPH_NODE *findNearestNode( double x, double z, double &cur_distance2 ) const;
    void deleteNode( int nodeID );
    void deleteSelectedNode(  );
    void createDefaultGraph( );
    void createNet_Horizontal( int nx, int ny );
    void createNet_Vertical( int nx, int ny );
    void createRandomGraph( int nx, int ny );
    void createRadialGraph( int nx, int ny );	
    //
    // Implement your own stuff
    //
	int getRandInt(int x0, int x1);
	bool edgeExist(int nodeID0, int nodeID1);
public:
    GRAPH_SYSTEM( );
    void reset( );
    void askForInput( );
    void clickAt(double x, double z);
    void handleKeyPressedEvent( unsigned char key );
    void handlePassiveMouseEvent( double x, double y );
    void draw( ) const;
    
    int addNode( float x, float y, float z, float r = 1.0 );
    int addEdge( int nodeID_0, int nodeID_1 );
    bool isSelectedNode( ) const;
    void getInfoOfSelectedPoint( double &r, vector3 &p ) const;
    //
    int getNumOfEdges( ) const;
    vector3 getNodePositionOfEdge( int edgeIndex, int nodeIndex ) const;

    int getNumOfNodes( ) const;
    void getNodeInfo( int nodeIndex, double &r, vector3 &p ) const;
protected:
    //
    // Implement your own stuff
    //
	int node_count;
	int edge_count;
	vector<GRAPH_NODE> mNodes;
	vector<GRAPH_EDGE> mEdges;
    GRAPH_NODE *mSelectedNode;
    GRAPH_NODE *mPassiveSelectedNode;
};

#endif