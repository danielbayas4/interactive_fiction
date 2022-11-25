

#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include "GameObject.h"
#include "strings.h"


using std::string;
using namespace std;

class Room {

private:
    const string* name;
    const string* description;
    Room* north;
    Room* east;
    Room* south;
    Room* west;

    /*
     [used] o debería ser list<GameObject> objects; o debería ser list<GameObject*> * objects
     */
    list<GameObject*> objects;


public:
    Room(const string *_name, const string *_desc, list<GameObject*> &_objects);

    ~Room();

    //string displayObjects();
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoomPar().
     */
    static list<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * Statically creates a room and then adds it to the global list.
     * @return A pointer to the newly created room.
     */
    static Room* addRoomPar(const string *_name, const string *_desc, list<GameObject*> &_objects);

    static void addRoom(Room* room);


    void addObject(GameObject * gameObject);
    void deleteObject(GameObject * gameObject);

    //getObjects
        //



    Room* getNorth() const;
    void setNorth(Room* _north);

    Room* getEast() const;
    void setEast(Room *_east);

    Room* getSouth() const;
    void setSouth(Room *_south);

    Room* getWest() const;
    void setWest(Room *_west);

};

#endif //TEXTADV_ROOM_H
