/* maya
 * Copyright (c) 2012-2020 Joshua Scoggins
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

// platform.h - detects the operating system you are currently on if possible
// (otherwise it sets a generic target)

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#if defined(__linux__)
#if (defined(__ANDROID__) || defined(__android__))
#define PLATFORM_ANDROID
#else
#define PLATFORM_LINUX
#endif
#elif defined(__APPLE__)
#include "TargetConditionals.h"
#if TARGET_OS_MAC
#define PLATFORM_OSX
#elif TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#define PLATFORM_IOS
#else
#define PLATFORM_APPLE_UNKNOWN
#endif
#elif defined(__FreeBSD__)
#define PLATFORM_FREEBSD
#elif defined(__OpenBSD__)
#define PLATFORM_OPENBSD
#elif defined(__NetBSD__)
#define PLATFORM_NETBSD
#elif defined(__DragonFlyBSD__)
#define PLATFORM_DRAGONFLYBSD
#elif defined(_WIN32) || defined(_WIN64)
#define PLATFORM_NT
#elif defined(ARDUINO)
#define PLATFORM_ARDUINO
#else
#warning "Couldn't identify target platform, enabling generic"
#define PLATFORM_GENERIC
#endif

#endif // end __PLATFORM_H__
