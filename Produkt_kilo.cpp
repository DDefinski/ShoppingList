//
// Created by ADM on 06.12.2020.
//

#include "Produkt_kilo.h"

std::string Produkt_kilo::unitMod() const {
    if (Amount - static_cast<int>(Amount) > 0.0000001)
        return " kilograma";//jesli jest liczba dziesietna
    if (static_cast<int>(Amount) % 10 < 5 && static_cast<int>(Amount) % 10 > 1 || static_cast<int>(Amount) % 100 < 15 && static_cast<int>(Amount) % 100 > 11)
        return " kilogramy";//jesli konczy sie na 2,3,4 ale nie na 12,13,14
    else if (static_cast<int>(Amount) == 1)
        return " kilogram";//jesli jest 1
    else
        return " kilogramow";//w przeciwnym wypadku
}
