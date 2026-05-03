#include "main.h"

//test main for skeleton
int main(){
    Graph graph;

    
    //Nodeok létrehozása
    Node* n1 = new Node(1, "Q_nyugatibejarat");
    Node* n2 = new Node(2, "I_nyugatibejarat");
    Node* n3 = new Node(3, "E_fobejarat");
    std::cout << "Node-ok letrehozva" << std::endl;

    //Nodeok hozzáadása a gráfomhoz
    graph.addNode(n1);
    graph.addNode(n2);
    graph.addNode(n3);
    std::cout <<"Node-ok hozzaadva a grafomhoz" << std::endl;

    //Élek létrehozása a konstruktorral.
    Edge* e1 = new Edge(1, "Q-I_utca", 200, n1, n2);
    Edge* e2 = new Edge(2, "Q-E_aluljaron", 420, n1, n3);
    std::cout << "Elek kulon letrehozva" << std::endl;

    //Élek hozzáadása a gráfopmhopz.
    graph.addEdge(n1, n2, "Q-I_utca", 200);
    graph.addEdge(n1, n3, "Q-E_aluljaro", 420);
    std::cout << "Elek a grafhoz adasa" << std::endl;

    graph.findPath(n1, n2);


    Planner planner;
    std::string node1 = n1->getName();
    std::string node2 = n2->getName();

    //planner.loadData("test.txt");
    //planner.routePlanner(node1, node2);
    //planner.saveData("test.txt");
    //Planner majd így fog működni.    
    
    std::cout << "Planner tesztjei" << std::endl;

    //Sima Pontok és Élek kiírása az operátorukkal.
    std::cout << "\nNode-ok:\n" << *n1 << "\n" << *n2 << "\n" << *n3 << std::endl;
    std::cout << "\nEdge-ek:\n" << *e1 << "\n" << *e2 << std::endl;



    //Gráf pontjainak kilistázásának a testje
    graph.listNodes();



    
    delete e1;
    delete e2;

    return 0;
}