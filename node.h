#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>

class Node{
    int id;
    std::string name;
public:
//konstruktor
    Node(int id, std::string name): id(id), name(name){}

//getters
    int getId() const{
        return id;
    }
    std::string getName() const{
        return name;
    }

//operatoprs

    bool operator==(const Node& other) const{
        if(this->id == other.id || this->name == other.name){
            return true;
        }
        return false;
    }




    friend std::ostream& operator<<(std::ostream& os, const Node& n){
        return os << n.id << " ; " << n.name;
    }
};


#endif //NODE_H