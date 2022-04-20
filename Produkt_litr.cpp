//
// Created by ADM on 06.12.2020.
//

#include "Produkt_litr.h"

std::string Produkt_litr::unitMod() const {
    if (Amount - static_cast<int>(Amount) > 0.0000001)
        return " litra";//jesli jest liczba dziesietna
    if (static_cast<int>(Amount) % 10 < 5 && static_cast<int>(Amount) % 10 > 1 || static_cast<int>(Amount) % 100 < 15 && static_cast<int>(Amount) % 100 > 11)
        return " litry";//jesli konczy sie na 2,3,4 ale nie na 12,13,14
    else if (static_cast<int>(Amount) == 1)
        return " litr";//jesli jest 1
    else
        return " litrow";//w przeciwnym wypadku
}
