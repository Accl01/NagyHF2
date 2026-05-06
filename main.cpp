#include "main.h"

void printMenu(){
    std::cout << ASCIILOGO << std::endl;
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
        std::cout << ASCIILOGO << std::endl;
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
            std::string start, end;
            std::cout << "Indulópont: ";
            std::getline(std::cin, start);
            std::cout << "Cél: ";
            std::getline(std::cin, end);
            planner.routePlanner(start, end);
            std::cout <<"Nyomj entert a folytatáshoz: ";
            std::cin.get();
            break;
        }
        case 2: {
            clearScreen();
            std::cout << ASCIILOGO << std::endl;
            std::cout << "\n\n" << ASCIICIM << std::endl;
            planner.listNodes();
            std::cout <<"Nyomj entert a folytatáshoz: ";
            std::cin.get();
            break;
        }
        case 3: {
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