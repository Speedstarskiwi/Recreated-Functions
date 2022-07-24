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

int __thiscall unknownshit(int *this, unsigned int *a2) { int v2; int v3; unsigned int v5;unsigned int v6; int v7;unsigned int v8;  DWORD *v9; unsigned int v10; int v11; v2 = this[1]; v3 = *this; v11 = *this; if ( *this == v2 ) return 0; v5 = *a2; v12 = this[4]; if ( v5 == v12 ) { LABEL_8: v9 = 0; } else { v6 = ((v2 - v3) >> 3) - 1; v7 = v6 & (v5 + (v5 >> 3)); v8 = 0; while ( 1 ) { v9 = (_DWORD *)(v3 + 8 * v7); if ( *v9 == v5 ) break; if ( *v9 != v12 ) { v3 = v11; v10 = v8 + v7 + 1; ++v8; v7 = v6 & v10; if ( v8 <= v6 ) continue; } goto LABEL_8; } } return v9 != 0 ? (unsigned int)(v9 + 1) : 0; }

int __fastcall r_lua_isvalidmember(int a1, const char* a2) /* custom function that checks if valid member i suggest you replace this whole function and scan the AOB below */
{
        int dword_3B42A38[605]
	int v4;
	int v5;
	const char* v6;
	int(__cdecl * *v7)(int);
	int v9;

	v4 = *(_DWORD*)(a1 + 68);
	if (!v4 || (v5 = *(__int16*)(v4 + 4), v6 = (const char*)(v4 + 20), v4 == -20))
		std::cout << "Wrong arguments performed" << std::endl;
	if (v5 < 0 || (v9 = dword_3B42A38[v5], (v7 = (int(__cdecl**)(int))unknownshit(&v9)) == 0))
		std::cout << v6 << " is not a valid member of " << a2 << std::endl;
	return (*v7)(a1);
	/* 55 8B EC 83 E4 ?? 51 53 56 57 8B F9 8B F2 8B 47 44 */
}
