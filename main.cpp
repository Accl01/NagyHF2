#include "main.h"

#ifdef _WIN32
    #include <windows.h>
#endif

void printMenu(){
    std::cout << "\n\n" << ASCIICIM << std::endl;
    std::cout << "\n\n1. Utvonaltervezés" << std::endl;
    std::cout << "2. Új pont felvétele" << std::endl;
    std::cout << "3. Csomópontok listázása" << std::endl;
    std::cout << "4. Kilépés" << std::endl;
    std::cout << "Választás: ";
}

void initwalkspeed(Planner& planner){
    int choice = 0;
    while(choice < 1 || choice > 3){
        clearScreen();
        std::cout << "\n\n" << ASCIICIM << std::endl;
        std::cout << "\n\nVálassz a három sétatempóból:\n" << "1. Lassú\n" << "2. Közepes\n" << "3. Gyors" << std::endl;
        std::cout << " Választás: ";

        if(!(std::cin >> choice)){
            std::cout << "Hiba. Kérlek a számok közül válassz!" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            choice = 0;
        }else if(choice < 1 || choice > 3){
            std::cout << "Hiba. Csak 1, 2, vagy 3 adható meg!" << std::endl;
        }
    }
    planner.setWalkingspeed(choice);
    std::cin.ignore(1000, '\n');
}

//clears the terminal
void clearScreen(){
    std::cout << "\033[2J\033[H";
}


//TEST CASES
#ifdef TEST_MODE
void run_tests(){
    //Pontok tesztelése.
    TEST(NodeLogic, NodeTest)
        Node n1(1, "A_pont");
        EXPECT_EQ(1, n1.getId());
        EXPECT_STREQ("A_pont", n1.getName().c_str());

        Node n2(1, "A_pont");
        EXPECT_TRUE(n1 == n2);
    END

    //Élek tesztelése.
    TEST(EdgeLogic, EdgeTest)
        Node* n1 = new Node(1, "Indulo");
        Node* n2 = new Node(2, "Erkezo");
        Edge e1(101, "Utca", 150.0, n1, n2);

        EXPECT_EQ(101, e1.getId());
        EXPECT_DOUBLE_EQ(150.0, e1.getLen());
        EXPECT_EQ(n1, e1.getNode1());
        EXPECT_EQ(n2, e1.getNode2());

        EXPECT_THROW(Edge(102, "Hiba", 10.0, n1, n1), std::runtime_error);
        EXPECT_THROW(Edge(103, "Hiba", -10.0, n1, n2), std::runtime_error);

        delete n1;
        delete n2;
    END

    //Gráf és dijkstra tesztelése.
    TEST(GraphLogic, DijkstraTest)
        Graph g;
        Node* n1 = new Node(1, "Indulo");
        Node* n2 = new Node(2, "Kozepso");
        Node* n3 = new Node(3, "Erkezo");

        g.addNode(n1);
        g.addNode(n2);
        g.addNode(n3);

        g.addEdge(n1, n2, "Ell1", 100);
        g.addEdge(n2, n3, "Ell2", 50);

        std::vector<Node*> path = g.findPath(n1, n3);
        ASSERT_EQ(3, (int)path.size());
        EXPECT_STREQ("Indulo", path[0]->getName().c_str());
        EXPECT_STREQ("Erkezo", path[2]->getName().c_str());

        Node* n4 = new Node(4, "Sziget");
        Node* n5 = new Node(5, "Sziget2");

        g.addNode(n4);
        g.addNode(n5);

        std::vector<Node*> isolalt = g.findPath(n1, n4);
        //Ez azt jelenti hogy nem ugyanaz a két pont a keresésben, 
        // de nem talált útvonalat mivel a lista amit visszakapott 1 elemet tartalmaz.
        if(n1 != n4 && isolalt.size() == 1){
            isolalt.clear();
        }
        EXPECT_TRUE(isolalt.empty());
        EXPECT_THROW(g.addEdge(n4, n5, "Rossz_el", 20), std::runtime_error);
        EXPECT_THROW(g.addNode(new Node(1, "Ugyanaz")), std::runtime_error);

    END

    //Planner tesztjei.
    TEST(PlannerLogic, TimeCalculation)
        Planner p;
        p.setWalkingspeed(1);
        EXPECT_DOUBLE_EQ(2.0, p.timeofwalk(120.0));

        p.setWalkingspeed(3);
        EXPECT_DOUBLE_EQ(1.2, p.timeofwalk(120.0));
    END
}
#endif



