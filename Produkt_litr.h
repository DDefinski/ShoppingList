//
// Created by ADM on 06.12.2020.
//

#ifndef DEFINSKIDANIEL_ETAP3_PRODUKT_LITR_H
#define DEFINSKIDANIEL_ETAP3_PRODUKT_LITR_H

#include "Produkt.h"


class Produkt_litr : public Produkt {
    double Amount;//ilosc produktu
    std::string unitMod() const override ;//dziedziczona po produkcie
public:
    Produkt_litr(std::string name, double amount) : Produkt(name), Amount(amount) {};//konstruktor
    Produkt_litr(const Produkt_litr* prod) : Produkt_litr(prod->Name, prod->Amount) {};//konstruktor kopiujący
    ~Produkt_litr() = default;//destruktor

    void setAmount(double amount) override { Amount = amount; };//dziedziczona po produkcie

    double getAmount() const override{return Amount;};//dziedziczona po produkcie

    std::string unit() const override { return "w litrach (moze byc liczba zmiennoprzecinkowa): "; }//dziedziczona po produkcie

    std::string static sUnit() {return "w litrach (moze byc liczba zmiennoprzecinkowa): " ;}//tez wypisuje jednostke, ale mozna ja wykorzystac bez obiektu

    void print() const override {//dziedziczona po produkcie
        std::cout << Name << "\tilosc:\t" << Amount << unitMod() << std::endl;
    }

};


#endif //DEFINSKIDANIEL_ETAP3_PRODUKT_LITR_H
