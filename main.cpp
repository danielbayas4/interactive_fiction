
#include <iostream>
#include <stdlib.h>

#include <memory>
#include <iterator>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"
#include "SpecificObjects.h"

#include <fstream>
using namespace std;

//error: en el debugger me sale una variable que está incorrecta
//  object = expression failed to parse: error: <user expression 1>:1:1: use of undeclared identifier 'object' object ^

//des-pro: insertar la librería de file stream
// - exp: es una para el input stream y otra para el output?

//th_exp: como se usan las distintas funciones de compare en C++?


//exp: Si hay que usar de alguna manera alguna de estas librerías
    #include <vector>
    #include <forward_list>
    #include <iomanip>

using std::string;
using std::unique_ptr; //th_exp: de que manera se usa este?


string commandBuffer;
State *currentState;

//group: objects of the game
list<GameObject *> allObjects = {peak, water,hammer, knife,food};

//consi: la lists de objetos está en "Objects of the game.h
list<GameObject * > objects1 = {};
list<GameObject * > objects2 = {};
list<GameObject * > objects3 = {};
list<GameObject * > objects4 = {};
list<GameObject * > objects5 = {};
//exp: tienen que estas listas estar vacías al inicio del juego, para el load?

//group: rooms of the game
auto * r1 = new Room(&r1name, &r1desc, objects1);
auto * r2 = new Room(&r2name, &r2desc,objects2);
auto * r3 = new Room(&r3name, &r3desc, objects3);
auto * r4 = new Room(&r4name, &r4desc, objects4);
auto * r5 = new Room(&r5name, &r5desc, objects5);

list<Room *> allRooms = {r1,r4,r3,r2,r5};
//independientemente de la ubicación en la que se encuentren


//req-output: Print out the command prompt then read a command into the provided string buffer.
//des-ele: @param buffer Pointer to the string buffer to use.
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "🔹 Insert the command: ";
    std::getline(std::cin, *buffer);
}


