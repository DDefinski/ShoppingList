//
// Created by ADM on 08.01.2021.
//

#ifndef DEFINSKIDANIEL_ETAP3_TCONTAINER_H
#define DEFINSKIDANIEL_ETAP3_TCONTAINER_H

template<typename T>
class Tcontainer {
    T *tab = new T;
    int _size = 0;

public:
    void pushback(T& item);
    void remove(int pos);
    int size() { return _size; };
    bool isEmpty() { return !_size; }

    T &operator[](int i) { return tab[i]; }

};

template<typename T>
void Tcontainer<T>::pushback(T& item) { tab[_size++] = item; }

template<typename T>
void Tcontainer<T>::remove(int pos) {
    if (pos >= 0 && pos < _size) {
        T *temp = new T;
        for (int i = 0, j = 0; i < _size && i != pos; i++) {
            temp[j++] = tab[i];
        }
        delete tab;
        tab = temp;
        _size--;
    }
}


#endif //DEFINSKIDANIEL_ETAP3_TCONTAINER_H
