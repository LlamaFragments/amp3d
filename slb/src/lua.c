/*
 inspired by one.c -- Lua core, libraries, and interpreter in a single file

    SLB - Simple Lua Binder
    Copyright (C) 2007-2011 Jose L. Hidalgo Vali�o (PpluX)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
  Jose L. Hidalgo (www.pplux.com)
  pplux@pplux.com
*/

#define MAKE_LIB 1
#define LUA_LIB   1
#define LUA_CORE  1
#define lobject_c
#include "lua/luaconf.h"

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
  #define _CRT_SECURE_NO_WARNINGS 1
#endif


/* Headers sorted by dependency */
#include "lua/lua.h"
#include "lua/llimits.h"
#include "lua/lobject.h"
#include "lua/ltm.h"
#include "lua/lualib.h"
#include "lua/lmem.h"
#include "lua/lzio.h"
#include "lua/lparser.h"
#include "lua/lstate.h"
#include "lua/lgc.h"
#include "lua/lstring.h"
#include "lua/ldebug.h"
#include "lua/llex.h"
#include "lua/lopcodes.h"
#include "lua/lcode.h"
#include "lua/ldo.h"
#include "lua/ltable.h"
#include "lua/lapi.h"
#include "lua/lfunc.h"
#include "lua/lvm.h"
#include "lua/lundump.h"
#include "lua/lauxlib.h"
#include "lua/lctype.h"



/* core -- used by all */
#undef LUA_CORE
#include "lua/lapi.c"
#include "lua/lcode.c"
#include "lua/ldebug.c"
#include "lua/ldo.c"
#include "lua/ldump.c"
#include "lua/lfunc.c"
#include "lua/lgc.c"
#include "lua/llex.c"
#include "lua/lmem.c"
#include "lua/lobject.c"
#include "lua/lopcodes.c"
#include "lua/lparser.c"
#include "lua/lstate.c"
#include "lua/lstring.c"


#include "lua/ltm.c"
#include "lua/lundump.c"
#include "lua/lctype.c"
#include "lua/lvm.c"
#include "lua/lzio.c"

//---------------------------------------------------------------------------
// Simulate limits.h for ltable:
//   - See llimits.h (line 272)
#ifndef luai_hashnum
  #include <float.h>
  #include <math.h>
  #define luai_hashnum(i,n) { int e;  \
    n = frexp(n, &e) * (lua_Number)(INT_MAX - DBL_MAX_EXP);  \
    lua_number2int(i, n); i += e; }
#endif

#include "lua/ltable.c"
//---------------------------------------------------------------------------

/* auxiliary library -- used by all */
#undef LUA_LIB
#include "lua/lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "lua/lbaselib.c"
#include "lua/lbitlib.c"
#include "lua/lcorolib.c"
#include "lua/ldblib.c"
#include "lua/liolib.c"
#include "lua/lmathlib.c"
#include "lua/loadlib.c"
#include "lua/loslib.c"
#include "lua/lstrlib.c"
#include "lua/ltablib.c"
#include "lua/linit.c"
#endif
