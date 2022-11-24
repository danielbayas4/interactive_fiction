
#include <iostream>

#include <memory>
#include <iterator>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"

//#include <vector>
//#include <forward_list>
//#include <iomanip>

/*
 * [m]
 * Exp: Que es el command buffer
 */

/*
 [used]
    Los aspectos que tengo que comprender para poder realizar el código
    - La diferencia entre poner list <List*> y <List>
 */


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * hammer = new GameObject(o1,des1,keyword1);
    auto * knife = new GameObject(o2,des2,keyword2);
    auto * peak = new GameObject(o3,des3,keyword3);
    auto * water = new GameObject(o4,des4,keyword4);
    auto * food = new GameObject(o5,des5,keyword5);

    list<GameObject * > objects1 = {hammer};
    list<GameObject * > objects2 = {knife};
    list<GameObject * > objects3 = {peak};
    list<GameObject * > objects4 = {water};
    list<GameObject * > objects5 = {food};

    auto * r1 = new Room(&r1name, &r1desc, objects1);
    auto * r2 = new Room(&r2name, &r2desc,objects2);
    auto * r3 = new Room(&r3name, &r3desc, objects3);
    auto * r4 = new Room(&r4name, &r4desc, objects4);
    auto * r5 = new Room(&r5name, &r5desc, objects5);



    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    //Desde el cuarto inicial

    r1->setNorth(r2);
    r1 ->setEast(r3);
    r1 ->setSouth(r4);
    r1 ->setWest(r5);


    //Desde el r2 (Blue room)

    r2 ->setSouth(r1);

    //Desde el r3 (Red room)
    r3 ->setWest(r1);

    //Desde el r4
    r4 ->setNorth(r1);

    //Desde el r5
    r5 ->setEast(r1);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


void gameLoop() {
    bool gameOver=false;

    while (!gameOver) {

        bool commandOk = false;

        /* Ask for a command. */
        /* The first word of a command would normally be the verb. The first word is the text before the first
      * space, or if there is no space, the whole string. */
        inputCommand(&commandBuffer);

        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' ')); //[m] Que carajos hace esto?
        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */


        //primero empieza con los comandos que tienens relación con el cuarto en el que estamos


        /*
         * switch(commandBuffer){
         *  case 'n': case "north":
         *      xRoom = currentState->getCurrentRoom()->getNorth();
         *
         *  case 's': case "south":
         *      xRoom = currentState->getCurrentRoom()->getSouth();
         *
         *  case 'e': case "east":
         *      xRoom = currentState->getCurrentRoom()->getEast();
         *
         *  case 'w': case: "west"
         *     xRoom = currentState->getCurrentRoom()->getWest();
         */


        Room * xRoom ;

        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true;
            xRoom = currentState->getCurrentRoom()->getNorth();
        }

        else if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            commandOk = true;

            xRoom = currentState -> getCurrentRoom()->getSouth();
        }

        else if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            commandOk = true;

            xRoom = currentState -> getCurrentRoom() -> getEast();
        }

        else if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            commandOk = true;

            xRoom = currentState->getCurrentRoom()->getWest();
        }


        if (xRoom == nullptr) {
            wrapOut(&badExit);
            wrapEndPara();

        } else {
            currentState->goTo(xRoom);
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}