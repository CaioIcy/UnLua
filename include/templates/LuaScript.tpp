// LuaScript::lua_get

template <> 
inline bool LuaScript::lua_get<bool>(const string& variableName_) {
	return (bool)lua_toboolean(luaState, -1);
}

template <> 
inline double LuaScript::lua_get<double>(const string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		printError(variableName_, "Not a number");
	}
	return (double)lua_tonumber(luaState, -1);
}

template <>
inline int LuaScript::lua_get<int>(const string& variableName_) {
	if(!lua_isnumber(luaState, -1)) {
		printError(variableName_, "Not a number");
	}
	return (int)lua_tonumber(luaState, -1);
}

template <>
inline string LuaScript::lua_get<string>(const string& variableName_) {
	string s = "null";
	if(lua_isstring(luaState, -1)) {
		s = string(lua_tostring(luaState, -1));
	} else {
		printError(variableName_, "Not a string");
	}
	return s;
}

// LuaScript::lua_getdefault

template<>
inline string LuaScript::lua_getdefault<string>() {
	return "null";
}
