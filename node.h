#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

#include "memtrace.h"

//Node class
class Node{
    int id;
    std::string name;
public:
//Node konstruktor
    Node(int id, std::string name): id(id), name(name){}

//Node getters
    int getId() const{
        return id;
    }
    std::string getName() const{
        return name;
    }

//Node operatoprs
    bool operator==(const Node& other) const{
        if(this->id == other.id || this->name == other.name){
            return true;
        }
        return false;
    }

    virtual ~Node() {}

    friend std::ostream& operator<<(std::ostream& os, const Node& n){
        return os << n.id << " ; " << n.name;
    }
};


#endif //NODE_H