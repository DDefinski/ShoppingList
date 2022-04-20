//
// Created by ADM on 19.11.2020.
//

#ifndef DEFINSKIDANIEL_ETAP3_LISTA_H
#define DEFINSKIDANIEL_ETAP3_LISTA_H

#include <vector>
#include "Produkt.h"
#include "Produkt_kilo.h"
#include "Produkt_szt.h"
#include "Produkt_litr.h"

#define LIST_SIZE 10

int readInt(bool ifAmount = false);
double readDouble();
std::string readString();

void red(const std::string& line);//wypisuje tekst na czerowno
void green(const std::string& line);//wypisuje tekst na zielono

class Lista {
    Produkt* list[LIST_SIZE]{};//tablica wskaznikow na produkty
    int Amount = 0;//ilosc elementow na liscie
    std::string Name;//nazwa listy

public:
    Lista(std::string name):Name(name){};//konstruktor
    Lista(const Lista &List);//konstruktor kopiujacy

    ~Lista();//destrukor

    bool addItem();//dodaje produkt tworzac go uzywajac konstruktora produktu
    void addItem(Produkt* item);//dodaje produkt tworzac go uzywajac konstruktora kopiujacego produktu

    void deleteItem(int pos);//usuwa produkt z listy

    void clearList();//czysci liste i usuwa produkty do niej przypisane, obiekt nie zostaje usuniety

    void print()const;//drukuje liste

    std::string getName() const { return Name; };//zwraca nazwe listy
    void setName(std::string name){Name=name;};//modyfikuje nazwe listy

    int getAmount() const { return Amount; };//zwraca ilosc produktow przypisanych do listy

    Produkt* getItem(int pos)const {return list[pos];};//zwraca wskaznik na produkt

    void editItem(int pos);//modyfikuje wybrany produkt przypisany do listy

    Lista& operator=(Lista const &list1);//operator przypisania listy

    std::string getProdName(int pos) const { return list[pos]->getName(); }//zwraca nazwe produktu z danego indeksu

};


#endif //DEFINSKIDANIEL_ETAP3_LISTA_H
