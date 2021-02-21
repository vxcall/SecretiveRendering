#pragma once

#define DEBUG

#ifdef DEBUG
#define LOGHEX(name, val) std::cout << name << ": " << std::hex << val << std::endl;
#define ALLOCCONSOLE()\
{\
    AllocConsole();\
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);\
}
#define FREECONSOLE()\
{\
    fclose(stdout);\
    FreeConsole();\
}
#else
#define LOGHEX(name, val)
#define ALLOCCONSOLE()
#define FREECONSOLE()
#endif