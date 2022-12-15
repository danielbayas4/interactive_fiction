

#ifndef INTERACTIVE_FICTION_GAMEOBJECT_H
#define INTERACTIVE_FICTION_GAMEOBJECT_H


#include "wordwrap.h"
#include <string>
#include <forward_list>
#include <list>
#include <iostream>

using namespace std;
using std::string;



class GameObject {

private:
    const string* name;
    const string* description;
    const string* keyword;

public:
    GameObject(const string * _name, const string * _desc, const string * _keyword);

    const string * getKeyword();
    const string * getName();

    void complete_description();
    void short_description();
};


#endif //INTERACTIVE_FICTION_GAMEOBJECT_H
