#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <string>
#include "node.h"

class Edge{
    int id;
    std::string name;
    double len;
    Node* node1;
    Node* node2;
public:
//konstruktor
    Edge(int id, std::string name, double len, Node* node1, Node* node2)
    : id(id), name(name), len(len), node1(node1), node2(node2){
        if(node1 == node2){
            throw std::runtime_error("Azonos pontokból lett létrehozva él.");
        }
        if(len <= 0){
            throw std::runtime_error("Negatív élhossz nem lehet");
        }
    }
    
//getters
    int getId() const{
        return id;
    }
    std::string getName() const{
        return name;
    }

    double getLen() const{
        return len;
    }

    Node* getNode1() const{
        return node1;
    }

    Node* getNode2() const{
        return node2;
    }

//operators
    friend std::ostream& operator<<(std::ostream& os, const Edge& e){
        return os << e.name << ", (" << e.len << "m)";
    }


};

#endif //EDGE_H