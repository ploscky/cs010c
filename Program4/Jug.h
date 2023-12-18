#include <list>
#include <string>
#include <vector>

using namespace std;

struct Vertex {
    int A; //how much in jug A
    int B; //how much in jug B
    int id; //unique node id

    //adjacency list
    //each vertex can go one of six places for our six possible actions
    vector<int> newStateAfterAction; 

    Vertex(int A, int B, int id) : A(A), B(B), id(id), newStateAfterAction(6,-1) {}
};

class Jug {
    private:
        int Ca; //capacity A
        int Cb; //capacity B
        int N; //goal
        int cfA, cfB, ceA, ceB, cpAB, cpBA;

        vector<Vertex> graph;
        vector<int> costs;
        vector<string> actions;

    public:
        Jug(int, int, int, int, int, int, int, int, int);
        int solve(string&);

    private:
        //this looks up an A:B combination in the graph and returns its id (same as its index)
        int findInGraph(int A, int B, vector<int>& unfinishedVertices);
        
        // Helper for printGraph
        void showState(int);

        // Display the graph in readable form
        void printGraph();

        bool validInputs() const;

        void traverse(int, int) const;

        int getID(int, int) const;
};