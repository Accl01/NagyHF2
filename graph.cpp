#include "graph.h"


void Graph::addNode(Node* newnode){
    for(Node* n : nodes){
            if(n->getName() == newnode->getName() || n->getId() == newnode->getId()){   //Nodes cant have the same name or Id
                delete newnode;
                throw std::runtime_error("Név vagy Id egyezési hiba.");
            }
        }
    nodes.push_back(newnode);
}


void Graph::addEdge(Node* n1, Node* n2, std::string name, double len){
    //Nullptr cant be an edge
    if(n1 == nullptr || n2 == nullptr){
        throw std::runtime_error("Nullptr!");
    }
    //Cant have looped edge
    if(n1->getId() == n2->getId()){
        throw std::runtime_error("Ugyan az a ket el!");
    }
    
    //Cant have same name as other edge
    for(Edge* e : edges){
        if(e->getName() == name){
            throw std::runtime_error("Egyezik a név");
        }
    }
    //All the graph needs to be connected
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
    //Edges id-s start from 101, added automaticly
    int newedgeid;
    if(edges.empty()){
        newedgeid = 101;
    }else{
        newedgeid = edges.back()->getId() + 1;
    }
    //Adds new edge if all criteria met
    edges.push_back(new Edge(newedgeid, name, len, n1, n2));
}


//Lists all nodes in the graph, 
void Graph::listNodes() const{
    if(nodes.empty()){
        std::cout << "A gráf üres." << std::endl;
    }else{
        std::cout << "\n--- Elérhető csomópontok ---" << std::endl;
        for(Node* n : nodes){
            std::cout << *n << std::endl;
        }
    }

}

//Gets all edges connected to a node
std::vector<Edge*> Graph::getConnection(Node* node) const {
    std::vector<Edge*> ki;
    for(Edge* e : edges){
        if(e->getNode1() == node || e->getNode2() == node){
            ki.push_back(e);
        }
    }
    return ki;
}


//Helps with the dijkstra
Node* Graph::findNodebyname(const std::string& name) const{
    for(Node* n : nodes){
        if(n != nullptr && n->getName() == name){
            return n;
        }
    }
    return nullptr;
}


//Dijkstra algo
std::vector<Node*> Graph::findPath(Node* start, Node* end) const{
    if(start == nullptr || end == nullptr){
        throw std::runtime_error("Hiba: Érvénytelen pont.");
    }

    std::map<Node*, double> tavolsag;       //Stores shortest distance from start to each node
    std::map<Node*, Node*> elozo;           //Stores the previous node to reconstruct the path
    std::vector<Node*> unvisited = nodes;   //Stores unviseted nodes

    const double INF = 9999999999999.0;     //Infinite declared as a large double

    //Sets all distances INF except starting node
    for(Node* n : nodes){
        tavolsag[n] = INF;
        elozo[n] = nullptr;
    }
    tavolsag[start] = 0;

    while(!unvisited.empty()){
        //1. Find the node with the shortest path in the unvisited set
        int minIndex = 0;
        for(size_t i = 1; i < unvisited.size(); ++i){
            if(tavolsag[unvisited[i]] < tavolsag[unvisited[minIndex]]){
                minIndex = i;
            }
        }
        Node* u = unvisited[minIndex];

        //Stop if we reached the end or the other nodes are unreachable
        if(u == end || tavolsag[u] == INF) break;

        //2. Remove current node from unvisited
        unvisited.erase(unvisited.begin() + minIndex);

        //3. Update distance to neighbors
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
    //4. Path reconstruction: trace back form end to start using 'elozo' map
    std::vector<Node*> path;
    Node* x = end;
    while(x != nullptr){
        path.push_back(x);
        x = elozo[x];
    }
    
    //5. Reveres path to get Start to End order
    for(size_t i = 0; i < (path.size() / 2); ++i){  // path.size / 2 set is enough to swapp all
        Node* temp = path[i];
        path[i] = path[path.size() - 1 - i];        //Swapping with the mirrored index(path.size -1 -i)
        path[path.size() - 1 - i] = temp;   
    }

    return path;
}
