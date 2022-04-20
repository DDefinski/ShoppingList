//
// Created by ADM on 19.11.2020.
//

#include <iostream>
#include "Lista.h"
//definicja funkcji red i green w zaleznosci od systemu operacyjnego
#ifdef _WIN32

#include <windows.h>

void red(const std::string &line) {//for windows
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    std::cout << line << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void green(const std::string &line) {//for windows
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    std::cout << line << std::endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

#else
void red(const std::string& line){//for linux
    std::cout << "\033[31m" << line << "\033[0m" <<std::endl;
}

void green(const std::string& line){//for linux
    std::cout << "\033[32m" << line << "\033[0m" <<std::endl;
}
#endif


Lista::Lista(const Lista &List) : Name(List.Name), Amount(List.Amount) {
    for (int i = 0; i < List.Amount; i++) {
        if (typeid(*List.list[i]) == typeid(Produkt_litr))
            list[i] = new Produkt_litr(dynamic_cast<Produkt_litr *>(List.getItem(i)));
        else if (typeid(*List.list[i]) == typeid(Produkt_kilo))
            list[i] = new Produkt_kilo(dynamic_cast<Produkt_kilo *>(List.getItem(i)));
        else
            list[i] = new Produkt_szt(dynamic_cast<Produkt_szt *>(List.getItem(i)));
    }
};

/* konstruktor kopiujący może być także napisany w taki sposób
Lista::Lista(Lista &List){
 *this = List
}
*/

Lista::~Lista() {
    for (int i = 0; i < Amount; i++)
        delete list[i];
}

bool Lista::addItem() {
    int choice;
    do {
        std::cout << "Wybierz jednostke dla produktu\n"
                     "1: Sztuki\n"
                     "2: Kilogramy\n"
                     "3: Litry\n"

                     "Wybierz akcje: " << std::endl;
        choice = readInt();
        if (choice < 1 || choice > 3)
            red("Niepoprawy wybor");

    } while (choice < 1 || choice > 3);

    std::cout << "Podaj nazwe produktu ktory chcesz dodac: " << std::endl;
    std::string name = readString();

    bool ifExist = false;

    for (int i = 0; i < Amount; i++) {
        if (list[i]->getName() == name) {
            if (choice == 1 && typeid(*list[i]) == typeid(Produkt_szt)) {
                ifExist = true;
                break;
            } else if (choice == 2 && typeid(*list[i]) == typeid(Produkt_kilo)) {
                ifExist = true;
                break;
            } else if (choice == 3 && typeid(*list[i]) == typeid(Produkt_litr)) {
                ifExist = true;
                break;
            }
        }
    }

    if (ifExist) {
        red("Produkt tego typu o takiej nazwie juz istnieje, nie mozna dodac nowego,\n"
            "mozesz go zmodyfikowac wyszukujac go na liscie.");
        return false;
    }

    switch (choice) {
        case 1: {
            std::cout << "Podaj ilosc tego produktu " << Produkt_szt::sUnit() << std::endl;
            int amount = readInt(true);
            list[Amount++] = new Produkt_szt(name, amount);
            break;
        }
        case 2: {
            std::cout << "Podaj ilosc tego produktu " << Produkt_kilo::sUnit() << std::endl;
            double amount = readDouble();
            list[Amount++] = new Produkt_kilo(name, amount);
            break;
        }
        case 3: {
            std::cout << "Podaj ilosc tego produktu " << Produkt_litr::sUnit() << std::endl;
            double amount = readDouble();
            list[Amount++] = new Produkt_litr(name, amount);
            break;
        }
    }

    return true;
}

void Lista::addItem(Produkt *item) {
    if (typeid(*item) == typeid(Produkt_litr))
        list[Amount++] = new Produkt_litr(dynamic_cast<Produkt_litr *>(item));
    else if (typeid(*item) == typeid(Produkt_kilo))
        list[Amount++] = new Produkt_kilo(dynamic_cast<Produkt_kilo *>(item));
    else
        list[Amount++] = new Produkt_szt(dynamic_cast<Produkt_szt *>(item));
}

void Lista::print() const {
    if (Amount) {
        std::cout << "Lista o nazwie: " << getName() << std::endl;
        for (int i = 0; i < Amount; i++) {
            std::cout << i << ". ";
            list[i]->print();
        }
    } else
        red("Lista jest pusta");
}

void Lista::deleteItem(int pos) {
    delete list[pos];
    list[pos] = nullptr;
    for (int i = pos + 1; i < Amount; i++) {//wchodzimy jesli podany indeks nie byl ostatni
        list[i - 1] = list[i];//przesuwamy dalsze wskazniki na poprzednie indeksy
        if (i == Amount - 1)//wchodzimy jesli dojdziemy do ostatniego zajetego miejsca
            list[i] = nullptr;//ustawiamy ostatni zajety wskaznik na nullptr
    }
    Amount--;
}

void Lista::clearList() {
    for (int i = 0; i < Amount; i++) {
        delete list[i];
        list[i] = nullptr;
    }
    Amount = 0;
}

void Lista::editItem(int pos) {
    int choice;
    do {
        std::cout << "Co chcesz zmienic\n"
                     "1. Nazwa\n"
                     "2. Ilosc\n"
                     "3. Caly produkt\n"
                     "Wybierz akcje: " << std::endl;
        choice = readInt();
        if (choice < 1 || choice > 3)
            red("Niepoprawy wybor");

    } while (choice < 1 || choice > 3);

    if (choice == 1 || choice == 3) {
        std::cout << "Podaj nowa nazwe produktu: " << std::endl;
        std::string nName = readString();
        list[pos]->setName(nName);
        green("Pomyslnie zmieniono nazwe");
    }

    if (choice == 2 || choice == 3) {
        std::cout << "Podaj nowa ilosc produktu " << list[pos]->unit() << std::endl;
        double nAmount;
        nAmount = (typeid(*list[pos]) == typeid(Produkt_szt)) ? readInt(true) : readDouble();
        list[pos]->setAmount(nAmount);
        green("Pomyslnie zmieniono ilosc");
    }
}

Lista &Lista::operator=(Lista const &list1) {
    if (this != &list1) {
        if (Amount)
            clearList();
        for (int i = 0; i < list1.Amount; i++) {
            if (typeid(*list1.list[i]) == typeid(Produkt_litr))
                list[i] = new Produkt_litr(dynamic_cast<Produkt_litr *>(list1.list[i]));
            else if (typeid(*list1.list[i]) == typeid(Produkt_kilo))
                list[i] = new Produkt_kilo(dynamic_cast<Produkt_kilo *>(list1.list[i]));
            else
                list[i] = new Produkt_szt(dynamic_cast<Produkt_szt *>(list1.list[i]));
        }
        Name = list1.Name;
        Amount = list1.Amount;
    }
    return *this;
}


int readInt(bool ifAmount) {
    std::string line;
    bool isIncorrect;
    do {
        isIncorrect = true;
        std::getline(std::cin, line);
        if (line.empty()) {
            red("Nalezy wprowadzic jakas wartosc");
            std::cout << "Sprobuj ponownie" << std::endl;
            continue;
        }

        if (ifAmount && *line.begin() == '0') {
            red("Ilosc nie moze byc rowna 0 ani od niego sie zaczynac");
            std::cout << "Sprobuj ponownie" << std::endl;
            continue;
        }

        for (std::string::iterator it = line.begin(); it != line.end(); it++) {
            if (!isdigit(*it)) {
                red("Niepoprawny wybor");
                red("Poprawny format powinien zawierac jedynie cyfry z przedzialu 0-9");
                std::cout << "Sprobuj ponownie" << std::endl;
                break;
            }
            if (line.end() - 1 == it)//jesli doszlismy do konca lini bez zadnego bledu to mozemy wyjsc w petli while
                isIncorrect = false;
        }
    } while (isIncorrect);

    return atoi(line.c_str());
}

double readDouble() {
    std::string line;
    bool isIncorrect;
    bool wasDotAlready;
    bool isGreaterThanZero;
    do {
        isIncorrect = true;
        wasDotAlready = false;
        isGreaterThanZero = false;
        std::getline(std::cin, line);

        if (line.empty()) {
            red("Nalezy wprowadzic jakas wartosc");
            std::cout << "Sprobuj ponownie" << std::endl;
            continue;
        }

        if (!isdigit(*line.begin())) {
            red("Niepoprawny wybor");
            red("Wpisywana fraza powinna zaczynac sie cyfra");
            std::cout << "Sprobuj ponownie" << std::endl;
            continue;
        }


        for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
            if (!isdigit(*it)) {
                if (*it == '.') {
                    if (wasDotAlready || it == line.end() - 1) {//jesli juz raz wystapila kropka / kropka jest ostatnia
                        red("Niepoprawny wybor");
                        red("Poprawny format to liczba albo liczba zmiennoprzecinkowa oddzielona kropka");
                        std::cout << "Sprobuj ponownie" << std::endl;
                        break;
                    }
                    wasDotAlready = true;//kropka wystapila
                    continue;

                } else {//znak inny od liczby i od kropki
                    red("Niepoprawny wybor");
                    red("Poprawny format to liczba albo liczba zmiennoprzecinkowa oddzielona kropka");
                    std::cout << "Sprobuj ponownie" << std::endl;
                    break;
                }
            }
            if (*it != '0')//jesli kazda cyfra bedzie 0 to program nie pozwoli wpisac takiej ilosci
                isGreaterThanZero = true;
            if (it == line.end() - 1)
                isIncorrect = false;
        }

        if (!isGreaterThanZero && !isIncorrect) {
            red("Niepoprawny wybor");
            red("Ilosc produktu musi byc rozna od zera");
            std::cout << "Sprobuj ponownie" << std::endl;
        }


    } while (isIncorrect || !isGreaterThanZero);


    return atof(line.c_str());
}

std::string readString() {
    std::string line;
    bool isIncorrent = true;
    do {
        std::getline(std::cin, line);
        if (line.empty()) {
            red("Nalezy wprowadzic jakas wartosc");
            std::cout << "Sprobuj ponownie" << std::endl;
            continue;
        }
        isIncorrent = false;

    } while (isIncorrent);

    return line;
}









