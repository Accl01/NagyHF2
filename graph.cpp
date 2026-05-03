#include "graph.h"

void Graph::addNode(Node* newnode){
    for(Node* n : nodes){
            if(n->getName() == newnode->getName() || n->getId() == newnode->getId()){
                delete newnode;
                throw std::runtime_error("Név vagy Id egyezési hiba."); // Plannerben elkapom
            }
        }
    nodes.push_back(newnode);
}

void Graph::addEdge(Node* n1, Node* n2, std::string name, double len){
    for(Edge* e : edges){
        if(e->getName() == name){
            throw std::runtime_error("Egyezik a név");
        }
        //Az egész gráf össszeköttetve legyen
        if(!edges.empty()){
            bool connect = false;
            for(Edge* e : edges){
                if(e->getNode1() == n1 || e->getNode2() == n1 ||
                    e->getNode1() == n2 || e->getNode2() == n2){
                        connect = true;
                        break;
                    }
            }
            if(!connect){
                throw std::runtime_error("Nincs kapcsolat.");
            }
        }
        
        int newedgeid;
        if(edges.empty()){
            newedgeid = 101;
        }else{
            newedgeid = edges.back()->getId() + 1;
        }
        edges.push_back(new Edge(newedgeid, name, len, n1, n2));
    }
}


void Graph::listNodes(){
    if(nodes.empty()){
        std::cout << "A gráf üres." << std::endl;
    }else{
        std::cout << "\n--- Elérhető csomópontok ---" << std::endl;
        for(Node* n : nodes){
            std::cout << *n << std::endl;
        }
    }

}

std::vector<Edge*> Graph::getConnection(Node* node){
    std::vector<Edge*> ki;
    for(Edge* e : edges){
        if(e->getNode1() == node || e->getNode2() == node){
            ki.push_back(e);
        }
    }
    return ki;
}

//Dijkstra!

std::vector<Node*> Graph::findPath(Node* start, Node* end){
    if(start == nullptr || end == nullptr){
        throw std::runtime_error("Hiba: Érvénytelen pont.");
    }

    std::map<Node*, double> tavolsag;
    std::map<Node*, Node*> elozo;
    std::vector<Node*> unvisited = nodes;

    const double INF = 9999999999999.0;

    for(Node* n : nodes){
        tavolsag[n] = INF;
        elozo[n] = nullptr;
    }
    tavolsag[start] = 0;

    while(!unvisited.empty()){

    }
}
