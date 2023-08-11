#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void show_lua_stack_situation(lua_State *L){
    int top = lua_gettop(L);
    printf("the current stack top is: %d\n", top);
    
    for (int i = 1; i <= top; i++) { // loop from bottom to top
        int t = lua_type(L, i); // get the type of the element
        switch (t) {
        case LUA_TSTRING: // strings
            printf("%s\n", lua_tostring(L, i)); // print the string value
            break;
        case LUA_TBOOLEAN: // booleans
            printf(lua_toboolean(L, i) ? "true\n" : "false\n"); // print true or false
            break;
        case LUA_TNUMBER: // numbers
            printf("%g\n", lua_tonumber(L, i)); // print the number value
            break;
        default: // other types
            printf("%s\n", lua_typename(L, t)); // print the type name
            break;
        }
    }
}