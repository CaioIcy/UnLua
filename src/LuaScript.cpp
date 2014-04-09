#include "LuaScript.h"

LuaScript::LuaScript(const string& filename) {
    this->luaState = luaL_newstate();
    if (luaL_loadfile(this->luaState, filename.c_str()) || lua_pcall(luaState, 0, 0, 0)) {
        cout << "Error: failed to load ("<< filename << ")" << endl;
        this->luaState = 0;
    }

    if(this->luaState){
        luaL_openlibs(this->luaState);
    }
}

LuaScript::~LuaScript() {
    if(this->luaState){
        lua_close(this->luaState);
    }
}

void LuaScript::printError(const string& variableName, const string& reason) {
    cout<< "Error: can't get [" <<variableName<< "]. " << reason << endl;
}

vector<int> LuaScript::getIntVector(const string& name) {
    vector<int> v;
    lua_gettostack(name);
    if(lua_isnil(this->luaState, -1)) { // array is not found
        return vector<int>();
    }
    lua_pushnil(this->luaState);
    while(lua_next(this->luaState, -2)) {
        v.push_back((int)lua_tonumber(this->luaState, -1));
        lua_pop(this->luaState, 1);
    }
    clean();
    return v;
}

vector<string> LuaScript::getTableKeys(const string& name) {
    string code = 
        "function getKeys(name) "
        "s = \"\""
        "for k, v in pairs(_G[name]) do "
        "    s = s..k..\",\" "
        "    end "
        "return s "
        "end"; // function for getting table keys

    luaL_loadstring(this->luaState, code.c_str()); // execute code
    lua_pcall(this->luaState, 0, 0, 0);
    lua_getglobal(this->luaState, "getKeys"); // get function
    lua_pushstring(this->luaState, name.c_str());
    lua_pcall(this->luaState, 1 , 1, 0); // execute function

    string test = lua_tostring(luaState, -1);
    vector<string> strings;
    string temp = "";

    cout<< "TEMP:" << test << endl;

    for(unsigned int i = 0; i < test.size(); i++) {     
        if(test.at(i) != ',') {
            temp += test.at(i);
        } else {
            strings.push_back(temp);
            temp= "";
        }
    }
    clean();
    return strings;
}

bool LuaScript::lua_gettostack(const string& variableName) {
    this->level = 0;
    string var = "";
    for(unsigned int i = 0; i < variableName.size(); i++) {
        if(variableName.at(i) == '.') {
            if(this->level == 0) {
                lua_getglobal(this->luaState, var.c_str());
            }
            else {
                lua_getfield(this->luaState, -1, var.c_str());
            }

            if(lua_isnil(this->luaState, -1)) {
                printError(variableName, var + " is not defined");
                return false;
            }
            else {
                var = "";
                this->level++;
            }
        } else {
            var += variableName.at(i);
        }
    }

    if(level == 0) {
        lua_getglobal(this->luaState, var.c_str());
    }
    else {
        lua_getfield(this->luaState, -1, var.c_str());
    }

    if(lua_isnil(luaState, -1)) {
        printError(variableName, var + " is not defined");
        return false;
    }

    return true;
}

// Generic get
template<typename T>
T lua_get(const string& variableName_) {
    return 0;
}
