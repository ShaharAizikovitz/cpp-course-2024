// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// TODO: reference additional headers your program requires here
#pragma message("Compiling precompiled headers.\n")
// most specialised first
#include "Time_Date.h"
#include "Date_Only.h"
#include "Time_Only.h"
#include "Bitfield.h"
#include "Range_Check.h"
#include "Sum_Operators.h"

#include <utility>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <type_traits>
#include <iostream>
#include <cstddef>
#include <stdexcept>
//#include <shared_mutex>
#include <string>
#include <memory>
#include <thread>
#include <exception>
#include <ostream>
