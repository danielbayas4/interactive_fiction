//
// Created by Daniel Bayas on 29/11/22.
//
#ifndef TEXTADV_SPECIFICOBJECTS_H
#define TEXTADV_SPECIFICOBJECTS_H

//una lista de listas de los cuartos
//una lista de lista para el inventario

#include "GameObject.h"

using namespace std;
using std::string;

auto * hammer = new GameObject(&o1,&des1,&keyword1);
auto * knife = new GameObject(&o2,&des2,&keyword2);
auto * peak = new GameObject(&o3,&des3,&keyword3);
auto * water = new GameObject(&o4,&des4,&keyword4);
auto * food = new GameObject(&o5,&des5,&keyword5);

class SpecificObjects{
    private:
        //list<GameObject * > specificObjects;

    public:
//    list<GameObject * > getSpecificObjects();
//    SpecificObjects();

};

#endif //TEXTADV_SPECIFICOBJECTS_H