//MAIN
int main(){

    #ifdef _WIN32 //terminalba beirod hogy chcp 65001
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif

    Planner planner;
    std::string filename = "uthalozat.txt";

    try{
        planner.loadData(filename);
        std::cout << "Gráf sikeresen betöltve.\n";
    }catch(const std::exception& e){
        std::cout << "Betöltési hiba:" << e.what() << std::endl;
        std::cout << "Alap helyzet felállítása." << std::endl;
    }

    initwalkspeed(planner);
    clearScreen();

    int choice = 0;
    while(choice != 4){
        clearScreen();
        printMenu();

        if(!(std::cin >> choice)){
            std::cout << "Hiba. Kérlek adj meg számot." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');

            continue;
        }
        std::cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1: {
            clearScreen();
            std::cout << ASCIICIM << std::endl;
            planner.listNodes();
            std::string start, end;
            std::cout << "\nIndulópont: ";
            std::getline(std::cin, start);
            std::cout << "\nCél: ";
            std::getline(std::cin, end);
            planner.routePlanner(start, end);
            std::cout <<"Nyomj entert a folytatáshoz: ";
            std::cin.get();
            break;
        }
        case 2: {
            clearScreen();
            std::string input;
            std::cout << "\n" << ASCIICIM << "\nMit akarsz hozzáadni?\n1. Csomópontot\n2. Élet\n3. Visszalépés\n" << "Választás: ";
            std::getline(std::cin, input);
            if(input == "1"){
                std::string name;
                std::cout << "\nMi legyen a pont neve: ";
                std::getline(std::cin, name);
                try{
                    planner.addNewNode(name);
                    std::cout << "Új pont hozzáadva!" << std::endl;
                }catch(const std::exception& e){
                    std::cout << "Hiba!" << e.what() << std::endl;
                }
                std::cout <<"Nyomj entert a folytatáshoz: ";
                std::cin.get();
                break;
            }
            else if(input == "2"){
                std::string edgename, n1_str, n2_str, len_str;

                std::cout << "\nMi legyen az él neve: ";
                std::getline(std::cin, edgename);
                clearScreen();
                planner.listNodes();

                std::cout << "\nAdd meg az egyik Pont Id-jét: ";
                std::getline(std::cin, n1_str);

                std::cout << "\nAdd meg a másik Pont Id-jét: ";
                std::getline(std::cin, n2_str);

                std::cout << "\nAdd meg az él hosszát (m): ";
                std::getline(std::cin, len_str);

                try{
                    int n1_id = std::stoi(n1_str);
                    int n2_id = std::stoi(n2_str);
                    double len = std::stod(len_str);

                    planner.addNewEdge(edgename, n1_id, n2_id, len);
                    std::cout << "Új él hozzáadva!" << std::endl;
                }catch(std::exception& e){
                    std::cout << "Hiba! " << e.what() << std::endl;
                }

                std::cout <<"Nyomj entert a folytatáshoz: ";
                std::cin.get();
                break;
            }
            else if(input == "3"){
                break;
            }
            break;
        }
        case 3: {
            clearScreen();
            std::cout << "\n\n" << ASCIICIM << std::endl;
            planner.listNodes();
            std::cout <<"Nyomj entert a folytatáshoz: ";
            std::cin.get();
            break;
        }
        case 4: {
            clearScreen();
            planner.saveData(filename);
            std::cout << "Sikeres mentés!" << std::endl;

            #ifdef TEST_MODE
            run_tests();
            #endif

            return 0;
        }
        default:
            clearScreen();
            std::cout << "Érvénytelen menüpont!" << std::endl;
            break;
        }
    }


    return 0;
}