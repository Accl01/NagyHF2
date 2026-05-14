#include "planner.h"

//Plans route between to nodes given by their name
void Planner::routePlanner(const std::string& startName, const std::string& endName) const{
    Node* start = graph.findNodebyname(startName);
    Node* end = graph.findNodebyname(endName);

    std::vector<Node*> route;
    if(start != nullptr && end != nullptr){
        route = graph.findPath(start, end);
    }else{
        std::cout << "Az egyik pont nem található!!" << std::endl;
    }

    //After the dijkstra calculates the shortest path the function prints it out with printRoute
    printRoute(route);
}

//Prints the route form the routePlanner
void Planner::printRoute(std::vector<Node*> path) const{
    //If there is nod route between the two nodes
    if(path.empty()){
        std::cout << "Nincs kiírható útvonal" << std::endl;
        return;
    }
    //If there is only one node in the vector the start and end node are the same
    if(path.size() == 1){
        std::cout << "Már a célban vagy: " << path[0]->getName() << std::endl;
        return;
    }

    double length = 0;
    //Calculates the length of the path
    for(size_t i = 0; i < path.size() - 1; i++){
        Node* current = path[i];
        Node* after = path[i+1];

        std::vector<Edge*> connenctions = graph.getConnection(current);
        for(Edge* e : connenctions){
            if(e->getNode1() == after || e->getNode2() == after){
                length += e->getLen();
            }
        }
    }
    //Claculates the time to walk the length
    double time = timeofwalk(length);

    std::cout << "\nA leggyorsabb útvonal" << std::endl;
    std::cout << "Osszesen: " << length << "m, " << time << " perc" << std::endl;

    std::cout << " Az utvonal: " << std::endl;
    for(size_t i = 0; i < path.size(); ++i){
        std::cout << path[i]->getName() << std::endl;
    }
}

//Calculates the time to walk a distance
double Planner::timeofwalk(double len) const{
    double speed;
    switch(this->walkingSpeed){
        case 1:
            speed = 60; //Lassu
            break;

        case 2:
            speed = 80; //Kozepes
            break;

        case 3:
            speed = 100; //Gyors
            break;

        default:
            speed = 80;
            break;
    }
    return len / speed;
}

void Planner::listNodes() const{
    graph.listNodes();
}

//Adds node to the graph, calculates new Id for them.
void Planner::addNewNode(const std::string name){
    int newId = 1;
    if(!graph.getNodes().empty()){
        newId = graph.getNodes().back()->getId() + 1;
    }
    graph.addNode(new Node(newId, name));
}

//Adds new edge to the graph
void Planner::addNewEdge(const std::string name, int n1_id, int n2_id, double len){
    Node* node1 = nullptr;
    Node* node2 = nullptr;

    for(Node* n : graph.getNodes()){
        if(n->getId() == n1_id){node1 = n;}
        if(n->getId() == n2_id){node2 = n;}
    }
    if(node1 && node2){
        graph.addEdge(node1, node2, name, len);
    }else{
        throw std::runtime_error("Nemstimmel valamelyik Id!");
    }
}


//Reads the custom txt format and loads the planners graph with its nodes and edges
void Planner::loadData(std::string filename){
    std::vector<std::string> input = file.readTXT(filename);
    if(input.empty()) return;

    std::string mode = "";  //Tracking if we are reading nodes or edges

    for(std::string line: input){
        //Skip empty lines
        if(line.empty() || line[0] == '#'){
            continue;
        }
        //"Switch" mode base one 'mode'
        if(line.find("[Pontok]") != std::string::npos){
            mode = "P";
            std::cout << "Pontok beolvasása folyamatban." << std::endl;
            continue;
        }

        if(line.find("[Vonalak]") != std::string::npos){
            mode = "V";
            std::cout << "Vonalak beolvasása folyamatban." << std::endl;
            continue;
        }

        //Splits line by ';'
        std::stringstream ss(line);
        std::string i;                             //Input
        std::vector<std::string> iline;            //Input line

        while(std::getline(ss, i, ';')){
            iline.push_back(i);
        }

        try{
            //Processes Nodes
            if(mode == "P" && iline.size() >= 2){
                int id = std::stoi(iline[0]);
                graph.addNode(new Node(id, iline[1]));
            }
            //Processes Edges
            else if(mode == "V" && iline.size() >= 5){
                int n1_id = std::stoi(iline[2]);
                int n2_id = std::stoi(iline[3]);
                double len = std::stod(iline[4]);

                Node* startnode = nullptr;
                Node* endnode = nullptr;

                for(Node* n : graph.getNodes()){
                    if(n->getId() == n1_id){startnode = n;}
                    if(n->getId() == n2_id){endnode = n;}
                }
                if(startnode && endnode){
                    graph.addEdge(startnode, endnode, iline[1], len);
                }
            }
        }catch(const std::exception& e){
            std::cerr << "Hiba sorbeolvasásbál" << e.what() << iline[0] << mode <<  std::endl;
            continue;
        }
    }
}

//Saves graph to the txt
void Planner::saveData(std::string filename){
    std::vector<std::string> output;
    //Saveing the nodes
    output.push_back("[Pontok]");
    output.push_back("# ID;Név");

    for(Node* n : graph.getNodes()){
        std::stringstream ss;
        ss << n->getId() << ";" << n->getName();
        output.push_back(ss.str()); 
    }

    //Saving the edges
    output.push_back("[Vonalak]");
    output.push_back("# ID;Név;Honnan_ID;Hova_ID;Hossz(m)");

    for(Edge* e : graph.getEdges()){
        std::stringstream ss;
        ss << e->getId() << ";" << e->getName() << ";" << e->getNode1()->getId() << ";" << e->getNode2()->getId() << ";" << e->getLen();
        output.push_back(ss.str());
    }
    file.writeTXT(filename, output);
}