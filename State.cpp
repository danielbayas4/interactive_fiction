//
// Created by DrMark on 10/2/2017.
//

#include "State.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe_room();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {
    list<GameObject*> inventory;
};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}



void State::add_to_inventory(GameObject * gameObject) {
    inventory.push_back(gameObject); //inserte la segunda función de los push_back
}

void State::deleteObject_inventory(GameObject * to_be_eliminated) {

    State::inventory.remove(to_be_eliminated);
}

void State::describe_objects_inventory(){
    if (inventory.empty()){
        cout << "       " << endl;
        cout << "There are not objects in your inventory \n" << endl;
    }

    else {
        cout << "       " << endl;
        cout << "🔶 Inventory objects 🔶" << endl;

        for (const auto object: inventory) { //p-change: debería quitar const?
            object->short_description();
        }

    }
    cout << "       " << endl;
}

bool State::isPresent_inventory(string keyword){
    //alt: si es que getObject_inventory no me da null, entonces regresa true

    for (auto object: inventory){
        //todo:que compare los dos strings
        //usando el equals
        if(keyword == *(object-> getKeyword())){
            return true;
        }
    }
    return false;
}

GameObject * State::getObject_inventory(string keyword_input){
    for (const auto object: inventory){
        int are_equals = keyword_input.compare(*(object-> getKeyword()));

        if (are_equals == 0){
            return object;
        }
    }
    return nullptr;
    }

