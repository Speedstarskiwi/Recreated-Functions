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
