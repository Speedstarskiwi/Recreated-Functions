/* inline function remastered for the luau compiler and serializers */
/* please read each comment for updating otherwise the function wont work! */

/* defines */
extern const char* const luaT_typenames_fake[];
const int R_LUA_TNONE = -1;

const char* __fastcall r_lua_typenames(std::uintptr_t rL, int type)
{
    const char* result = "no value";
    if (type != R_LUA_TNONE)
        return (const char*)*((DWORD*)&luaT_typenames_fake + type);
    return result;
}

extern const void* r_lua_topointer(uintptr_t rL, int idx) { /* probably gonna need modded types */

	const auto o = r_lua_index2addr(rL, idx);
	switch (ttype(o)) {
	case LUA_TTABLE:
		return hvalue(o);
	case LUA_TFUNCTION:
		return clvalue(o);
	case LUA_TTHREAD:
		return thvalue(o);
	case LUA_TUSERDATA:
	case LUA_TLIGHTUSERDATA:
		return r_lua_touserdata(rL, idx);
	default: return NULL;
	}
}

char* __fastcall r_lua_pseudo2addr(DWORD* rL, int index) /* scan the pattern below to update this function */
{
    /* 81 FA ?? ?? ?? ?? 74 ?? 81 FA ?? ?? ?? ?? 74 ?? 8B 41 1C */
    int type1;
    int v4;
    DWORD* v5;
    char* v6;
    int v7;
    DWORD* v8;
    char* v9;
    char* byte_2609B68;

    switch (index)
    {
    case -10002:
        v8 = rL + 6;
        v9 = (char*)v8 - *v8;
        *((DWORD*)v9 + 384) = rL[14];
        *((DWORD*)v9 + 387) = 7;
        return (char*)v8 - *v8 + 1536;

    case -10001:
        v4 = rL[7];
        v5 = rL + 6;
        v6 = (char*)v5 - *v5;
        if (v4 == rL[9])
            v7 = rL[14];
        else
            v7 = *(DWORD*)(**(DWORD**)v4 + 12);
        *((DWORD*)v6 + 384) = v7;
        *((DWORD*)v6 + 387) = 7;
        return (char*)v5 - *v5 + 1536;

    case -10000:
        return (char*)rL - rL[6] + 1576;

    default:
        type1 = **(DWORD**)rL[7];
        if (-10002 - index > *(unsigned __int8*)(type1 + 4))
            return byte_2609B68;
        else
            return (char*)(type1 + 16 * (-10002 - index + 1));
    }
}

