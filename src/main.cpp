#include <iostream>
#include <string>

#include "LuaScript.h"

using std::string;
using std::vector;
using std::endl;
using std::cout;

#define UNUSED(x) ((void)(x))

int main(int argc, char **argv) {
    UNUSED(argc);
    UNUSED(argv);

    LuaScript script("lua/Player.lua");

    double posX = script.get<double>("player.position.x");
    double posY = script.get<double>("player.position.y");
    string filename = script.get<string>("player.filename");
    int hp = script.get<int>("player.HP");

    cout<< "Position X = " << posX << ", Y = " << posY << endl;
    cout<< "Filename:" << filename << endl;
    cout<< "HP:" << hp << endl;

    // getting arrays
    vector<int> v = script.getIntVector("array");
    cout << "Contents of array:";
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++) {
            cout << *it << ",";
    }
    cout << endl;

    // getting table keys:
    vector<string> keys = script.getTableKeys("player");
    cout << "Keys of [player] table:";
    for(vector<string>::iterator it = keys.begin(); it != keys.end(); it++) {
            cout << *it << ",";
    }
    cout << endl;

    return 0;
}
