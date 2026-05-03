#ifndef GRAPH_H
#define GRAPH_H

#include <istream>
#include <string>
#include <vector>
#include <map>

#include "edge.h"
#include "node.h"

class Graph {
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

public:
    const std::vector<Node*>& getNodes() const{
        return nodes;
    }

    void addNode(Node* newnode);
    void addEdge(Node* n1, Node* n2, std::string name, double len);
    void listNodes();
    Node* findNodebyname(const std::string& name) const;

    std::vector<Edge*> getConnection(Node* node);

    std::vector<Node*> findPath(Node* start, Node* end);


    //destruktor, virtualisan foglalt edges es nodes hoz.
    virtual ~Graph(){
        for(Node* n : nodes){delete n;} 
        for(Edge* e : edges){delete e;}
    }

};


#endif //GRAPH_H