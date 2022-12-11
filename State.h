
#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
    list<GameObject*> inventory;


public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;

    void deleteObject_inventory(GameObject * to_be_eliminated); //[m] Expansion: Debería usar el pointer o solamente '(string input-keyword)' ?
    void add_to_inventory(GameObject * gameObject);
    void describe_objects_inventory();
    bool isPresent_inventory(string keyword);
    GameObject * getObject(string  keyword);

};

#endif //TEXTADV_STATE_H
