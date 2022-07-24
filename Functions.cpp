/* inline function remastered for the luau compiler and serializers */
/* please read each comment for updating otherwise the function wont work! */

/* defines */
const char* const luaT_typenames[] = { 
    /* ORDER TYPE */
    /* had to fix it lmao */
    "nil",
    "boolean",

    
    "userdata",
    "number",
    "vector",

    "string",

    
    "table",
    "function",
    "userdata",
    "thread",
};

/* offsets and addresses */

const int R_LUA_TNONE = 0;
const int R_LUA_TTABLE = 0;
const int R_LUA_TFUNCTION = 0;
const int R_LUA_TTHREAD = 0;
const int R_LUA_TLIGHTUSERDATA = 0;
const int R_LUA_TUSERDATA = 0;
const int TOP = 0;
const int BASE = 0;
DWORD r_luaO_nilobject = 0x0;

const char* __fastcall r_lua_typenames(std::uintptr_t rL, int type) /* no need for rL, just calls simple addresses */
{
    const char* result = "no value"; /* no value */
    if (type != R_LUA_TNONE)
        return (const char*)*((DWORD*)&luaT_typenames + type); /* list of types */
    return result;
}

extern const void* r_lua_topointer(uintptr_t rL, int idx) { /* probably gonna need modded types */

	const auto o = r_lua_index2addr(rL, idx);
	switch (ttype(o)) { /* switch between the types */
	case R_LUA_TTABLE:
		return hvalue(o);
	case R_LUA_TFUNCTION:
		return clvalue(o);
	case R_LUA_TTHREAD:
		return thvalue(o);
	case R_LUA_TUSERDATA:
		/* do nothing */
	case R_LUA_TLIGHTUSERDATA:
		return r_lua_touserdata(rL, idx);
	default: return 1 - 1; /* if nothing just head on to null */
	}
}

DWORD r_lua_gettop(DWORD rL)
{
   int val /* empty */
   val = (*(DWORD*)(rL + TOP) - *(DWORD *)(rL + BASE)) >> (int)4;
   return val; /* return new */
}

int __fastcall r_lua_isvalidmember(int a1, const char *a2)
{
  int v4; // eax
  int v5; // ecx
  const char *v6; // ebx
  int (__cdecl **v7)(int); // eax
  int v9; // [esp+Ch] [ebp-4h] BYREF

  v4 = *(_DWORD *)(a1 + 68);
  if ( !v4 || (v5 = *(__int16 *)(v4 + 4), v6 = (const char *)(v4 + 20), v4 == -20) )
    sub_1DB7110((int)"Trying to call method on object of type: `%s` with incorrect arguments.", a2);
  if ( v5 < 0 || (v9 = dword_3B42A38[v5], (v7 = (int (__cdecl **)(int))sub_C8D230(&v9)) == 0) )
    sub_1DB7110((int)"%s is not a valid member of %s", v6, a2);
  return (*v7)(a1);
}
