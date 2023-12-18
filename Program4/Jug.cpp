#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <string>
#include "Jug.h"

using namespace std;

Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) 
    : Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA),
      costs{cfA, cfB, ceA, ceB, cpAB, cpBA}, 
      actions{"fill A", "fill B", "empty A", "empty B", "pour A B", "pour B A"}
    {   
        if (!validInputs()) {
            return;
        }
            //stack that keeps track of which nodes are not part of the graph
            vector<int> unfinishedNodes;

            //starts by adding the empty jug-- will make a note of it in the unfinishedNodes stack
            findInGraph(0, 0, unfinishedNodes);

            //for each unfinished vertex, we have to add connections that correspond
            //to the new state after doing one of the six actions (so six outedges).
            while(unfinishedNodes.size() > 0) {
            //get an unfinished node
            int id = unfinishedNodes.back();
            unfinishedNodes.pop_back();
        
            //this state has a current A and B value
            int A = graph[id].A;
            int B = graph[id].B;
            //cout << "Fix vertex " << id << " (" << A << ',' << B << ")" << endl;
            // State after we fill up the A jug
            int fillA = findInGraph(Ca, B, unfinishedNodes);

            // After filling the B jug
            int fillB = findInGraph(A, Cb, unfinishedNodes);

            // After emptying the A jug
            int emptyA = findInGraph(0, B, unfinishedNodes);

            // After emptying the B jug
            int emptyB = findInGraph(A, 0, unfinishedNodes);

            // After pouring A into B
            int roomInB = Cb - B;
            int AtoBpoursize = min(A, roomInB);
            int pourAToB = findInGraph(A-AtoBpoursize, B+AtoBpoursize, unfinishedNodes);

            // After pouring B into A
            int roomInA = Ca - A;
            int BtoApoursize = min(B, roomInA);
            int pourBToA = findInGraph(A+BtoApoursize, B-BtoApoursize, unfinishedNodes);

            // Now we can set the six outedges for this vertex
            graph[id].newStateAfterAction[0] = fillA;
            graph[id].newStateAfterAction[1] = fillB;
            graph[id].newStateAfterAction[2] = emptyA;
            graph[id].newStateAfterAction[3] = emptyB;
            graph[id].newStateAfterAction[4] = pourAToB;
            graph[id].newStateAfterAction[5] = pourBToA;
            
            }   
        //}
    //printGraph();
    //cout << endl;
  }

// This looks up an A:B combination in the graph and returns its id (same as its index)
int Jug::findInGraph(int A, int B, vector<int>& unfinishedVertices) {
    // We may already have this combination of A and B.  If so, return it
    for(unsigned int i = 0; i < graph.size(); ++i) {
        if (graph[i].A == A and graph[i].B == B) {
            return i;
        }
    }

    // We did not have it, so create a new vertex with this combination
    // Also add the index to the list of unfinished nodes so we remember
    // to set its six outedges
    int id = graph.size();
    unfinishedVertices.push_back(id);
    //cout << "Add: " << A << "," << B << " at index " << id << endl;
    graph.push_back(Vertex(A, B, id));
    return id;
}

// Helper for printGraph
void Jug::showState(int i) {
    cout << '\t' << i;
    if (i != -1) {
        cout << '(' << graph[i].A << ',' << graph[i].B << ')';
    }
}

// Display the graph in readable form
void Jug::printGraph() {
    cout << "ID\t(A,B)\tfillA\tfillB\temptyA\temptyB\tpourAB\tpourBA" << endl;
    for(const auto& v: graph) {
        cout << v.id << "\t(" << v.A << ',' << v.B << ")";
        showState(v.newStateAfterAction[0]);
        showState(v.newStateAfterAction[1]);
        showState(v.newStateAfterAction[2]);
        showState(v.newStateAfterAction[3]);
        showState(v.newStateAfterAction[4]);
        showState(v.newStateAfterAction[5]);
        cout << endl;
    }
}

bool Jug::validInputs() const {
    return (N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0)
    && (Ca > 0 && Ca <= Cb) 
    && (N <= Cb && Cb <= 1000);
    
}


int Jug::solve(string& solution) {
    if (!validInputs()) {
        solution = "";
        return -1;
    }

    vector<int> predV(graph.size(), 0); //stores the previous vertex of the index
    vector<string> predVAction(graph.size(), "");
    vector<int> unvisitedQueue; //store vertices that haven't been visited yet (will pop once reached)
    //filling queue 
    for (unsigned int i = 0; i < graph.size(); ++i) {
        unvisitedQueue.push_back(graph.at(i).id);
    }
    vector<bool> isVertexVisited(graph.size(), false);

    vector<int> distance(graph.size(), INT_MAX); //vector storing the distances (costs); initialized w/ INT_MAX as inf
    const int idnum = 0;
    distance.at(idnum) = 0; //starting vertex has distance of 0

    //jug A empty, B has N gallons
    int solutionID = getID(0, N);
    bool foundSolution = false;

    //keep popping from queue until it's empty
    for (unsigned int j = 0; j < graph.size(); ++j) {
        int min = INT_MAX;
        int minID = 0;
        for (unsigned int i = 0; i < graph.size(); ++i) {
            if (!isVertexVisited.at(i)) {
                if (distance.at(i) < min) {
                    min = distance.at(i);
                    minID = i;
                }
            }
        }
        isVertexVisited.at(minID) = true;
        int currentVertexID = minID;

        Vertex& currentVertex = graph.at(currentVertexID); //currentVertex holds the adjacent vertices (possible actions)
        for (unsigned int i = 0; i < 6; ++i) {
            int cost = costs.at(i);
            //childID holds index of current state's child after the action
            int childID = currentVertex.newStateAfterAction.at(i); 
            if (childID == currentVertexID) {
                continue;
            }
            if (childID == solutionID) {
                foundSolution = true;
            }

            int alternativePathDistance = distance.at(currentVertexID) + cost; //calculate alternative path

            //find shortest path and store it in distance and predV so it can be retraced and printed out
            if (alternativePathDistance <= distance.at(childID)) {
                distance.at(childID) = alternativePathDistance;
                predV.at(childID) = currentVertexID; //update the cost
                predVAction.at(childID) = actions.at(i); //also store the action strings
            }
        }
    }

    int startID = graph.at(0).id;
    if (!foundSolution) {
        solution = "";
        return 0;
    }
    else {
        int currentID = solutionID;
        string actionString = "";
        while (currentID != startID) {
            string& action = predVAction.at(currentID);
            currentID = predV.at(currentID);
            actionString = action + "\n" + actionString;
        }
        solution = actionString + "success " + to_string(distance.at(solutionID));
        return 1;
    }
    
}


int Jug::getID(int capA, int capB) const {
    for(unsigned int i = 0; i < graph.size(); ++i) {
        if (graph[i].A == capA and graph[i].B == capB) {
            return i;
        }
    }
    return -1;
    
}

