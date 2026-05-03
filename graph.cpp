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
    if(n1 == nullptr || n2 == nullptr){
        throw std::runtime_error("Nullptr!");
    }
    if(n1 == n2){
        throw std::runtime_error("Ugyan az a ket el!");
    }
    
    for(Edge* e : edges){
        if(e->getName() == name){
            throw std::runtime_error("Egyezik a név");
        }
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


std::vector<Edge*> Graph::getConnection(Node* node) const {
    std::vector<Edge*> ki;
    for(Edge* e : edges){
        if(e->getNode1() == node || e->getNode2() == node){
            ki.push_back(e);
        }
    }
    return ki;
}



Node* Graph::findNodebyname(const std::string& name) const{
    for(Node* n : nodes){
        if(n != nullptr && n->getName() == name){
            return n;
        }
    }
    return nullptr;
}


//Dijkstra!

std::vector<Node*> Graph::findPath(Node* start, Node* end) const{
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
        int minIndex = 0;
        for(size_t i = 1; i < unvisited.size(); ++i){
            if(tavolsag[unvisited[i]] < tavolsag[unvisited[minIndex]]){
                minIndex = i;
            }
        }

        Node* u = unvisited[minIndex];
        if(u == end || tavolsag[u] == INF) break;

        unvisited.erase(unvisited.begin() + minIndex);
        for(Edge* e : getConnection(u)){
            Node* v = nullptr;
            if(e->getNode1() == u){
                v = e->getNode2();
            }else{
                v = e->getNode1();
            }

            double alternative = tavolsag[u] + e->getLen();

            if(alternative < tavolsag[v]){
                tavolsag[v] = alternative;
                elozo[v] = u;
            }
        }
    }

    std::vector<Node*> path;
    Node* x = end;
    while(x != nullptr){
        path.push_back(x);
        x = elozo[x];
    }

    for(size_t i = 0; i < (path.size() / 2); ++i){
        Node* temp = path[i];
        path[i] = path[path.size() - 1 - i];
        path[path.size() - 1 - i] = temp;
    }

    return path;
}
