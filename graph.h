#ifndef GRAPH_H
#define GRAPH_H

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "memtrace.h"
#include "edge.h"
#include "node.h"

class Graph {
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

public:
    const std::vector<Node*>& getNodes() const{
        return nodes;
    }

    const std::vector<Edge*>& getEdges() const{
        return edges;
    }

    void addNode(Node* newnode);
    void addEdge(Node* n1, Node* n2, std::string name, double len);
    void listNodes() const;
    Node* findNodebyname(const std::string& name) const;

    std::vector<Edge*> getConnection(Node* node) const;

    std::vector<Node*> findPath(Node* start, Node* end) const;


    //destruktor, virtualisan foglalt edges es nodes hoz.
    virtual ~Graph(){
        for(Node* n : nodes){delete n; nodes.clear();} 
        for(Edge* e : edges){delete e; edges.clear();}
    }

};


#endif //GRAPH_H