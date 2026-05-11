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

void clearScreen(){
    std::cout << "\033[2J\033[H";
}

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
            break;
        }
        default:
            clearScreen();
            std::cout << "Érvénytelen menüpont!" << std::endl;
            break;
        }
    }


    return 0;
}