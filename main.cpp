#include <iostream>
#include <fstream>
#include "Produkt.h"
#include "Lista.h"
#include "Tcontainer.h"

void addList(Tcontainer<Lista *> &List);//dodaje nowy wskaznik na liste do wektora

void deleteList(Tcontainer<Lista *> &List);//usuwa obiekt i wskaznik na niego z wektora

void clearList(Tcontainer<Lista *> &List);//usuwa wszystkie produkty wskazywane przez liste i czysci tablice wskaznikow

void copyList(Tcontainer<Lista *> &List);//nadpisuje istniejaca liste kopia innej

void copyNewList(Tcontainer<Lista *> &List);//dodaje kopie istniejacej listy na koniec wektora

void printList(Tcontainer<Lista *> &List);//drukuje wybrana liste

int chooseList(Tcontainer<Lista *> &List);//zwraca indeks wybranej przez uzytkownika listy

void addItem(Tcontainer<Lista *> &List);//dodaje produkt do listy

int copyItem(Tcontainer<Lista *> &List, int *from);//dodaje kopie istniejacego produktu do wybranej listy

void moveItem(Tcontainer<Lista *> &List, int *from);//przenosi produkt na inną liste

void removeItem(Tcontainer<Lista *> &List);//usuwa wybrany produkt z listy

void editItem(Tcontainer<Lista *> &List);//modyfikuje nazwe i/lub ilosc produktu

void connectLists(Tcontainer<Lista *> &List);//scala listy

struct no_list_existing {
};
struct not_enough_lists {
};
struct the_same_lists {
};


int main(int argc, char *argv[]) {

    Tcontainer<Lista *> listy;
    int moveVar = 0;//zmienna potrzebna do funkcji moveitem

    std::ifstream in;
    std::streambuf *defaultCin = std::cin.rdbuf();//zapamietanie podstawowego bufora

    if (argc > 1) {//przekerowanie bufora na plik
        in.open(argv[1]);
        std::cin.rdbuf(in.rdbuf());
    }

    int choice = 0;
    do {
        if (choice != 10101010)
            std::cout << "\n---====== MENU =====---\n"
                         "1: Stworz nowa pusta liste\n"
                         "2: Dodaj nowy produkt na liste\n"
                         "3: Stworz nowa liste bedaca kopia juz istniejacej\n"
                         "4: Skopiuj produkt\n"
                         "5: Zastap jedna liste kopia drugiej\n"
                         "6: Przenies produkt miedzy listami\n"
                         "7: Zedytuj produkt\n"
                         "8: Usun produkt\n"
                         "9: Usun liste\n"
                         "10: Wyczysc liste\n"
                         "11: Scal 2 listy\n"
                         "12: Pokaz liste\n"
                         "\n0: Zakoncz dzialanie programu\n\n"

                         "Wybierz akcje: " << std::endl;
        choice = readInt();
        try {
            switch (choice) {
                case 0:
                    break;
                case 1:
                    addList(listy);
                    break;
                case 2:
                    addItem(listy);
                    break;
                case 3:
                    copyNewList(listy);
                    break;
                case 4:
                    copyItem(listy, &moveVar);
                    break;
                case 5:
                    copyList(listy);
                    break;
                case 6:
                    moveItem(listy, &moveVar);
                    break;
                case 7:
                    editItem(listy);
                    break;
                case 8:
                    removeItem(listy);
                    break;
                case 9:
                    deleteList(listy);
                    break;
                case 10:
                    clearList(listy);
                    break;
                case 11:
                    connectLists(listy);
                    break;
                case 12:
                    printList(listy);
                    break;
                case 10101010:
                    std::cin.rdbuf(defaultCin);//powrot do domyslnego bufora
                    break;
                default:
                    red("Niepoprawny wybor");
                    std::cout << "Sprobuj ponownie" << std::endl;
            }
        }
        catch (no_list_existing) {
            red("Najpierw stworz liste");
        }
        catch (not_enough_lists) {
            red("Musza istniec przynajmniej 2 listy");
        }
        catch (the_same_lists) {
            red("Nalezy wybrac 2 rozne listy");
        }

    } while (choice != 0);

    return 0;
}

