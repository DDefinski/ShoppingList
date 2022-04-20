//
// Created by ADM on 19.11.2020.
//

#ifndef DEFINSKIDANIEL_ETAP3_PRODUKT_H
#define DEFINSKIDANIEL_ETAP3_PRODUKT_H

#include <string>
#include <iostream>
#include <iomanip>
class Produkt {
protected:
    std::string Name;//nazwa produktu
    virtual std::string unitMod() const = 0;//odmienia jednostke produktu do wypisania w liscie

public:
    Produkt( std::string name) : Name(name) {};//konstruktor
    Produkt(const Produkt &prod) : Produkt(prod.Name) {};//konstruktor kopiujacy
    ~Produkt()= default;//destruktor

    virtual void setAmount(double amount){};//modyfikuje ilosc produktu

    virtual double getAmount() const = 0;//zwraca ilosc produktu

    void setName(std::string name) { Name = name; };//modyfikuje nazwe produktu

    virtual void print() const = 0;//wypisuje produkt

    virtual std::string unit() const = 0;//wypisuje jednostke produktu

    std::string getName() {return Name;};//zwraca nazwe produktu
};


#endif //DEFINSKIDANIEL_ETAP3_PRODUKT_H