//req-output: sets up the map
void initRooms() {

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

        //group: Comandos de manipulación de objetos / El loading and saving
        if (commandBuffer.find(' ') != string::npos){
            string input_keyword = commandBuffer.substr(endOfVerb + 1);

            if ((commandBuffer.compare(0, endOfVerb, "get") == 0) || (commandBuffer.compare(0, endOfVerb, "drop") == 0)
            || (commandBuffer.compare(0, endOfVerb, "examine") == 0)){

                GameObject *xgameObject = nullptr;

                bool in_room = currentState->getCurrentRoom()->isPresent_room(input_keyword);
                bool in_inventory = false;

                if (in_room) {
                    xgameObject = currentState->getCurrentRoom()->getObject_room(input_keyword);
                }

                else {
                    in_inventory = currentState->isPresent_inventory(input_keyword);

                    if (in_inventory) {
                        xgameObject = currentState->getObject_inventory(input_keyword);
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
                        }
                        else {
                            currentState->getCurrentRoom()->deleteObject_room(xgameObject);
                            currentState->add_to_inventory(xgameObject);
                            cout << "\n 🔺 The object " + *(xgameObject->getName()) + " was successfully gotten" << endl;

                            currentState->describe_objects_inventory();
                        }
                    }

                    else if ((commandBuffer.compare(0, endOfVerb, "drop") == 0)) {
                        commandOk = true;
                        if (in_room) {
                            wrapOut(&already_room);
                            wrapEndPara();
                        }

                        else {
                            currentState->deleteObject_inventory(xgameObject);
                            currentState ->getCurrentRoom()->addObject_room(xgameObject);
                            cout << "/\n 🔺  The object " + *(xgameObject->getName()) + " was successfully dropped \n ";

                            currentState->describe_objects_inventory();
                        }

                    }

                    else if ((commandBuffer.compare(0, endOfVerb, "examine") == 0)) {
                        commandOk = true;
                        xgameObject->complete_description();
                    }
                }
            }

            else{

                /*
                 * other: formato de mi archivo

                    object_inventory1
                    object_inventory2
                    $$$
                    Initial room
                    current_room
                    object_room1
                    $$$
                    Purple room
                    not_current_room
                    object_room2

                 */

                if ((commandBuffer.compare(0, endOfVerb, "load") == 0)){
                    //des-pro: preguntar por el nombre de un text file forecast
                    //des-pro: hacer que se inserte cual es el current room forecast

                    //des-bug: solamente esta haciendo el loop por el primer cuarto por el que pasa

                    commandOk = true;

                    ifstream filee(input_keyword); //p-cause: no estoy seguro si es que va a identificar al file de esta manera

                    //exp: como hago para que imprima incluso lo que esta después de un espacio en blanco
                    bool nextStorage = false;

                    if (filee.fail()){
                        cout << "Could not read the information "<< endl;
                    }

                    while (!filee.eof()){
                        //des-pro: lee los determinados objetos (para el inventario) hasta llegar al delimiter $$$

                        //group: update inventory information

                        string file_line;

                        while (!nextStorage){
                            //improvement: no creo que tiene que ir dentro del while loop
                            getline(filee, file_line);

                            if (file_line.compare("$$$") == 0){
                                //des-pro: nos saltamos a la siguiente línea que empezará con el nombre del cuarto
                                nextStorage = true;
                            }
                            else{
                                for (GameObject * object: allObjects){
                                    if (object ->getKeyword()->compare(file_line) == 0){
                                        currentState ->add_to_inventory(object);
                                    }
                            }
                            }
                        }

                        nextStorage = false;

                        while (!nextStorage){
                            getline(filee, file_line);

                            //des-pro: compara con cada cuarto el nombre impuesto, para procesar

                            for (Room * room: allRooms){
                                if (nextStorage == true){
                                    getline(filee, file_line);
                                }
                                nextStorage = false;

                                //fault: por alguna razón a pesar de que los strings sean iguales, esto no lo identifica como tal
                                string room_name = room ->getName();

                                int comparison_strings = room_name.compare(file_line);

                                if (comparison_strings == 0){
                                    getline(filee, file_line);

                                    if (file_line.compare("current_room") == 0){
                                        room = currentState ->getCurrentRoom();
                                    }

                                    while (!nextStorage){
                                        getline(filee, file_line);

                                        if (file_line.compare("$$$") == 0){
                                            nextStorage = true;
                                        }
                                        else {
                                            for (GameObject * gameObject: allObjects){
                                                if (gameObject ->getKeyword()->compare(file_line) == 0){
                                                    room->addObject_room(gameObject);
                                                }
                                            }
                                        }


                                    }

                                }
                            }

                            //temporary
                            nextStorage = true;

                        }
                        cout << "Information successfully loaded" << endl;
                        filee.close();
                        break;
                        //exp: como hago para que funcione sin usar el break?

                    }

                }

                else if ((commandBuffer.compare(0, endOfVerb, "save") == 0)){
                    //des-pro: preguntar por el nombre de un text file forecast
                    //des-pro: agarra la información de currentState -> getCurrentRoom() forecast
                    //des-pro: hacer que se inserte cual es el current room forecast



                    //pseudo
                    /*
                            primero tiene que imprimir 'Inventory'
                            luego los objetos dentro de este mismo

                            verifico cuál es el current room e imprimo la información con el current_room
                            luego hago un for loop por todos los cuartos menos este.
                            - este tiene que imprimir en esa sección -not_current_room




                            entra en un for loop con todos los cuartos del state
                            coge el nombre del room y lo coloca en el file
                            luego, por cada objeto de este mismo, lo coloca abajo
                            al terminar otorga el delimiter (que me servirá en el load)
                         */

                    //tiene que almacenar el cuarto en el que se encuentra, los objetos de este mismo, y los objetos del inventario
                    //un file para los del inventario
                    //un file para los del cuarto
                    //un file para la información del cuarto

                    //break;
                }
            }

        }

        //group: Comandos de traslado
        else if ((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)
                 || (commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)
                 || (commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)
                 || (commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {

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

            if (xRoom == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();

            } else {
                currentState->goTo(xRoom);
            }

        }


        else {

            if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
                commandOk = true;
                gameOver = true;
            }


            else if ((commandBuffer.compare(0, endOfVerb, "inventory") == 0)) {
                //des-bug: esta imprimiendo de igual manera la información del room, y solo quiero que imprima la del inventario
                commandOk = true;
                currentState->describe_objects_inventory();
            }



        }


        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
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

