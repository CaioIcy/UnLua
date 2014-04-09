#ifndef INCLUDE_LUASCRIPT_H
#define INCLUDE_LUASCRIPT_H

#include "LuaCpp.h"

#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::endl;
using std::cout;

class LuaScript {

	public:
		LuaScript(const string& filename_);
		virtual ~LuaScript();
		
		void printError(const string& variableName_, const string& reason_);
		vector<int> getIntVector(const string& name_);
		vector<string> getTableKeys(const string& name_);
		bool lua_gettostack(const string& variableName_);

		inline void clean(){
		    int n = lua_gettop(this->luaState);
		    lua_pop(this->luaState, n);
		}

		template<typename T>
		T get(const std::string& variableName) {
		    if(!luaState) {
		        printError(variableName, "Script is not loaded");
		        return lua_getdefault<T>();
		    }

		    T result;
		    if(lua_gettostack(variableName)) { // variable succesfully on top of stack
		        result = lua_get<T>(variableName);  
		    }
		    else {
		        result = lua_getdefault<T>();
		    }


		    clean();
		    return result;
		}

		// Generic get
		template<typename T>
		T lua_get(const string& variableName_);

		template<typename T>
		T lua_getdefault() {
			return 0;
		}

	private:
		lua_State* luaState;
		int level;

};


// Template definitions.
#include "templates/LuaScript.tpp"

#endif //INCLUDE_LUASCRIPT_H
