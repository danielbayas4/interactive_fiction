
#include "wordwrap.h"


#include <forward_list>
#include <list>
#include "GameObject.h"

using namespace std;
using std::string;

GameObject::GameObject(const string * _name, const string * _desc, const string * _keyword):
        name(_name), description(_desc), keyword(_keyword){}

const string * GameObject::getKeyword(){
    return keyword;
}

const string * GameObject::getName(){
    return name;
}

void GameObject:: complete_description(){
    cout << "- Complete name: ";
    wrapOut(name);
    wrapEndPara();

    cout << "- Keyword: ";
    wrapOut(keyword);
    wrapEndPara();

    cout << "- Function: ";
    wrapOut(description);
    wrapEndPara();


}
void GameObject::short_description(){
    cout << "- " << *name << ":" << *keyword << endl;
}


