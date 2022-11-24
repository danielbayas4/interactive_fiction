

#include "Room.h"
#include "wordwrap.h"
#include "GameObject.h"
#include <list>

using namespace std;

/**
 * Stores a static list of all rooms.
 * List storing all rooms that have been registered via addRoomPar().
 */
list< Room * > Room::rooms; //[m] Confusion: Por qué carajos pone al pointer dentro de estas comillas?
//[m] Por qué no se declaro esta variable dentro del h file?





Room::Room(const string* _name, const string *_desc, list<GameObject*> & _objects):
        name(_name), description(_desc), objects(_objects), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {};
Room::~Room() {
    Room::rooms.remove(this);

}

//string objectsStrings(list<GameObject*> & _objects){
//
//}
//
////objects -> insert(iter, gameOb);
////To-do: Eso de start y end
//
//    list<GameObject *>::iterator it;
//    for (it = objects.begin(); it != objects.end(); ++it){
//        std::cout << it->name;
//    }
////}

void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    //Aquí tiene que aparecer un string con la información

}

void Room::addObject(GameObject * gameOb) {
   objects.push_back(gameOb);
}
void Room::deleteObject(GameObject * rGameObject){
    objects.remove(rGameObject);
}




Room* Room::addRoomPar(const string *_name, const string *_desc, list<GameObject *> _objects) {
    auto *newRoom = new Room(_name, _desc,_objects);
    Room::rooms.push_back(newRoom); //[m] Que carajos hace este push back?
    return newRoom; //A pointer to the newly created room.
}
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}




Room* Room::getNorth() const {
    return this->north;
    /*
     * [used] Por qué hay un const a lado de la función, si es que la variable north no es constante?
     * [m] Por qué en la de setNorth no hay el const?
     */
}
void Room::setNorth(Room* _north) {
    this->north = _north;
}


Room* Room:: getEast() const {
    return this->east;
}
void Room:: setEast(Room* _east) {
    this -> east = _east;
}

Room* Room::getSouth() const {
    return this-> south;
}
void Room::setSouth(Room *_south) {
    this -> south = _south;
}

Room* Room::getWest() const {
    return this-> west;
}
void Room::setWest(Room *_west) {
    this -> west = _west;
}
