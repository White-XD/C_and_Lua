#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "utils.h"


int main (void) {
    // initialize Lua interpreter
    lua_State *L = luaL_newstate();
    // load Lua base libraries (print / math / etc)
    luaL_openlibs(L);

    ////////////////////////////////////////////
    // We can use Lua here !
    // Need access to the LuaState * variable L
    /////////////////////////////////////////////
    if(!luaL_dofile(L, "lua_func.lua")){
    // if(!luaL_loadfile(L, "lua_func.lua")){
        printf("luaL_dofile() success.\n");
    }else{
        printf("luaL_dofile() failed.\n");
        return 0;
    }

    // Push the fib function on the top of the lua stack
    lua_getglobal(L, "minus");

    // Push the argument (the number 13) on the stack 
    lua_pushnumber(L, 13);
    lua_pushnumber(L, 10);

    // call the function with 1 argument, returning a single result.  Note that the function actually
    // returns 2 results -- we just want one of them.  The second result will *not* be pushed on the
    // lua stack, so we don't need to clean up after it
    lua_call(L, 2, 1);

    // Get the result from the lua stack
    int result = (int)lua_tointeger(L, -1);

    printf("result: %d\n",result);
    // Clean up.  If we don't do this last step, we'll leak stack memory.
    lua_pop(L, 1);
    
    show_lua_stack_situation(L);
    // Cleanup:  Deallocate all space assocatated with the lua state */
    lua_close(L);
    return 0; 
}
