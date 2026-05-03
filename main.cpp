#include "main.h"

//test main
int main(){
    Graph graph;

    Node* n1 = new Node(1, "Q_nyugatibejarat");
    Node* n2 = new Node(2, "I_nyugatibejarat");
    Node* n3 = new Node(3, "E_fobejarat");

    graph.addNode(n1);
    graph.addNode(n2);
    graph.addNode(n3);

    Edge* e1 = new Edge(1, "Q-I_utca", 200, n1, n2);
    Edge* e2 = new Edge(2, "Q-E_aluljaron", 420, n1, n3);

    graph.addEdge(n1, n2, "Q-I_utca", 200);
    graph.addEdge(n1, n3, "Q-E_aluljaro", 420);

    std::cout << "Node-ok:\n" << n1 << "\n" << n2 << "\n" << n3 << std::endl;
    std::cout << "\nEdge-ek:\n" << e1 << "\n" << e2 << std::endl;


}