void addList(Tcontainer<Lista *> &List) {
    std::cout << "Podaj nazwe listy: " << std::endl;
    std::string name = readString();
    Lista *temp = new Lista(name);
    List.pushback(temp);
    green("Pomyslnie utworzono liste ");
}

void deleteList(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        std::cout << "Wybierz indeks listy, ktora chcesz usunac: " << std::endl;
        int choice = chooseList(List);
        delete List[choice];//usuwa wskazywany obiekt
        List.remove(choice);//usuwa wskaznik z wektora i przesuwa dalsze elementy do przodu
        green("Pomyslnie usunieto liste ");

    } else {
        no_list_existing exception;
        throw exception;
    }

    //red("Nie mozna usunac listy, zadna nie istnieje");//TODO wyjatek}

}

void clearList(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        std::cout << "Wybierz indeks listy, ktora chcesz wyczyscic: " << std::endl;
        int choice = chooseList(List);
        List[choice]->clearList();
        green("Pomyslnie wyczyszczono liste");
    } else {
        no_list_existing exception;
        throw exception;
    }
}

void copyList(Tcontainer<Lista *> &List) {
    if (List.size() > 1) {//musza istniej przynajmniej 2 listy
        std::cout << "Wybierz indeks listy, ktora chcesz skopiowac: " << std::endl;
        int from = chooseList(List);
        std::cout << "Wybierz indeks listy, ktora chcesz nadpisac: " << std::endl;
        int to = chooseList(List);
        if (to == from) {
            the_same_lists exception;
            throw exception;
            //red("Nalezy wybrac 2 rozne listy");//TODO wyjatek 2 rozne listy
            //return;
        }
        *List[to] = *List[from];//operator przypisania listy
        green("Pomyslnie skopiowano liste");
        int choice2;
        do {
            std::cout <<
                      "\n---====== MENU =====---\n"
                      "1: Zmien nazwe utworzonej listy\n"
                      "2: Nie zmieniaj nazwy utworzonej listy\n"

                      "Wybierz akcje: " << std::endl;
            choice2 = readInt();
            switch (choice2) {
                case 1: {
                    std::cout << "Podaj nowa nazwe dla listy: " << std::endl;
                    std::string nName = readString();
                    List[to]->setName(nName);
                    green("Pomyslnie zmieniono nazwe");
                    break;
                }
                case 2:
                    break;
                default: {
                    red("Niepoprawy wybor");
                    std::cout << "Sprobuj ponownie" << std::endl;
                }
            }
        } while (choice2 != 1 && choice2 != 2);
    } else{
        not_enough_lists exception;
        throw exception;
        //red("Musza istniec przynajmniej 2 listy");//TODO wyjatek 2 istnieja
    }

}

void copyNewList(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        std::cout << "Wybierz indeks listy, ktora chcesz skopiowac: " << std::endl;
        int choice = chooseList(List);
        Lista *temp = new Lista(*List[choice]);
        List.pushback(temp);
        green("Pomyslnie skopiowano liste");
        int choice2;
        do {
            std::cout <<
                      "\n---====== MENU =====---\n"
                      "1: Zmien nazwe utworzonej listy\n"
                      "2: Nie zmieniaj nazwy utworzonej listy\n"

                      "Wybierz akcje: " << std::endl;
            choice2 = readInt();
            switch (choice2) {
                case 1: {
                    std::cout << "Podaj nowa nazwe dla listy" << std::endl;
                    std::string nName = readString();
                    List[List.size() - 1]->setName(nName);
                    green("Pomyslnie zmieniono nazwe");
                    break;
                }
                case 2:
                    break;
                default: {
                    red("Niepoprawy wybor");
                    std::cout << "Sprobuj ponownie" << std::endl;
                }
            }
        } while (choice2 != 1 && choice2 != 2);

    } else{
        no_list_existing exception;
        throw exception;
    }
        //red("Nie mozna skopiowac listy, zadna nie istnieje");//TODO wyjatek
}

