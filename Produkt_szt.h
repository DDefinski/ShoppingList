//
// Created by ADM on 06.12.2020.
//

#ifndef DEFINSKIDANIEL_ETAP3_PRODUKT_SZT_H
#define DEFINSKIDANIEL_ETAP3_PRODUKT_SZT_H

#include "Produkt.h"


class Produkt_szt : public Produkt {
    int Amount;//ilosc produktu
    std::string unitMod() const override ;//dziedziczona po produkcie
public:
    Produkt_szt(std::string name, int amount) : Produkt(name), Amount(amount) {};//konstruktor
    Produkt_szt(const Produkt_szt* prod) : Produkt_szt(prod->Name, prod->Amount) {};//konstruktor kopiujący
    ~Produkt_szt() = default;//destruktor

    void setAmount(double amount) override { Amount = static_cast<int>(amount); };//dziedziczona po produkcie

    double getAmount() const override{return Amount;};//dziedziczona po produkcie

    std::string unit() const override {return "w sztukach: " ;}//dziedziczona po produkcie

    std::string static sUnit() {return "w sztukach: " ;}//tez wypisuje jednostke, ale mozna ja wykorzystac bez obiektu

    void print() const override {//dziedziczona po produkcie
        std::cout << Name << "\tilosc:\t" << Amount << unitMod() << std::endl;
    }

};


#endif //DEFINSKIDANIEL_ETAP3_PRODUKT_SZT_H
