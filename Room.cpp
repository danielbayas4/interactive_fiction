

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

void Room::describe() const {
    //req-output: se tiene que imprimir la lista de objetos en el command line

    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    for (const auto object: objects) { //p-change: debería quitar const?
        cout << "🔶 Here is the list of objects of the room 🔶" << endl;
        object->describe();
    }

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
        } else{
            return false;
        }
    }

    }


GameObject * Room::getObject(string keyword){
    //des-pro: incorporarlo en el main, en ves de solo usar el de state forecast

    for (const auto object: objects){
        int are_equals = keyword.compare(*(object-> getKeyword()));


        if (are_equals == 0){
            return object;
        }
        else{
            return nullptr;
        }
    }

    for (const auto object: this->objects){
        //do-tur:comparar los dos strings
            //other: usando el equals
            //other: usando la función compare
        if(keyword.compare(*(object-> getKeyword()))){
            return object;
        }
    }
    //consi: Uso esta función considerando que el objeto si existe dentro del cuarto, por lo que mi código no llegaría a esta sección
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
