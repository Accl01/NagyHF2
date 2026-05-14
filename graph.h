#ifndef GRAPH_H
#define GRAPH_H

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "memtrace.h"
#include "edge.h"
#include "node.h"

//Graph class
class Graph {
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;
public:
//Graph getters
    const std::vector<Node*>& getNodes() const{
        return nodes;
    }

    const std::vector<Edge*>& getEdges() const{
        return edges;
    }
//Graph adders
    void addNode(Node* newnode);
    void addEdge(Node* n1, Node* n2, std::string name, double len);

//Lists out all nodes
    void listNodes() const;

//Helps finding a node by its name. It is needed for the dijkstra
    Node* findNodebyname(const std::string& name) const;

//Gets all the edges connecting to a node
    std::vector<Edge*> getConnection(Node* node) const;

//Dijkstra pathfinding algorithm
    std::vector<Node*> findPath(Node* start, Node* end) const;


//Destruktor, for virtually reserved memory of nodes and edges
    virtual ~Graph(){
        for(Node* n : nodes){delete n; nodes.clear();} 
        for(Edge* e : edges){delete e; edges.clear();}
    }
};


#endif //GRAPH_H