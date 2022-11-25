

#ifndef INTERACTIVE_FICTION_GAMEOBJECT_H
#define INTERACTIVE_FICTION_GAMEOBJECT_H


#include "wordwrap.h"
#include <string>
#include <forward_list>
#include <list>

using namespace std;

using std::string;


class GameObject {

private:
    //Les quité los pointers para usar el reference, debería usar pointer?
    const string name;
    const string description;
    const string keyword; //For the command

public:
    GameObject(const string &_name, const string &_desc, const string &_keyword); //Tengo que agregar el pointer aquí
    string getName();


    //void setName();
};


#endif //INTERACTIVE_FICTION_GAMEOBJECT_H
