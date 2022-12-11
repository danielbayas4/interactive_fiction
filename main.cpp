
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include <memory>
#include <iterator>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"
#include "Objects of the game.h"

//th_exp: como se usan las distintas funciones de compare en C++?


//exp: Si hay que usar de alguna manera alguna de estas librerías
    #include <vector>
    #include <forward_list>
    #include <iomanip>

using std::string;
using std::unique_ptr; //th_exp: de que manera se usa este?


string commandBuffer;
State *currentState;

static string second_word(){
    size_t pos = commandBuffer.find(" ");
    string second;
    if (pos != string::npos){
        second = commandBuffer.substr(1 + pos);

        return second;
    }
}

//req-output: Print out the command prompt then read a command into the provided string buffer.
//des-ele: @param buffer Pointer to the string buffer to use.
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "🔹 Insert the command: ";
    std::getline(std::cin, *buffer);
}


//req-output: sets up the map
void initRooms() {
    //consi: la lists de objetos está en "Objects of the game.h
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

    //des-pro: Desde el cuarto inicial
    r1->setNorth(r2);
    r1 ->setEast(r3);
    r1 ->setSouth(r4);
    r1 ->setWest(r5);


    //des-pro: Desde el r2 (Blue room)
    r2 ->setSouth(r1);

    //des-pro: Desde el r3 (Red room)
    r3 ->setWest(r1);

    //des-pro: Desde el r4
    r4 ->setNorth(r1);

    //des-pro: Desde el r5
    r5 ->setEast(r1);
}


//req-output: sets up the game state
void initState() {
    currentState = new State(Room::rooms.front());
}


void gameLoop() {
    bool gameOver = false;

    while (!gameOver) {

        bool commandOk = false;

        inputCommand(&commandBuffer);

        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        Room *xRoom;
        xRoom = currentState -> getCurrentRoom();

        //group: Comandos de traslado


        if ((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)) {
            commandOk = true;
            xRoom = currentState->getCurrentRoom()->getNorth();
        }

        else if ((commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)) {
            commandOk = true;
            xRoom = currentState->getCurrentRoom()->getSouth();
        }

        else if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
            commandOk = true;
            xRoom = currentState->getCurrentRoom()->getEast();

        }

        else if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
            commandOk = true;
            xRoom = currentState->getCurrentRoom()->getWest();
        }

        if ((commandBuffer.compare(0, endOfVerb, "inventory") == 0)) {
            commandOk = true;
            currentState->describe_objects_inventory();
        }

        //load
        //save



        //group: Comandos de manipulación de objetos
        if (commandBuffer.find(' ') != string::npos){
            string input_keyword = commandBuffer.substr(endOfVerb + 1);

            GameObject *xgameObject = nullptr;

            bool in_room = currentState->getCurrentRoom()->isPresent_room(input_keyword);
            bool in_inventory;

            if (in_room) {
                xgameObject = currentState->getCurrentRoom()->getObject(input_keyword);
            }

            else {
                in_inventory = currentState->isPresent_inventory(input_keyword);

                if (in_inventory) {
                    xgameObject = currentState->getObject(input_keyword);
                }
            }

            if (xgameObject == nullptr) {
                wrapOut(&non_existent_object);
                wrapEndPara();

            }

            else {
                //des-ele: si el elemento existe en cualquiera de las dos listas

                if ((commandBuffer.compare(0, endOfVerb, "get") == 0)) {
                    commandOk = true;

                    if (in_inventory) {
                        wrapOut(&already_inventory);
                        wrapEndPara();
                    } else {
                        currentState->getCurrentRoom()->deleteObject_room(xgameObject);
                        currentState->add_to_inventory(xgameObject);
                    }

                }
                if ((commandBuffer.compare(0, endOfVerb, "drop") == 0)) {
                    commandOk = true;
                    if (in_room) {
                        wrapOut(&already_room);
                        wrapEndPara();
                    } else {
                        currentState->deleteObject_inventory(xgameObject);
                    }
                }

                if ((commandBuffer.compare(0, endOfVerb, "examine") == 0)) {
                    commandOk = true;
                    xgameObject->describe();
                }
            }
        }


        if (xRoom == nullptr) {
            wrapOut(&badExit);
            wrapEndPara();

        } else {
            currentState->goTo(xRoom);
        }




        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }

        //des-pro: Aquí se debería acabar la lectura, si es que el comando no se relacionaba con un objeto forecast
        // - Esto me permitirá no incluir esa sección de código en los distintos comandos relacionados con el objeto
    }


}

int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;

//    auto gamo = new GameObject(&o1,&des1,&keyword1);
//    std::cout << "name: " <<gamo -> getName() << " " <<endl;
//    std::cout << "keyword: " << *(gamo -> getKeyword()) << "" <<endl;
//
//
//    std::cout << "with the wrapOut: ";
//
//    wrapOut(gamo-> getKeyword());
//    wrapEndPara();
}