void printList(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        int choice = chooseList(List);
        List[choice]->print();
    } else{
        no_list_existing exception;
        throw exception;
    }
        //red("Nie mozna wypisac listy, zadna nie istnieje");//TODO wyjatek
}

int chooseList(Tcontainer<Lista *> &List) {
    int choice;
    do {
        std::cout << "   =====================" << std::endl;
        for (int i = 0; i < List.size(); i++) {
            std::cout << i << ": " << List[i]->getName() << std::endl;
        }
        std::cout << "   =====================" << std::endl;
        std::cout << "Wybierz liste 0-" << List.size() - 1 << ": " << std::endl;
        choice = readInt();
        if (choice < 0 || choice >= List.size()) {
            red("Niepoprawy wybor");
            std::cout << "Sprobuj ponownie" << std::endl;
        }
    } while (choice >= List.size() || choice < 0);

    return choice;
}

void addItem(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        std::cout << "Na ktora liste chcesz dodac produkt" << std::endl;
        int choice = chooseList(List);
        if (List[choice]->getAmount() < LIST_SIZE) {
            if (List[choice]->addItem())
                green("Pomyslnie dodano produkt");
        } else
            red("Ta lista jest pelna, nie mozna dodac produtku");
    } else{
        no_list_existing exception;
        throw exception;
    }
        //red("Najpierw stworz liste");//TODO wyjatek
}

void removeItem(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        std::cout << "Z ktorej listy chcesz usunac produkt" << std::endl;
        int choice = chooseList(List);
        List[choice]->print();
        if (List[choice]->getAmount()) {
            int pos;
            do {
                std::cout << "Podaj indeks produktu ktory chcesz usunac" << std::endl;
                pos = readInt();
                if (pos < 0 || pos >= List[choice]->getAmount()) {
                    red("Podany indeks jest bledny");
                    std::cout << "Sprobuj ponownie" << std::endl;
                }

            } while (pos < 0 || pos >= List[choice]->getAmount());

            List[choice]->deleteItem(pos);
            green("Pomyslnie usunieto produkt");
        }
    } else{
        no_list_existing exception;
        throw exception;
    }
        //red("Najpierw stworz liste");//TODO wyjatek
}

void editItem(Tcontainer<Lista *> &List) {
    if (!List.isEmpty()) {
        int choice = chooseList(List);
        List[choice]->print();
        if (List[choice]->getAmount()) {
            int pos;
            do {
                std::cout << "Podaj indeks produktu ktory chcesz edytowac" << std::endl;
                pos = readInt();
                if (pos < 0 || pos >= List[choice]->getAmount()) {
                    red("Podany indeks jest bledny");
                    std::cout << "Sprobuj ponownie" << std::endl;
                }

            } while (pos < 0 || pos >= List[choice]->getAmount());

            List[choice]->editItem(pos);
        }
    } else{
        no_list_existing exception;
        throw exception;
    }
        //red("Najpierw stworz liste");//TODO wyjatek
}

int copyItem(Tcontainer<Lista *> &List, int *exitFrom) {
    if (List.size() > 1) {
        std::cout << "Z ktorej listy chcesz przepisac produkt" << std::endl;
        int from = chooseList(List);

        if (!List[from]->getAmount()) {
            red("lista jest pusta");
            return -1;
        }

        List[from]->print();
        int pos;
        do {
            std::cout << "Podaj indeks produktu ktory chcesz przepisac" << std::endl;
            pos = readInt();
            if (pos < 0 || pos >= List[from]->getAmount()) {
                red("Podany indeks jest bledny");
                std::cout << "Sprobuj ponownie" << std::endl;
            }
        } while (pos < 0 || pos >= List[from]->getAmount());


        std::cout << "Na ktora liste chcesz wpisac produkt" << std::endl;
        int to = chooseList(List);

        if (to == from) {
            the_same_lists exception;
            throw exception;
            //red("Nalezy wybrac 2 rozne listy");//TODO wyjatek 2 rozne listy
            //return -1;
        }
        bool wasExisting = false;

        if (List[to]->getAmount() < LIST_SIZE) {
            for (int i = 0; i < List[to]->getAmount(); i++)
                if (List[to]->getItem(i)->getName() == List[from]->getItem(pos)->getName())
                    if (typeid(*List[to]->getItem(i)) == typeid(*List[from]->getItem(pos))) {
                        List[to]->getItem(i)->setAmount(
                                List[to]->getItem(i)->getAmount() + List[from]->getItem(pos)->getAmount());
                        green("Taki produkt juz istnial na liscie, zamiast dodawac taki sam, wartosci zostaly zsumowane");
                        wasExisting = true;
                        break;
                    }
            if (!wasExisting) {
                List[to]->addItem(List[from]->getItem(pos));
                green("Pomyslnie przepisano produkt");
            }
            *exitFrom = from;
            return pos;
        } else {
            red("Ta lista jest pelna");
            return -1;
        }

    } else {
        not_enough_lists exception;
        throw exception;
        //red("Musza istniec przynajmniej 2 listy");//TODO wyjatek 2 istnieja
        //return -1;
    }
}

