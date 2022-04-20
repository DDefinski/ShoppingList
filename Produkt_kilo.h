//
// Created by ADM on 06.12.2020.
//

#ifndef DEFINSKIDANIEL_ETAP3_PRODUKT_KILO_H
#define DEFINSKIDANIEL_ETAP3_PRODUKT_KILO_H

#include "Produkt.h"


class Produkt_kilo : public Produkt {
    double Amount;//ilosc produktu
    std::string unitMod() const override ;//dziedziczona po produkcie
public:
    Produkt_kilo(std::string name, double amount) : Produkt(name), Amount(amount) {};//konstruktor
    Produkt_kilo(const Produkt_kilo* prod) : Produkt_kilo(prod->Name, prod->Amount) {};//konstruktor kopiujący
    ~Produkt_kilo() = default;//destruktor

    void setAmount(double amount) override { Amount = amount; };//dziedziczona po produkcie

    double getAmount() const override{return Amount;};//dziedziczona po produkcie

    std::string unit() const override { return "w kilogramach (moze byc liczba zmiennoprzecinkowa): ";}//dziedziczona po produkcie

    std::string static sUnit() {return "w kilogramach (moze byc liczba zmiennoprzecinkowa): " ;}//tez wypisuje jednostke, ale mozna ja wykorzystac bez obiektu


    void print() const override {//dziedziczona po produkcie
        std::cout << Name << "\tilosc:\t" << Amount << unitMod() << std::endl;
    }
};


#endif //DEFINSKIDANIEL_ETAP3_PRODUKT_KILO_H
