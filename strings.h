
#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>
using std::string;


// Initial room
const string r1name = "Initial room";
const string r1desc = "You are in the initial room. It's really quite boring, but then, it's just for testing really. There's a passage to all of the directions.";

//North del initial
const string r2name = "Blue Room";
const string r2desc = "You are the blue room. You know because it's blue. That's about all though. There's a passage to the the south.";

//Este del initial
const string r3name = "Red Room";
const string r3desc = "You are the red room. You know because it's red. That's about all though. There's a passage to the west.";

//Sur del initial
const string r4name = "Purple Room";
const string r4desc = "You are the purple room. You know because it's purple. That's about all though. There's a passage to the north.";

//Oeste del initial
const string r5name = "Green Room";
const string r5desc = "You are the green room. You know because it's green. That's about all though. There's a passage to the east.";

const string badExit = "You can't go that way.";
const string badCommand = "I don't understand that.";

const string non_existent_object = "The object you mentioned does not exist neither in the room or in your inventory";
const string already_inventory = "The object you mentioned is already in the inventory";

const string already_room = "The object you mentioned is already in the room";

//todo: errors que deberían aparecer si es que no existe el objeto que se quieren dentro de






const string o1 = "Hammer";
const string des1 = "Defend from a zombie";
const string keyword1 = "ham";

const string o2 = "Knife";
const string des2 = "Defend from a zombie";
const string keyword2 = "kn";

const string o3 = "Peak";
const string des3 = "Defend from a zombie";
const string keyword3 = "peak";

const string o4 = "Water";
const string des4 = "Nurture and survive";
const string keyword4 = "co2";

const string o5= "Food";
const string des5 = "Nurture and survive";
const string keyword5 = "food";


#endif //TEXTADV_STRINGS_H