void moveItem(Tcontainer<Lista *> &List, int *from) {
    int pos = copyItem(List, from);
    if (pos >= 0) {
        List[*from]->deleteItem(pos);
    }
}

void connectLists(Tcontainer<Lista *> &List) {
    if (List.size() > 1) {
        std::cout << "Wybierz pierwsza liste" << std::endl;
        int first = chooseList(List);
        std::cout << "Wybierz druga liste" << std::endl;
        int second = chooseList(List);

        if (first == second) {
            the_same_lists exception;
            throw exception;
            //red("Nalezy wybrac 2 rozne listy");//TODO wyjatek 2 rozne listy
            //return;
        }
        //sprawdzenie ile obiektow sie powtarza
        int decrease = 0;
        for (int i = 0; i < List[second]->getAmount(); i++)
            for (int j = 0; j < List[first]->getAmount(); j++)
                if (List[second]->getProdName(i) == List[first]->getProdName(j))//jesli maja taka sama nazwe i jednostke
                    if (typeid(*List[second]->getItem(i)) == typeid(*List[first]->getItem(j)))
                        decrease++;

        //sprawdzenie czy bedzie maksymalnie 10 produktow
        if (List[second]->getAmount() + List[first]->getAmount() - decrease > 10) {
            red("Na listach znajduje sie za duzo produktow, nie mozna ich scalic");
            return;
        }

        //scalanie listy
        int sizeFirst = List[first]->getAmount();
        int sizeSecond = List[second]->getAmount();
        bool ifExists;
        int pos;

        for (int i = 0; i < sizeSecond; i++) {
            for (int j = 0; j < sizeFirst; j++) {
                ifExists = false;
                if (List[second]->getProdName(i) == List[first]->getProdName(j)//jesli maja taka sama nazwe i jednostke
                    && typeid(*List[second]->getItem(i)) == typeid(*List[first]->getItem(j))) {
                    ifExists = true;
                    pos = j;
                    break;
                }
            }

            if (ifExists)
                List[first]->getItem(pos)->setAmount(
                        List[first]->getItem(pos)->getAmount() + List[second]->getItem(i)->getAmount());
            else
                List[first]->addItem(List[second]->getItem(i));
        }

        delete List[second];
        List.remove(second);
        green("Pomyslnie scalono listy");

        int choice;
        do {
            std::cout <<
                      "\n---====== MENU =====---\n"
                      "1: Zmien nazwe utworzonej listy\n"
                      "2: Nie zmieniaj nazwy utworzonej listy\n"

                      "Wybierz akcje: " << std::endl;
            choice = readInt();
            switch (choice) {
                case 1: {
                    std::cout << "Podaj nowa nazwe dla listy" << std::endl;
                    std::string nName = readString();
                    List[first]->setName(nName);
                    green("Pomyslnie zmieniono nazwe");
                    break;
                }
                case 2:
                    break;
                default:
                    red("Niepoprawy wybor");
            }
        } while (choice != 1 && choice != 2);


    } else {
        not_enough_lists exception;
        throw exception;
        //red("Musza istniec przynajmniej 2 listy");//TODO wyjatek 2 istnieja
    }
}


