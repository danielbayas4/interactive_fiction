

#include "Room.h"
#include "wordwrap.h"
#include "GameObject.h"
#include <list>
#include <iostream>
#include <iterator>
#include<string.h>

using namespace std;

/*
    th_exp: static list

    des-ele
     - Stores a static list of all the rooms
     - List storing all rooms that have been registered via addRoomPar()
 */
list<Room * > Room::rooms;




Room::Room(const string* _name, const string *_desc, list<GameObject*> & _objects):
        name(_name), description(_desc), objects(_objects), north(nullptr), south(nullptr), east(nullptr), west(nullptr) {};

Room::~Room() {
    Room::rooms.remove(this);
}

void Room::describe_room() const {

    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    if (objects.empty()){

        cout << "       " << endl;
        cout << "There are not objects in this room" << endl;
    } else {
        //req-output: se tiene que imprimir la lista de objetos en el command line

        cout << "       " << endl;
        cout << "🔶 List of objects of the room 🔶" << endl;
        for (const auto object: objects) { //p-change: debería quitar const?
            object->short_description();
        }
    }
    cout << "       " << endl;
}



void Room::addObject_room(GameObject * gameObject) {
    objects.push_back(gameObject);
}

void Room::deleteObject_room (GameObject * to_eliminate_object){
    Room::objects.remove(to_eliminate_object);
}



bool Room::isPresent_room (string keyword_){ //p-cause: si va con el & ?

    //[used] do-tur:comparar los dos strings
        //other: usando el equals
        //other: usando la función compare

    for (const auto object: objects){
        int are_equals = keyword_.compare(*(object-> getKeyword()));

        if (are_equals == 0){
            return true;
        }

    }
        return false;
    }




GameObject * Room::getObject_room(string keyword){
    //consi: Uso esta función considerando que el objeto si existe dentro del cuarto, por lo que mi código no llegaría a esta sección

    for (const auto object: objects){
        int are_equals = keyword.compare(*(object-> getKeyword()));

        if (are_equals == 0){
            return object;
        }
    }
    //return nullptr;

}


Room* Room::addRoomPar(const string *_name, const string *_desc, list<GameObject *> &_objects) {
    auto *newRoom = new Room(_name, _desc,_objects);
    Room::rooms.push_back(newRoom); //misu: Que carajos hace este push back?
    return newRoom; //des: A pointer to the newly created room.
}
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}













Room* Room::getNorth() const { //conf: se usa el const después del nombre y no antes / const getNorth()
    return this->north;
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

string Room::getName() {
    return *name;
}
