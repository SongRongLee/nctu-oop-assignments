//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2016/02/27
//

#ifndef __MY_GRAPH_BASICS_H_
#define __MY_GRAPH_BASICS_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
using std::vector;

class GRAPH_NODE {
public:
    GRAPH_NODE( ) {
        r = 1.0;
        p = vector3(0.0, 0.0, 0.0);
    }
	GRAPH_NODE(float x,float y,float z,float r, int id) {
		this->r = r;
		this->p = vector3(x, y, z);
		this->id = id;
	}
    vector3 p;  //position
    double r;   //radius   
    int id;     // note: ID (identifier) may not be the sams as index.
    //
    // Add your own data members here
    //
};
class GRAPH_EDGE {
public:	
    int nodeID[2];  // nodeID[0]: the first node
                    // nodeID[1]: the second node
    int id;         // note: ID (identifier) may not be the sams as index.
	GRAPH_EDGE(int node0,int node1,int id){
		nodeID[0] = node0;
		nodeID[1] = node1;
		this->id = id;
	}
    //
    // Add your own data members here
    //
};
#endif