#include <stdio.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "utils.h"

int c_add(lua_State *L)
{
   // Step 1:  extract the parameters from the lua stack:
   double n1 = lua_tonumber(L,1);
   double n2 = lua_tonumber(L,2);

   //  Step 2:  Do the actual calculation.  Normally, this will be more interesting than a single sum!
    double sum = n1 + n2;

   // Step 3:  Push the result on the lua stack. 
    lua_pushnumber(L,sum);

   // Return the number of arguments we pushed onto the stack (that is, the number of return values this
   // function has
    return 1;
}

int c_average(lua_State *L)
{
    // Get the number of parameters
    int n = lua_gettop(L);

    double sum = 0;
    int i;

    // loop through each argument, adding them up
    for (i = 1; i <= n; i++)
    {
        sum += lua_tonumber(L, i);
    }

    // push the average on the lua stack
    lua_pushnumber(L, sum / n);

    // push the sum on the lua stack
    lua_pushnumber(L, sum);

    // return the number of results we pushed on the stack
    return 2;
}

static void register_c_funcs (lua_State *L) {
    lua_register(L, "c_add", c_add); // create a global named "c_sum"
    lua_register(L, "c_average", c_average); // create a global named "c_sum"
}

static void call_c_func (lua_State *L) {
    luaL_dofile(L, "call_c.lua");

    show_lua_stack_situation(L);

    lua_getglobal(L, "call_c"); // get the global "c_sum"

    lua_pushnumber(L, 3); // push the first argument
    lua_pushnumber(L, 4); // push the second argument

    lua_call(L, 2, 1); // call c_sum with 2 arguments and 1 result

    double z = lua_tonumber(L, -1); // get the result
    lua_pop(L, 1); // pop the result

    printf("The sum is %f.\n", z); // print the result
}

int main(){
    lua_State *L = luaL_newstate(); // create a Lua state
    luaL_openlibs(L); // open the standard libraries
    register_c_funcs(L); // register the c_sum function
    call_c_func(L); // call the c_sum function
    lua_close(L); // close the Lua state

    return 0;
}
