/*
 * Copyright (c) 2016 Joshua Scoggins
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgement in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

// os_shim.h - a separate header to denote target platform for CLIPS in such a
// way to make updates to the code base easy
//
#ifndef __OS_SHIM_H__
#define __OS_SHIM_H__
#include "Platform.h"

#if defined(PLATFORM_LINUX)
#define LINUX 1
#elif defined(PLATFORM_OSX) || defined(PLATFORM_IOS) || defined(PLATFORM_APPLE_UNKNOWN)
#define DARWIN 1
#elif defined(PLATFORM_FREEBSD) || defined(PLATFORM_OPENBSD) || defined(PLATFORM_NETBSD) || defined(PLATFORM_DRAGONFLYBSD)
#define UNIX_V 1
#elif defined(PLATFORM_NT)
#define WIN_MVC 1
#elif defined(PLATFORM_ARDUINO)
#define GENERIC 1
#else

#endif

#endif // end __OS_SHIM_H__
