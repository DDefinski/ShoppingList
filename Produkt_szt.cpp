//
// Created by ADM on 06.12.2020.
//

#include "Produkt_szt.h"

std::string Produkt_szt::unitMod() const {
    if(Amount%10<5 && Amount%10>1 || Amount%100<15 && Amount%100>11)
        return " sztuki";//2,3,4 ale nie 12,13,14
    else if(Amount==1)
        return " sztuka";//1
    else
        return " sztuk";//inaczej
}
